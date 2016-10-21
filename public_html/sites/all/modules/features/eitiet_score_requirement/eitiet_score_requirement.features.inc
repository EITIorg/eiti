<?php
/**
 * @file
 * eitiet_score_requirement.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_score_requirement_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
