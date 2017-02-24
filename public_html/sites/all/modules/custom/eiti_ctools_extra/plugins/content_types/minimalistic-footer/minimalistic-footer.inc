<?php

/**
 * @file
 * Minimalistic footer to replace the standard footer.
 */

$plugin = array(
  'title' => t('Minimalistic Footer'),
  'description' => t('A standard minimalistic footer (to be used when the blocks are disabled, like in Progress Report pages).'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__minimalistic_footer__render',
  'edit form' => 'eiti_ctools_extra__minimalistic_footer__settings_form',
  'defaults' => array(
    'title' => '',
  ),
);

/**
 * Output function for the 'Minimalistic Footer' content type.
 */
function eiti_ctools_extra__minimalistic_footer__render($subtype, $conf, $panel_args, $context) {
  global $language;

  $block['wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'minimalistic-wrapper',
        'minimalistic-footer'
      ),
    )
  );
  $block['wrapper']['content'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'single-fluid-row-wrapper',
      )
    )
  );

  // Description.
  $block['wrapper']['content']['description'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'footer-description'
      ),
    ),
  );
  $block['wrapper']['content']['description']['content']['#markup'] = check_markup($conf['description']['value'], $conf['description']['format']);

  // References.
  $block['wrapper']['content']['references'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'footer-references'
      ),
    ),
  );
  $block['wrapper']['content']['references']['content']['#markup'] = check_markup($conf['references']['value'], $conf['references']['format']);

  return (object) array(
    'content' => $block,
  );
}

/**
 * Settings form for the Minimalistic Footer.
 */
function eiti_ctools_extra__minimalistic_footer__settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $cleanup_list = array(
    'context',
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

  $form['description'] = array(
    '#title' => t('Footer Description'),
    '#type' => 'text_format',
    '#description' => t('Minimalistic footer is composed from a description and some additional references. Please specify the description here.'),
    '#default_value' => $conf['description']['value'],
    '#format' => $conf['description']['format'],
  );

  $form['references'] = array(
    '#title' => t('References'),
    '#type' => 'text_format',
    '#description' => t('If you have references towards other sources, specify these here, in a free-form.'),
    '#default_value' => $conf['references']['value'],
    '#format' => $conf['references']['format'],
  );

  return $form;
}

function eiti_ctools_extra__minimalistic_footer__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
