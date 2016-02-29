<?php
/**
 * @file
 * eitientities.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitientities_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function eitientities_image_default_styles() {
  $styles = array();

  // Exported image style: bm-large.
  $styles['bm-large'] = array(
    'label' => 'Bookmark: Large',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 478,
          'height' => 478,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bm-medium.
  $styles['bm-medium'] = array(
    'label' => 'Bookmark: Medium',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 478,
          'height' => 238,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bm-small.
  $styles['bm-small'] = array(
    'label' => 'Bookmark: Small',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 238,
          'height' => 238,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
