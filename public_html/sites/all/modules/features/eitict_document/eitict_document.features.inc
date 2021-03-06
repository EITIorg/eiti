<?php

/**
 * @file
 * eitict_document.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_document_ctools_plugin_api($module = NULL, $api = NULL) {
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
function eitict_document_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function eitict_document_node_info() {
  $items = array(
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Use this for documents and publications (The EITI Standard, Workplans, Factsheets, etc.)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
