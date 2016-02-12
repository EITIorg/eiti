<?php

/**
 * @file
 * Provides a custom Key Facts widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Key Facts',
  'description' => 'Widget that contains a couple of key facts.',
  'render callback' => 'contentblock_key_facts_render',
  'settings form' => 'contentblock_key_facts_settings',
  'entity form alter' => 'contentwidget_key_facts_form_alter',
  'entity group alter' => 'contentwidget_key_facts_group_alter',
  'defaults' => array(
    'fact' => array(
      'facts_number' => 4,
    ),
  ),
);

/**
 * Render callback for the 'Key Facts' predefined widget.
 */
function contentblock_key_facts_render($plugin, $widget_settings, $entity, $langcode) {
  // Prepare the variables.
  if (isset($entity->field_cbw_key_facts['und'][0]) && $image_file = (object) $entity->field_cbw_key_facts['und'][0]) {
    $image_url = file_create_url($image_file->uri);
  }
  else {
    $image_url = FALSE;
  }

  // Prepare the wrapper.
  $block = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('wide-image-wrapper')
    )
  );
  if ($image_url) {
    $block['image'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#attributes' => array(
        'class' => array('background-image', 'wide-image'),
        'src' => $image_url
      )
    );
  }
  $block['overlay'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('overlay-wrapper'),
    )
  );

  // And now prepare the list of facts that we'll render in theme_item_list.
  $fact_items = array();
  for ($fact_count = 0; $fact_count < $widget_settings['fact']['facts_number']; $fact_count++) {
    $fact = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('icon-' . _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'icon')),
          drupal_html_class('fact-wrapper-' . $fact_count),
        ),
      ),
    );
    $fact['value_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(drupal_html_class('value-wrapper')),
      ),
    );

    // There are 2 cases: manually entered data, and computed data (which requires
    // a callback function that returns either the value, or array with value and
    // the suffix.
    $value_type = _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'type');
    if ($value_type == 'manual') {
      $fact['value_wrapper']['value'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('value'),
        ),
        '#value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'value'),
      );
      $fact['value_wrapper']['suffix'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('value-suffix')
        ),
        '#value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'value_suffix'),
      );
    }
    elseif ($value_type == 'computed'){
      $value_key = _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'compute_value');
      $functions = contentblock_key_fact_get_computed_values('functions');
      if (function_exists($functions[$value_key])) {
        $value = $functions[$value_key]();
      }
      else {
        $value = array(
          'value' => t('N/A'),
          'suffix' => '',
        );
      }
      $fact['value_wrapper']['value'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('value'),
        ),
        '#value' => isset($value['value']) ? $value['value']: $value,
      );
      $fact['value_wrapper']['suffix'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('value-suffix')
        ),
        '#value' => isset($value['suffix']) ? $value['suffix'] : '',
      );
    }
    $fact['description'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#attributes' => array(
        'class' => array('fact-description')
      ),
      '#value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'fact_description'),
    );
    $fact_items[] = drupal_render($fact);
  }

  $block['overlay']['facts'] = array(
    '#theme' => 'item_list',
    '#items' => $fact_items,
    '#type' => 'ul',
    '#title' => '',
    '#attributes' => array('class' => array('wide-image-fact-wrapper')),
  );

  return $block;
}

/**
 * Settings form for the 'Ket Facts' predefined widget.
 */
function contentblock_key_facts_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  $settings_form['fact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Key Facts:'),
    '#collapsible' => FALSE,
    '#prefix' => '<div id="fact-wrapper">',
    '#suffix' => '</div>',
  );
  $settings_form['fact']['facts_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Key Facts'),
    '#options' => drupal_map_assoc(range(1, 4)),
    '#description' => t('Please specify the number of facts you want to use.'),
    '#default_value' => $widget_settings['fact']['facts_number'],
    '#ajax' => array(
      'callback' => 'contentblock_key_facts_settings_ajax',
      'event' => 'change',
      'wrapper' => 'fact-wrapper',
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
  $computed_options = contentblock_key_fact_get_computed_values('options');

  for ($fact_count = 0; $fact_count < $widget_settings['fact']['facts_number']; $fact_count++) {
    $settings_form['fact']['fact_' . $fact_count] = array(
      '#type' => 'fieldset',
      '#title' => t('Key Fact #!number:', array('!number' => ($fact_count + 1))),
      '#collapsible' => FALSE,
    );

    $settings_form['fact']['fact_' . $fact_count]['icon_' . $fact_count] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'icon'),
    );
    $settings_form['fact']['fact_' . $fact_count]['fact_description_' . $fact_count] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#description' => t('Description of this key fact.'),
      '#size' => 50,
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'fact_description'),
    );
    $settings_form['fact']['fact_' . $fact_count]['type_' . $fact_count] = array(
      '#type' => 'radios',
      '#title' => t('Fact Type'),
      '#description' => t('Type of the fact.'),
      '#options' => $type_options,
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'type'),
    );

    $field_name_prefix = 'field_fpp_widget[und][0][settings][key_facts][fact]';
    $settings_form['fact']['fact_' . $fact_count]['value_' . $fact_count] = array(
      '#type' => 'textfield',
      '#title' => t('Key Fact Value'),
      '#size' => 10,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'value'),
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[fact_' . $fact_count . '][type_' . $fact_count .']"]' => array('value' => 'manual')),
        ),
      ),
    );
    $settings_form['fact']['fact_' . $fact_count]['value_suffix_' . $fact_count] = array(
      '#type' => 'textfield',
      '#title' => t('Value Suffix'),
      '#description' => t('Example: "T", "B$", "%", etc.'),
      '#size' => 10,
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'value_suffix'),
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[fact_' . $fact_count . '][type_' . $fact_count .']"]' => array('value' => 'manual')),
        ),
      ),
    );
    $settings_form['fact']['fact_' . $fact_count]['compute_value_' . $fact_count] = array(
      '#type' => 'select',
      '#title' => t('Computed Value'),
      '#description' => t('Pick the value you want to output.'),
      '#options' => $computed_options,
      '#default_value' => _contentblock_key_fact_get_property_value($widget_settings, $fact_count, 'compute_value'),
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name_prefix . '[fact_' . $fact_count . '][type_' . $fact_count .']"]' => array('value' => 'computed')),
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
 * @return
 *  Returns the value of the setting.
 */
function _contentblock_key_fact_get_property_value($widget_settings, $delta, $key) {
  $value = isset($widget_settings['fact']['fact_' . $delta][$key . '_' . $delta]) ? $widget_settings['fact']['fact_' . $delta][$key . '_' . $delta] : '';
  return $value;
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
function contentblock_key_fact_get_computed_values($return) {
  $items = array();

  // ####### DEFINE ITEMS ######
  // Please make sure you specify a nice label in format: "<Scope>: <Description>".
  // Also make sure that the function callback returns either value, or an array
  // which has 2 keys: value and suffix.
  $items['eiti_countries'] = array(
    'label' => t('Global: Countries Count'),
    'function' => 'contentblock_key_fact_get_countries_count',
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
function contentblock_key_fact_get_countries_count() {
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
function contentblock_key_facts_settings_ajax($form, $form_state) {
  // TODO: maybe we should check the language.
  return $form['field_fpp_widget'][LANGUAGE_NONE][0]['settings']['key_facts']['fact'];
}
