<?php

/**
 * @file
 * Quick Summary Tool containing the banner, logo and various other information.
 */

$plugin = array(
  'title' => t('Quick Summary Tool'),
  'description' => t('Shows a quick overview of each EITI Report or all the EITI Reports from each country.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__quick_summary_tool__render',
);

/**
 * Output function for the 'Quick Summary Tool' content type.
 */
function eiti_ctools_extra__quick_summary_tool__render($subtype, $conf, $panel_args, $context) {
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'quick-summary-tool--wrapper',
      'class' => array(
        'quick-summary-tool--wrapper',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );

  // Retrieve the QST form.
  $block['form'] = drupal_get_form('eiti_ctools_extra__quick_summary_tool__form');

  return (object) array(
    'content' => $block,
  );
}

function eiti_ctools_extra__quick_summary_tool__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Build the form for the quick_summary_tool plugin.
 * @param $form
 * @param $form_state
 */
function _eiti_ctools_extra__quick_summary_tool__form() {
  return $form;
}
