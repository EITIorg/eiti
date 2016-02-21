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
  'render callback' => 'contentblock_viz_groupedbarchart_dynamic_render',
  'settings form' => 'contentblock_viz_groupedbarchart_dynamic_settings',
  'defaults' => array(
    'extra_settings' => array(
      'expose_year' => TRUE,
      'commodities' => array(),
    ),
  ),
);

/**
 * Render callback for the 'Bar Chart' predefined widget.
 */
function contentblock_viz_groupedbarchart_dynamic_render($plugin, $widget_settings, $entity, $langcode) {
  $block = array();

  // Prepare the ID.
  $viz_id = implode('_', array($plugin['name'], $entity->fpid, $entity->vid));
  if ($widget_settings['extra_settings']['expose_year']) {
    $available_years_options = contentblock_viz_groupedbarchart_production_get_years_range();
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
  }
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
    drupal_set_message(t('Please make sure you have the "eiti-charts" library.'));
  }

  $endpoints = contentblock_viz_groupedbarchart_dynamic_get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['barchart_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $settings = array(
    $viz_id => array(
      'type' => 'GroupedBar',
      'name' => t('Production Chart for !year', array('!year' => $default_year)),
      'width' => 1300,
      'height' => 400,
      'margin' => array(
        'top' => 10,
        'bottom' => 50,
        'left' => 100,
        'right' => 10
      ),
      'xlabel' => t('Countries'),
      'ylabel' => t('Production Volumes (Sm3)'),
      'description' => t('Production volumes for !year.', array('!year' => $default_year)),
      'container' => $viz_id,
      'expose_year' => $widget_settings['extra_settings']['expose_year'],
      'endpoint' =>  $endpoint . '?filter[indicator]=' . implode(',', $widget_settings['extra_settings']['commodities']),
      'endpoint_year' =>  $endpoint . '?filter[year][0]=' . $default_year . '&filter[indicator]=' . implode(',', $widget_settings['extra_settings']['commodities']),
      'current_year' => $default_year,
      'year_selector_class' => drupal_html_class($viz_id . '-year-selector'),
      'description_year' => t('Production volumes for'),
      'name_year' => t('Production Chart for'),
    ),
  );
  drupal_add_js(array('contentwidgets' => $settings), array('type' => 'setting', 'scope' => 'footer'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Bar Chart' predefined widget.
 */
function contentblock_viz_groupedbarchart_dynamic_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Settings.
  $settings_form['barchart_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Grouped Bar Chart Settings'),
    '#description' => t('Generic grouped bar chart settings.')
  );

  $type_options = contentblock_viz_groupedbarchart_dynamic_get_data_types('options');
  array_unshift($type_options, t('- Select -'));
  $settings_form['barchart_settings']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#description' => t('Please select which data would you like to pull from the Summary Data.'),
    '#default_value' => isset($widget_settings['barchart_settings']['data_type']) ? $widget_settings['barchart_settings']['data_type'] : '',
    '#options' => $type_options,
    '#ajax' => array(
      'callback' => 'contentblock_viz_groupedbarchart_dynamic_ajax_settings',
      'event' => 'change',
      'wrapper' => 'extra-settings',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = contentblock_viz_groupedbarchart_dynamic_get_data_types('extra settings');
  $settings_form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Settings'),
    '#prefix' => '<div id="extra-settings">',
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
function contentblock_viz_groupedbarchart_dynamic_ajax_settings($form, $form_state) {
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
    return $form['field_fpp_widget'][LANGUAGE_NONE][0]['settings']['viz_groupedbar_dynamic']['extra_settings'];
  }
}

/**
 * Returns all data type options.
 *
 * @param string $return
 *   This can be either: 'options', 'endpoint', 'extra settings'.
 *
 * @return array
 *   The Return array depends on the $return parameter you specify, either it's
 *   an array of labels for the options, or it's an array of api endpoints.
 */
function contentblock_viz_groupedbarchart_dynamic_get_data_types($return) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['production_country'] = array(
    'label' => t('Production: By Country'),
    'endpoint' => 'api/v1.0/grouped_bar/production',
    'extra settings' => 'contentblock_viz_groupedbarchart_production_countries_settings'
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
    }
  }

  // If nothing was set as a return string, then just return plain items.
  if (!$return) {
    return $items;
  }
  return $output;
}

/**
 * Extra settings for the production by country.
 */
function contentblock_viz_groupedbarchart_production_countries_settings(&$form, &$form_state, &$widget_settings) {
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
 * Small helper callback that returns the range of available years.
 */
function contentblock_viz_groupedbarchart_production_get_years_range() {
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
