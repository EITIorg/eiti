<?php
/**
 * @file
 * eitiet_score_data.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_score_data_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
