<?php
/**
 * @file
 * eitict_progress_report.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_progress_report_ctools_plugin_api($module = NULL, $api = NULL) {
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
function eitict_progress_report_node_info() {
  $items = array(
    'progress_report' => array(
      'name' => t('Progress Report'),
      'base' => 'node_content',
      'description' => t('Use this content-type to create a progress report (custom styled report page).'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
