<?php

/**
 * @file
 * Provides a custom Visualization - BarChart with Manual Input
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Visualization: Grouped Bar chart static'),
  'description' => t('A grouped bar chart with a manual input data.'),
  'render callback' => 'contentwidget_viz_groupedbarchart_static_render',
  'settings form' => 'contentwidget_viz_groupedbarchart_static_settings',
  'defaults' => array(
    'groups_number' => 1,
    'values_number' => 1,
    'barchart_settings' => array(
      'name' => '',
      'description' => '',
      'x-axis' => '',
      'y-axis' => '',
      'data_type' => '',
    ),
    'barchart_value' => array(),
  ),
);

/**
 * Render callback for the 'Bar Chart' predefined widget.
 */
function contentwidget_viz_groupedbarchart_static_render($plugin, $widget_settings, $entity, $langcode) {
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

  // Prepare the data.
  $widget_data = array();
  // @TODO: Simplify data structure!
  for ($group_delta = 0; $group_delta < $widget_settings['groups_number']; $group_delta++) {
    $data_group = array(
      'name' => $widget_settings['barchart_value']['group_' . $group_delta]['group_name_' . $group_delta],
    );
    for ($value_delta = 0; $value_delta < $widget_settings['values_number']; $value_delta++) {
      $data_group['x'][$value_delta] = $widget_settings['barchart_value']['group_' . $group_delta]['x_' . $value_delta];
      $data_group['y'][$value_delta] = round(floatval($widget_settings['barchart_value']['group_' . $group_delta]['y_' . $value_delta]));
    }

    $widget_data[$group_delta] = $data_group;
  }

  // Send the settings, so that later we can load them in our behaviour.
  $settings = array(
    'container' => $identifier,
    'type' => 'GroupedBar',
    'title' => $widget_settings['barchart_settings']['name'],
    'description' => $widget_settings['barchart_settings']['description'],
    'xlabel' => $widget_settings['barchart_settings']['x-axis'],
    'ylabel' => $widget_settings['barchart_settings']['y-axis'],
    'widgetData' => $widget_data,
  );

  drupal_add_js(array('eitiContentWidgetPlotly' => array($identifier => $settings)), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Bar Chart' predefined widget.
 */
function contentwidget_viz_groupedbarchart_static_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Settings.
  $settings_form['barchart_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Grouped Bar Chart Settings'),
    '#description' => t('Generic grouped bar chart settings.')
  );
  $settings_form['barchart_settings']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the Bar Chart'),
    '#description' => t('Name of the Grouped Bar Chart.'),
    '#default_value' => $widget_settings['barchart_settings']['name'],
  );
  $settings_form['barchart_settings']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Chart Description'),
    '#description' => t('The description will be display underneath the widget.'),
    '#default_value' => $widget_settings['barchart_settings']['description'],
  );
  $settings_form['barchart_settings']['x-axis'] = array(
    '#type' => 'textfield',
    '#title' => t('X-Axis Label'),
    '#description' => t('Specify the <strong>label</strong> for the x-axis.'),
    '#default_value' => $widget_settings['barchart_settings']['x-axis']
  );
  $settings_form['barchart_settings']['y-axis'] = array(
    '#type' => 'textfield',
    '#title' => t('Y-Axis Label'),
    '#description' => t('Specify the <strong>label</strong> for the y-axis.'),
    '#default_value' => $widget_settings['barchart_settings']['y-axis']
  );

  $groups_number = $widget_settings['groups_number'];
  $values_number = $widget_settings['values_number'];

  $settings_form['values_number'] = array(
    '#type' => 'select',
    '#title' => t('Values Number'),
    '#description' => t('How many values per group should be created?'),
    '#options' => drupal_map_assoc(range(1, 10)),
    '#default_value' => $values_number,
    '#ajax' => array(
      'callback' => 'contentwidget_viz_groupedbarchart_static_settings_values_ajax',
      'event' => 'change',
      'wrapper' => 'grouped-barchart',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $settings_form['groups_number'] = array(
    '#type' => 'select',
    '#title' => t('Groups Number'),
    '#description' => t('How many groups would you like to create?'),
    '#options' => drupal_map_assoc(range(1, 8)),
    '#default_value' => $groups_number,
    '#ajax' => array(
      'callback' => 'contentwidget_viz_groupedbarchart_static_settings_values_ajax',
      'event' => 'change',
      'wrapper' => 'grouped-barchart',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Chart Values.
  $settings_form['barchart_value'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chart Values'),
    '#description' => t('Group chart values split in groups.'),
    '#prefix' => '<div id="grouped-barchart">',
    '#suffix' => '</div>',
  );

  for ($delta = 0; $delta < $groups_number; $delta++) {
    $settings_form['barchart_value']['group_' . $delta] = array(
      '#type' => 'fieldset',
      '#title' => t('Group #' . ($delta + 1)),
    );
    $settings_form['barchart_value']['group_' . $delta]['group_name_' . $delta] = array(
      '#type' => 'textfield',
      '#title' => t('Group Label'),
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>',
      '#default_value' => isset($widget_settings['barchart_value']['group_' . $delta]['group_name_' . $delta]) ? $widget_settings['barchart_value']['group_' . $delta]['group_name_' . $delta] : '',
    );
    for ($v_delta = 0; $v_delta < $values_number; $v_delta++) {
      $settings_form['barchart_value']['group_' . $delta]['x_' . $v_delta] = array(
        '#type' => 'textfield',
        '#title' => t('X Value'),
        '#description' => t('I.E: Year (2015), Country (Norway), etc.'),
        '#prefix' => '<div class="container-inline">',
        '#size' => 10,
        '#default_value' => isset($widget_settings['barchart_value']['group_' . $delta]['x_' . $v_delta]) ? $widget_settings['barchart_value']['group_' . $delta]['x_' . $v_delta] : '',
      );
      $settings_form['barchart_value']['group_' . $delta]['y_' . $v_delta] = array(
        '#type' => 'textfield',
        '#title' => t('Y Value'),
        '#description' => t('Basically the value (numbers).'),
        '#suffix' => '</div>',
        '#size' => 10,
        '#default_value' => isset($widget_settings['barchart_value']['group_' . $delta]['y_' . $v_delta]) ? $widget_settings['barchart_value']['group_' . $delta]['y_' . $v_delta] : '',
      );
    }
  }

  return $settings_form;
}

/**
 * Small custom ajax callback.
 */
function contentwidget_viz_groupedbarchart_static_settings_values_ajax($form, $form_state) {
  $entity = $form_state['entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_groupedbar_static']['barchart_value'];
}

