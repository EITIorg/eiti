<?php

/**
 * @file
 * eitiet_organisation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_organisation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
