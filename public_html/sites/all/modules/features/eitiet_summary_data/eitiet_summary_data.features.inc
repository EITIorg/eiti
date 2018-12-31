<?php
/**
 * @file
 * eitiet_summary_data.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_summary_data_ctools_plugin_api($module = NULL, $api = NULL) {
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
function eitiet_summary_data_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
