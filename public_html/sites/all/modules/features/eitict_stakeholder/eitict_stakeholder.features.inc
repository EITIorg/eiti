<?php

/**
 * @file
 * eitict_stakeholder.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_stakeholder_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function eitict_stakeholder_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function eitict_stakeholder_node_info() {
  $items = array(
    'stakeholder' => array(
      'name' => t('Stakeholder'),
      'base' => 'node_content',
      'description' => t('Used for listings of stakeholder countries, companies, organisations, institutional investors, and civil society.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
