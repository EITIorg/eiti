<?php
/**
 * @file
 * eitict_board_decision.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitict_board_decision_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node board_decision content'.
  $permissions['administer panelizer node board_decision content'] = array(
    'name' => 'administer panelizer node board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node board_decision context'.
  $permissions['administer panelizer node board_decision context'] = array(
    'name' => 'administer panelizer node board_decision context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node board_decision defaults'.
  $permissions['administer panelizer node board_decision defaults'] = array(
    'name' => 'administer panelizer node board_decision defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node board_decision layout'.
  $permissions['administer panelizer node board_decision layout'] = array(
    'name' => 'administer panelizer node board_decision layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node board_decision overview'.
  $permissions['administer panelizer node board_decision overview'] = array(
    'name' => 'administer panelizer node board_decision overview',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node board_decision settings'.
  $permissions['administer panelizer node board_decision settings'] = array(
    'name' => 'administer panelizer node board_decision settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'create board_decision content'.
  $permissions['create board_decision content'] = array(
    'name' => 'create board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any board_decision content'.
  $permissions['delete any board_decision content'] = array(
    'name' => 'delete any board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own board_decision content'.
  $permissions['delete own board_decision content'] = array(
    'name' => 'delete own board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any board_decision content'.
  $permissions['edit any board_decision content'] = array(
    'name' => 'edit any board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own board_decision content'.
  $permissions['edit own board_decision content'] = array(
    'name' => 'edit own board_decision content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view any unpublished board_decision content'.
  $permissions['view any unpublished board_decision content'] = array(
    'name' => 'view any unpublished board_decision content',
    'roles' => array(
      'restricted user' => 'restricted user',
      'translation editor' => 'translation editor',
    ),
    'module' => 'view_unpublished',
  );

  return $permissions;
}
