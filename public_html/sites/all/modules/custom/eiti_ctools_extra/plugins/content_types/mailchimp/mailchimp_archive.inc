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
  'title' => t('Mailchimp: Archive'),
  'description' => t('Insert a mailchimp archive.'),
  'category' => t('Widget Library'),
  'edit form' => 'eiti_ctools_extra__mailchimp_archive__edit_form',
  'icon' => drupal_get_path('module', 'contentwidget') . '/icon-eiti-base.png',
  'render callback' => 'eiti_ctools_extra__mailchimp_archive__render',
  'single' => TRUE,
  'defaults' => array(
    'limit' => 10,
    'campaign_id' => '691e61806662528c68908252f',
  ),
);

/**
 * Output function for the 'Mailchimp Archive' content type.
 */
function eiti_ctools_extra__mailchimp_archive__render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Now build the content.
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'archive-wrapper',
        'single-fluid-row-wrapper'
      ),
    )
  );
  $campaign_id = !empty($conf['campaign_id']) ? $conf['campaign_id'] : '691e61806662528c68908252f';
  $script_uri = '//eiti.us5.list-manage.com/generate-js/?u=' . $campaign_id . '&fid=1';
  if (!empty($conf['limit'])) {
    $script_uri .= '&show=' . $conf['limit'];
  }
  $content['text_wrapper'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array('pane-title-wrapper'),
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
  $content['script'] = array(
    '#markup' => format_string('<script src="!script_path" type="text/javascript" language="javascript"></script>', array(
      '!script_path' => $script_uri,
    )),
  );
  $block->content = $content;
  return $block;
}

/**
 * A settings form for this widget.
 */
function eiti_ctools_extra__mailchimp_archive__edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['campaign_id'] = array(
    '#title' => t('Campaign ID'),
    '#type' => 'textfield',
    '#description' => t('Please specify the campaign id. In example here: //eiti.us5.list-manage.com/generate-js/?u=<strong>691e61806662528c68908252f</strong>&fid=1, the ID is <strong>691e61806662528c68908252f</strong>.'),
    '#default_value' => $conf['campaign_id'],
  );

  $form['limit'] = array(
    '#title' => t('How many items to show?'),
    '#type' => 'select',
    '#options' => array(
      '' => t('- Select - '),
      '5' => t('5 Items'),
      '10' => t('10 Items'),
      '15' => t('15 Items'),
      '20' => t('20 Items'),
      '25' => t('25 Items'),
      '50' => t('50 Items'),
    ),
    '#default_value' => $conf['limit'],
  );

  return $form;
}

/**
 * Submit form callback.
 */
function eiti_ctools_extra__mailchimp_archive__edit_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
