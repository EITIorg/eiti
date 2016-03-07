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
  'entity form alter' => 'contentwidget_icon_blocks_form_alter',
  'entity group alter' => 'contentwidget_icon_blocks_group_alter',
  'hook_entity_view' => 'contentwidget_icon_blocks_hook_entity_view',
  'hook_fieldable_panels_pane_view' => 'contentwidget_icon_blocks_hook_fieldable_panels_pane_view',
  'defaults' => array(
    'icon_blocks_number' => '',
  ),
);

/**
 * Render callback for the 'Icon Link' predefined widget.
 */
function contentwidget_icon_blocks_render($plugin, $widget_settings, $entity, $langcode) {
  $total_items = $widget_settings['icon_blocks_number'];

  // Iterate through the link icons (formatting already inspired from the prototype).
  $items = array();
  $delta = NULL;
  for ($delta = 0; $delta < $total_items; $delta++) {
    $icon_block = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'icon-block-wrapper',
          'icon-block-wrapper--' . $delta,
          'mobject',
        ),
      ),
    );

    $icon_block['icon_blocks']['icon_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-icon',
          'group-side',
        ),
      ),
    );

    $icon = _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'icon');
    $options = array(
      'height' => '3em',
      'width' => '3em',
    );
    $icon_block['icon_blocks']['icon_wrapper']['icon'] = array(
      '#markup' => helpertheme_get_svg_icon($icon, $options),
    );

    // Now, the rest.
    $icon_block['icon_blocks']['text_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-text',
          'group-main',
        ),
      ),
    );

    // Get the block title.
    $title = _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'title');
    $title_as_link = _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'title_as_link');
    if ($title_as_link == TRUE) {
      $link_options = array(
        'html' => FALSE,
        'absolute' => TRUE,
        'external' => TRUE,
      );
      $title = l($title, _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'url'), $link_options);
    }
    $icon_block['icon_blocks']['text_wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h4',
      '#value' => $title,
      '#attributes' => array(
        'class' => array(
          'title',
        ),
      )
    );

    $icon_block['icon_blocks']['text_wrapper']['description'] = array(
      '#markup' => filter_xss(_contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'description')),
    );

    $items[$delta] = render($icon_block);
  }

  $block['icon_blocks'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => '',
    '#type' => 'ul',
    '#attributes' => array(
      'class' => array(
        'icon-blocks-wrapper',
        'icon-blocks-wrapper--count-' . $total_items,
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
  $default_size = isset($widget_settings['icon_blocks_number']) ? $widget_settings['icon_blocks_number'] : '';

  $available_sizes = array('' => t('- Select -'));
  $sizes = drupal_map_assoc(range(1, 9));
  foreach ($sizes as $size) {
    $available_sizes[$size] = format_plural($size, '1 Icon Link', '@count Icon Links');
  }
  $settings_form['icon_blocks_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Icon Links'),
    '#options' => $available_sizes,
    '#default_value' => $default_size,
    '#ajax' => array(
      'callback' => 'contentwidget_icon_blocks_settings_ajax',
      'wrapper' => 'icon-links-wrapper',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  $settings_form['icon_blocks_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="icon-links-wrapper">',
    '#suffix' => '</div>',
  );

  // Fetch the re-usable icon options.
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  // Create the forms for the icon links.
  for ($delta = 0; $delta < $widget_settings['icon_blocks_number']; $delta++) {
    $settings_form['icon_blocks_wrapper'][$delta] = array(
      '#type' => 'fieldset',
      '#title' => t('Icon Link #@number:', array('@number' => ($delta + 1))),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $settings_form['icon_blocks_wrapper'][$delta]['icon'] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#required' => TRUE,
      '#default_value' => _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'icon'),
    );
    $settings_form['icon_blocks_wrapper'][$delta]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#required' => TRUE,
      '#default_value' => _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'title'),
    );
    $settings_form['icon_blocks_wrapper'][$delta]['title_as_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Title as a Link'),
      '#description' => t('If you want to use the title as the link (and not the default "Visit Link >"), check this box.'),
      '#default_value' => _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'title_as_link'),
    );
    $settings_form['icon_blocks_wrapper'][$delta]['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'description'),
    );
    $settings_form['icon_blocks_wrapper'][$delta]['url'] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#required' => TRUE,
      '#default_value' => _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, 'url'),
      '#description' => t('You can specify either an internal or external URL (if it is an external, make sure to specify the full path: i.e. http://google.com'),
    );
  }

  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function contentwidget_icon_blocks_settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['icon_blocks']['icon_blocks_wrapper'];
}

/**
 * Callback that returns the value for a specific settings key for specific delta.
 *
 * @param $widget_settings
 *  Full widget settings array.
 *
 * @param $delta
 *  Delta of the key fact.
 *
 * @param $key
 *  Key of the setting we want to return.
 *
 * @return string
 *  Returns the value of the setting.
 */
function _contentwidget_icon_blocks_get_property_value($widget_settings, $delta, $key) {
  return isset($widget_settings['icon_blocks_wrapper'][$delta][$key]) ? $widget_settings['icon_blocks_wrapper'][$delta][$key] : '';
}
