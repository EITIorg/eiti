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
    $query = Database::getConnection('default', $this->arguments['source_connection'])->select('users_roles', 'ur');
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

  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->formatMappings = array(
      '1' => 'filtered_html',
      '2' => 'plain_text',
      '3' => 'filtered_html',
      '4' => 'plain_text',
    );
  }

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

    // Take care of the paths.
    $this->migrateRedirects($entity, $row);

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
      $changed_old_value = $node->changed;
      node_save($node);
      $node = $this->fixChangePropertyValue($node, $changed_old_value);

      // Process the old redirects.
      $redirects = $this->fetchLegacyRedirects($row->nid);
      foreach ($redirects as $redirect) {
        $new_redirect_default = array(
          'uid' => $node->uid,
          'language' => $redirect->language,
        );
        $new_redirect = new stdClass();
        redirect_object_prepare($new_redirect, $new_redirect_default);
        $redirect_destination = entity_uri('node', $node);
        $new_redirect->redirect = $redirect_destination['path'];
        $new_redirect->source = $redirect->source;

        // Only save if the redirect does not already exist.
        if (EITIMigrateRedirectEntityHandler::redirectValidate($new_redirect)) {
          redirect_save($new_redirect);
        }
      }
    }
  }

  /**
   * Helper function that returns the terms of a specific vocabulary.
   */
  public function fetchSourceTerm($vid, $tids) {
    $terms = array();
    $query = Database::getConnection('default', $this->arguments['source_connection'])->select('taxonomy_term_data', 'td');
    $query->fields('td');
    $query->condition('vid', $vid);
    $query->condition('tid', $tids, 'IN');
    $result = $query->execute();
    foreach ($result as $term_row) {
      $terms[] = $term_row;
    }
    return $terms;
  }

  /**
   * Migrate the redirects.
   */
  public function migrateRedirects($entity, $row) {
    $source_ids = $this->getMap()->lookupSourceID(array($row->tnid));
    $source_tnid = (!empty($source_ids)) ? $source_ids['sourceid1'] : FALSE;

    // This is translation!
    if (!empty($row->tnid) && $row->tnid != 0 && ($source_tnid && $source_tnid != $row->nid)) {
      $source_nid = $row->tnid;
      $source_node = node_load($source_nid);
      $redirect_destination = entity_uri('node', $source_node);

      // Process the old ones.
      $redirects = $this->fetchLegacyRedirects($row->nid);
      foreach ($redirects as $redirect) {
        $new_redirect_default = array(
          'uid' => $entity->uid,
          'language' => $redirect->language,
        );
        $new_redirect = new stdClass();
        redirect_object_prepare($new_redirect, $new_redirect_default);
        $new_redirect->redirect = $redirect_destination['path'];
        $new_redirect->source = $redirect->source;

        // Only save if the redirect does not already exist.
        if (EITIMigrateRedirectEntityHandler::redirectValidate($new_redirect)) {
          redirect_save($new_redirect);
        }
      }
      // Now we need to add the current path as a redirect.
      $new_redirect_default = array(
        'uid' => $entity->uid,
        'language' => $entity->language,
      );
      $new_redirect = new stdClass();
      redirect_object_prepare($new_redirect, $new_redirect_default);
      $new_redirect->redirect = $redirect_destination['path'];
      $parsed = redirect_parse_url($row->path);
      $new_redirect->source = isset($parsed['path']) ? ltrim($parsed['path'], '/') : '';
      if (!empty($parsed['query'])) {
        $new_redirect->source_options['query'] = $parsed['query'];
      }
      if (EITIMigrateRedirectEntityHandler::redirectValidate($new_redirect)) {
        redirect_save($new_redirect);
      }

      // Special case when we have a Stub.
      if ($source_node->title == 'Stub') {
        $source_node->language = 'en';
        $changed_old_value = $source_node->changed;
        node_save($source_node);
        $source_node = $this->fixChangePropertyValue($source_node, $changed_old_value);
      }
    }
    elseif (!empty($entity->nid)) {
      // In this case, it's an updated stub (source of translation).
      $old_stub = node_load($entity->nid);
      $entity->translations = $old_stub->translations;
    }
  }

  public function fixChangePropertyValue($node, $changed) {
    // Unfortunately, http://drupal.org/node/722688 was not accepted, so fix
    // the changed timestamp
    db_update('node')
      ->fields(array('changed' => $changed))
      ->condition('nid', $node->nid)
      ->execute();
    $node->changed = $changed;
    return $node;
  }

  /**
   * Helper function that fetches legacy redirects via given node nid.
   */
  public function fetchLegacyRedirects($nid) {
    $query = Database::getConnection('default', $this->sourceConnection)
       ->select('redirect', 'r')
       ->fields('r')
       ->condition('r.redirect', 'node/' . $nid);
    $results = $query->execute();
    return $results->fetchAll();
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

    // This is translation!
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
      $this->mergeTranslatableNodeFields($source_node, $entity);

      if (!isset($source_node->translations->data[$entity->language])) {
        // Add the new translation and store it.
        $handler->setTranslation(array(
          'translate' => 0,
          'status' => $entity->status,
          'language' => $entity->language,
          'source' => $original_language,
          'uid' => (empty($entity->uid)) ? 0 : $entity->uid,
          'changed' => (empty($entity->changed)) ? REQUEST_TIME : $entity->changed,
          'created' => (empty($entity->created)) ? REQUEST_TIME : $entity->created,
        ));
      }
      // All statuses are published by default.
      $source_node->status = TRUE;

      // Save the source node.
      field_attach_presave('node', $source_node);
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
      // In this case, it's an updated stub (source of translation).
      $old_stub = node_load($entity->nid);
      $entity->translations = $old_stub->translations;
    }

    // Now we look-up the existing node, and if there IS ONE we merge the fields.
    if (!empty($entity->nid)) {
      $existing_node = node_load($entity->nid, NULL, TRUE);
      $this->mergeTranslatableNodeFields($entity, $existing_node);
    }
  }

  /**
   * Merged translatable fields together.
   *
   * @param $a
   *   First Entity, entity who's values will store both values.
   *
   * @param $b
   *   Second Entity, entities who's values will be copied to $a.
   */
  public function mergeTranslatableNodeFields($a, $b) {
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
      if (!empty($a->{$translatable_field}) && !empty($b->{$translatable_field})) {
        $a->{$translatable_field} = array_merge($a->{$translatable_field}, $b->{$translatable_field});
      }
      elseif(empty($a->{$translatable_field}) && !empty($b->{$translatable_field})) {
        $a->{$translatable_field} = $b->{$translatable_field};
      }
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

