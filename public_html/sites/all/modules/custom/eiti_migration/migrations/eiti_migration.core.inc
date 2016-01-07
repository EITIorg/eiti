<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Migration used to migrate users from the legacy to the new system.
 */
class EITIUsersMigration extends DrupalUser7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('This migration is used to pull all the users from the legacy system to the new one. Preserving their roles.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));
  }


  /**
   * We need to do some work to properly import users.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Fetch the old role and find out what is the correct new role.
    $query = Database::getConnection('default', 'legacy')->select('users_roles', 'ur');
    $query->join('role', 'r', 'ur.rid = r.rid');
    $query->fields('ur', array('rid'));
    $query->fields('r', array('name'));
    $query->condition('uid', $row->uid);
    $result = $query->execute();
    foreach ($result as $role_row) {
      $new_role = user_role_load_by_name($role_row->name);
      $row->roles[] = $new_role->rid;
    }
  }
}

/**
 * Core EITI Node Migration.
 *
 * All Node migrations should extend this instead of DrupalNode7Migration.
 * Here is where we handle Media in the Body, i18n to entity_translation or
 * Node-based translations to Field-based translations, this is also the place
 * where we do our best to handle the poorly migrated data into the legacy system.
 */
abstract class EITINodeMigration extends DrupalNode7Migration {
  /**
   * That's where row preparation magic is done.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $row->bundle = (isset($row->bundle)) ? $row->bundle : $this->sourceType;

    // Second try to fetch the fields.
    // Why? Because d6 -> d7 import was done poorly.
    $this->getSourceValuesSecondTry($row, $row->nid);
  }

  /**
   * Prepare function.
   */
  public function prepare($entity, $row) {
    // Replace the old <img> tags with the new Media JSON.
    if (!empty($entity->body)) {
      MigrateDestinationMedia::rewriteImgTags($entity);
    }

    // Check if it is a translation.
    $this->entityTranslate($entity, $row);
  }

  /**
   * Final complete function.
   */
  public function complete($node, stdClass $row) {
    // We don't care for updating tnids (because: entity_translations).
    $source_ids = $this->getMap()->lookupSourceID(array($row->tnid));
    $source_tnid = (!empty($source_ids)) ? $source_ids['sourceid1'] : FALSE;
    if (empty($row->tnid) || $row->tnid == 0 || ($source_tnid && $source_tnid == $row->nid)) {
      $handler = entity_translation_get_handler('node', $node);

      // Init translations and update the node.
      $handler->initTranslations();
      node_save($node);
    }
  }

  /**
   * This is where we check if the pre-imported entity is actually
   * a translation of another.
   */
  public function entityTranslate($entity, $row) {
    // If this is a translation, then we do all the things related to translations,
    // but we don't *create* the node itself.
    $source_ids = $this->getMap()->lookupSourceID(array($row->tnid));
    $source_tnid = (!empty($source_ids)) ? $source_ids['sourceid1'] : FALSE;

    if (!empty($row->tnid) && $row->tnid != 0 && ($source_tnid && $source_tnid != $row->nid)) {
      $source_nid = $row->tnid;
      $source_node = node_load($source_nid);

      // Special case when we have a Stub.
      if ($source_node->title == 'Stub') {
        $source_node->language = 'en';
        node_save($source_node);
      }
      $handler = entity_translation_get_handler('node', $source_node);
      $handler->loadTranslations();
      $original_language = $handler->getLanguage();

      // We need to get all of the possible translations to create. So we look
      // for any translatable fields.
      $translatable_fields = array();
      foreach (field_info_instances('node', $this->destinationType) as $instance) {
        $field_name = $instance['field_name'];
        $field = field_info_field($field_name);

        if ($field['translatable']) {
          $translatable_fields[] = $field_name;
        }
      }

      // Set the values.
      foreach ($translatable_fields as $translatable_field) {
        if (!empty($source_node->{$translatable_field}) && !empty($entity->{$translatable_field})) {
          $source_node->{$translatable_field} = array_merge($source_node->{$translatable_field}, $entity->{$translatable_field});
        }
        elseif(empty($source_node->{$translatable_field}) && !empty($entity->{$translatable_field})) {
          $source_node->{$translatable_field} = $entity->{$translatable_field};
        }
      }

      if (!isset($source_node->translations->data[$entity->language])) {
        // Add the new translation and store it.
        $handler->setTranslation(array(
          'translate' => 0,
          'status' => 1,
          'language' => $entity->language,
          'source' => $original_language,
          'uid' => (empty($entity->uid)) ? 0 : $entity->uid,
          'changed' => (empty($entity->changed)) ? REQUEST_TIME : $entity->changed,
          'created' => (empty($entity->created)) ? REQUEST_TIME : $entity->created,
        ));
      }
      // Save the source node.
      node_save($source_node);

      // Now cancel the creation of the node.
      throw new MigrateException(t("Translation node encountered (translation of !source_nid [!source_lang]: !source_title). Import dropped: !nid [!language]",
            array(
              '!source_nid' => $source_node->nid,
              '!source_lang' => $source_node->language,
              '!source_title' => $source_node->title,
              '!nid' => $row->nid,
              '!language' => $row->language,
            )), Migration::MESSAGE_NOTICE, MigrateMap::STATUS_IGNORED);
    }
    elseif (!empty($entity->nid)) {
      // In this case, it's an updated stub.
      $old_stub = node_load($entity->nid);
      $entity->translations = $old_stub->translations;
    }
  }

  /**
   * Because the legacy has screwed up table values.
   */
  public function getSourceValuesSecondTry($row, $entity_id) {
    $sourceFieldInfo = $this->version->getSourceFieldInfo();
    foreach ($sourceFieldInfo as $field_name => $field_info) {
      if (empty($row->{$field_name})) {
        // Find the data in field_data_$field_name.
        $table = "field_data_$field_name";
        $result = Database::getConnection('default', $this->arguments['source_connection'])
                  ->select($table, 'f')
                  ->fields('f')
                  ->condition('entity_type', 'node')
                  ->condition('entity_id', $entity_id)
                  ->orderBy('delta')
                  ->execute();
        foreach ($result as $field_row) {
          $i = 0;
          // We assume the first column is the "primary" value of the field, and
          // assign the field name rather than the column name for it.
          foreach ($sourceFieldInfo[$field_name]['columns'] as $display_name => $column_name) {
            if ($i++ == 0) {
              $index = $field_name;
            }
            else {
              $index = $display_name;
            }
            if (isset($row->$index) && !is_array($row->$index)) {
              $row->$index = array($row->$index);
            }
            $row->{$index}[] = $field_row->$column_name;
          }
        }
      }

    }

  }
}

