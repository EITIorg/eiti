<?php
/**
 * @file
 * eitict_internal.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitict_internal_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create internal content'.
  $permissions['create internal content'] = array(
    'name' => 'create internal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any internal content'.
  $permissions['delete any internal content'] = array(
    'name' => 'delete any internal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own internal content'.
  $permissions['delete own internal content'] = array(
    'name' => 'delete own internal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any internal content'.
  $permissions['edit any internal content'] = array(
    'name' => 'edit any internal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own internal content'.
  $permissions['edit own internal content'] = array(
    'name' => 'edit own internal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
