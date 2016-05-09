<?php

/**
 * @file
 * Provides a custom Fact Blocks widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Fact Blocks'),
  'description' => t('Widget that contains a few key facts.'),
  'render callback' => 'contentwidget__fact_blocks__render',
  'settings form' => 'contentwidget__fact_blocks__settings',
  'defaults' => array(
    'facts_number' => 4,
  ),
);

/**
 * Render callback for the 'Fact Blocks' predefined widget.
 */
function contentwidget__fact_blocks__render($plugin, $widget_settings, $entity, $langcode) {
  // Prepare the wrapper.
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
    )
  );

  $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $langcode);
  if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
    $featured_image_data = $entity->field_fpp_background_image[$image_field_language][0];

    // Use the featured image as background image.
    $selector_prefix = implode('-', array('fieldable_panels_pane', entity_id('fieldable_panels_pane', $entity)));
    helpertheme_get_background_image_with_overlay($block, $featured_image_data, $selector_prefix);
  }
  else {
    $block['#attributes']['class'][] = 'no-background-image';
  }

  $block['overlay']['#attributes']['class'][] = 'single-fluid-row-wrapper';

  // And now prepare the list of facts that we'll render in theme_item_list.
  $fact_items = array();
  for ($delta = 0; $delta < $widget_settings['facts_number']; $delta++) {
    $fact_block = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'fact-block-wrapper',
          'fact-block-wrapper--' . $delta,
        ),
      ),
    );

    $fact_block['media_block'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-icon-value-suffix-wrapper',
          'mobject',
          'mobject--small',
          'clearfix',
        ),
      ),
    );
    $fact_block['media_block']['icon_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-icon',
          'group-side',
        ),
      ),
    );

    $icon = _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'icon');
    $options = array(
      'height' => '3em',
      'width' => '3em',
    );
    $fact_block['media_block']['icon_wrapper']['icon'] = array(
      '#markup' => helpertheme_get_svg_icon($icon, $options),
    );

    $fact_block['media_block']['value_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'widget-value',
          'group-main',
        ),
      ),
    );

    // There are 2 cases: manually entered data, and computed data (which requires
    // a callback function that returns either the value, or array with value and
    // the suffix.
    $value = array(
      'value' => t('N/A'),
      'suffix' => '',
    );
    $value_type = _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'type');
    if ($value_type == 'manual') {
      $value['value'] = _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'value');
      $value['suffix'] = _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'suffix');
    }
    elseif ($value_type == 'computed'){
      $value_key = _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'computed_value');
      $functions = _contentwidget__fact_blocks__get_computed_values('functions');
      if (function_exists($functions[$value_key])) {
        $value = $functions[$value_key]();
      }
    }

    $fact_block['media_block']['value_wrapper']['value'] = array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#attributes' => array(
        'class' => array('value'),
      ),
      '#value' => check_plain($value['value']),
    );

    if (!empty($value['suffix'])) {
      $fact_block['media_block']['value_wrapper']['suffix'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('suffix')
        ),
        '#value' => check_plain($value['suffix']),
      );
    }

    $fact_block['description'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#attributes' => array(
        'class' => array('widget-description')
      ),
      '#value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'description'),
    );

    $fact_items[$delta] = render($fact_block);
  }

  $block['overlay']['links'] = array(
    '#theme' => 'item_list',
    '#items' => $fact_items,
    '#type' => 'ul',
    '#title' => '',
    '#attributes' => array(
      'class' => array('fact-blocks-wrapper'),
    ),
  );

  return $block;
}

/**
 * Settings form for the 'Ket Facts' predefined widget.
 */
