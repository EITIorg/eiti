<?php

/**
 * @file
 * Provides a custom Icon Link widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Icon Blocks',
  'description' => 'Use this widget to add multiple icon blocks.',
  'render callback' => 'contentwidget_icon_blocks_render',
  'settings form' => 'contentwidget_icon_blocks_settings',
  'defaults' => array(
    'blocks_count' => 1,
  ),
);

/**
 * Render callback for the 'Icon Link' predefined widget.
 */
function contentwidget_icon_blocks_render($plugin, $widget_settings, $entity, $langcode) {
  $blocks_count = $widget_settings['blocks_count'];

  // Iterate through the link icons (formatting already inspired from the prototype).
  $blocks_list = array();
  $delta = NULL;
  for ($delta = 0; $delta < $blocks_count; $delta++) {
    $icon_block = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'icon-block-wrapper',
          'icon-block-wrapper--' . $delta,
          'mobject',
          'clearfix',
        ),
      ),
    );

    // Add the block icon.
    $icon_block['icon_blocks']['icon_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-icon',
          'group-side',
        ),
      ),
    );
    $icon = $widget_settings['blocks'][$delta]['icon'];
    $options = array(
      'height' => '4em',
      'width' => '4em',
    );
    $icon_block['icon_blocks']['icon_wrapper']['icon'] = array(
      '#markup' => helpertheme_get_svg_icon($icon, $options),
    );

    $icon_block['icon_blocks']['text_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-text',
          'group-main',
        ),
      ),
    );

    // Add the block title.
    $icon_block['icon_blocks']['text_wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h4',
      '#value' => t($widget_settings['blocks'][$delta]['title']),
      '#attributes' => array(
        'class' => array(
          'title',
        ),
      )
    );

    // Add the block links.
    if (!empty($widget_settings['blocks'][$delta]['links'])) {
      $block_links_list = array();
      foreach ($widget_settings['blocks'][$delta]['links'] as $link_delta => $link_info) {
        $block_links_list[$link_delta] = l(t($link_info['title']), $link_info['url']);
      }

      $icon_block['icon_blocks']['text_wrapper']['links'] = array(
        '#theme' => 'item_list',
        '#items' => $block_links_list,
        '#attributes' => array('class' => array('icon-block-links')),
      );
    }

    $blocks_list[$delta] = render($icon_block);
  }

  $block['icon_blocks'] = array(
    '#theme' => 'item_list',
    '#items' => $blocks_list,
    '#title' => '',
    '#type' => 'ul',
    '#attributes' => array(
      'class' => array(
        'icon-blocks-wrapper',
        'icon-blocks-wrapper--count-' . $blocks_count,
      ),
    ),
  );

  return $block;
}

/**
 * Settings form for the 'Icon Link' predefined widget.
 */
function contentwidget_icon_blocks_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $blocks_count = isset($widget_settings['blocks_count']) ? $widget_settings['blocks_count'] : '';

  $available_sizes = array('' => t('- Select -'));
  $sizes = drupal_map_assoc(range(1, 9));
  foreach ($sizes as $size) {
    $available_sizes[$size] = format_plural($size, '1 Block', '@count Blocks');
  }

  $wrapper_id = 'icon-blocks-form-elements-wrapper';
  $settings_form['blocks_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of Icon Blocks'),
    '#options' => $available_sizes,
    '#default_value' => $blocks_count,
    '#ajax' => array(
      'callback' => 'contentwidget_icon_blocks_settings_ajax',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  $settings_form['blocks'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $wrapper_id,
    ),
  );


  $triggering_element = empty($form_state['triggering_element']) ? array() : $form_state['triggering_element'];
  $triggering_element_name = empty($triggering_element['#parents']) ? NULL : array_pop($triggering_element['#parents']);
  if ($triggering_element_name == 'blocks_count') {
    $blocks_count = $triggering_element['#value'];
  }
  else {
    $blocks_count = $widget_settings['blocks_count'];
  }

  // Create the forms for the icon links.
  for ($delta = 0; $delta < $blocks_count; $delta++) {
    $block_settings = empty($widget_settings['blocks'][$delta]) ? array() : $widget_settings['blocks'][$delta];
    $settings_form['blocks'][$delta] = _contentwidget_get_icon_block_elements($form_state, $block_settings, $delta);
  }

  $settings_form['#attached']['css'] = array(
    drupal_get_path('module', 'helpergeneric') . '/helpergeneric.admin.css',
  );

  return $settings_form;
}

