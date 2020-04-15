<?php

/**
 * @file
 * eitiet_implementing_country.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitiet_implementing_country_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function eitiet_implementing_country_image_default_styles() {
  $styles = array();

  // Exported image style: logo_scaled_226x150.
  $styles['logo_scaled_226x150'] = array(
    'label' => 'Logo: Scaled to 226x150',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 150,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 226,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
