<?php
/**
 * @file
 * eitiet_summarydata.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitiet_summarydata_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'summarydata entity access overview'.
  $permissions['summarydata entity access overview'] = array(
    'name' => 'summarydata entity access overview',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  // Exported permission: 'summarydata entity administer'.
  $permissions['summarydata entity administer'] = array(
    'name' => 'summarydata entity administer',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  // Exported permission: 'summarydata entity create'.
  $permissions['summarydata entity create'] = array(
    'name' => 'summarydata entity create',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  // Exported permission: 'summarydata entity delete'.
  $permissions['summarydata entity delete'] = array(
    'name' => 'summarydata entity delete',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  // Exported permission: 'summarydata entity edit'.
  $permissions['summarydata entity edit'] = array(
    'name' => 'summarydata entity edit',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  // Exported permission: 'summarydata entity view'.
  $permissions['summarydata entity view'] = array(
    'name' => 'summarydata entity view',
    'roles' => array(),
    'module' => 'eitientity_summarydata',
  );

  return $permissions;
}
