<?php
/**
 * @file
 * eitict_bookmark.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_bookmark_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function eitict_bookmark_node_info() {
  $items = array(
    'bookmark' => array(
      'name' => t('Bookmark'),
      'base' => 'node_content',
      'description' => t('Use this content-type to create short and stylized links to internal or external pages.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
