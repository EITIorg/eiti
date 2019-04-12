<?php

/**
 * @file
 * Board decisions.
 */

$plugin = array(
  'title' => t('Board decisions'),
  'description' => t('Board decisions list.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__board_decisions__render',
  'edit form' => 'eiti_ctools_extra__board_decisions__settings_form',
  'defaults' => array(
    'display' => 'default',
  ),
);

/**
 * Output function for board decisions.
 */
function eiti_ctools_extra__board_decisions__render($subtype, $conf, $panel_args, $context) {
  $block['board_decisions'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'board-decisions',
        'single-fluid-row-wrapper',
      ),
    ),
  );
  $block['board_decisions']['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h2',
    '#value' => t('Board decisions'),
    '#attributes' => array('class' => array('title'), 'id' => drupal_html_id('Board decisions')),
    '#prefix' => '<div class="pane-title-wrapper">',
    '#suffix' => '</div>',
  );
  $display = isset($conf['display']) ? $conf['display'] : 'default';
  $block['board_decisions']['list'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => views_embed_view('board_decisions', $display),
    '#attributes' => array('class' => array('list')),
  );

  return (object) array(
    'content' => $block,
  );
}

/**
 * Settings form for board decisions.
 */
function eiti_ctools_extra__board_decisions__settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $cleanup_list = array(
    'override_title',
    'override_title_text',
    'override_title_heading',
    'override_title_markup',
  );
  foreach ($cleanup_list as $key) {
    if (isset($form[$key])) {
      $form[$key]['#access'] = FALSE;
    }
  }

  $form['display'] = array(
    '#title' => t('Display'),
    '#type' => 'select',
    '#options' => array(
      'default' => t('All published'),
      'validation' => t('Published with validation'),
      'unpublished' => t('All unpublished'),
    ),
    '#default_value' => $conf['display'],
  );

  return $form;
}

function eiti_ctools_extra__board_decisions__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
