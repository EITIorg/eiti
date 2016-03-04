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
  'render callback' => 'contentwidget_viz_stackedbar_dynamic_render',
  'settings form' => 'contentwidget_viz_stackedbar_dynamic_settings',
  'defaults' => array(
    'stackedbar_settings' => array(
      'data_type' => '',
    ),
    'extra_settings' => array(
      'taxes' => array(),
    ),
  ),
);

/**
 * Render callback for the 'StackedBar Chart' predefined widget.
 */
function contentwidget_viz_stackedbar_dynamic_render($plugin, $widget_settings, $entity, $langcode) {
  $block = array();

  // If we're in Panelizer, we don't want to create the whole chart there, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map'])) {
    return array('#markup' => t('Configured Stacked Bar Widget - with dynamic data (from Summary Data).'));
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

  $endpoints = contentwidget_viz_stackedbar_dynamic_get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['stackedbar_settings']['data_type']];

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = contentwidget_viz_stackedbar_dynamic_get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['stackedbar_settings']['data_type']];
  $settings = array(
    'type' => 'StackedBar',
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
    'endpoint' => $endpoint,
  );

  // As dynamic as we tried to be, this is a little exception.
  if ($widget_settings['stackedbar_settings']['data_type'] == 'government_taxes') {
    // We want to pass the commodities to the filter and the country from the context.
    $settings['endpoint'] = $endpoint . '?filter[gfs_code]=' . implode(',', $widget_settings['extra_settings']['taxes']);
    // Yes, because I HAVE NO IDEA how to load ctools / panels / panelizer contexts properly.
    $country = menu_get_object('implementing_country');
    if (!empty($country)) {
      $settings['endpoint'] .= '&filter[country_iso]=' . $country->iso;
    }
    else {
      return array('#markup' => t('This widget requires country context.'));
    }
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
 * Settings form for the 'StackedBar Chart' predefined widget.
 */
function contentwidget_viz_stackedbar_dynamic_settings(&$element, &$form_state, $plugin, $widget_settings) {
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
  $type_options = contentwidget_viz_stackedbar_dynamic_get_data_types('options');
  $items = contentwidget_viz_stackedbar_dynamic_get_data_types();
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
    '#default_value' => isset($widget_settings['stackedbar_settings']['data_type']) ? $widget_settings['stackedbar_settings']['data_type'] : '',
    '#options' => $type_options,
    '#ajax' => array(
      'callback' => 'contentwidget_viz_stackedbar_dynamic_ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = contentwidget_viz_stackedbar_dynamic_get_data_types('extra settings');
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
function contentwidget_viz_stackedbar_dynamic_ajax_settings($form, $form_state) {
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
function contentwidget_viz_stackedbar_dynamic_get_data_types($return = NULL) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['government_taxes'] = array(
    'label' => t('Country: Government Tax Revenue'),
    'endpoint' => '/api/v1.0/stacked_bar/government_taxes',
    'extra settings' => 'contentwidget_viz_stackedbar_government_taxes_country_settings',
    'x-axis' => t('Years'),
    'y-axis' => t('Government Revenue (normalized to USD)'),
    'title' => t('Government Tax Revenue'),
    'description' => t('Revenue the government obtained from taxes (by tax type)'),
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
 * Extra settings for the Governmental Taxes per Country.
 */
function contentwidget_viz_stackedbar_government_taxes_country_settings(&$form, &$form_state, &$widget_settings, $ctools_contexts = array()) {
  // Load all GFS codes so we can Identify the parent Taxes GFS.
  $gfs_codes_all = eitientity_gfs_code_get_by_bundle('gfs_code');
  $gfs_taxes_parent = array();
  foreach ($gfs_codes_all as $gfs) {
    if ($gfs->code == '11E') {
      $gfs_taxes_parent = $gfs;
      break;
    }
  }
  // Now that we've located it, load the tree.
  $gfs_tree = eitientity_gfs_code_get_tree($gfs_taxes_parent->id);
  $gfs_options = array();
  foreach ($gfs_tree as $gfs) {
    $gfs_options[$gfs->id] = t('@name (@code)', array(
      '@name' => $gfs->name,
      '@code' => $gfs->code,
    ));
  }
  // And now we want to eliminate all the groups (if anyone has this GFS as a parent, it's OUT).
  // Why? Because they have no values.
  $gfs_ids = array_keys($gfs_options);
  foreach ($gfs_codes_all as $gfs) {
    if (in_array($gfs->parent, $gfs_ids)) {
      unset($gfs_options[$gfs->parent]);
    }
  }
  $form['taxes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Please select the taxes you want to display.'),
    '#description' => t('You may specify the taxes you want to be displayed in the widget.'),
    '#options' => $gfs_options,
    '#default_value' => isset($widget_settings['extra_settings']['taxes']) ? $widget_settings['extra_settings']['taxes'] : TRUE,
  );
}
