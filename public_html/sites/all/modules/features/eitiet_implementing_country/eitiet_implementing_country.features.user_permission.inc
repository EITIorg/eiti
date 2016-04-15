<?php
/**
 * @file
 * eitiet_implementing_country.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitiet_implementing_country_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer implementing_country normal content'.
  $permissions['administer panelizer implementing_country normal content'] = array(
    'name' => 'administer panelizer implementing_country normal content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal context'.
  $permissions['administer panelizer implementing_country normal context'] = array(
    'name' => 'administer panelizer implementing_country normal context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal defaults'.
  $permissions['administer panelizer implementing_country normal defaults'] = array(
    'name' => 'administer panelizer implementing_country normal defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal layout'.
  $permissions['administer panelizer implementing_country normal layout'] = array(
    'name' => 'administer panelizer implementing_country normal layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal overview'.
  $permissions['administer panelizer implementing_country normal overview'] = array(
    'name' => 'administer panelizer implementing_country normal overview',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal settings'.
  $permissions['administer panelizer implementing_country normal settings'] = array(
    'name' => 'administer panelizer implementing_country normal settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'delete terms in country_status'.
  $permissions['delete terms in country_status'] = array(
    'name' => 'delete terms in country_status',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in country_status'.
  $permissions['edit terms in country_status'] = array(
    'name' => 'edit terms in country_status',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'implementing_country entity access overview'.
  $permissions['implementing_country entity access overview'] = array(
    'name' => 'implementing_country entity access overview',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'implementing_country entity administer'.
  $permissions['implementing_country entity administer'] = array(
    'name' => 'implementing_country entity administer',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'implementing_country entity create'.
  $permissions['implementing_country entity create'] = array(
    'name' => 'implementing_country entity create',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'implementing_country entity delete'.
  $permissions['implementing_country entity delete'] = array(
    'name' => 'implementing_country entity delete',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'implementing_country entity edit'.
  $permissions['implementing_country entity edit'] = array(
    'name' => 'implementing_country entity edit',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'implementing_country entity view'.
  $permissions['implementing_country entity view'] = array(
    'name' => 'implementing_country entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_implementing_country',
  );

  // Exported permission: 'translate implementing_country entities'.
  $permissions['translate implementing_country entities'] = array(
    'name' => 'translate implementing_country entities',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'entity_translation',
  );

  return $permissions;
}
