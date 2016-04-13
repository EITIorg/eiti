<?php

/**
 * @file
 * Ctools Plugin (content-type aka ctools panel pane).
 *
 * What is the difference between these ctools content_types vs contentwidget (with predefined_widgets):
 *  - You don't need to re-use instances of these widgets, but you can re-use the widget itself.
 *  - You don't need to create instances (and bundles, and fields, and.. etc).
 *  - The clearer UI of the Ctools Dialog Form (we can put them in a separate bucket).
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Map: Full'),
  'single' => TRUE,
  'description' => t('Add a fully interactive map. Initially intended to be used on a separate map page'),
  'category' => t('EITI Maps'),
  'render callback' => 'eiti_ctools_extra_map_full_render',
  'edit form' => 'eiti_ctools_extra_map_full_edit_form',
  'render last' => TRUE,
);

/**
 * Output function for the 'Full Map' content type.
 */
function eiti_ctools_extra_map_full_render($subtype, $conf, $panel_args, $context) {
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
  drupal_add_js($plugin_info['path'] . '/map_full.js');

  // Now build the content.
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'section',
    '#attributes' => array(
      'class' => array(
        'eiti-map-wrapper',
        'full-map-wrapper',
      ),
    )
  );

  // For now, this is hardcoded, we should change it later.
  $map_html_id = drupal_html_id('map_all');
  $content['map-div'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => $map_html_id,
      'class' => array(
        'main-map',
      )
    )
  );

  $widget_js_settings = array(
    'container' => $map_html_id,
    'position' => array(12.897489, -12.761718),
  );
  drupal_add_js(array('eitiMapFull' => $widget_js_settings), 'setting');

  $block->content = $content;

  return $block;
}

/**
 * Returns an edit form for site stats (don't really need for now).
 *
 * @TODO: make configurable stats.
 */
function eiti_ctools_extra_map_full_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}
