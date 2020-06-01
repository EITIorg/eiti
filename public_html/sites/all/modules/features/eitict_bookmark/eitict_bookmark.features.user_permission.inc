<?php

/**
 * @file
 * eitict_bookmark.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitict_bookmark_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create bookmark content'.
  $permissions['create bookmark content'] = array(
    'name' => 'create bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any bookmark content'.
  $permissions['delete any bookmark content'] = array(
    'name' => 'delete any bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own bookmark content'.
  $permissions['delete own bookmark content'] = array(
    'name' => 'delete own bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any bookmark content'.
  $permissions['edit any bookmark content'] = array(
    'name' => 'edit any bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own bookmark content'.
  $permissions['edit own bookmark content'] = array(
    'name' => 'edit own bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
