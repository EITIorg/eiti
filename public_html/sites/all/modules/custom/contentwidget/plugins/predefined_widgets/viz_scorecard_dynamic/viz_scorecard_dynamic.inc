<?php

/**
 * @file
 * Provides a custom Visualization - Scorecard Table
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Visualization: Scorecard dynamic',
  'description' => 'Scorecard based on score data',
  'render callback' => 'contentwidget__viz_scorecard_dynamic__render',
  'settings form' => 'contentwidget__viz_scorecard_dynamic__settings',
  'defaults' => array(
    'scorecard_settings' => array(
      'data_type' => '',
    ),
    'extra_settings' => array(),
  ),
);

/**
 * Render callback for the 'Scorecard' predefined widget.
 */
function contentwidget__viz_scorecard_dynamic__render($plugin, $widget_settings, $entity, $langcode) {
  // If we're in Panelizer, we don't want to create the whole chart there, bail.
  $menu_item = menu_get_item();
  if (in_array('panelizer', $menu_item['map']) || in_array('editor', $menu_item['map'])) {
    return array('#markup' => t('Configured Scorecard Widget - with dynamic data (from Score Data).'));
  }

  // Load the library.
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
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => $identifier,
      'class' => array(
        'eiti-chart-widget',
        drupal_html_class('eiti-chart-widget--' . $plugin['name']),
      ),
    ),
    '#weight' => 10,
  );

  $endpoints = _contentwidget__viz_scorecard_dynamic__get_data_types('endpoint');
  $endpoint = $endpoints[$widget_settings['scorecard_settings']['data_type']];

  // Build year select options.
  $default_year = $widget_settings['extra_settings']['year'];
  $available_years_options = array();
  $counter_words = array(t('First'), t('Second'), t('Third'), t('Fourth'), t('Fifth'),
    t('Sixth'), t('Seventh'), t('Eighth'), t('Ninth'), t('Tenth'));
  if ($widget_settings['extra_settings']['country']) {
    $score_data = eitientity_score_data_lookup_by_country($widget_settings['extra_settings']['country']);
    if ($score_data !== FALSE && !empty($score_data)) {
      foreach ($score_data as $score_data_delta => $score_data_entity) {
        if (!entity_access('view', 'score_data', $score_data_entity)) {
          unset($score_data[$score_data_delta]);
          continue;
        }
        // Set year to latest if it's not set, but one is available.
        if (!$widget_settings['extra_settings']['year'] && $score_data_entity->year > $default_year) {
          $default_year = $score_data_entity->year;
        }
        $available_years_options[$score_data_entity->year] = $score_data_entity->year;
      }
      ksort($available_years_options);
      $counter = 0;
      foreach ($available_years_options as $y_key => $y_val) {
        $available_years_options[$y_key] = $counter_words[$counter] . ' ' . t('Validation') . ' (' . $y_val . ')';
        $counter++;
      }
    }
  }

  // Pdf link.
  $pdf_link = url(
    'scorecard-pdf',
    array(
      'query' => array(
        'filter[country]' => $widget_settings['extra_settings']['country'],
        'filter[year]' => $default_year,
      )
    )
  );
  $pdf_link_plain = url('scorecard-pdf');
  $pdf_markup = '<div class="pdf-link">';
  $pdf_markup .= '<a target="_blank" data-plain-link="' . $pdf_link_plain . '" href="' . $pdf_link . '">' . t('Download PDF') . '</a>';
  $pdf_markup .= '</div>';
  $pdf_markup .= '<div class="pdf-description">';
  $pdf_markup .= t('We recommend using Adobe Acrobat PDF reader to access all content and features in this document. You can download the program for free here <a href="https://get.adobe.com/reader/" target="_blank">https://get.adobe.com/reader/</a>');
  $pdf_markup .= '</div>';
  $block['pdf'] = array('#markup' => $pdf_markup);

  $year_selector_class = drupal_html_class($identifier . '--sc-year-selector');
  $block['sc_widget_year_selector'] = array(
    '#type' => 'select',
    '#name' => 'sc_year_selector',
    '#title' => t('Validation'),
    '#title_display' => 'invisible',
    '#options' => $available_years_options,
    '#value' => $default_year,
    '#attributes' => array(
      'class' => array($year_selector_class),
    ),
  );

  // Send the settings, so that later we can load them in our behaviour.
  $js_settings = _contentwidget__viz_scorecard_dynamic__get_data_types('js settings');
  $js_settings = $js_settings[$widget_settings['scorecard_settings']['data_type']];
  $country_entity = entity_load_single('implementing_country', $widget_settings['extra_settings']['country']);
  $settings = array(
    'type' => 'Scorecard',
    'name' => $country_entity->name . ' - ' . $available_years_options[$default_year],
    'country' => $country_entity->name,
    'width' => 800,
    'height' => 600,
    'margin' => array(
      'top' => 1,
      'bottom' => 1,
      'left' => 6,
      'right' => 1
    ),
    'container' => $identifier,
    'endpoint' => $endpoint,
    'filter_endpoint' => $endpoint,
    'year_selector_class' => $year_selector_class,
    'endpoint_data' => array(),
  );

  // As dynamic as we tried to be, this is a little exception.
  if ($widget_settings['scorecard_settings']['data_type'] == 'score_data') {
    $settings['endpoint'] .= '?filter[country]=' . $widget_settings['extra_settings']['country'];
    $settings['endpoint'] .= '&filter[year]=' . $default_year;
    $settings['endpoint_data']['filter']['country'] = $widget_settings['extra_settings']['country'];
    $settings['endpoint_data']['filter']['year'] = $default_year;
  }

  // Wrap things up.
  $settings = array(
    $identifier => $settings,
  );
  //drupal_add_js(array('contentWidgets' => $settings), array('type' => 'setting', 'scope' => 'footer'));
  drupal_add_js(array('contentWidgets' => $settings), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'contentwidget') . '/js/content-widgets.js', array('scope' => 'footer'));
  return $block;
}

