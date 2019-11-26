<?php

/**
 * @file
 * eiti_webforms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eiti_webforms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'administer CAPTCHA settings'.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'administer panelizer node webform defaults'.
  $permissions['administer panelizer node webform defaults'] = array(
    'name' => 'administer panelizer node webform defaults',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer recaptcha'.
  $permissions['administer recaptcha'] = array(
    'name' => 'administer recaptcha',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'recaptcha',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit webform components'.
  $permissions['edit webform components'] = array(
    'name' => 'edit webform components',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'set webform_clear times'.
  $permissions['set webform_clear times'] = array(
    'name' => 'set webform_clear times',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform_clear',
  );

  // Exported permission: 'skip CAPTCHA'.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(),
    'module' => 'captcha',
  );

  // Exported permission: 'view any unpublished webform content'.
  $permissions['view any unpublished webform content'] = array(
    'name' => 'view any unpublished webform content',
    'roles' => array(),
    'module' => 'view_unpublished',
  );

  return $permissions;
}
