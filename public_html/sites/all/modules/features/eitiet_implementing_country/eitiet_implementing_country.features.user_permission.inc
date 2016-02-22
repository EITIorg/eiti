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
    'roles' => array(),
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
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer implementing_country normal settings'.
  $permissions['administer panelizer implementing_country normal settings'] = array(
    'name' => 'administer panelizer implementing_country normal settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  return $permissions;
}
