<?php
/**
 * @file
 * eitict_board_decision.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_board_decision_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function eitict_board_decision_node_info() {
  $items = array(
    'board_decision' => array(
      'name' => t('Board decision'),
      'base' => 'node_content',
      'description' => t('Use this content type to create a board decision entry'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
