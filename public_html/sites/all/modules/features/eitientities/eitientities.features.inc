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

  // Exported image style: ar-thumb.
  $styles['ar-thumb'] = array(
    'label' => 'Article Thumbnail (144px by 144px)',
    'effects' => array(
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 144,
          'height' => 144,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bm-large.
  $styles['bm-large'] = array(
    'label' => 'Bookmark: Large',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 470,
          'height' => 470,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bm-medium.
  $styles['bm-medium'] = array(
    'label' => 'Bookmark: Medium',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 470,
          'height' => 234,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bm-small.
  $styles['bm-small'] = array(
    'label' => 'Bookmark: Small',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 234,
          'height' => 234,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: dc-cover.
  $styles['dc-cover'] = array(
    'label' => 'Document Cover (100px wide)',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 100,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: pr-photo.
  $styles['pr-photo'] = array(
    'label' => 'Person Photo (100px by 100px)',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 100,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
