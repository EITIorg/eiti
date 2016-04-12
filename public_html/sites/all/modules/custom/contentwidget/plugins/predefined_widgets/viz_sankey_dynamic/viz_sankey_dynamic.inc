<?php

/**
 * @file
 * Provides a custom Visualization - Sankey Chart with Data from the Summary Data.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Visualization: Sankey Chart dynamic',
  'description' => 'A sankey chart with data pulled from the Summary Data.',
  'render callback' => 'contentwidget_viz_sankey_dynamic_render',
  'settings form' => 'contentwidget_viz_sankey_dynamic_settings',
  'defaults' => array(
    'sankey_settings' => array(
      'data_type' => '',
    ),
    'extra_settings' => array(),
  ),
);

/**
 * Render callback for the 'Sankey Chart' predefined widget.
 */
function contentwidget_viz_sankey_dynamic_render($plugin, $widget_settings, $entity, $langcode) {
  $block = array();

  // If we're in Panelizer, we don't want to create the whole chart there, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map']) || in_array('editor', $menu_item['map'])) {
    return array('#markup' => t('Configured Sankey Widget - with dynamic data (from Summary Data).'));
  }

  // Prepare the ID.
  $viz_id = implode('_', array($plugin['name'], $entity->fpid, $entity->vid));
  $block['widget'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => $viz_id,
      'class' => array(drupal_html_class($plugin['name']), 'eiti-visualization-wrapper'),
    )
  );

  // Load the library.
  $library = libraries_load('eitiChartWidgets', 'minified');
  if (empty($library)) {
    return array('#markup' => t('Charts library could not be loaded.'));
  }

  $endpoints = contentwidget_viz_sankey_dynamic_get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['sankey_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = contentwidget_viz_sankey_dynamic_get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['sankey_settings']['data_type']];
  $settings = array(
    'type' => 'Sankey',
    'name' => $js_settings['title'],
    'width' => 800,
    'height' => 600,
    'margin' => array(
      'top' => 1,
      'bottom' => 1,
      'left' => 6,
      'right' => 1
    ),
    'container' => $viz_id,
    'endpoint' => $endpoint,
  );

  // As dynamic as we tried to be, this is a little exception.
  if ($widget_settings['sankey_settings']['data_type'] == 'disbursed_by_company_per_country') {
    // Yes, because I HAVE NO IDEA how to load ctools / panels / panelizer contexts properly.
    $country = menu_get_object('implementing_country');
    if (!empty($country)) {
      $settings['endpoint'] .= '?filter[country_iso]=' . $country->iso;
      $settings['endpoint'] .= '&filter[years_from]=' . $widget_settings['extra_settings']['years']['years_from'];
      $settings['endpoint'] .= '&filter[years_to]=' . $widget_settings['extra_settings']['years']['years_to'];
      $settings['endpoint'] .= '&filter[limit]=' . $widget_settings['extra_settings']['company_number'];
      $settings['name'] .= t(" (Top @number in @min - @max (USD))", array(
        '@number' => $widget_settings['extra_settings']['company_number'],
        '@min' => $widget_settings['extra_settings']['years']['years_from'],
        '@max' => $widget_settings['extra_settings']['years']['years_to'],
      ));
    }
    else {
      return array('#markup' => t('This widget requires country context.'));
    }

  }

  // Wrap things up.
  $settings = array(
    $viz_id => $settings,
  );
  drupal_add_js(array('contentWidgets' => $settings), array('type' => 'setting', 'scope' => 'footer'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Sankey Chart' predefined widget.
 */
function contentwidget_viz_sankey_dynamic_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $plugin_filepath = $plugin['path'] . '/' . $plugin['file'];;
  $form_state['build_info']['files'][$plugin_filepath] = $plugin_filepath;

  // Extract these for possible re-use.
  $entity = $element['#entity'];
  $entity_type = $element['#entity_type'];
  $language = $element['#language'];
  $field = $element['#field_name'];
  $ctools_contexts = isset($form_state['contexts']['panelizer']) ? $form_state['contexts']['panelizer'] : array();

  // Settings.
  $settings_form['sankey_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sankey Chart Settings'),
    '#description' => t('Generic sankey bar chart settings.')
  );

  // We want to cut out those who's context is required.
  $type_options = contentwidget_viz_sankey_dynamic_get_data_types('options');
  $items = contentwidget_viz_sankey_dynamic_get_data_types();
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
  $wrapper_id = 'extra-settings-sankey-dynamic';
  $settings_form['sankey_settings']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#description' => t('Please select which data would you like to pull from the Summary Data.'),
    '#default_value' => isset($widget_settings['sankey_settings']['data_type']) ? $widget_settings['sankey_settings']['data_type'] : '',
    '#options' => $type_options,
    '#ajax' => array(
      'callback' => 'contentwidget_viz_sankey_dynamic_ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = contentwidget_viz_sankey_dynamic_get_data_types('extra settings');
  $settings_form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Settings'),
    '#prefix' => '<div id="' . $wrapper_id . '">',
    '#suffix' => '</div>',
  );

  if (isset($extra_settings[$widget_settings['sankey_settings']['data_type']])) {
    $function = $extra_settings[$widget_settings['sankey_settings']['data_type']];
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
function contentwidget_viz_sankey_dynamic_ajax_settings($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];

  // Polish the #parents.
  $key = array_search('data_type', $parents, TRUE);
  unset($parents[$key]);
  $key = array_search('sankey_settings', $parents, TRUE);
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
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_sankey_dynamic']['extra_settings'];
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
function contentwidget_viz_sankey_dynamic_get_data_types($return = FALSE) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['disbursed_by_company_per_country'] = array(
    'label' => t('Country: Disbursed Revenues By Company'),
    'endpoint' => '/api/v1.0/sankey/disbursed_by_companies_per_country',
    'title' => t('Disbursements by Company'),
    'extra settings' => 'contentwidget_viz_sankeys_dynamic_disbursed_revenues_settings',
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
        $output[$key]['title'] = $item['title'];
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
 * Extra settings for our disbursed revenues sankey widget.
 */
function contentwidget_viz_sankeys_dynamic_disbursed_revenues_settings(&$form, &$form_state, $widget_settings, $ctools_contexts) {
//  $form['no-settings'] = array('#markup' => t('No extra settings for this sankey chart.'));
  $country = $ctools_contexts->data;
  $years = contentwidget_viz_sankeys_dynamic_get_years_min_max($country->id);
  $min_year = format_date($years['min'], 'custom', 'Y');
  $max_year = format_date($years['max'], 'custom', 'Y');
  $years_options = drupal_map_assoc(range($min_year, $max_year));

  $form['years'] = array(
    '#type' => 'fieldset',
    '#title' => t('Years'),
    '#description' => t('Years to select the data from.'),
    '#element_validate' => array('contentwidget_viz_sankey_form_validation'),
  );
  $form['years']['years_from'] = array(
    '#type' => 'select',
    '#title' => t('From Year'),
    '#options' => $years_options,
    '#default_value' => isset($widget_settings['extra_settings']['years']['years_from']) ? $widget_settings['extra_settings']['years']['years_from'] : $min_year,
    '#prefix' => '<div class="container-inline">',
  );
  $form['years']['years_to'] = array(
    '#type' => 'select',
    '#title' => t('To Year'),
    '#options' => $years_options,
    '#default_value' => isset($widget_settings['extra_settings']['years']['years_to']) ? $widget_settings['extra_settings']['years']['years_to'] : $max_year,
    '#suffix' => '</div>',
  );
  $company_number_options = drupal_map_assoc(array(5, 10, 15, 20));
  $form['company_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Companies'),
    '#description' => t("Please specify the number of companies you want to include. Note: <em>We can't include all companies, because the output will be unreadable</em>."),
    '#options' => $company_number_options,
    '#default_value' => isset($widget_settings['extra_settings']['company_number']) ? $widget_settings['extra_settings']['company_number'] : 10,
  );
}

/**
 * Our small custom validation.
 */
function contentwidget_viz_sankey_form_validation($element, $form_state) {
  $parents_year_from = $element['years_from']['#parents'];
  $parents_year_to = $element['years_to']['#parents'];
  $year_from = drupal_array_get_nested_value($form_state['values'], $parents_year_from);
  $year_to = drupal_array_get_nested_value($form_state['values'], $parents_year_to);
  if ($year_from > $year_to) {
    form_set_error(implode('][', $element['#parents']), t('Please make sure you have selected a valid range (Years From -> Years To).'));
  }
}

/**
 * Small helper callback that returns the range of available years.
 */
function contentwidget_viz_sankeys_dynamic_get_years_min_max($country_id) {
  // Better to make just 1 query and then a PHP loop, vs having 2 or 4 queries;
  $query = db_select('eiti_summary_data', 'sd');
  $query->fields('sd', array('year_start', 'year_end'));
  $query->condition('status', TRUE);
  $query->condition('country_id', $country_id);
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

  return array(
    'min' => $min,
    'max' => $max,
  );
}
