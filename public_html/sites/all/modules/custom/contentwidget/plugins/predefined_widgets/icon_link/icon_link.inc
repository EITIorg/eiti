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
  'title' => 'Icon Link',
  'description' => 'Use this widget to add multiple icon-links blocks.',
  'render callback' => 'contentwidget_icon_link_render',
  'settings form' => 'contentwidget_icon_link_settings',
  'entity form alter' => 'contentwidget_icon_link_form_alter',
  'entity group alter' => 'contentwidget_icon_link_group_alter',
  'hook_entity_view' => 'contentwidget_icon_link_hook_entity_view',
  'hook_fieldable_panels_pane_view' => 'contentwidget_icon_link_hook_fieldable_panels_pane_view',
  'defaults' => array(
    'icon_links_number' => '',
  ),
);

/**
 * Render callback for the 'Icon Link' predefined widget.
 */
function contentwidget_icon_link_render($plugin, $widget_settings, $entity, $langcode) {
  $size = $widget_settings['icon_links_number'];

  // Iterate through the link icons (formatting already inspired from the prototype).
  $items = array();
  for ($link = 0; $link < $size; $link++) {
    $icon_link = array();
    $icon_link['icon_link'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('additional-resource-widget', drupal_html_class('widget-' . $link))
      ),
    );
    $icon_link['icon_link']['icon_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('widget-icon')
      ),
    );
    // TODO: Specify the path to the correct SVG icon.
    $icon = _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'icon');
    $path_to_icon = '';
    $icon_link['icon_link']['icon_wrapper']['icon'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#attributes' => array(
        'src' => array($path_to_icon),
      )
    );

    // Now, the rest.
    $icon_link['icon_link']['text_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('widget-text')
      ),
    );
    $title = _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'title');
    $title_as_link = _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'title_as_link');
    if ($title_as_link == TRUE) {
      $title = l($title, _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'url'));
    }
    $icon_link['icon_link']['text_wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h4',
      '#value' => $title,
      '#attributes' => array(
        'class' => array('additional-resource-title'),
      )
    );
    $icon_link['icon_link']['text_wrapper']['description'] = array(
      '#markup' => filter_xss(_contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'description')),
    );
    if ($title_as_link == FALSE) {
      $icon_link['icon_link']['text_wrapper']['url'] = array(
        '#theme' => 'link',
        '#text' => t('Visit Link'),
        '#path' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'url'),
        '#options' => array(
          'attributes' => array('class' => array('visit-link')),
          'html' => FALSE,
          'absolute' => TRUE,
          'external' => TRUE,
        ),
      );
    }
    $items[] = render($icon_link);
  }

  $block['icon_links'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => '',
    '#type' => 'ul',
    '#attributes' => array(
      'class' => array(
        'section-additional-resources',
        'bookmark-items-count-' . $size,
        'clearfix',
      ),
    ),
  );

  return $block;
}

/**
 * Settings form for the 'Icon Link' predefined widget.
 */
function contentwidget_icon_link_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $default_size = isset($widget_settings['icon_links_number']) ? $widget_settings['icon_links_number'] : '';

  $available_sizes = array('' => t('- Select -'));
  $sizes = drupal_map_assoc(range(1, 9));
  foreach ($sizes as $size) {
    $available_sizes[$size] = format_plural($size, '1 Icon Link', '@count Icon Links');
  }
  $settings_form['icon_links_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Icon Links'),
    '#options' => $available_sizes,
    '#default_value' => $default_size,
    '#ajax' => array(
      'callback' => 'contentwidget_icon_link_settings_ajax',
      'wrapper' => 'icon-links-wrapper',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  $settings_form['icon_links_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="icon-links-wrapper">',
    '#suffix' => '</div>',
  );

  // Fetch the re-usable icon options.
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  // Create the forms for the icon links.
  for ($link = 0; $link < $widget_settings['icon_links_number']; $link++) {
    $settings_form['icon_links_wrapper']['link_' . $link] = array(
      '#type' => 'fieldset',
      '#title' => t('Icon Link #@number:', array('@number' => ($link + 1))),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $settings_form['icon_links_wrapper']['link_' . $link]['icon_' . $link] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#required' => TRUE,
      '#default_value' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'icon'),
    );
    $settings_form['icon_links_wrapper']['link_' . $link]['title_' . $link] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#required' => TRUE,
      '#default_value' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'title'),
    );
    $settings_form['icon_links_wrapper']['link_' . $link]['title_as_link_' . $link] = array(
      '#type' => 'checkbox',
      '#title' => t('Title as a Link'),
      '#description' => t('If you want to use the title as the link (and not the default "Visit Link >"), check this box.'),
      '#default_value' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'title_as_link'),
    );
    $settings_form['icon_links_wrapper']['link_' . $link]['description_' . $link] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'description'),
    );
    $settings_form['icon_links_wrapper']['link_' . $link]['url_' . $link] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#required' => TRUE,
      '#default_value' => _contentwidget_key_icon_link_get_property_value($widget_settings, $link, 'url'),
      '#description' => t('You can specify either an internal or external URL (if it is an external, make sure to specify the full path: i.e. http://google.com'),
    );
  }

  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function contentwidget_icon_link_settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['icon_link']['icon_links_wrapper'];
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
 * @return
 *  Returns the value of the setting.
 */
function _contentwidget_key_icon_link_get_property_value($widget_settings, $delta, $key) {
  $value = isset($widget_settings['icon_links_wrapper']['link_' . $delta][$key . '_' . $delta]) ? $widget_settings['icon_links_wrapper']['link_' . $delta][$key . '_' . $delta] : '';
  return $value;
}
