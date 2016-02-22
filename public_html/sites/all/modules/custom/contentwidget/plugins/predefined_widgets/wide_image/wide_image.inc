<?php

/**
 * @file
 * Provides a custom Wide Image widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Wide Image (Header)',
  'description' => 'Display a wide image with an overlaid Header, Sub-Header and some links .',
  'render callback' => 'contentblock_wide_image_render',
  'settings form' => 'contentblock_wide_image_settings',
  'entity form alter' => 'contentwidget_wide_image_form_alter',
  'entity group alter' => 'contentwidget_wide_image_group_alter',
  'defaults' => array(),
);

/**
 * Render callback for the 'Wide Image' predefined widget.
 */
function contentblock_wide_image_render($plugin, $widget_settings, $entity, $langcode) {
  $image_url = '';
  $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $langcode);
  if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
    $image_file = (object) $entity->field_fpp_background_image[$image_field_language][0];
    $image_url = file_create_url($image_file->uri);
  }

  $header_small = (!empty($widget_settings['header_small'])) ? $widget_settings['header_small'] : FALSE;
  $header_big = (!empty($widget_settings['header_big'])) ? $widget_settings['header_big'] : FALSE;

  // And now prepare the list of links.
  $link_items = array();
  for ($link_count = 0; $link_count < $widget_settings['links']['links_number']; $link_count++) {
    $item_title = $widget_settings['links']['link_' . $link_count]['title_' . $link_count];
    $item_link = $widget_settings['links']['link_' . $link_count]['link_' . $link_count];
    $item_icon = $widget_settings['links']['link_' . $link_count]['icon_' . $link_count];
    if (empty($item_title) || empty($item_link) || empty($item_icon)) {
      continue;
    }

    // Get the SVG icon markup.
    $svgicon = helpertheme_get_svg_icons($item_icon, array('width' => '2em', 'height' => '2em'));

    $item_options = array(
      'attributes' => array(
        'class' => array(
          'link',
          'link-with-icon',
          drupal_html_class('icon--' . $item_icon),
        ),
      ),
      'html' => TRUE,
    );
    $link_items[] = l(t('!icon @title', array('!icon' => $svgicon, '@title' => $item_title)), $item_link, $item_options);
  }

  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'wide-image-background',
        'clearfix',
      )
    )
  );

  if (!empty($image_url)) {
    $block_style = "background-image: url(${image_url});";
    $block['#attributes']['style'] = $block_style;
  }

  $block['overlay'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'single-fluid-row-wrapper',
        'overlay-wrapper',
      ),
    ),
  );

  // Only if it's set, we want to show the tag.
  if ($header_small) {
    $block['overlay']['header_small'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h2',
      '#value' => $header_small,
      '#attributes' => array(
        'class' => array('title'),
      ),
    );
  }

  // Only if it's set, we want to show the tag.
  if ($header_big) {
    $block['overlay']['header_big'] = array(
      '#type' => 'html_tag',
      '#tag' => 'p',
      '#value' => $header_big,
      '#attributes' => array(
        'class' => array('subtitle'),
      ),
    );
  }

  $block['overlay']['links'] = array(
    '#theme' => 'item_list',
    '#items' => $link_items,
    '#type' => 'ul',
    '#title' => '',
    '#attributes' => array(
      'class' => array('wide-image-links-wrapper'),
    ),
  );

  return $block;
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentblock_wide_image_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  $header_small = isset($widget_settings['header_small']) ? $widget_settings['header_small'] : '';
  $header_big = isset($widget_settings['header_big']) ? $widget_settings['header_big'] : '';
  $links_max = isset($widget_settings['links']['links_number']) ? $widget_settings['links']['links_number'] : 4;

  $settings_form['header_small'] = array(
    '#type' => 'textfield',
    '#title' => t('Small Header'),
    '#description' => t('Please specify the small header text.'),
    '#default_value' => $header_small,
    '#size' => 100,
  );
  $settings_form['header_big'] = array(
    '#type' => 'textfield',
    '#title' => t('Big Header'),
    '#description' => t('Please specify the big header text.'),
    '#default_value' => $header_big,
    '#size' => 100,
  );

  $settings_form['links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links:'),
    '#collapsible' => FALSE,
    '#prefix' => '<div id="links-wrapper">',
    '#suffix' => '</div>',
  );
  $settings_form['links']['links_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Links'),
    '#options' => drupal_map_assoc(range(0, 4)),
    '#description' => t('Please specify the number of links you want to use.'),
    '#default_value' => $links_max,
    '#ajax' => array(
      'callback' => 'contentblock_wide_image_settings_ajax',
      'event' => 'change',
      'wrapper' => 'links-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Create links.
  for ($link_count = 0; $link_count < $links_max; $link_count++) {
    $settings_form['links']['link_' . $link_count] = array(
      '#type' => 'fieldset',
      '#title' => t('Link #!number:', array('!number' => ($link_count + 1))),
      '#collapsible' => FALSE,
    );

    $link_url = isset($widget_settings['links']['link_' . $link_count]['link_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['link_' . $link_count] : '';
    $link_title = isset($widget_settings['links']['link_' . $link_count]['title_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['title_' . $link_count] : '';
    $link_icon = isset($widget_settings['links']['link_' . $link_count]['icon_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['icon_' . $link_count] : '';

    $icons = helpertheme_get_svg_icons();
    $options = array('' => t('No Icon'));
    $options += drupal_map_assoc(array_keys($icons));
    $settings_form['links']['link_' . $link_count]['icon_' . $link_count] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $options,
      '#icons' => $icons,
      '#default_value' => $link_icon,
    );
    $settings_form['links']['link_' . $link_count]['title_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('Link Title'),
      '#size' => 30,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => $link_title,
    );
    $settings_form['links']['link_' . $link_count]['link_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#suffix' => '</div>',
      '#size' => 50,
      '#default_value' => $link_url,
    );
  }
  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function contentblock_wide_image_settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity->language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['wide_image']['links'];
}
