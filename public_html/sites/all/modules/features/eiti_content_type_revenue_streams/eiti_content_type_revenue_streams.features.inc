<?php

/**
 * @file
 * eiti_content_type_revenue_streams.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eiti_content_type_revenue_streams_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
