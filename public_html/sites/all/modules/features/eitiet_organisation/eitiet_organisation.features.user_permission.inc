<?php
/**
 * @file
 * eitiet_organisation.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitiet_organisation_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'organisation entity administer'.
  $permissions['organisation entity administer'] = array(
    'name' => 'organisation entity administer',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_organisation',
  );

  // Exported permission: 'organisation entity create'.
  $permissions['organisation entity create'] = array(
    'name' => 'organisation entity create',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_organisation',
  );

  // Exported permission: 'organisation entity delete'.
  $permissions['organisation entity delete'] = array(
    'name' => 'organisation entity delete',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_organisation',
  );

  // Exported permission: 'organisation entity edit'.
  $permissions['organisation entity edit'] = array(
    'name' => 'organisation entity edit',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_organisation',
  );

  // Exported permission: 'organisation entity view'.
  $permissions['organisation entity view'] = array(
    'name' => 'organisation entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_organisation',
  );

  return $permissions;
}
