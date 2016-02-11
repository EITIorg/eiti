<?php
/**
 * @file
 * eitiet_summary_data.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitiet_summary_data_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'summary_data entity access overview'.
  $permissions['summary_data entity access overview'] = array(
    'name' => 'summary_data entity access overview',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_summary_data',
  );

  // Exported permission: 'summary_data entity administer'.
  $permissions['summary_data entity administer'] = array(
    'name' => 'summary_data entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_summary_data',
  );

  // Exported permission: 'summary_data entity create'.
  $permissions['summary_data entity create'] = array(
    'name' => 'summary_data entity create',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_summary_data',
  );

  // Exported permission: 'summary_data entity delete'.
  $permissions['summary_data entity delete'] = array(
    'name' => 'summary_data entity delete',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_summary_data',
  );

  // Exported permission: 'summary_data entity edit'.
  $permissions['summary_data entity edit'] = array(
    'name' => 'summary_data entity edit',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_summary_data',
  );

  // Exported permission: 'summary_data entity view'.
  $permissions['summary_data entity view'] = array(
    'name' => 'summary_data entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_summary_data',
  );

  return $permissions;
}
