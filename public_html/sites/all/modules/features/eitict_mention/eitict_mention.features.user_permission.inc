<?php
/**
 * @file
 * eitict_mention.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitict_mention_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create mention content'.
  $permissions['create mention content'] = array(
    'name' => 'create mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any mention content'.
  $permissions['delete any mention content'] = array(
    'name' => 'delete any mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own mention content'.
  $permissions['delete own mention content'] = array(
    'name' => 'delete own mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any mention content'.
  $permissions['edit any mention content'] = array(
    'name' => 'edit any mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own mention content'.
  $permissions['edit own mention content'] = array(
    'name' => 'edit own mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
