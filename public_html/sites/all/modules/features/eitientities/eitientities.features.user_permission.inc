<?php
/**
 * @file
 * eitientities.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitientities_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'gfs_code entity administer'.
  $permissions['gfs_code entity administer'] = array(
    'name' => 'gfs_code entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_gfs_code',
  );

  // Exported permission: 'gfs_code entity view'.
  $permissions['gfs_code entity view'] = array(
    'name' => 'gfs_code entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_gfs_code',
  );

  // Exported permission: 'indicator entity administer'.
  $permissions['indicator entity administer'] = array(
    'name' => 'indicator entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_indicator',
  );

  // Exported permission: 'indicator entity view'.
  $permissions['indicator entity view'] = array(
    'name' => 'indicator entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_indicator',
  );

  // Exported permission: 'indicator_value entity administer'.
  $permissions['indicator_value entity administer'] = array(
    'name' => 'indicator_value entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_indicator_value',
  );

  // Exported permission: 'indicator_value entity view'.
  $permissions['indicator_value entity view'] = array(
    'name' => 'indicator_value entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_indicator_value',
  );

  // Exported permission: 'revenue_stream entity administer'.
  $permissions['revenue_stream entity administer'] = array(
    'name' => 'revenue_stream entity administer',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity create'.
  $permissions['revenue_stream entity create'] = array(
    'name' => 'revenue_stream entity create',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity delete'.
  $permissions['revenue_stream entity delete'] = array(
    'name' => 'revenue_stream entity delete',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity edit'.
  $permissions['revenue_stream entity edit'] = array(
    'name' => 'revenue_stream entity edit',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity view'.
  $permissions['revenue_stream entity view'] = array(
    'name' => 'revenue_stream entity view',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  return $permissions;
}
