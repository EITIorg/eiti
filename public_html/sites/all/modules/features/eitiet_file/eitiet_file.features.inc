<?php
/**
 * @file
 * eitiet_file.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_file_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
}
