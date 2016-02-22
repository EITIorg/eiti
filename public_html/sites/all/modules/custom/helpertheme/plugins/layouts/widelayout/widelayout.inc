<?php

/**
 * @file
 * Custom layout definition.
 */

/**
 * Implements hook_panels_layouts().
 */
$plugin = array(
  'title' => t('WideLayout'),
  'category' => t('Custom Layouts'),
  'icon' => 'icon.png',
  'theme' => 'panels_widelayout',
  // CSS is excluded because of the need to create a single aggregated CSS.
  //'css' => 'style.css',
  'admin css' => '../custom.admin.css',
  'regions' => array(
    'main' => t('Main'),
  ),
);
