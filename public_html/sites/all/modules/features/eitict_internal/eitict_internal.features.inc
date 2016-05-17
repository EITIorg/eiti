<?php
/**
 * @file
 * eitict_internal.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_internal_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function eitict_internal_node_info() {
  $items = array(
    'internal' => array(
      'name' => t('Internal Page'),
      'base' => 'node_content',
      'description' => t('If you want to create a simple internal page, using content access rules to limit the access to specific roles, use this content-type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
