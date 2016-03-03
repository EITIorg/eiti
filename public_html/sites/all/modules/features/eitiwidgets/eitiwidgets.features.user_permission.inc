<?php
/**
 * @file
 * eitiwidgets.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitiwidgets_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access fieldable panels panes master list'.
  $permissions['access fieldable panels panes master list'] = array(
    'name' => 'access fieldable panels panes master list',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'administer fieldable panels panes'.
  $permissions['administer fieldable panels panes'] = array(
    'name' => 'administer fieldable panels panes',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane featured_bookmarks defaults'.
  $permissions['administer panelizer fieldable_panels_pane featured_bookmarks defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane featured_bookmarks defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane header defaults'.
  $permissions['administer panelizer fieldable_panels_pane header defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane header defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane icon_links defaults'.
  $permissions['administer panelizer fieldable_panels_pane icon_links defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane icon_links defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane key_facts defaults'.
  $permissions['administer panelizer fieldable_panels_pane key_facts defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane key_facts defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane quote defaults'.
  $permissions['administer panelizer fieldable_panels_pane quote defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane quote defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane table defaults'.
  $permissions['administer panelizer fieldable_panels_pane table defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane table defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane tabs_with_widgets defaults'.
  $permissions['administer panelizer fieldable_panels_pane tabs_with_widgets defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane tabs_with_widgets defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane text defaults'.
  $permissions['administer panelizer fieldable_panels_pane text defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane text defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane visualization defaults'.
  $permissions['administer panelizer fieldable_panels_pane visualization defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane visualization defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'create fieldable featured_bookmarks'.
  $permissions['create fieldable featured_bookmarks'] = array(
    'name' => 'create fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable header'.
  $permissions['create fieldable header'] = array(
    'name' => 'create fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable icon_links'.
  $permissions['create fieldable icon_links'] = array(
    'name' => 'create fieldable icon_links',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable key_facts'.
  $permissions['create fieldable key_facts'] = array(
    'name' => 'create fieldable key_facts',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable quote'.
  $permissions['create fieldable quote'] = array(
    'name' => 'create fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable table'.
  $permissions['create fieldable table'] = array(
    'name' => 'create fieldable table',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable tabs_with_widgets'.
  $permissions['create fieldable tabs_with_widgets'] = array(
    'name' => 'create fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable text'.
  $permissions['create fieldable text'] = array(
    'name' => 'create fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable visualization'.
  $permissions['create fieldable visualization'] = array(
    'name' => 'create fieldable visualization',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable featured_bookmarks'.
  $permissions['delete fieldable featured_bookmarks'] = array(
    'name' => 'delete fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable header'.
  $permissions['delete fieldable header'] = array(
    'name' => 'delete fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable icon_links'.
  $permissions['delete fieldable icon_links'] = array(
    'name' => 'delete fieldable icon_links',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable key_facts'.
  $permissions['delete fieldable key_facts'] = array(
    'name' => 'delete fieldable key_facts',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable quote'.
  $permissions['delete fieldable quote'] = array(
    'name' => 'delete fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable table'.
  $permissions['delete fieldable table'] = array(
    'name' => 'delete fieldable table',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable tabs_with_widgets'.
  $permissions['delete fieldable tabs_with_widgets'] = array(
    'name' => 'delete fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable text'.
  $permissions['delete fieldable text'] = array(
    'name' => 'delete fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable visualization'.
  $permissions['delete fieldable visualization'] = array(
    'name' => 'delete fieldable visualization',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable featured_bookmarks'.
  $permissions['edit fieldable featured_bookmarks'] = array(
    'name' => 'edit fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable header'.
  $permissions['edit fieldable header'] = array(
    'name' => 'edit fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable icon_links'.
  $permissions['edit fieldable icon_links'] = array(
    'name' => 'edit fieldable icon_links',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable key_facts'.
  $permissions['edit fieldable key_facts'] = array(
    'name' => 'edit fieldable key_facts',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable quote'.
  $permissions['edit fieldable quote'] = array(
    'name' => 'edit fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable table'.
  $permissions['edit fieldable table'] = array(
    'name' => 'edit fieldable table',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable tabs_with_widgets'.
  $permissions['edit fieldable tabs_with_widgets'] = array(
    'name' => 'edit fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable text'.
  $permissions['edit fieldable text'] = array(
    'name' => 'edit fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable visualization'.
  $permissions['edit fieldable visualization'] = array(
    'name' => 'edit fieldable visualization',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'translate fieldable_panels_pane entities'.
  $permissions['translate fieldable_panels_pane entities'] = array(
    'name' => 'translate fieldable_panels_pane entities',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'entity_translation',
  );

  return $permissions;
}
