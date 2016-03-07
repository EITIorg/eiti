<?php

/**
 * @file
 * Provides a custom Visualization - BarChart with Data from the Summary Data.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Visualization: Grouped Bar chart dynamic',
  'description' => 'A grouped bar chart with data pulled from the Summary Data.',
  'render callback' => 'contentwidget_viz_groupedbarchart_dynamic_render',
  'settings form' => 'contentwidget_viz_groupedbarchart_dynamic_settings',
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
function contentwidget_viz_groupedbarchart_dynamic_render($plugin, $widget_settings, $entity, $langcode) {
  $block = array();

  // If we're in Panelizer, we don't want to create the whole chart there, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map']) || in_array('editor', $menu_item['map'])) {
    return array('#markup' => t('Configured Grouped Bar Widget - with dynamic data (from Summary Data).'));
  }

  // Prepare the ID.
  $viz_id = implode('_', array($plugin['name'], $entity->fpid, $entity->vid));
  $block['widget'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => $viz_id,
    )
  );

  // Load the library.
  $library = libraries_load('eiti-charts');
  if (empty($library)) {
    return array('#markup' => t('Charts library could not be loaded.'));
  }

  $endpoints = contentwidget_viz_groupedbarchart_dynamic_get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['barchart_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = contentwidget_viz_groupedbarchart_dynamic_get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['barchart_settings']['data_type']];
  $settings = array(
    'type' => 'GroupedBar',
    'name' => $js_settings['title'],
    'width' => 800,
    'height' => 400,
    'margin' => array(
      'top' => 10,
      'bottom' => 50,
      'left' => 100,
      'right' => 10
    ),
    'xlabel' => $js_settings['x-axis'],
    'ylabel' => $js_settings['y-axis'],
    'description' => $js_settings['description'],
    'container' => $viz_id,
    'expose_year' => $widget_settings['extra_settings']['expose_year'],
    'endpoint' => $endpoint,
  );

  // As dynamic as we tried to be, this is a little exception.
  if ($widget_settings['barchart_settings']['data_type'] == 'production_countries') {
    // We want to pass the commodities to the filter.
    $settings['endpoint'] = $endpoint . '?filter[indicator]=' . implode(',', $widget_settings['extra_settings']['commodities']);
  }
  elseif ($widget_settings['barchart_settings']['data_type'] == 'production_per_country') {
    // We want to pass the commodities to the filter and the country from the context.
    $settings['endpoint'] = $endpoint . '?filter[indicator]=' . implode(',', $widget_settings['extra_settings']['commodities']);
    // Yes, because I HAVE NO IDEA how to load ctools / panels / panelizer contexts properly.
    $country = menu_get_object('implementing_country');
    if (!empty($country)) {
      $settings['endpoint'] .= '&filter[country_iso]=' . $country->iso;
    }
  }

  // Adjust settings for the expose year case.
  if ($widget_settings['extra_settings']['expose_year']) {
    $available_years_options = contentwidget_viz_groupedbarchart_production_get_years_range();
    $last_year = array_slice($available_years_options, -1);
    $default_year = reset($last_year);

    $block['widget_year_selector'] = array(
      '#type' => 'select',
      '#title' => t('Reporting Year'),
      '#options' => $available_years_options,
      '#default_value' => $default_year,
      '#attributes' => array(
        'class' => array('widget-selector', drupal_html_class($viz_id . '-year-selector')),
      )
    );

    // And we want to alter some settings in this case.
    $settings['description_original'] = $settings['description'];
    $settings['name_original'] =  $settings['name'];
    $settings['name'] = t('@title for !year', array(
      '@title' => $settings['name'],
      '!year' => $default_year
    ));
    $settings['description'] = t('@description for !year.', array(
      '@description' => $settings['description'],
      '!year' => $default_year,
    ));
    $settings['endpoint_year'] = $endpoint . '?filter[year][0]=' . $default_year . '&filter[indicator]=' . implode(',', $widget_settings['extra_settings']['commodities']);
    $settings['current_year'] = $default_year;
    $settings['year_selector_class'] = drupal_html_class($viz_id . '-year-selector');
  }

  // Wrap things up.
  $settings = array(
    $viz_id => $settings,
  );
  drupal_add_js(array('contentwidgets' => $settings), array('type' => 'setting', 'scope' => 'footer'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Bar Chart' predefined widget.
 */