/**
 * Helper function creating the form elements for an icon block.
 *
 * @see: contentwidget_icon_blocks_settings()
 */
function _contentwidget_get_icon_block_elements(&$form_state, $block_settings, $delta) {
  $triggering_element = empty($form_state['triggering_element']) ? array() : $form_state['triggering_element'];
  $triggering_element_name = NULL;
  if (!empty($triggering_element['#parents'])) {
    $temp_element_name = array_pop($triggering_element['#parents']);
    $temp_element_delta = array_pop($triggering_element['#parents']);

    if ($temp_element_delta == $delta) {
      $triggering_element_name = $temp_element_name;
    }
  }

  // Fetch the re-usable icon options.
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  $elements = array(
    '#type' => 'fieldset',
    '#title' => t('Icon Block #@number:', array('@number' => ($delta + 1))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $elements['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => isset($block_settings['title']) ? $block_settings['title'] : '',
  );

  $elements['icon'] = array(
    '#type' => 'radioicons',
    '#title' => t('Icon'),
    '#options' => $icon_options,
    '#icons' => $icons,
    '#required' => TRUE,
    '#default_value' => isset($block_settings['icon']) ? $block_settings['icon'] : '',
  );

  $available_sizes = array();
  $sizes = drupal_map_assoc(range(1, 9));
  foreach ($sizes as $size) {
    $available_sizes[$size] = format_plural($size, '1 Link', '@count Links');
  }

  if ($triggering_element_name == 'links_count') {
    $links_count = (int) $triggering_element['#value'];
  }
  else {
    $links_count = (int) isset($block_settings['links_count']) ? $block_settings['links_count'] : 1;
  }

  $wrapper_id = 'icon-blocks-' . $delta . '-links-form-elements-wrapper';
  $elements['links_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of Links in Block'),
    '#options' => $available_sizes,
    '#default_value' => $links_count,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'contentwidget_icon_blocks_links_settings_ajax',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  $elements['links'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $wrapper_id,
    ),
  );

  // Create the forms for the icon links.
  for ($delta = 0; $delta < $links_count; $delta++) {
    $link_elements = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'form-item',
          'form-element-inline-wrapper',
        ),
      ),
    );

    $link_title = isset($block_settings['links'][$delta]['title']) ? $block_settings['links'][$delta]['title'] : '';
    $link_elements['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $link_title,
      '#required' => TRUE,
      '#size' => 30,
    );

    $link_url = isset($block_settings['links'][$delta]['url']) ? $block_settings['links'][$delta]['url'] : '';
    $link_elements['url'] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#default_value' => $link_url,
      '#required' => TRUE,
    );

    $elements['links'][$delta] = $link_elements;
  }

  return $elements;
}

/**
 * Ajax callback for the settings form.
 */
function contentwidget_icon_blocks_settings_ajax($form, $form_state) {
  $triggering_element = $form_state['triggering_element'];

  // Go one level up in the form, to the container.
  $element = drupal_array_get_nested_value($form, array_slice($triggering_element['#array_parents'], 0, -1));

  return $element['blocks'];
}

/**
 * Ajax callback for the settings form.
 */
function contentwidget_icon_blocks_links_settings_ajax($form, $form_state) {
  $triggering_element = $form_state['triggering_element'];

  // Go one level up in the form, to the container.
  $element = drupal_array_get_nested_value($form, array_slice($triggering_element['#array_parents'], 0, -1));

  return $element['links'];
}
