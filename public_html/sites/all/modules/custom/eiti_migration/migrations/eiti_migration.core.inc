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
      self::rewriteImgTags($entity);
      self::rewriteHrefs($entity);
    }

    // Take care of the paths.
    $this->migrateRedirects($entity, $row);

    // Check if it is a translation.
    $this->entityTranslate($entity, $row);
  }

  /**
   * Overridden and rewritten method that rewrites the Img Tags.
   */
  static public function rewriteImgTags($entity, $field = 'body') {
    if (is_array($entity->$field)) {
      migrate_instrument_start('MigrateDestinationMedia rewriteImgTags');
      foreach ($entity->$field as $language => $values) {
        $body = isset($values[0]['value']) ? $values[0]['value'] : '';
        break;
      }
      // Quickly skip any non-candidates.
      if (!stristr($body, '<img')) {
        migrate_instrument_stop('EITINodeMigration rewriteImgTags');
        return;
      }
      // Pass full img tags into the callback.
      $new_body = preg_replace_callback('|<img [^>]*>|i', array('EITINodeMigration', 'replaceOverriddenCallback'),
        $body);
      $entity->{$field}[$language][0]['value'] = $new_body;
      migrate_instrument_stop('EITINodeMigration rewriteImgTags');
    }
  }

  /**
   * Overridden and rewritten method that rewrites the Hrefs.
   */
  static public function rewriteHrefs($entity, $field = 'body') {
    if (is_array($entity->$field)) {
      migrate_instrument_start('MigrateDestinationMedia rewriteHrefs');
      foreach ($entity->$field as $language => $values) {
        $body = isset($values[0]['value']) ? $values[0]['value'] : '';
        break;
      }
      // Quickly skip any non-candidates.
      if (!stristr($body, '<a')) {
        migrate_instrument_stop('EITINodeMigration rewriteHrefs');
        return;
      }
      // Pass full img tags into the callback.
      $new_body = preg_replace_callback('|<a [^>]*>|i', array('EITINodeMigration', 'replaceHrefCallback'),
        $body);
      $entity->{$field}[$language][0]['value'] = $new_body;
      migrate_instrument_stop('EITINodeMigration rewriteHrefs');
    }
  }

  /**
   * Overridden static version of replaceCallback.
   */
  static protected function replaceOverriddenCallback(array $matches) {
    $legacy_domain = variable_get('eiti_migration_legacy_domain', 'eiti.org');
    $src_matches = array();
    // Default to the original <img> tag
    $result = $matches[0];
    // Extract the src parameter
    if (preg_match('|src=[\'"]([^\'"]+)[\'"]|i', $matches[0], $src_matches)) {
      // Replace the scheme and host portions of the referenced URI with the
      // Drupal scheme as it's saved in the file_unmanaged table
      $src = $src_matches[1];
      $fid = db_select('file_managed', 'f')
        ->fields('f', array('fid'))
        ->condition('filename', basename($src))
        ->execute()
        ->fetchField();

      // If there's no FID in our database, well, we'll fetch the image from the web and save it.
      if (!$fid && !empty($src)) {
        $path_info = parse_url($src);
        $full_path = FALSE;
        if (isset($path_info['host']) && ($path_info['host'] == 'eiti.org' || $path_info['host'] == 'www.eiti.org' )) {
          $full_path = 'https://' . $legacy_domain . $path_info['path'];
        }
        elseif (empty($path_info['host'])) {
          $full_path = (substr($path_info['path'], 0, 1) == '/') ? 'https://' . $legacy_domain . $path_info['path'] : 'https://' . $legacy_domain . '/' . $path_info['path'];
        }

        // Now that we know what's the path.
        if ($full_path) {
          $file = system_retrieve_file($full_path, 'public://migrated_images/' . basename($src), TRUE);
          if ($file) {
            $fid = $file->fid;
          }
        }
      }

      // Now replace the files with their media JSON equivalent.
      if ($fid) {
        $image_info = array(
          'type' => 'media',
          'view_mode' => 'wide',
          'fid' => $fid,
          'attributes' => array(
            'alt' => '',
            'title' => '',
            'class' => 'media-image',
            'typeof' => 'foaf:Image',
            'wysiwyg' => 1,
          ),
        );
        // Get the height and width parameters if present
        preg_match('|width=[\'"]([^\'"]+)[\'"]|i', $matches[0], $width);
        preg_match('|height=[\'"]([^\'"]+)[\'"]|i', $matches[0], $height);
        // image width
        if ($width) {
          $image_info['attributes']['width'] = $width[1];
        }
        // image height
        if ($height) {
          $image_info['attributes']['height'] = $height[1];
        }

        $result = '[[' . drupal_json_encode($image_info) . ']]';
      }
    }
    return $result;
  }

  /**
   * A callback function from preg_replace_callback.
   */
  static public function replaceHrefCallback(array $matches) {
    module_load_include('inc', 'pathauto', 'pathauto');

    $legacy_domain = variable_get('eiti_migration_legacy_domain', 'eiti.org');
    $href_matches = array();
    $file = FALSE;

    // Default to the original <a> tag
    $result = $matches[0];
    // Extract the src parameter
    if (preg_match('|href=[\'"]([^\'"]+)[\'"]|i', $matches[0], $href_matches)) {
      // Replace the scheme and host portions of the referenced URI with the
      // Drupal scheme as it's saved in the file_unmanaged table
      $href = $href_matches[1];

      $fid = db_select('file_managed', 'f')
        ->fields('f', array('fid'))
        ->condition('filename', basename($href))
        ->execute()
        ->fetchField();

      // If there's no FID in our database, well, we'll fetch the image from the web and save it.
      if (!empty($href)) {
        if (empty($fid)) {
          $path_info = parse_url($href);
          $full_path = FALSE;
          if (isset($path_info['host']) && ($path_info['host'] == 'eiti.org' || $path_info['host'] == 'www.eiti.org' )) {
            $full_path = 'https://' . $legacy_domain . $path_info['path'];
          }
          elseif (empty($path_info['host']) && !empty($path_info['path'])) {
            $full_path = (substr($path_info['path'], 0, 1) == '/') ? 'https://' . $legacy_domain . $path_info['path'] : 'https://' . $legacy_domain . '/' . $path_info['path'];
          }

          // Now that we know what's the path.
          if ($full_path) {
            $basename = basename($href);
            $info = pathinfo($basename);
            $basename_clean = pathauto_clean_alias($info['filename']);

            // We want specifically paths with extensions (files, duh).
            if (!empty($info['extension'])) {
              $file = system_retrieve_file($full_path, 'public://migrated_files/' . $basename_clean . '.' . $info['extension'], TRUE);

              // Fix it, so all the files are by default documents and NOT reports.
              if ($file->type == 'report') {
                $file->type = 'document';
                $file = file_save($file);
              }
            }
          }
        }

        // Now replace to an absolute path (relative to domain).
        $path_info = parse_url($href);
        $relative_path = $path_info['path'];
        if (isset($path_info['host']) && ($path_info['host'] == $legacy_domain || $path_info['host'] == 'www.' . $legacy_domain )) {
          $result = str_replace($href, $relative_path, $result);
        }

        // Also preserve the old aliases (because in images case, we rewrite to Media FID anyway, here we just need to preserve the alises).
        if ($file) {
          $path_alias['alias'] = variable_get('file_public_path', 'sites/default/files') . '/' . file_uri_target($file->uri);
          $path_alias['source'] = urldecode(ltrim($relative_path, '/'));

          $conditions = array(
            'alias' => $path_alias['alias'],
          );
          $alias_lookup = path_load($conditions);
          if (empty($alias_lookup)) {
            if (strlen($path_alias['alias']) >= 255) {
              $msg = t("File alias cannot be created, alias is too long: !file",
                array(
                  '!file' => $path_alias['alias'],
                )
              );
              $mg = Migration::currentMigration();
              $mg->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
            }
            elseif (strlen($path_alias['source']) >= 255) {
              $msg = t("File alias cannot be created, source is too long: !file",
                array(
                  '!file' => $path_alias['source'],
                )
              );
              $mg = Migration::currentMigration();
              $mg->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
            }
            else {
              path_save($path_alias);
            }
          }
        }
      }
    }
    return $result;
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

  /**
   * Small helper function that changes the 'changed' timestamp.
   */
  public function fixChangePropertyValue($node, $changed) {
    // Unfortunately, http://drupal.org/node/722688 was not accepted, so fix
    // the changed timestamp.
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

/**
 * Class EITIDrupalFileMigration
 *
 * Custom File Migration wrapper class.
 */
class EITIDrupalFileMigration extends DrupalFile7Migration {
  /**
   * Prepare function.
   */
  public function complete($entity, $row) {
    // Take care of the paths.
    $this->migrateRedirects($entity, $row);
  }

  /**
   * Migrate the redirects.
   */
  public function migrateRedirects($entity, $row) {
    $legacy_path = self::getOldPath($row->uri);

    // Now we need to add the current path as a redirect.
    $path_alias = array(
      'language' => isset($entity->language) ? $entity->language : LANGUAGE_NONE,
    );
    $path_alias['alias']= variable_get('file_public_path', 'sites/default/files') . '/' . file_uri_target($entity->uri);
    $path_alias['source'] = $legacy_path;

    $conditions = array(
      'alias' => $path_alias['alias'],
    );
    $alias_lookup = path_load($conditions);
    if (empty($alias_lookup)) {
      path_save($path_alias);
    }
  }

  /**
   * Small function that gets a Legacy Path using an URI.
   */
  static public function getOldPath($uri) {
    list($scheme, $target) = explode('://', $uri, 2);

    $target = trim($target, '\/');
    $path = str_replace('\\', '/', $target);
    return 'files/' . $path;
  }
}


