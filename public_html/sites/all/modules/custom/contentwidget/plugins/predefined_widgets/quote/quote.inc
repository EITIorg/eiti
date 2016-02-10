<?php

/**
 * @file
 * Provides a custom Quote widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Quote',
  'description' => 'Wide image with an overlaid quote.',
  'render callback' => 'contentblock_quote_render',
  'settings form' => 'contentblock_quote_settings',
  'entity form alter' => 'contentwidget_quote_form_alter',
  'entity group alter' => 'contentwidget_quote_group_alter',
  'defaults' => array(
    'quote' => array(
      'quote_text' => '',
      'quote_from' => '',
      'quote_is_link' => FALSE,
      'quote_link_url' => '',
    ),
  ),
);

/**
 * Render callback for the 'Quote' predefined widget.
 */
function contentblock_quote_render($plugin, $widget_settings, $entity, $langcode) {
  // Prepare the variables.
  $quote_text = $widget_settings['quote']['quote_text'];
  $quote_from = $widget_settings['quote']['quote_from'];
  $quote_is_link = $widget_settings['quote']['quote_is_link'];
  $quote_link_url = $widget_settings['quote']['quote_link_url'];

  $image_url = '';
  if (!empty($entity->field_cbw_wide_image[LANGUAGE_NONE][0])) {
    $image_file = (object) $entity->field_cbw_wide_image[LANGUAGE_NONE][0];
    $image_url = file_create_url($image_file->uri);
  }

  // And now prepare the list of links.
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('wide-image-wrapper')
    ),
  );

  if (!empty($image_url)) {
    $block['image'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#attributes' => array(
        'class' => array('background-image', 'wide-image'),
        'src' => $image_url,
      ),
    );
  }

  $block['overlay'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('overlay-wrapper'),
    ),
  );

  // If it's not a URL, we simply render the quote in the overlay.
  if ($quote_is_link && !empty($quote_link_url)) {
    // We need a quote that's linkable.
    $quote['quote'] = array(
      '#type' => 'html_tag',
      '#tag' => 'blockquote',
      '#value' => $quote_text,
    );
    if ($quote_from) {
      $quote['quote-from'] = array(
        '#type' => 'html_tag',
        '#tag' => 'em',
        '#attributes' => array(
          'class' => array('quote-from')
        ),
        '#value' => $quote_from,
      );
    }

    $block['overlay']['quote_link'] = array(
      '#type' => 'link',
      '#href' => $quote_link_url,
      '#title' => drupal_render($quote),
      '#options' => array(
        'html' => TRUE,
        'absolute' => TRUE,
        'external' => TRUE,
      )
    );
  }
  else {
    $block['overlay']['quote'] = array(
      '#type' => 'html_tag',
      '#tag' => 'blockquote',
      '#value' => $quote_text,
    );
    // Only if it's set, we want to show the tag.
    if ($quote_from) {
      $block['overlay']['quote-from'] = array(
        '#type' => 'html_tag',
        '#tag' => 'em',
        '#attributes' => array(
          'class' => array('quote-from')
        ),
        '#value' => $quote_from,
      );
    }
  }

  return $block;
}

/**
 * Settings form for the 'Quote' predefined widget.
 */
function contentblock_quote_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  $quote_text = $widget_settings['quote']['quote_text'];
  $quote_from = $widget_settings['quote']['quote_from'];
  $quote_is_link = $widget_settings['quote']['quote_is_link'];
  $quote_link_url = $widget_settings['quote']['quote_link_url'];

  $settings_form['quote'] = array(
    '#type' => 'fieldset',
    '#title' => t('Quote'),
    '#description' => t('Quote configuration goes here.')
  );
  $settings_form['quote']['quote_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Quote'),
    '#description' => t('Quote text.'),
    '#default_value' => $quote_text,
    '#size' => 100,
    '#field_prefix' => '"',
    '#field_suffix' => '"',
  );
  $settings_form['quote']['quote_from'] = array(
    '#type' => 'textfield',
    '#title' => t('Quote Source'),
    '#description' => t('Source of the quote: a website, a person, etc.'),
    '#default_value' => $quote_from,
    '#size' => 100,
  );
  $settings_form['quote']['quote_is_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is the quote a link?'),
    '#description' => t('Please specify whether this quote is a link or not.'),
    '#default_value' => $quote_is_link,
    '#size' => 100,
  );
  $settings_form['quote']['quote_link_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Quote link URL'),
    '#description' => t('If this quote leads somewhere, please specify the <strong>absolute</strong> URL (even if it is a local one).'),
    '#default_value' => $quote_link_url,
    '#states' => array(
      'visible' => array(
        'input[name="field_cbwidget[und][0][settings][quote][quote][quote_is_link]"]' => array('checked' => TRUE),
      ),
    ),
    '#size' => 100,
  );

  return $settings_form;
}

/**
 * We want to alter the form, to add bits of custom validation
 */
function contentwidget_quote_form_alter(&$form, &$form_state) {
  // We need to make sure that this file is included anyway, because validation will trigger an error.
  form_load_include($form_state, 'inc', 'contentwidget', 'plugins/predefined_widgets/quote/quote');
  // Add our custom validation.
  $form['actions']['submit']['#validate'][] = 'contentwidget_featured_quote_form_validate';
}

/**
 * Our small validation.
 */
function contentwidget_featured_quote_form_validate($form, $form_state) {
  if ($form_state['values']['field_cbwidget'][LANGUAGE_NONE][0]['widget'] == 'quote') {
    $widget_settings = !empty($form_state['values']['field_cbwidget'][LANGUAGE_NONE][0]['settings']) ? unserialize($form_state['values']['field_cbwidget'][LANGUAGE_NONE][0]['settings']) : array();

    $quote_text = isset($widget_settings['quote']['quote_text']) ? $widget_settings['quote']['quote_text'] : '';
    if (empty($quote_text)) {
      $msg = t('A quote widgets requires a quote-text.');
      form_set_error('field_cbwidget][und][0][settings][quote][quote][quote_text', $msg);
    }
  }
}

/**
 * Callback for the groups pre-render, allows us to interact with entity groups.
 */
function contentwidget_quote_group_alter(&$element) {
  // Make sure the group is there.
  if (!empty($element['group_wide_image'])) {
    // Make sure that the group shows up only when the widget is "Wide Image".
    $element['group_wide_image']['#id'] = 'group-wide-image-details';
    if (empty($element['group_wide_image']['#states']['visible'])) {
      $element['group_wide_image']['#states'] = array(
        'visible' => array()
      );
    }
    else {
      $element['group_wide_image']['#states']['visible'][] = 'or';
    }
    $element['group_wide_image']['#states']['visible'][] = array('input[name="field_cbwidget[und][0][widget]"]' => array('value' => 'quote'));
  }
}
