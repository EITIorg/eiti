<?php

/**
 * @file
 * Migrate support for Redirect module.
 *
 * Original one didn't handle the languages correctly, so we decided to
 * write a custom one.
 *
 * Inspired from MigrateRedirectEntityHandler.
 * @see https://www.drupal.org/node/1116408
 */

class EITIMigrateRedirectEntityHandler extends MigrateDestinationHandler {

  /**
   * Constructor.
   */
  public function __construct() {
    $this->registerTypes(array('entity'));
  }

  /**
   * Overrides fields().
   */
  public function fields() {
    return array('migrate_redirects' => t('Original path(s) to redirect from.'));
  }

  /**
   * Validates a redirect.
   *
   * We need to check if a redirect already exists. Calling redirect_save on an
   * already existing redirect will throw a db error due to duplicate entries.
   *
   * This function is similar to the validate function in the redirect module
   * but the feedback is handled via the Migrate's saveMessage functionality.
   *
   * @return bool
   *   TRUE if the redirect is valid and can be saved.
   */
  static public function redirectValidate($redirect) {
    $redirect = (object) $redirect;

    // Check that there there are no redirect loops.
    $migration = Migration::currentMigration();
    if (url($redirect->source) == url($redirect->redirect)) {
      $migration->saveMessage(t('Redirect to self (!redirect) ignored',
                              array('!redirect' => $redirect->redirect)),
                  MigrationBase::MESSAGE_INFORMATIONAL);
      return FALSE;
    }
    redirect_hash($redirect);
    if ($existing = redirect_load_by_hash($redirect->hash)) {
      if ($redirect->rid != $existing->rid) {
        $migration->saveMessage(t('The source path is already being redirected.'),
          MigrationBase::MESSAGE_INFORMATIONAL);
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Get redirects from entity or row.
   */
  protected function getRedirects($entity, $row) {
    // If there are multiple redirects defined for the entity, they will be in
    // $row. If there is just one, it will be in $entity.
    if (!empty($row->migrate_redirects)) {
      $migrate_redirects = $row->migrate_redirects;
    }
    else {
      $migrate_redirects = isset($entity->migrate_redirects) ? $entity->migrate_redirects : NULL;
    }
    // If it is not an array already, make it one now.
    if ($migrate_redirects && !is_array($migrate_redirects)) {
      $migrate_redirects = array($migrate_redirects);
    }
    return $migrate_redirects;
  }

  /**
   * Overrides complete().
   *
   * @param object $entity
   *   The Drupal entity.
   * @param stdClass $row
   *   The row being migrated.
   */
  public function complete($entity, stdClass $row) {
    $migration = Migration::currentMigration();
    $destination = $migration->getDestination();
    $entity_type = $destination->getEntityType();
    $migrate_redirects = $this->getRedirects($entity, $row);

    // We looked up the destination entity_type in the constructor.
    if (!empty($migrate_redirects) && ($redirect_destination = entity_uri($entity_type, $entity))) {
      foreach ($migrate_redirects as $path) {
        $redirect_defaults = array(
          'status_code' => 301,
        );
        if (isset($entity->uid)) {
          $redirect_defaults['uid'] = $entity->uid;
        }
        $redirect_defaults['language'] = empty($entity->language) ? 'en' : $entity->language;
        $redirect = new stdClass();
        redirect_object_prepare($redirect, $redirect_defaults);
        $redirect->redirect = $redirect_destination['path'];
        $parsed = redirect_parse_url($path);
        $redirect->source = isset($parsed['path']) ? ltrim($parsed['path'], '/') : '';
        if (!empty($parsed['query'])) {
          $redirect->source_options['query'] = $parsed['query'];
        }

        // Only save if the redirect does not already exist.
        if (self::redirectValidate($redirect)) {
          redirect_save($redirect);
        }
      }
    }
  }
}

/**
 * Implements hook_migrate_api().
 */
function redirect_migrate_api() {
  $api = array(
    'api' => 2,
    'destination handlers' => array(
      'MigrateRedirectEntityHandler',
    ),
  );
  return $api;
}