/**
 * Settings form for the 'Scorecard' predefined widget.
 */
function contentwidget__viz_scorecard_dynamic__settings(&$element, &$form_state, $plugin, $widget_settings) {
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
  $settings_form['scorecard_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scorecard Chart Settings'),
    '#description' => t('Generic scorecard table settings.')
  );

  // We want to cut out those who's context is required.
  $type_options = _contentwidget__viz_scorecard_dynamic__get_data_types('options');
  $items = _contentwidget__viz_scorecard_dynamic__get_data_types();
  $form_state['required_ctools_contexts_available'] = FALSE;
  foreach ($type_options as $option_key => $label) {
    if (!empty($items[$option_key]['context required']) && (empty($ctools_contexts) || $ctools_contexts->plugin !== $items[$option_key]['context required'])) {
      unset($type_options[$option_key]);

      if (!isset($form_state['pane'])) {
        $settings_form['scorecard_settings']['no-pane'] = array(
          '#markup' => '<strong>'. t('Please configure this pane inside of the "Customize display > Content" page.') . '</strong>',
        );
        return $settings_form;
      }
    }
  }
  $form_state['required_ctools_contexts_available'] = TRUE;

  array_unshift($type_options, t('- Select -'));
  $wrapper_id = 'extra-settings-scorecard-dynamic';
  $settings_form['scorecard_settings']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#description' => t('Please select which data would you like to pull from the Summary Data.'),
    '#default_value' => isset($widget_settings['scorecard_settings']['data_type']) ? $widget_settings['scorecard_settings']['data_type'] : '',
    '#options' => $type_options,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__viz_scorecard_dynamic__ajax_settings',
      'event' => 'change',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Check if there are any extra settings.
  $extra_settings = _contentwidget__viz_scorecard_dynamic__get_data_types('extra settings');
  $settings_form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Settings'),
    '#prefix' => '<div id="' . $wrapper_id . '">',
    '#suffix' => '</div>',
  );

  if (isset($extra_settings[$widget_settings['scorecard_settings']['data_type']])) {
    $function = $extra_settings[$widget_settings['scorecard_settings']['data_type']];
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
function _contentwidget__viz_scorecard_dynamic__ajax_settings($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];

  // Polish the #parents.
  $key = array_search('data_type', $parents, TRUE);
  unset($parents[$key]);
  $key = array_search('scorecard_settings', $parents, TRUE);
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
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_scorecard_dynamic']['extra_settings'];
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
function _contentwidget__viz_scorecard_dynamic__get_data_types($return = FALSE) {
  $items = array();

  // ####### DEFINE ITEMS ######
  $items['score_data'] = array(
    'label' => t('Country: Score data'),
    'endpoint' => '/api/v1.0/score_data',
    'title' => t('Scoredata by Country'),
    'extra settings' => '_contentwidget__viz_scorecard_dynamic_settings',
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
 * Extra settings for our widget.
 */
function _contentwidget__viz_scorecard_dynamic_settings(&$form, &$form_state, $widget_settings, $ctools_contexts) {
  $entity = $ctools_contexts->data;
  if ($entity instanceof ImplementingCountryEntity) {
    $default_country = $entity->id;
  }
  else {
    $default_country = '';
  }

  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'implementing_country')
    ->propertyCondition('status', '1');
  $results = $efq->execute();
  $countries = entity_load('implementing_country', array_keys($results['implementing_country']));
  $country_options = array();
  foreach ($countries as $entity_id => $country) {
    $country_options[$entity_id] = $country->name;
  }
  asort($country_options);
  $country_options = array('' => '- Select a Country') + $country_options;
  $form['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#description' => t("Please specify for which country this Scorecard is for..."),
    '#options' => $country_options,
    '#default_value' => isset($widget_settings['extra_settings']['country']) ? $widget_settings['extra_settings']['country'] : $default_country,
    '#ajax' => array(
      'callback' => '_contentwidget__viz_scorecard_dynamic__ajax_settings_year',
      'event' => 'change',
      'wrapper' => 'extra-settings-scorecard-dynamic-year',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Now we need to find out what are all the possible years for a certain country.
  $country_id = isset($widget_settings['extra_settings']['country']) ? $widget_settings['extra_settings']['country'] : $default_country;
  if (empty($country_id)) {
    $year_options = array('' => '- Select a Country First');
  }
  else {
    $year_options = array('' => '- Select Year');
    $score_data = eitientity_score_data_lookup_by_country($country_id);
    if ($score_data !== FALSE && !empty($score_data)) {
      foreach ($score_data as $score_data_delta => $score_data_entity) {
        // This will keep'em unique.
        $year_options[$score_data_entity->year] = $score_data_entity->year;
      }
      asort($year_options);
    }
    else {
      $year_options = array('' => '- Country w/o data, Pick another country');
    }
  }
  $form['year'] = array(
    '#type' => 'select',
    '#title' => t('Year'),
    '#description' => t("Please specify for which year the Scorecard is for..."),
    '#options' => $year_options,
    '#default_value' => isset($widget_settings['extra_settings']['year']) ? $widget_settings['extra_settings']['year'] : '',
    '#prefix' => '<div id="extra-settings-scorecard-dynamic-year">',
    '#suffix' => '</div>',
  );
}

/**
 * Our small custom validation.
 */
function contentwidget_viz_scoredata_form_validation($element, $form_state) {
}
/**
 * Small ajax function that returns all the possible years for the selected country.
 */
function _contentwidget__viz_scorecard_dynamic__ajax_settings_year($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];

  // Polish the #parents.
  $key = array_search('data_type', $parents, TRUE);
  unset($parents[$key]);
  $key = array_search('scorecard_settings', $parents, TRUE);
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
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['viz_scorecard_dynamic']['extra_settings']['year'];
  }
}

