<?php

/**
 * @file
 * Minimalistic footer to replace the standard footer.
 */

$plugin = array(
  'title' => t('Minimalistic Footer'),
  'description' => t('A standard minimalistic footer (to be used when the blocks are disabled, like in Progress Report pages).'),
  'category' => t('Widget Library'),
  'render callback' => 'eiti_ctools_extra__minimalistic_footer__render',
  'edit form' => 'eiti_ctools_extra__minimalistic_footer__settings_form',
  'admin info' => 'eiti_ctools_extra__minimalistic_footer__admin_info',
  'defaults' => array(
    'title' => '',
    'close' => TRUE,
    'close_dismissible' => TRUE,
    'close_dismissible_group' => '',
    'close_position' => 'top',
    'close_delay' => '0',
    'close_time' => '200',
    'hex_background' => 'f0f0f0',
  ),
);

/**
 * Output function for the 'Minimalistic Footer' content type.
 */
function eiti_ctools_extra__minimalistic_footer__render($subtype, $conf, $panel_args, $context) {
  $block['wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'minimalistic-wrapper',
        'minimalistic-footer',
        'clearfix',
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
  $block['wrapper']['content']['description']['content']['#markup'] = check_markup(t($conf['description']['value']), $conf['description']['format']);

  // References.
  $block['wrapper']['content']['references'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'footer-references'
      ),
    ),
  );
  $block['wrapper']['content']['references']['content']['#markup'] = check_markup(t($conf['references']['value']), $conf['references']['format']);

  // Make the button optional.
  if (!empty($conf['close']) && $conf['close'] == TRUE) {
    $block['wrapper']['content']['toggle_btn']['#markup'] = l('Close', '', array(
      'fragment' => 'close',
      'attributes' => array(
        'class' => array('footer-close-action'),
        'data-animation-delay' => !empty($conf['close_delay']) ? $conf['close_delay'] : '0',
        'data-animation-time' => !empty($conf['close_time']) ? $conf['close_time'] : '200',
        'data-dismissible' => $conf['close_dismissible'],
        'data-group' => !empty($conf['close_dismissible_group']) ? drupal_html_class($conf['close_dismissible_group']) : '',
        'data-target' => (!empty($panel_args[0]) && !empty($conf['pane_id'])) ? $panel_args[0] . '-' . $conf['pane_id'] : '',
      ),
      'external' => TRUE,
    ));
    if ($conf['close_position'] == 'bottom') {
      $block['wrapper']['#attributes']['class'][] = 'close-bottom-position';
    }

    // Inject the group class for group-functionality.
    if (!empty($conf['close_dismissible_group'])) {
      $block['wrapper']['#attributes']['class'][] = 'group-' . drupal_html_class($conf['close_dismissible_group']);
    }

    // Adjust the weights.
    $block['wrapper']['menu_items']['toggle_btn']['#weight'] = '2';

    // Add the cookie library - we have to memorize whether the user has dismissed the footers or not.
    drupal_add_library('system', 'jquery.cookie');
  }

  // Apply the background.
  if (!empty($conf['hex_background'])) {
    $block['wrapper']['#attributes']['style'] = 'background:#' . $conf['hex_background'] . ';';
  }

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

  $form['close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the "Close" button'),
    '#description' => t('If you want to enable the close button, please check this box.'),
    '#default_value' => $conf['close'],
  );

  $form['close_delay'] = array(
    '#title' => t('Closing Delay'),
    '#type' => 'textfield',
    '#description' => t('Please specify how many milliseconds should the delay be.'),
    '#field_suffix' => t(' Milliseconds'),
    '#size' => 6,
    '#default_value' => $conf['close_delay'],
    '#states' => array(
      'visible' => array(
        'input[name="close"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['close_time'] = array(
    '#title' => t('Closing Animation'),
    '#type' => 'textfield',
    '#description' => t('Please specify how many milliseconds should the close action take place? Note: "0" indicates that it should be instant.'),
    '#field_suffix' => t(' Milliseconds'),
    '#size' => 6,
    '#default_value' => $conf['close_time'] ? $conf['close_time'] : '200',
    '#states' => array(
      'visible' => array(
        'input[name="close"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['close_position'] = array(
    '#title' => t('Close Button Position'),
    '#type' => 'select',
    '#description' => t('Position of the close button'),
    '#default_value' => $conf['close_position'] ? $conf['close_position'] : 'top',
    '#options' => array('top' => t('Top'), 'bottom' => t('Bottom')),
    '#states' => array(
      'visible' => array(
        'input[name="close"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['close_dismissible'] = array(
    '#title' => t('Dismissible?'),
    '#type' => 'checkbox',
    '#description' => t('Please specify whether this footer should be dismissible or not.'),
    '#default_value' => $conf['close_dismissible'],
    '#states' => array(
      'visible' => array(
        'input[name="close"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['close_dismissible_group'] = array(
    '#title' => t('Dismissible Group'),
    '#type' => 'textfield',
    '#description' => t('If user dismisses an element which belongs to this group - all group elements get dismissed.'),
    '#default_value' => $conf['close_dismissible_group'],
    '#states' => array(
      'visible' => array(
        'input[name="close_dismissible"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['hex_background'] = array(
    '#title' => t('Background Color'),
    '#type' => 'textfield',
    '#description' => t('Please specify the background color.'),
    '#field_prefix' => '#',
    '#size' => 6,
    '#default_value' => $conf['hex_background'] ? $conf['hex_background'] : 'f0f0f0',
  );

  return $form;
}

function eiti_ctools_extra__minimalistic_footer__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
      $form_state['conf']['pane_id'] = $form_state['pane']->pid;
    }
  }
}

/**
 * Admin callback for the backend.
 */
function eiti_ctools_extra__minimalistic_footer__admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    if (empty($conf['close_dismissible_group'])) {
      $block->title = t('@type Minimalistic Footer Widget', array(
        '@type' => $conf['close_dismissible'] ? t('Dismissible'): t('Standard'),
      ));
    }
    else {
      $block->title = t('@type Minimalistic Footer Widget belonging to "@group" group', array(
        '@type' => $conf['close_dismissible'] ? t('Dismissible'): t('Standard'),
        '@group' => $conf['close_dismissible_group']
      ));
    }
    $block->content = t('Description: @desc', array(
      '@desc' => strip_tags($conf['description']['value'])
    ));
    return $block;
  }
}