function contentwidget__fact_blocks__settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  // Special case: we're in IEF. We want to get the REAL settings.
  if (!empty($form_state['inline_entity_form']) && !empty($form_state['triggering_element']['#ajax']) && $form_state['triggering_element']['#ajax']['callback'] == '_contentwidget__fact_blocks__settings_ajax') {
    $parents = $form_state['triggering_element']['#parents'];
    $get_rid_off_arr = array('facts_number');
    $parents = array_diff($parents, $get_rid_off_arr);
    $widget_settings = drupal_array_get_nested_value($form_state['values'], $parents);
  }

  $settings_form = array(
    '#type' => 'fieldset',
    '#title' => t('Fact Blocks'),
    '#collapsible' => FALSE,
    '#prefix' => '<div id="fact-blocks-wrapper">',
    '#suffix' => '</div>',
  );

  $settings_form['facts_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Fact Blocks'),
    '#options' => drupal_map_assoc(range(1, 4)),
    '#description' => t('Please specify the number of facts you want to use.'),
    '#default_value' => $widget_settings['facts_number'],
    '#ajax' => array(
      'callback' => '_contentwidget__fact_blocks__settings_ajax',
      'event' => 'change',
      'wrapper' => 'fact-blocks-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Create the fact widget and all that it includes.
  // Get the options here (we don't want to do it in the loop).
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));
  $type_options = array(
    'manual' => t('Manual'),
    'computed' => t('Computed'),
  );
  $computed_options = _contentwidget__fact_blocks__get_computed_values('options');

  for ($delta = 0; $delta < $widget_settings['facts_number']; $delta++) {
    $settings_form[$delta] = array(
      '#type' => 'fieldset',
      '#title' => t('Key Fact #!number:', array('!number' => ($delta + 1))),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $settings_form[$delta]['icon'] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'icon'),
    );
    $settings_form[$delta]['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#description' => t('Description of this key fact.'),
      '#size' => 50,
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'description'),
    );
    $settings_form[$delta]['type'] = array(
      '#type' => 'radios',
      '#title' => t('Fact Type'),
      '#description' => t('Type of the fact.'),
      '#options' => $type_options,
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'type'),
    );

    // For cases where field parents are set.
    if (!empty($element['#field_parents'])) {
      $parents = $element['#field_parents'];
      $field_name = array_shift($parents);
      $field_parents_path = $field_name . '[' . implode('][', $parents) . ']';

      $entity_language = entity_language('fieldable_panels_pane', $form_state['entity']);
      $widget_field_language = field_language('fieldable_panels_pane', $form_state['entity'], 'field_fpp_widget', $entity_language);
      $field_name_prefix = $field_parents_path . '[' . $element['#field_name'] . '][' . $widget_field_language . '][0][settings][fact_blocks]';
    }
    else {
      $field_name_prefix = $element['#field_name'] . '[und][0][settings][fact_blocks]';
    }

    $settings_form[$delta]['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Key Fact Value'),
      '#size' => 10,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'value'),
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[' . $delta . '][type]"]' => array('value' => 'manual')),
        ),
      ),
    );
    $settings_form[$delta]['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Value Suffix'),
      '#description' => t('Example: "T", "B$", "%", etc.'),
      '#size' => 10,
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'suffix'),
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[' . $delta . '][type]"]' => array('value' => 'manual')),
        ),
      ),
    );
    $settings_form[$delta]['computed_value'] = array(
      '#type' => 'select',
      '#title' => t('Computed Value'),
      '#description' => t('Pick the value you want to output.'),
      '#options' => $computed_options,
      '#default_value' => _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, 'computed_value'),
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[' . $delta . '][type]"]' => array('value' => 'computed')),
        ),
      ),
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
 * @return string
 *  Returns the value of the setting.
 */
function _contentwidget__fact_blocks__get_property_value($widget_settings, $delta, $key) {
  return isset($widget_settings[$delta][$key]) ? $widget_settings[$delta][$key] : '';
}

/**
 * Return the array of options for the computed field.
 *
 * @param string $return
 *   This can be either: 'options' or 'functions'.
 *
 * @return array
 *   The Return array depends on the $return parameter you specify, either it's
 * an array of labels for the options, or it's an array of callback functions.
 */
function _contentwidget__fact_blocks__get_computed_values($return) {
  $items = array();

  // ####### DEFINE ITEMS ######
  // Please make sure you specify a nice label in format: "<Scope>: <Description>".
  // Also make sure that the function callback returns either value, or an array
  // which has 2 keys: value and suffix.
  $items['eiti_countries'] = array(
    'label' => t('Global: Countries Count'),
    'function' => '_contentwidget__fact_blocks__get_countries_count',
  );

  $output = array();
  foreach ($items as $key => $item) {
    switch ($return) {
      case 'options':
        $output[$key] = $item['label'];
        break;
      case 'functions':
        $output[$key] = $item['function'];
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
 * Custom function that returns the count of implementing countries.
 */
function _contentwidget__fact_blocks__get_countries_count() {
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'implementing_country')
    ->propertyCondition('status', '1')
    ->count()
    ->execute();

  return array(
    'value' => $result,
    'suffix' => '',
  );
}

/**
 * Ajax callback for the settings form.
 */
function _contentwidget__fact_blocks__settings_ajax($form, $form_state) {
  $parents = $form_state['triggering_element']['#parents'];
  $key = array_search('facts_number', $parents, TRUE);
  unset($parents[$key]);
  $exists = FALSE;
  $value = drupal_array_get_nested_value($form, $parents, $exists);

  if ($exists) {
    return $value;
  }
  else {
    $entity = $form_state['entity'];
    $entity_language = entity_language('fieldable_panels_pane', $entity);
    $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
    return $form['field_fpp_widget'][$widget_field_language][0]['settings']['fact_blocks'];
  }
}
