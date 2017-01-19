<?php

/**
 * @file
 * Provides a custom 'Teaser' widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Teaser'),
  'description' => t('Display a teaser block, which contains title, description and link(s), with an optional background.'),
  'render callback' => 'contentwidget__teaser__render',
  'settings form' => 'contentwidget__teaser__settings',
  'defaults' => array(),
);

/**
 * Render callback for the 'Header' predefined widget.
 */
function contentwidget__teaser__render($plugin, $widget_settings, $entity, $langcode) {
  $display_settings = (!empty($widget_settings['display_settings'])) ? $widget_settings['display_settings'] : FALSE;
  $entity_emw = entity_metadata_wrapper('fieldable_panels_pane', $entity);

  // And now prepare the list of links.
  $link_items = array();
  for ($link_count = 0; $link_count < $widget_settings['links']['links_number']; $link_count++) {
    $item_title = $widget_settings['links']['link_' . $link_count]['title_' . $link_count];
    $item_link = $widget_settings['links']['link_' . $link_count]['link_' . $link_count];
    if (empty($item_title) || empty($item_link)) {
      continue;
    }

    $item_options = array(
      'attributes' => array(
        'class' => array(
          'link',
          'ghost-link',
        ),
      ),
      'html' => TRUE,
    );
    $link_items[] = l(t($item_title), $item_link, $item_options);
  }

  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('teaser-layout', drupal_html_class('layout-' . $widget_settings['display_settings']['layout_type']))
    )
  );

  $block['overlay']['teaser'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('teaser-content'),
    ),
  );

  $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $langcode);
  if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
    $featured_image_data = $entity->field_fpp_background_image[$image_field_language][0];

    // Use the featured image as background image.
    $selector_prefix = implode('-', array('fieldable_panels_pane', entity_id('fieldable_panels_pane', $entity)));
    helpertheme_get_background_image_with_overlay($block, $featured_image_data, $selector_prefix);
    $block['overlay']['#attributes']['class'][] = 'clearfix';
    $block['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }

  $title = $entity_emw->title->value();
  $description = $entity_emw->field_fpp_body->value();

  // Only if it's set, we want to show the tag.
  if (!empty($title)) {
    $block['overlay']['teaser']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h2',
      '#value' => $title,
      '#attributes' => array(
        'class' => array('title'),
      ),
    );
  }
  // Only if it's set, we want to show the tag.
  if (!empty($description)) {
    $block['overlay']['teaser']['description'] = array(
      '#type' => 'html_tag',
      '#tag' => 'p',
      '#value' => check_markup($description['value'], $description['format']),
      '#attributes' => array(
        'class' => array('teaser-description'),
      ),
    );
  }

  if (!empty($link_items)) {
    $block['overlay']['links_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('links-wrapper'),
      ),
    );
    $block['overlay']['links_wrapper']['links'] = array(
      '#theme' => 'item_list',
      '#items' => $link_items,
      '#type' => 'ul',
      '#title' => '',
      '#attributes' => array(
        'class' => array('links', 'ghost-links'),
      ),
    );
  }

  if (empty($entity->field_fpp_background_image[$image_field_language][0]) && empty($entity->field_fpp_background_video[$video_field_language])) {
    $block['overlay']['teaser']['#attributes']['class'][] = 'single-fluid-row-wrapper';
    $block['overlay']['links_wrapper']['links']['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }
  else {
//    $block['overlay']['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }

  return $block;
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentwidget__teaser__settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $entity = $form_state['entity'];
  $langcode = $entity->language;
  $links_max = isset($widget_settings['links']['links_number']) ? $widget_settings['links']['links_number'] : 4;

  // Let's add layout-related settings.
  $settings_form['display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $settings_form['display_settings']['layout_type'] = array(
    '#type' => 'select',
    '#title' => t('Layout type'),
    '#description' => t('Which layout would you like to use for this teaser?'),
    '#options' => array(
      'full_centered' => t('Full Width & Links Centered'),
      '2_3_left' => t('2/3 Width from Left & Links at Right'),
      '2_3_right' => t('2/3 Width from Right & Links at Left'),
    ),
    '#default_value' => isset($widget_settings['display_settings']['layout_type']) ? $widget_settings['display_settings']['layout_type'] : 'full_centered',
  );
  $settings_form['display_settings']['opacity'] = array(
    '#type' => 'select',
    '#title' => t('Opacity'),
    '#description' => t('How much opacity would you like to use?'),
    '#options' => drupal_map_assoc(range(0, 100, 10)),
    '#field_suffix' => t('%'),
    '#default_value' => isset($widget_settings['display_settings']['opacity']) ? $widget_settings['display_settings']['opacity'] : '50',
  );

  $settings_form['links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="links-wrapper">',
    '#suffix' => '</div>',
  );

  $settings_form['links']['links_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Links'),
    '#options' => drupal_map_assoc(range(0, 8)),
    '#description' => t('Please specify the number of links you want to use.'),
    '#default_value' => $links_max,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__teaser__settings_ajax',
      'event' => 'change',
      'wrapper' => 'links-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Create links.
  for ($link_count = 0; $link_count < $links_max; $link_count++) {
    $link_url = isset($widget_settings['links']['link_' . $link_count]['link_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['link_' . $link_count] : '';
    $link_title = isset($widget_settings['links']['link_' . $link_count]['title_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['title_' . $link_count] : '';

    $fieldset_name = t('Link #!number:', array('!number' => ($link_count + 1)));
    if (isset($link_title)) {
      $fieldset_name .= ' ' . check_plain($link_title);
    }

    $settings_form['links']['link_' . $link_count] = array(
      '#type' => 'fieldset',
      '#title' => $fieldset_name,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $settings_form['links']['link_' . $link_count]['title_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('Link Title'),
      '#size' => 30,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => $link_title,
      '#required' => TRUE,
    );
    $settings_form['links']['link_' . $link_count]['link_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#suffix' => '</div>',
      '#size' => 50,
      '#default_value' => $link_url,
      '#required' => TRUE,
    );
  }
  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function _contentwidget__teaser__settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['teaser']['links'];
}
