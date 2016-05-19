<?php
/**
 * @file
 * eitiwidgets.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiwidgets_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "fieldable_panels_panes" && $api == "fieldable_panels_pane_type") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function eitiwidgets_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
