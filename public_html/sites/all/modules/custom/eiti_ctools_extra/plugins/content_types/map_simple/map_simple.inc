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
  'title' => t('Map: Simple'),
  'category' => t('Widget Library'),
  'description' => t('Add a simplified interactive map. Initially intended to be used on the homepage.'),
  'edit form' => 'eiti_ctools_extra_map_simple_edit_form',
  'icon' => drupal_get_path('module', 'contentwidget') . '/icon-eiti-base.png',
  'render callback' => 'eiti_ctools_extra_map_simple_render',
  'render last' => TRUE,
  'single' => TRUE,
);

/**
 * Output function for the 'Semi-Interactive Map' content type.
 */
function eiti_ctools_extra_map_simple_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // We need this because we store the JS init file in the plugin folder.
  $plugin_info = ctools_get_plugins('ctools', 'content_types', $subtype);

  // Now our custom EITI Maps.
  $library_maps = eiti_ctools_extra_load_eiti_libraries('eitiMapWidgets', 'minified');
  if (empty($library_maps)) {
    $block->content = array(
      '#markup' => t('Please make sure the <strong>eitiMapWidgets</strong> library exists and has proper permission settings.'),
    );
    return $block;
  }

  // Add our init js.
  drupal_add_js($plugin_info['path'] . '/map_simple.js');

  // Now build the content.
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'section',
    '#attributes' => array(
      'class' => array(
        'eiti-map-wrapper',
        'semi-interactive-map-wrapper',
        'media-resizable-wrapper',
        'simple-map-wrapper',
      ),
    )
  );
  // For now, this is hardcoded, we should change it later.
  $map_html_id = drupal_html_id('map_overview');
  $content['map-div'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => $map_html_id,
      'class' => array(
        'semi-interactive-map',
        'media-resizable-element',
        'overview-map',
      ),
    )
  );
  $widget_js_settings = array(
    'container' => $map_html_id,
    'position' => array(12.897489, -12.761718),
  );
  drupal_add_js(array('eitiMapSimple' => $widget_js_settings), 'setting');

  $block->content = $content;
  return $block;
}

/**
 * Returns an edit form for site stats (don't really need for now).
 *
 * @TODO: make configurable stats.
 */
function eiti_ctools_extra_map_simple_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}
