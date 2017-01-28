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
  'title' => t('Timeline (Knightlab)'),
  'description' => t('Insert the embedded timeline widget from the Knightlab.'),
  'category' => t('Widget Library'),
  'edit form' => 'eiti_ctools_extra__timeline__edit_form',
  'icon' => drupal_get_path('module', 'contentwidget') . '/icon-eiti-base.png',
  'render callback' => 'eiti_ctools_extra__timeline__render',
  'single' => TRUE,
  'defaults' => array(
    'source' => '',
    'height' => 650,
    'width' => 100,
    'start_slide' => 0,
    'zoom_level' => 2,
    'show_nav_top' => FALSE,
    'start_at_end' => FALSE,
    'display_wide' => TRUE,
  ),
);


/**
 * Output function for the 'Mailchimp Archive' content type.
 */
function eiti_ctools_extra__timeline__render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Now build the content.
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'archive-wrapper',
      ),
    )
  );
  if ($conf['display_wide'] == FALSE) {
    $content['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }

  $timeline_path_root = 'https://cdn.knightlab.com/libs/timeline3/latest/embed/index.html';
  $timeline_path_params = array();
  $source_raw = !empty($conf['source']) ? $conf['source'] : '';
  $source = _eiti_ctools_extra_get_google_spreadsheet_id($source_raw);
  if (empty($source)) {
    drupal_set_message(t('Please make sure you have a correct Source spreadsheet specified for the timeline widget.'), 'warning');
    return '';
  }
  $timeline_path_params['source'] = $source;

  // The rest of params.
  $rest_params_mapping = array(
    'height' => 'height',
    'zoom_level' => 'initial_zoom',
    'start_at_end' => 'start_at_end',
    'start_slide' => 'start_at_slide',
  );
  foreach ($rest_params_mapping as $drupal_id => $url_id) {
    if (!empty($conf[$drupal_id])) {
      $timeline_path_params[$url_id] = $conf[$drupal_id];
    }
  }
  if (!empty($conf['show_nav_top']) && $conf['show_nav_top'] == TRUE) {
    $timeline_path_params['timenav_position'] = 'top';
  }

  // Assemble everything.
  $timeline_path = $timeline_path_root . '?' . http_build_query($timeline_path_params);
  $content['iframe'] = array(
    '#markup' => format_string("<iframe src='!timeline_path' width='!width' height='!height' webkitallowfullscreen mozallowfullscreen allowfullscreen frameborder='0'></iframe>", array(
      '!timeline_path' => $timeline_path,
      '!width' => $conf['width'] . '%',
      '!height' => $conf['height'],
    )),
  );

  // If there's specified a title, let's
  if (!empty($conf['title'])) {
    $content['text_wrapper'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#weight' => -10,
      '#attributes' => array(
        'class' => array('pane-title-wrapper', 'single-fluid-row-wrapper'),
      )
    );
    $content['text_wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h4',
      '#value' => t($conf['title']),
      '#attributes' => array(
        'class' => array(
          'title',
        ),
      )
    );
  }
  $block->content = $content;
  return $block;
}

/**
 * A settings form for this widget.
 */
function eiti_ctools_extra__timeline__edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['spreadsheet'] = array(
    '#title' => t('Spreadsheet'),
    '#type' => 'textfield',
    '#description' => t('Please paste in your spreadsheet you\'d like to use as the SOURCE for this timeline widget. Here\'s a template: !template.', array(
      '!template' => l(t('Template Link'), 'https://drive.google.com/a/developmentgateway.org/previewtemplate?id=1pHBvXN7nmGkiG8uQSUB82eNlnL8xHu6kydzH_-eguHQ&mode=public#'),
    )),
    '#default_value' => $conf['source'],
  );

  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeline Height'),
    '#description' => t('What should be the height of the widget?'),
    '#default_value' => $conf['height'],
    '#field_suffix' => t('px'),
    '#size' => 6,
  );
  $form['width'] = array(
    '#type' => 'select',
    '#title' => t('Timeline Width'),
    '#description' => t('What should be the width of the widget?'),
    '#options' => drupal_map_assoc(range(0, 100, 10)),
    '#field_suffix' => t('%'),
    '#default_value' => $conf['width'],
  );
  $form['start_slide'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Start Slide'),
    '#description' => t('Which slide should we start with?'),
    '#default_value' => $conf['start_slide'],
    '#size' => 6,
  );
  $form['zoom_level'] = array(
    '#type' => 'select',
    '#title' => t('Default Zoom Level'),
    '#description' => t('Zoom level to use?'),
    '#options' => drupal_map_assoc(range(0, 10)),
    '#default_value' => $conf['zoom_level'],
  );
  $form['start_at_end'] = array(
    '#type' => 'checkbox',
    '#title' => t('Star at the End'),
    '#description' => t('Start at the end?'),
    '#default_value' => $conf['start_at_end'],
  );
  $form['show_nav_top'] = array(
    '#type' => 'checkbox',
    '#title' => t('Navigation on Top'),
    '#description' => t('Want to use the navigation on the TOP?'),
    '#default_value' => $conf['show_nav_top'],
  );

  $form['display_wide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display this widget full width (Wide)'),
    '#description' => t('Want to display this WIDE?'),
    '#default_value' => $conf['display_wide'],
  );

  return $form;
}

/**
 * Submit form callback.
 */
function eiti_ctools_extra__timeline__edit_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
  $form_state['conf']['source'] = $form_state['values']['spreadsheet'];
}
