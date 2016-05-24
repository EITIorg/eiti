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
  );

  // Retrieve the QST form.
  $block['form'] = drupal_get_form('eiti_ctools_extra__quick_summary_tool__form');

  $block['information_placeholder'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'quick-summary-tool--information-placeholder',
      ),
    ),
  );

  return (object) array(
    'content' => $block,
  );
}
