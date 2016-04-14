<?php

/**
 * @file
 * Provides a custom Visualization - StackedBar Chart with Data from the Summary Data.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Visualization: Stacked Bar chart dynamic',
  'description' => 'A stacked bar chart with data pulled from the Summary Data.',
  'render callback' => 'contentwidget__viz_stackedbar_dynamic__render',
  'settings form' => 'contentwidget__viz_stackedbar_dynamic__settings_form',
  'defaults' => array(
    'stackedbar_settings' => array(
      'data_type' => '',
      'legend_position' => 'right',
    ),
    'extra_settings' => array(
      'gfs' => array(
        'gfs_codes' => array(),
      ),
    ),
  ),
);

/**
 * Render callback for the 'StackedBar Chart' predefined widget.
 */
function contentwidget__viz_stackedbar_dynamic__render($plugin, $widget_settings, $entity, $langcode) {
  // If we're in Panelizer, we don't want to create the whole chart there, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map']) || in_array('editor', $menu_item['map'])) {
    return array('#markup' => t('Configured Grouped Bar Widget - with dynamic data (from Summary Data).'));
  }

  // Load the Plotly.js library.
  $plotly_library = libraries_load('plotly', 'minified');
  if (empty($plotly_library)) {
    return array('#markup' => t('Plotly.js library could not be loaded.'));
  }

  // Load the library.
  // @TODO: Use restful.module for CSV export.
  $library = libraries_load('eitiChartWidgets', 'minified');
  if (empty($library)) {
    return array('#markup' => t('Charts library could not be loaded.'));
  }

  // Prepare the ID.
  $identifier_parts = array(
    'eiti-chart-widget',
    $entity->fpid,
    $entity->vid
  );
  $identifier = drupal_clean_css_identifier(implode('-', $identifier_parts));

  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'eiti-chart-widget-wrapper',
        $identifier . '-wrapper',
      ),
    ),
  );

  $block['widget'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $identifier,
      'class' => array(
        'eiti-chart-widget',
        drupal_html_class('eiti-chart-widget--' . $plugin['name']),
      ),
    ),
    '#weight' => 10,
  );

  $block['widget']['initializing'] = array(
    '#type' => 'html_tag',
    '#tag' => 'p',
    '#value' => t('Initializing chart.'),
    '#attributes' => array(
      'class' => array(
        'message-initializing',
      ),
    ),
  );

  $block['export'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $identifier . '--export',
      'class' => array(
        'eiti-chart-widget--export',
      ),
    ),
    '#weight' => 11,
  );

  $endpoints = _contentwidget__viz_stackedbar_dynamic__get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['stackedbar_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = _contentwidget__viz_stackedbar_dynamic__get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['stackedbar_settings']['data_type']];
  $settings = array(
    'type' => 'StackedBar',
    'title' => $js_settings['title'],
    'description' => $js_settings['description'],
    'xlabel' => $js_settings['x-axis'],
    'ylabel' => $js_settings['y-axis'],
    'legend_position' => $widget_settings['stackedbar_settings']['legend_position'],
    'container' => $identifier,
    'endpoint' => $endpoint,
    'endpoint_data' => array(),
  );

  switch ($widget_settings['stackedbar_settings']['data_type']) {
    case 'government_revenues':
      // We want to pass the commodities to the filter and the country from the context.
      $settings['endpoint_data']['filter']['gfs_code'] = implode(',', array_flip($widget_settings['extra_settings']['gfs']['gfs_codes']));
      $country = menu_get_object('implementing_country');
      if (!empty($country)) {
        $settings['endpoint_data']['filter']['country_iso'] = $country->iso;
      }
      else {
        return array('#markup' => t('This widget requires country context.'));
      }
      break;
  }

  drupal_add_js(array('eitiContentWidgetPlotly' => array($identifier => $settings)), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'StackedBar Chart' predefined widget.
 */
function contentwidget__viz_stackedbar_dynamic__settings_form(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Extract these for possible re-use.
  $entity = $element['#entity'];
  $entity_type = $element['#entity_type'];
  $language = $element['#language'];
  $field = $element['#field_name'];
  $ctools_contexts = isset($form_state['contexts']['panelizer']) ? $form_state['contexts']['panelizer'] : array();

  // Settings.
  $settings_form['stackedbar_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Stacked Bar Chart Settings'),
    '#description' => t('Generic stack bar chart settings.')
  );

  // We want to cut out those who's context is required.
  $type_options = _contentwidget__viz_stackedbar_dynamic__get_data_types('options');
  $items = _contentwidget__viz_stackedbar_dynamic__get_data_types();
  foreach ($type_options as $option_key => $label) {
    if ($items[$option_key]['context required'] && (empty($ctools_contexts) || $ctools_contexts->plugin !== $items[$option_key]['context required'])) {
      unset($type_options[$option_key]);

      if (!isset($form_state['pane'])) {
        $settings_form['sankey_settings']['no-pane'] = array(
          '#markup' => '<strong>'. t('Please configure this pane inside of the panelizer, because it requires panelizer context.') . '</strong>',
        );
        return $settings_form;
      }
    }
  }
  array_unshift($type_options, t('- Select -'));
  $wrapper_id = 'extra-settings-stacked-dynamic';
  $settings_form['stackedbar_settings']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#description' => t('Please select which data would you like to pull from the Summary Data.'),
    '#default_value' => $widget_settings['stackedbar_settings']['data_type'],
    '#options' => $type_options,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__viz_stackedbar_dynamic__ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $settings_form['stackedbar_settings']['legend_position'] = array(
    '#type' => 'select',
    '#title' => t('Legend Position'),
    '#options' => array(
      'above' => t('Above'),
      'right' => t('Right'),
    ),
    '#default_value' => $widget_settings['stackedbar_settings']['legend_position'],
    '#required' => TRUE,
  );

  // Check if there are any extra settings.
  $extra_settings = _contentwidget__viz_stackedbar_dynamic__get_data_types('extra settings');
  $settings_form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Settings'),
    '#prefix' => '<div id="' . $wrapper_id . '">',
    '#suffix' => '</div>',
  );

  if (isset($extra_settings[$widget_settings['stackedbar_settings']['data_type']])) {
    $function = $extra_settings[$widget_settings['stackedbar_settings']['data_type']];
    $function($settings_form['extra_settings'], $form_state, $widget_settings, $ctools_contexts);
  }
  else {
    $settings_form['extra_settings']['info'] = array('#markup' => t('Please select the data type.'));
  }

  return $settings_form;
}

