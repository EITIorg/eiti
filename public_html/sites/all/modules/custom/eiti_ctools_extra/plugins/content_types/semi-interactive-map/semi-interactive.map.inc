<?php

/**
 * @file
 * Ctools Plugin (content-type aka ctools panel pane).
 *
 * What is the difference between these ctools content_types vs contentwidgets (with eitiwidgets):
 *  - You don't need to re-use instances of these widgets, but you can re-use the widget itself.
 *  - You don't need to create instances (and bundles, and fields, and.. etc).
 *  - The clearer UI of the Ctools Dialog Form (we can put them in a separate bucket).
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Semi-Interactive Map'),
  'single' => TRUE,
  'description' => t('Add a semi-interactive map. Initially intended to be used on the homepage.'),
  'category' => t('EITI Maps'),
  'render callback' => 'eiti_ctools_extra_map_semi_interactive_render',
  'edit form' => 'eiti_ctools_extra_map_semi_interactive_edit_form',
  'render last' => TRUE,
);

/**
 * Output function for the 'Semi-Interactive Map' content type.
 */
function eiti_ctools_extra_map_semi_interactive_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = 'test';

  // We need this because we store the JS init file in the plugin folder.
  $plugin_info = ctools_get_plugins('ctools', 'content_types', $subtype);

  // Load the libraries, leaflet first.
  $library_leaflet = libraries_load('leaflet');
  if (empty($library_leaflet)) {
    $block->content = t('Please make sure the <strong>leaflet</strong> library exists and has proper permission settings.');
    return $block;
  }

  // Now our custom EITI Maps.
  $library_maps = libraries_load('eiti-maps');
  if (empty($library_maps)) {
    $block->content = t('Please make sure the <strong>eiti-maps</strong> library exists and has proper permission settings.');
    return $block;
  }

  // Add our init js.
  drupal_add_js($plugin_info['path'] . '/semi-interactive-map.init.js');

  // Now build the content.
  $content = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('semi-interactive-map-wrapper', 'section', 'map-container')
    )
  );
  // For now, this is hardcoded, we should change it later.
  $content['map-div'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => array(drupal_html_id('map1')),
      'style' => array('height:700px;;display:block;margin:auto;')
    )
  );
  $block->content = $content;
  return $block;
}

/**
 * Returns an edit form for site stats (don't really need for now).
 *
 * @TODO: make configurable stats.
 */
function eiti_ctools_extra_map_semi_interactive_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}
