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
  'title' => t('Table Of Contents'),
  'category' => t('Widget Library'),
  'description' => t('Add a simplified interactive map. Initially intended to be used on the homepage.'),
  'edit form' => 'eiti_ctools_extra_toc_edit_form',
  'render callback' => 'eiti_ctools_extra_toc_render',
  'render last' => TRUE,
  'single' => TRUE,
);

/**
 * Output function for the 'Table Of Contents' content type.
 */
function eiti_ctools_extra_toc_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // We need this because we store the JS init file in the plugin folder.
  $plugin_info = ctools_get_plugins('ctools', 'content_types', $subtype);

  // Add our init js.
  drupal_add_js($plugin_info['path'] . '/toc.js');

  // Now build the content.
  $wrapper_id = drupal_html_id('eiti-toc-wrapper');
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'section',
    '#attributes' => array(
      'id' => $wrapper_id,
      'class' => array(
        'eiti-toc-wrapper',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );

  $widget_js_settings = array(
    'container' => $wrapper_id,
  );
  drupal_add_js(array('eitiTableOfContents' => $widget_js_settings), 'setting');

  $block->content = $content;
  return $block;
}

/**
 * Returns an edit form for site stats (don't really need for now).
 *
 * @TODO: make configurable stats.
 */
function eiti_ctools_extra_toc_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}