function contentwidget_viz_groupedbarchart_dynamic_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Extract these for possible re-use.
  $entity = $element['#entity'];
  $entity_type = $element['#entity_type'];
  $language = $element['#language'];
  $field = $element['#field_name'];
  $ctools_contexts = isset($form_state['contexts']['panelizer']) ? $form_state['contexts']['panelizer'] : array();

  // Settings.
  $settings_form['barchart_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Grouped Bar Chart Settings'),
    '#description' => t('Generic grouped bar chart settings.')
  );

  // We want to cut out those who's context is required.
  $type_options = contentwidget_viz_groupedbarchart_dynamic_get_data_types('options');
  $items = contentwidget_viz_groupedbarchart_dynamic_get_data_types();
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
    '#description' => t('Please select which data would you like to pull from the Summary Data.'),
    '#default_value' => isset($widget_settings['barchart_settings']['data_type']) ? $widget_settings['barchart_settings']['data_type'] : '',
    '#options' => $type_options,
    '#ajax' => array(
      'callback' => 'contentwidget_viz_groupedbarchart_dynamic_ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = contentwidget_viz_groupedbarchart_dynamic_get_data_types('extra settings');
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
function contentwidget_viz_groupedbarchart_dynamic_ajax_settings($form, $form_state) {
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
function contentwidget_viz_groupedbarchart_dynamic_get_data_types($return = FALSE) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['production_countries'] = array(
    'label' => t('Global: Production Countries'),
    'endpoint' => '/api/v1.0/grouped_bar/production',
    'extra settings' => 'contentwidget_viz_groupedbarchart_production_countries_settings',
    'x-axis' => t('Countries'),
    'y-axis' => t('Production Volumes (Sm3)'),
    'title' => t('Global Production Chart'),
    'description' => t('Production volumes for all the countries'),
  );
  $items['production_per_country'] = array(
    'label' => t('Country: Production'),
    'endpoint' => '/api/v1.0/grouped_bar/production_per_country',
    'extra settings' => 'contentwidget_viz_groupedbarchart_production_per_country_settings',
    'x-axis' => t('Years'),
    'y-axis' => t('Production Volumes for all the Reported Years'),
    'title' => t('Production Chart'),
    'description' => t('Production volumes'),
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
 * Extra settings for the production by country (for all the countries).
 */
function contentwidget_viz_groupedbarchart_production_countries_settings(&$form, &$form_state, &$widget_settings) {
  $form['expose_year'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expose the Year Selector'),
    '#description' => t('If you check this box, users will be able to filter data by <strong>year</strong>.'),
    '#default_value' => isset($widget_settings['extra_settings']['expose_year']) ? $widget_settings['extra_settings']['expose_year'] : TRUE,
  );
  $numerics = eitientity_indicator_get_by_bundle('numeric');
  $groups = eitientity_indicator_get_by_bundle('group');
  $production_group_id = '';
  foreach ($groups as $id => $group) {
    if ($group->name == 'Production volume and value (3.5.a)') {
      $production_group_id = $id;
      break;
    }
  }
  $commodities = array('Oil, volume', 'Gas, volume', 'NGL, volume');
  $commodities_options = array();
  foreach ($numerics as $id => $indicator) {
    if (in_array($indicator->name, $commodities) && $indicator->parent == $production_group_id) {
      $commodities_options[$id] = $indicator->name;
    }
  }
  $form['commodities'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Please select the commodities you want to use.'),
    '#description' => t('If you check this box, users will be able to filter data by the <strong>commodity</strong>.'),
    '#options' => $commodities_options,
    '#default_value' => isset($widget_settings['extra_settings']['commodities']) ? $widget_settings['extra_settings']['commodities'] : TRUE,
  );
}

/**
 * Extra settings for the production per country (for one predefined country)
 */
function contentwidget_viz_groupedbarchart_production_per_country_settings(&$form, &$form_state, &$widget_settings) {
  // We basically re-use previously define settings callback with little adjustments.
  contentwidget_viz_groupedbarchart_production_countries_settings($form, $form_state, $widget_settings);
  unset($form['expose_year']);
}

/**
 * Small helper callback that returns the range of available years.
 */
function contentwidget_viz_groupedbarchart_production_get_years_range() {
  // Better to make just 1 query and then a PHP loop, vs having 2 or 4 queries;
  $query = db_select('eiti_summary_data', 'sd');
  $query->fields('sd', array('year_start', 'year_end'));
  $query->condition('status', TRUE);
  $result = $query->execute();
  $results = $result->fetchAll();

  // Flat the values.
  $values = array();
  foreach ($results as $result) {
    $values[] = $result->year_start;
    $values[] = $result->year_end;
  }
  // Sort'em.
  sort($values);

  $min = array_shift($values);
  $max = array_pop($values);

  $year_min = format_date($min, 'custom', 'Y');
  $year_max = format_date($max, 'custom', 'Y');
  $years = range($year_min, $year_max);

  return drupal_map_assoc($years);
}
