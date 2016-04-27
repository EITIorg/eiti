<?php

/**
 * @file
 * Provides a custom Tabs widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Tabs'),
  'description' => t('Widget that contains a couple of widgets.'),
  'render callback' => 'contentwidget__tabs__render',
  'settings form' => 'contentwidget__tabs__settings',
  'defaults' => array(
    'tabs_number' => 4,
  ),
);

/**
 * Render callback for the 'Tabs' predefined widget.
 */
function contentwidget__tabs__render($plugin, $widget_settings, $entity, $langcode) {
  // If we're in Panelizer, we don't want to create the whole widget here, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map'])) {
    return array('#markup' => t('Tabs - Widget that contains a couple of widgets.'));
  }

  // Prepare the variables.
  $referenced_ids = array();

  foreach ($entity->field_fpp_content_widgets[$langcode] as $reference) {
    $referenced_ids[] = $reference['target_id'];
  }
  $referenced_entities = entity_load('fieldable_panels_pane', $referenced_ids);
  $referenced_entities_view_arr = entity_view('fieldable_panels_pane', $referenced_entities);
  $referenced_entities_view_arr = array_values($referenced_entities_view_arr['fieldable_panels_pane']);

  // Prepare the wrapper.
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('tabs-widget-wrapper'),
      'id' => array(drupal_html_id('tabs_' . $entity->fpid)),
    ),
    '#attached' => array(
      'library' => array(
        array('system', 'ui.tabs'),
      ),
      'js' => array(
        drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js',
      ),
    ),
  );

  // And now prepare the list of facts that we'll render in theme_item_list.
  $tab_links = array();
  $tabs_content = array();
  for ($tab_delta = 0; $tab_delta < $widget_settings['tabs_number']; $tab_delta++) {
    // Prepare the links (tab header).
    $tab_link = array(
      '#theme' => 'link',
      '#text' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'tab_title'),
      '#path' => '',
      '#options' => array(
        'fragment' => 'ief-tab-' . $entity->fpid . '-' . $tab_delta,
        'attributes' => array(
          'class' => array(drupal_html_class('icon-' . _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'icon'))),
        ),
        'html' => TRUE,
      ),
    );
    $tab_links[] = render($tab_link);

    // Prepare the tab's content.
    $tab = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array(drupal_html_id('ief-tab-' . $entity->fpid . '-' . $tab_delta)),
        'class' => array('tab-content'),
      ),
    );
    $tab['description'] = array(
      '#markup' => check_markup(_contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'tab_description'))
    );
    $tab['primary_link'] = array(
      '#theme' => 'link',
      '#text' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_primary_title'),
      '#path' => url(_contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_primary_url')),
      '#options' => array(
        'attributes' => array(
          'class' => array('primary-tab-link'),
        ),
        'html' => FALSE,
      ),
    );
    $tab['secondary_link'] = array(
      '#theme' => 'link',
      '#text' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_secondary_title'),
      '#path' => url(_contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_secondary_url')),
      '#options' => array(
        'attributes' => array(
          'class' => array('secondary-tab-link'),
        ),
        'html' => FALSE,
      ),
    );
    $tab['widget'] = $referenced_entities_view_arr[$tab_delta];
    $tabs_content[] = $tab;
  }

  //$block['tabs_links'] = array(
  //  '#theme' => 'item_list',
  //  '#items' => $tab_links,
  //  '#type' => 'ul',
  //  '#title' => '',
  //  '#attributes' => array('class' => array('tab-links')),
  //);
  //$block['tabs_content'] = $tabs_content;

  return $block;
}

/**
 * Settings form for the 'Tabs' predefined widget.
 */
function contentwidget__tabs__settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  $settings_form['tabs_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Tabs'),
    '#options' => drupal_map_assoc(range(1, 6)),
    '#description' => t('Please specify the number of tabs you want to use.'),
    '#default_value' => $widget_settings['tabs_number'],
    '#ajax' => array(
      'callback' => '_contentwidget__tabs__settings_ajax',
      'event' => 'change',
      'wrapper' => 'tabs-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $settings_form['tabs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tab Widget Settings:'),
    '#collapsible' => FALSE,
    '#prefix' => '<div id="tabs-wrapper">',
    '#suffix' => '</div>',
  );

  // Create the fact widget and all that it includes.

  // Get the options here (we don't want to do it in the loop).
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  for ($tab_delta = 0; $tab_delta < $widget_settings['tabs_number']; $tab_delta++) {
    $settings_form['tabs']['tab_' . $tab_delta] = array(
      '#type' => 'fieldset',
      '#title' => t('Tab #!number:', array('!number' => ($tab_delta + 1))),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $settings_form['tabs']['tab_' . $tab_delta]['icon_' . $tab_delta] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'icon'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['tab_title_' . $tab_delta] = array(
      '#type' => 'textfield',
      '#title' => t('Tab Title'),
      '#description' => t('Title of the tab (displayed under the icon).'),
      '#size' => 50,
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'tab_title'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['tab_description_' . $tab_delta] = array(
      '#type' => 'textarea',
      '#title' => t("Tab's Description"),
      '#description' => t('Give this tab some context, or contextual description.'),
      '#size' => 50,
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'tab_description'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['link_primary_title_' . $tab_delta] = array(
      '#type' => 'textfield',
      '#title' => t('Primary Link: Title'),
      '#size' => 30,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_primary_title'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['link_primary_url_' . $tab_delta] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#size' => 30,
      '#suffix' => '</div>',
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_primary_url'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['link_secondary_title_' . $tab_delta] = array(
      '#type' => 'textfield',
      '#title' => t('Secondary Link: Title'),
      '#size' => 30,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_secondary_title'),
    );
    $settings_form['tabs']['tab_' . $tab_delta]['link_secondary_url_' . $tab_delta] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#size' => 30,
      '#suffix' => '</div>',
      '#default_value' => _contentwidget__tabs__key_tab_get_property_value($widget_settings, $tab_delta, 'link_secondary_url'),
    );
  }
  return $settings_form;
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
function _contentwidget__tabs__key_tab_get_property_value($widget_settings, $delta, $key) {
  $value = isset($widget_settings['tabs']['tab_' . $delta][$key . '_' . $delta]) ? $widget_settings['tabs']['tab_' . $delta][$key . '_' . $delta] : '';
  return $value;
}

/**
 * Ajax callback for the settings form.
 */
function _contentwidget__tabs__settings_ajax($form, $form_state) {
  $entity = $form_state['entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace("#tabs-wrapper", render($form['field_fpp_widget'][$widget_field_language][0]['settings']['tabs']['tabs'])),
      ajax_command_replace("#ief-cardinality", render($form['field_fpp_content_widgets'][$widget_field_language]['cardinality_count'])),
    )
  );
}