/**
 * Small custom ajax callback.
 */
function _contentwidget__viz_stackedbar_dynamic__ajax_settings($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];

  // Polish the #parents.
  $key = array_search('data_type', $parents, TRUE);
  unset($parents[$key]);
  $key = array_search('stackedbar_settings', $parents, TRUE);
  unset($parents[$key]);
  $parents[] = 'extra_settings';

  $exists = FALSE;
  $value = drupal_array_get_nested_value($form, $parents, $exists);
  if ($exists) {
    return $value;
  }
  else {
    $entity = $form_state['entity'];
    $entity_language = entity_language('fieldable_panels_pane', $entity);
    $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_stackedbar_dynamic']['extra_settings'];
  }
}

/**
 * Returns all data type options.
 *
 * @param string $return
 *   This can be either: 'options', 'endpoint', 'extra settings' and 'js settings'.
 *
 * @return array
 *   The Return array depends on the $return parameter you specify, either it's
 *   an array of labels for the options, or it's an array of api endpoints.
 */
function _contentwidget__viz_stackedbar_dynamic__get_data_types($return = NULL) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['government_revenues'] = array(
    'label' => t('Country: Government Revenue'),
    'endpoint' => '/api/v1.0/stacked_bar/government_revenues',
    'extra settings' => '_contentwidget__viz_groupedbar_dynamic__government_revenues_country_settings',
    'x-axis' => t('Years'),
    'y-axis' => t('Government Revenue (normalized to USD)'),
    'title' => t('Government Revenues'),
    'description' => t('Revenues the government obtained.'),
    'context required' => 'entity:implementing_country',
  );

  $output = array();
  foreach ($items as $key => $item) {
    switch ($return) {
      case 'options':
        $output[$key] = $item['label'];
        break;
      case 'endpoint':
        $output[$key] = $item['endpoint'];
        break;
      case 'extra settings':
        $output[$key] = $item['extra settings'];
        break;
      case 'js settings':
        $output[$key]['x-axis'] = $item['x-axis'];
        $output[$key]['y-axis'] = $item['y-axis'];
        $output[$key]['title'] = $item['title'];
        $output[$key]['description'] = $item['description'];
        break;
    }
  }

  // If nothing was set as a return string, then just return plain items.
  if (!$return) {
    return $items;
  }
  return $output;
}

/**
 * Extra settings for the Governmental Revenues per Country.
 */
function _contentwidget__viz_groupedbar_dynamic__government_revenues_country_settings(&$form, &$form_state, &$widget_settings, $ctools_contexts = array()) {
  // Load all GFS codes so we can identify all the parents.
  $form['gfs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Revenue Stream as Disclosed by Government'),
    '#description' => t('You may specify the revenues (GFS Codes) you want to be displayed in the widget.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('gfs-codes-container')),
  );

  $gfs_codes = eitientity_gfs_code_get_tree();
  $options = array();
  foreach ($gfs_codes as $gfs_code) {
    $options[$gfs_code->id] = '<span>' . str_repeat('-', $gfs_code->depth) . '[' . check_plain($gfs_code->code) . ']</span> ' . filter_xss($gfs_code->name);
  }

  $inline_style = '.gfs-codes-container label.option {font-family: monospace; font-size: 1em; vertical-align: top;}';
  $form['gfs']['style'] = array(
    '#type' => 'html_tag',
    '#tag' => 'style',
    '#value' => $inline_style,
  );

  $form['gfs']['gfs_codes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Flat list of all GFS Codes'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => isset($widget_settings['extra_settings']['gfs']['gfs_codes']) ? $widget_settings['extra_settings']['gfs']['gfs_codes'] : TRUE,
  );
}
