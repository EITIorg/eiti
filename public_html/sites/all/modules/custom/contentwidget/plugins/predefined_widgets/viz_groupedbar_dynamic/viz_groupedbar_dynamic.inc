<?php

/**
 * @file
 * Provides a custom Visualization - BarChart with data from the Summary Data.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Visualization: Grouped Bar chart dynamic',
  'description' => 'A bar chart with data pulled from the Summary Data.',
  'render callback' => 'contentwidget__viz_groupedbar_dynamic__render',
  'settings form' => 'contentwidget__viz_groupedbar_dynamic__settings_form',
  'defaults' => array(
    'barchart_settings' => array(
      'data_type' => '',
    ),
    'extra_settings' => array(
      'expose_year' => FALSE,
      'commodities' => array(),
    ),
  ),
);

/**
 * Render callback for the 'Bar Chart' predefined widget.
 */
function contentwidget__viz_groupedbar_dynamic__render($plugin, $widget_settings, $entity, $langcode) {
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

  $endpoints = _contentwidget__viz_groupedbar_dynamic__get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['barchart_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = _contentwidget__viz_groupedbar_dynamic__get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['barchart_settings']['data_type']];
  $settings = array(
    'container' => $identifier,
    'type' => 'GroupedBar',
    'title' => $js_settings['title'],
    'description' => $js_settings['description'],
    'xlabel' => $js_settings['x-axis'],
    'ylabel' => $js_settings['y-axis'],
    'expose_year' => $widget_settings['extra_settings']['expose_year'],
    'endpoint' => $endpoint,
    'endpoint_data' => array(),
  );

  switch ($widget_settings['barchart_settings']['data_type']) {
    case 'production_countries':
      // We want to pass the commodities to the filter.
      $settings['endpoint_data']['filter']['indicator'] = implode(',', $widget_settings['extra_settings']['commodities']);
      break;
    case 'production_per_country':
      // We want to pass the commodities to the filter and the country from the context.
      $settings['endpoint_data']['filter']['indicator'] = implode(',', $widget_settings['extra_settings']['commodities']);
      // Yes, because I HAVE NO IDEA how to load ctools / panels / panelizer contexts properly.
      $country = menu_get_object('implementing_country');
      if (!empty($country)) {
        $settings['endpoint_data']['filter']['country_iso'] = $country->iso;
      }
      else {
        return array('#markup' => t('This widget requires country context.'));
      }
      break;
    case 'external_per_country':
      // We want to pass the commodities to the filter and the country from the context.
      $settings['endpoint_data']['filter']['indicator'] = implode(',', $widget_settings['extra_settings']['external_indicators']);
      // Yes, because I HAVE NO IDEA how to load ctools / panels / panelizer contexts properly.
      $country = menu_get_object('implementing_country');
      if (!empty($country)) {
        $settings['endpoint_data']['filter']['country_iso'] = $country->iso;
      }
      else {
        return array('#markup' => t('This widget requires country context.'));
      }
      break;
  }

  // Adjust settings for the expose year case.
  if ($widget_settings['extra_settings']['expose_year']) {
    $available_years_options = _contentwidget__viz_groupedbar_dynamic__production_get_years_range();

    $current_year = date('Y');
    if (in_array($current_year, $available_years_options)) {
      $default_year = $current_year;
    }
    else if (in_array($current_year - 1, $available_years_options)) {
      $default_year = $current_year - 1;
    }
    else {
      $default_year = end($available_years_options);
    }

    $block['widget_year_selector'] = array(
      '#type' => 'select',
      '#name' => 'year_selector',
      '#title' => t('Reporting Year'),
      '#options' => $available_years_options,
      '#value' => $default_year,
      '#attributes' => array(
        'class' => array(drupal_html_class($identifier . '--year-selector')),
      ),
    );

    $settings['year_selector_class'] = drupal_html_class($identifier . '--year-selector');
    $settings['endpoint_data']['filter']['year'] = $default_year;
  }

  drupal_add_js(array('eitiContentWidgetPlotly' => array($identifier => $settings)), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Bar Chart' predefined widget.
 */
function contentwidget__viz_groupedbar_dynamic__settings_form(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Extract these for possible re-use.
  $entity = $element['#entity'];
  $entity_type = $element['#entity_type'];
  $language = $element['#language'];
  $field = $element['#field_name'];
  $ctools_contexts = isset($form_state['contexts']['panelizer']) ? $form_state['contexts']['panelizer'] : array();

  // Settings.
  $settings_form['barchart_settings'] = array(
    '#type' => 'container',
  );

  // We want to cut out those who's context is required.
  $type_options = _contentwidget__viz_groupedbar_dynamic__get_data_types('options');
  $items = _contentwidget__viz_groupedbar_dynamic__get_data_types();
  foreach ($type_options as $option_key => $label) {
    if (isset($items[$option_key]['context required']) && (empty($ctools_contexts) || $ctools_contexts->plugin !== $items[$option_key]['context required'])) {
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
  $wrapper_id = 'extra-settings-groupedbar-dynamic';
  $settings_form['barchart_settings']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#description' => t('The type of data to retrieve from the Summary Data.'),
    '#default_value' => isset($widget_settings['barchart_settings']['data_type']) ? $widget_settings['barchart_settings']['data_type'] : '',
    '#options' => $type_options,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__viz_groupedbar_dynamic__ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = _contentwidget__viz_groupedbar_dynamic__get_data_types('extra settings');
  $settings_form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Settings'),
    '#prefix' => '<div id="' . $wrapper_id . '">',
    '#suffix' => '</div>',
  );
  if (isset($extra_settings[$widget_settings['barchart_settings']['data_type']])) {
    $function = $extra_settings[$widget_settings['barchart_settings']['data_type']];
    $function($settings_form['extra_settings'], $form_state, $widget_settings);
  }
  else {
    $settings_form['extra_settings']['info'] = array('#markup' => t('Please select the data type.'));
  }

  return $settings_form;
}

/**
 * Small custom ajax callback.
 */
function _contentwidget__viz_groupedbar_dynamic__ajax_settings($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];

  // Polish the #parents.
  $key = array_search('data_type', $parents, TRUE);
  unset($parents[$key]);
  $key = array_search('barchart_settings', $parents, TRUE);
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
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_groupedbar_dynamic']['extra_settings'];
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
function _contentwidget__viz_groupedbar_dynamic__get_data_types($return = FALSE) {
  $items = array();

  $items['production_countries'] = array(
    'label' => t('Global: Production Countries'),
    'endpoint' => '/api/v1.0/grouped_bar/production',
    'extra settings' => '_contentwidget__viz_groupedbar_dynamic__production_countries_settings',
    'x-axis' => t('Countries'),
    'y-axis' => t('Production Volumes (Sm3)'),
    'title' => t('Global Production Chart'),
    'description' => t('Production volumes for all the countries'),
  );
  $items['production_per_country'] = array(
    'label' => t('Country: Production'),
    'endpoint' => '/api/v1.0/grouped_bar/production_per_country',
    'extra settings' => '_contentwidget__viz_groupedbar_dynamic__production_per_country_settings',
    'x-axis' => t('Years'),
    'y-axis' => t('Production Volumes for all the Reported Years'),
    'title' => t('Production Chart'),
    'description' => t('Production volumes'),
    'context required' => 'entity:implementing_country',
  );
  $items['external_per_country'] = array(
    'label' => t('Country: External Indicators'),
    'endpoint' => '/api/v1.0/grouped_bar/external_per_country',
    'extra settings' => '_contentwidget__viz_groupedbar_dynamic__external_per_country_settings',
    'x-axis' => t('Years'),
    'y-axis' => t('USD'),
    'title' => t('External Indicators Chart'),
    'description' => t('External Indicators for all the Reported Years'),
    'context required' => 'entity:implementing_country',
  );

  // If nothing was set as a return string, then just return plain items.
  if (!$return) {
    return $items;
  }

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
        $output[$key]['title'] = $item['title'];
        $output[$key]['description'] = $item['description'];
        $output[$key]['x-axis'] = $item['x-axis'];
        $output[$key]['y-axis'] = $item['y-axis'];
        break;
    }
  }

  return $output;
}

/**
 * Extra settings for the production by country (for all the countries).
 */
function _contentwidget__viz_groupedbar_dynamic__production_countries_settings(&$form, &$form_state, &$widget_settings) {
  $form['expose_year'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expose the Year Selector'),
    '#description' => t('If you check this box, users will be able to filter data by <strong>year</strong>.'),
    '#default_value' => isset($widget_settings['extra_settings']['expose_year']) ? $widget_settings['extra_settings']['expose_year'] : TRUE,
  );

  $production_group_id = '';
  $groups = eitientity_indicator_get_by_bundle('group');
  foreach ($groups as $id => $group) {
    if ($group->name == 'Production volume and value (3.5.a)') {
      $production_group_id = $id;
      break;
    }
  }

  $commodities_options = array();
  $commodities = array('Oil, volume', 'Gas, volume', 'NGL, volume');
  $numeric_indicators = eitientity_indicator_get_by_bundle('numeric');
  foreach ($numeric_indicators as $id => $indicator) {
    if (in_array($indicator->name, $commodities) && $indicator->parent == $production_group_id) {
      $commodities_options[$id] = $indicator->name;
    }
  }
  $form['commodities'] = array(
    '#type' => 'checkboxes',
    '#required' => TRUE,
    '#title' => t('Commodities'),
    '#options' => $commodities_options,
    '#default_value' => isset($widget_settings['extra_settings']['commodities']) ? $widget_settings['extra_settings']['commodities'] : TRUE,
  );
}

/**
 * Extra settings for the production per country (for one predefined country).
 */
function _contentwidget__viz_groupedbar_dynamic__production_per_country_settings(&$form, &$form_state, &$widget_settings) {
  // We basically re-use previously define settings callback with little adjustments.
  _contentwidget__viz_groupedbar_dynamic__production_countries_settings($form, $form_state, $widget_settings);
  unset($form['expose_year']);
}

/**
 * Extra settings for the external indicators per country (for one predefined country).
 */
function _contentwidget__viz_groupedbar_dynamic__external_per_country_settings(&$form, &$form_state, &$widget_settings) {
  $numerics = eitientity_indicator_get_by_bundle('numeric');
  $groups = eitientity_indicator_get_by_bundle('group');
  $external_group_id = '';
  foreach ($groups as $id => $group) {
    if ($group->name == 'External indicators') {
      $external_group_id = $id;
      break;
    }
  }
  $external_indicators = array(
    'Extractives',
    'GDP',
    'Aid',
    'FDI',
    'Remittances',
    'Total Gov Revenue',
  );
  $external_options = array();
  foreach ($numerics as $id => $indicator) {
    if (in_array($indicator->name, $external_indicators) && $indicator->parent == $external_group_id) {
      $external_options[$id] = $indicator->name;
    }
  }
  $message = 'If you check this box, users will be able to filter data by the <strong>external indicators</strong>.' .
    '<br/>Note: <em>If you want to use these values, make sure you have them in the Summary Data files.' .
    'If you don\'t, then edit the Summary Data and create the indicator values manually.</em>';

  $form['external_indicators'] = array(
    '#type' => 'checkboxes',
    '#title' => t('External Indicators'),
    '#description' => t($message),
    '#required' => TRUE,
    '#options' => $external_options,
    '#default_value' => isset($widget_settings['extra_settings']['external_indicators']) ? $widget_settings['extra_settings']['external_indicators'] : TRUE,
  );
}

/**
 * Small helper callback that returns the range of available years.
 */
function _contentwidget__viz_groupedbar_dynamic__production_get_years_range() {
  // Better to make just 1 query and then a PHP loop, vs having 2 or 4 queries;
  $query = db_select('eiti_summary_data', 'sd');
  $query->addExpression("date_part('year', to_timestamp(sd.year_end))", 'year');
  $query->condition('status', TRUE);
  $result = $query->execute();
  $results = $result->fetchAll();

  // Flat the values.
  $values = array();
  foreach ($results as $result) {
    $values[] = $result->year;
  }
  // Sort'em.
  sort($values);
  return drupal_map_assoc($values);
}
