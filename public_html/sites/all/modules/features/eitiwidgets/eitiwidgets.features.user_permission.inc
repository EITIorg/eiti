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

  // Exported permission: 'administer panelizer fieldable_panels_pane fact_blocks defaults'.
  $permissions['administer panelizer fieldable_panels_pane fact_blocks defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane fact_blocks defaults',
    'roles' => array(),
    'module' => 'panelizer',
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

  // Exported permission: 'administer panelizer fieldable_panels_pane icon_blocks defaults'.
  $permissions['administer panelizer fieldable_panels_pane icon_blocks defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane icon_blocks defaults',
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

  // Exported permission: 'administer panelizer fieldable_panels_pane value_chain defaults'.
  $permissions['administer panelizer fieldable_panels_pane value_chain defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane value_chain defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer fieldable_panels_pane visualization defaults'.
  $permissions['administer panelizer fieldable_panels_pane visualization defaults'] = array(
    'name' => 'administer panelizer fieldable_panels_pane visualization defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'create fieldable countdown'.
  $permissions['create fieldable countdown'] = array(
    'name' => 'create fieldable countdown',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable fact_blocks'.
  $permissions['create fieldable fact_blocks'] = array(
    'name' => 'create fieldable fact_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable featured_articles'.
  $permissions['create fieldable featured_articles'] = array(
    'name' => 'create fieldable featured_articles',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable featured_bookmarks'.
  $permissions['create fieldable featured_bookmarks'] = array(
    'name' => 'create fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable featured_persons'.
  $permissions['create fieldable featured_persons'] = array(
    'name' => 'create fieldable featured_persons',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable featured_publications'.
  $permissions['create fieldable featured_publications'] = array(
    'name' => 'create fieldable featured_publications',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable header'.
  $permissions['create fieldable header'] = array(
    'name' => 'create fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable icon_blocks'.
  $permissions['create fieldable icon_blocks'] = array(
    'name' => 'create fieldable icon_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable persons_grid'.
  $permissions['create fieldable persons_grid'] = array(
    'name' => 'create fieldable persons_grid',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable quote'.
  $permissions['create fieldable quote'] = array(
    'name' => 'create fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable table'.
  $permissions['create fieldable table'] = array(
    'name' => 'create fieldable table',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable tabs_with_widgets'.
  $permissions['create fieldable tabs_with_widgets'] = array(
    'name' => 'create fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable teaser'.
  $permissions['create fieldable teaser'] = array(
    'name' => 'create fieldable teaser',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable text'.
  $permissions['create fieldable text'] = array(
    'name' => 'create fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable value_chain'.
  $permissions['create fieldable value_chain'] = array(
    'name' => 'create fieldable value_chain',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'create fieldable visualization'.
  $permissions['create fieldable visualization'] = array(
    'name' => 'create fieldable visualization',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable countdown'.
  $permissions['delete fieldable countdown'] = array(
    'name' => 'delete fieldable countdown',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable fact_blocks'.
  $permissions['delete fieldable fact_blocks'] = array(
    'name' => 'delete fieldable fact_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable featured_articles'.
  $permissions['delete fieldable featured_articles'] = array(
    'name' => 'delete fieldable featured_articles',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable featured_bookmarks'.
  $permissions['delete fieldable featured_bookmarks'] = array(
    'name' => 'delete fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable featured_persons'.
  $permissions['delete fieldable featured_persons'] = array(
    'name' => 'delete fieldable featured_persons',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable featured_publications'.
  $permissions['delete fieldable featured_publications'] = array(
    'name' => 'delete fieldable featured_publications',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable header'.
  $permissions['delete fieldable header'] = array(
    'name' => 'delete fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable icon_blocks'.
  $permissions['delete fieldable icon_blocks'] = array(
    'name' => 'delete fieldable icon_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable persons_grid'.
  $permissions['delete fieldable persons_grid'] = array(
    'name' => 'delete fieldable persons_grid',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable quote'.
  $permissions['delete fieldable quote'] = array(
    'name' => 'delete fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable table'.
  $permissions['delete fieldable table'] = array(
    'name' => 'delete fieldable table',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable tabs_with_widgets'.
  $permissions['delete fieldable tabs_with_widgets'] = array(
    'name' => 'delete fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable teaser'.
  $permissions['delete fieldable teaser'] = array(
    'name' => 'delete fieldable teaser',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable text'.
  $permissions['delete fieldable text'] = array(
    'name' => 'delete fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable value_chain'.
  $permissions['delete fieldable value_chain'] = array(
    'name' => 'delete fieldable value_chain',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'delete fieldable visualization'.
  $permissions['delete fieldable visualization'] = array(
    'name' => 'delete fieldable visualization',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable countdown'.
  $permissions['edit fieldable countdown'] = array(
    'name' => 'edit fieldable countdown',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable fact_blocks'.
  $permissions['edit fieldable fact_blocks'] = array(
    'name' => 'edit fieldable fact_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable featured_articles'.
  $permissions['edit fieldable featured_articles'] = array(
    'name' => 'edit fieldable featured_articles',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable featured_bookmarks'.
  $permissions['edit fieldable featured_bookmarks'] = array(
    'name' => 'edit fieldable featured_bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable featured_persons'.
  $permissions['edit fieldable featured_persons'] = array(
    'name' => 'edit fieldable featured_persons',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable featured_publications'.
  $permissions['edit fieldable featured_publications'] = array(
    'name' => 'edit fieldable featured_publications',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable header'.
  $permissions['edit fieldable header'] = array(
    'name' => 'edit fieldable header',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable icon_blocks'.
  $permissions['edit fieldable icon_blocks'] = array(
    'name' => 'edit fieldable icon_blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable persons_grid'.
  $permissions['edit fieldable persons_grid'] = array(
    'name' => 'edit fieldable persons_grid',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable quote'.
  $permissions['edit fieldable quote'] = array(
    'name' => 'edit fieldable quote',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable table'.
  $permissions['edit fieldable table'] = array(
    'name' => 'edit fieldable table',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable tabs_with_widgets'.
  $permissions['edit fieldable tabs_with_widgets'] = array(
    'name' => 'edit fieldable tabs_with_widgets',
    'roles' => array(),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable teaser'.
  $permissions['edit fieldable teaser'] = array(
    'name' => 'edit fieldable teaser',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable text'.
  $permissions['edit fieldable text'] = array(
    'name' => 'edit fieldable text',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable value_chain'.
  $permissions['edit fieldable value_chain'] = array(
    'name' => 'edit fieldable value_chain',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'fieldable_panels_panes',
  );

  // Exported permission: 'edit fieldable visualization'.
  $permissions['edit fieldable visualization'] = array(
    'name' => 'edit fieldable visualization',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
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
