<?php
/**
 * @file
 * eitict_stakeholder.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitict_stakeholder_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create stakeholder content'.
  $permissions['create stakeholder content'] = array(
    'name' => 'create stakeholder content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any stakeholder content'.
  $permissions['delete any stakeholder content'] = array(
    'name' => 'delete any stakeholder content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own stakeholder content'.
  $permissions['delete own stakeholder content'] = array(
    'name' => 'delete own stakeholder content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in stakeholder_types'.
  $permissions['delete terms in stakeholder_types'] = array(
    'name' => 'delete terms in stakeholder_types',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any stakeholder content'.
  $permissions['edit any stakeholder content'] = array(
    'name' => 'edit any stakeholder content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own stakeholder content'.
  $permissions['edit own stakeholder content'] = array(
    'name' => 'edit own stakeholder content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in stakeholder_types'.
  $permissions['edit terms in stakeholder_types'] = array(
    'name' => 'edit terms in stakeholder_types',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
