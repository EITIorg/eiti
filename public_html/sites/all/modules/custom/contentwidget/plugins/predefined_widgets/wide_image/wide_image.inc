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
  'settings alter' => 'contentwidget_wide_image_settings_alter',
  'entity form alter' => 'contentwidget_wide_image_form_alter',
  'entity group alter' => 'contentwidget_wide_image_group_alter',
  'defaults' => array(),
);

/**
 * Render callback for the 'Wide Image' predefined widget.
 */
function contentblock_wide_image_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];

  // Prepare the variables.
  $image_file = (object) $entity->field_cbw_wide_image['und'][0];
  $image_url = file_create_url($image_file->uri);
  $header_small = (!empty($widget_settings['wide_image']['header_small'])) ? $widget_settings['wide_image']['header_small'] : FALSE;
  $header_big = (!empty($widget_settings['wide_image']['header_big'])) ? $widget_settings['wide_image']['header_big'] : FALSE;

  // And now prepare the list of links.
  $link_items = array();
  for ($link_count = 0; $link_count < $widget_settings['wide_image']['links']['links_number']; $link_count++) {
    $link_items[] = theme_link(array(
      'text' => $widget_settings['wide_image']['links']['link_' . $link_count]['title_' . $link_count],
      'path' => $widget_settings['wide_image']['links']['link_' . $link_count]['link_' . $link_count],
      'options' => array(
        'attributes' => array(
          'class' => array('link-with-icon', 'icon', $widget_settings['wide_image']['links']['link_' . $link_count]['icon_' . $link_count])
        ),
        'html' => FALSE,
      )
    ));
  }
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('wide-image-wrapper')
    )
  );
  $block['image'] = array(
    '#type' => 'html_tag',
    '#tag' => 'img',
    '#attributes' => array(
      'class' => array('background-image', 'wide-image'),
      'src' => $image_url
    )
  );
  $block['overlay'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('overlay-wrapper'),
    )
  );
  // Only if it's set, we want to show the tag.
  if ($header_small) {
    $block['overlay']['header_small'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h3',
      '#value' => $header_small,
    );
  }
  // Only if it's set, we want to show the tag.
  if ($header_big) {
    $block['overlay']['header_big'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h1',
      '#value' => $header_big,
    );
  }
  $block['overlay']['links'] = array(
    '#theme' => 'item_list',
    '#items' => $link_items,
    '#type' => 'ul',
    '#title' => '',
    '#attributes' => array('class' => array('wide-image-links-wrapper')),
  );

  return $block;
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentblock_wide_image_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  $header_small = isset($widget_settings['wide_image']['header_small']) ? $widget_settings['wide_image']['header_small'] : '';
  $header_big = isset($widget_settings['wide_image']['header_big']) ? $widget_settings['wide_image']['header_big'] : '';
  $links_max = isset($widget_settings['wide_image']['links']['links_number']) ? $widget_settings['wide_image']['links']['links_number'] : 4;

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

    $link_url = isset($widget_settings['wide_image']['links']['link_' . $link_count]['link_' . $link_count]) ? $widget_settings['wide_image']['links']['link_' . $link_count]['link_' . $link_count] : '';
    $link_title = isset($widget_settings['wide_image']['links']['link_' . $link_count]['title_' . $link_count]) ? $widget_settings['wide_image']['links']['link_' . $link_count]['title_' . $link_count] : '';
    $link_icon = isset($widget_settings['wide_image']['links']['link_' . $link_count]['icon_' . $link_count]) ? $widget_settings['wide_image']['links']['link_' . $link_count]['icon_' . $link_count] : '';

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
  // TODO: maybe we should check the language.
  return $form['field_cbwidget'][LANGUAGE_NONE][0]['settings']['wide_image']['links'];
}

/**
 * Callback for the groups pre-render, allows us to interact with entity groups.
 */
function contentwidget_wide_image_group_alter(&$element) {
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
    $element['group_wide_image']['#states']['visible'][] = array('input[name="field_cbwidget[und][0][widget]"]' => array('value' => 'wide_image'));
  }
}
