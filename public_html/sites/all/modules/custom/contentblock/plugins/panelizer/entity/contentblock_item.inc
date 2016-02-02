<?php
/**
 * @file
 * Definition of the ContentBlock item plugin.
 */

$plugin = array(
  'handler' => 'PanelizerEntityContentBlockItem',
  'entity path' => NULL,
  'hooks' => array(
    'menu' => TRUE,
    'admin_paths' => TRUE,
    'page_alter' => TRUE,
    'permission' => TRUE,
    'panelizer_defaults' => TRUE,
    'form_alter' => TRUE,
  ),
);
