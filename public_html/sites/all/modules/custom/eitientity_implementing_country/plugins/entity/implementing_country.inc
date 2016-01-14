<?php
/**
 * @file
 * Provides the definition of a panelizer entity plugin.
 */

$plugin = array(
  'handler' => 'ImplementingCountryPanelizerEntity',
  'entity path' => 'implementing_country/%implementing_country',
  'uses page manager' => TRUE,
  'hooks' => array(
    'menu' => TRUE,
    'admin_paths' => TRUE,
    'permission' => TRUE,
    'panelizer_defaults' => TRUE,
    'default_page_manager_handlers' => TRUE,
    'form_alter' => TRUE,
    'page_alter' => FALSE,
    'views_data_alter' => TRUE,
    'views_plugins_alter' => FALSE,
  ),
);
