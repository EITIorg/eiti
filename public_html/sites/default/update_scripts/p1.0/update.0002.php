<?php

// Provide a list of modules to be installed.
$modules = array(
  //'admin',
  'admin_menu',
    //'admin_devel',
    //'admin_menu_toolbar',
    //'admin_views',
  //'adminimal_theme',
  'adminimal_admin_menu',

  'ctools',
    //'bulk_export',
    //'ctools_access_ruleset',
    //'ctools_ajax_sample',
    //'ctools_custom_content',
    //'ctools_plugin_example',
    //'page_manager',
    //'stylizer',
    //'views_content',

  'features',
    'strongarm',

  'libraries',

  'title', // Replaces entity legacy fields with regular fields.

  /*
   * Install some developer modules.
   */
  'diff',
  //'module_filter',

);
_us_module__install($modules);

// Set administration theme.
variable_set('admin_theme', 'adminimal');

// Use administration theme for node edit pages.
variable_set('node_admin_theme', 1);

// Increase the maximum number of messages to keep in the database log.
variable_set('dblog_row_limit', 100000);

// Only allow administrators to register accounts.
variable_set('user_register', USER_REGISTER_ADMINISTRATORS_ONLY);

// Do not allow users to upload pictures on their accounts.
variable_set('user_pictures', 0);

// Delete user picture settings.
db_delete('variable')
  ->condition('name', db_like('user_picture_') . '%', 'LIKE')
  ->execute();

// Automatically replace legacy fields with regular fields for new bundles.
$title_settings = array(
  'auto_attach' => array(
    'filename' => 'filename',
  ),
  'hide_label' => array(
    'entity' => 'entity',
    'page' => 0,
  ),
);
variable_set('title_file', $title_settings);

// Automatically replace legacy fields with regular fields for new bundles.
$title_settings = array(
  'auto_attach' => array(
    'title' => 'title',
  ),
  'hide_label' => array(
    'entity' => 'entity',
    'page' => 0,
  ),
);
variable_set('title_node', $title_settings);

// Automatically replace legacy fields with regular fields for new bundles.
$title_settings = array(
  'auto_attach' => array(
    'name' => 'name',
    'description' => 'description',
  ),
  'hide_label' => array(
    'entity' => 'entity',
    'page' => 0,
  ),
);
variable_set('title_taxonomy_term', $title_settings);

// Set default export path for new features.
variable_set('features_default_export_path', 'sites/all/modules/features');
