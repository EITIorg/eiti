<?php

/**
 * Helper for hook_field_info().
 *
 * @see helperfield_field_info().
 */
function _helperfield__helperfield_icon__hook_field_info() {
  return array(
    'helperfield_icon' => array(
      'label' => t('HelperField: Icon'),
      'description' => t('Exposes an icon selector.'),
      'settings' => array(),
      'instance_settings' => array('available_icons' => array()),
      'default_widget' => 'helperfield_radio_selector',
      'default_formatter' => 'helperfield_icon_default',
    ),
  );
}

/**
 * Helper for hook_field_widget_info().
 *
 * @see helperfield_field_widget_info().
 */
function _helperfield__helperfield_icon__hook_field_widget_info() {
  return array(
    'helperfield_radio_selector' => array(
      'label' => t('Radio Icon Selector'),
      'field types' => array('helperfield_icon'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
    ),
  );
}

/**
 * Helper for hook_field_formatter_info().
 *
 * @see helperfield_field_formatter_info().
 */
function _helperfield__helperfield_icon__hook_field_formatter_info() {
  return array(
    'helperfield_icon_default' => array(
      'label' => t('Icon'),
      'description' => t('Display the rendered icon.'),
      'field types' => array('helperfield_icon'),
    ),
  );
}

/**
 * Helper for hook_field_is_empty().
 *
 * @see helperfield_field_is_empty().
 */
function _helperfield__helperfield_icon__hook_field_is_empty($item, $field) {
  if (empty($item['icon'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Helper for hook_field_instance_settings_form().
 *
 * @see helperfield_field_instance_settings_form().
 */
function _helperfield__helperfield_icon__hook_field_instance_settings_form($field, $instance) {
  $form = array();

  // @TODO: Allow site developers to limit the available svg_icons sets.
  $settings = $instance['settings'];

  return $form;
}

/**
 * Helper for hook_field_widget_form().
 *
 * @see helperfield_field_widget_form().
 */
function _helperfield__helperfield_icon__hook_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // Fetch the re-usable icon options.
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  $element['icon'] = array(
    '#type' => 'radioicons',
    '#title' => $element['#title'],
    '#options' => $icon_options,
    '#icons' => $icons,
    '#required' => $element['#required'],
    '#default_value' => isset($items[$delta]['icon']) ? $items[$delta]['icon'] : '',
  );

  // @TODO: Add custom validation handler.
  //$element['#element_validate'] = array('helperfield_field_widget_element_validate');

  return $element;
}

/**
 * Helper for hook_field_formatter_view().
 *
 * @see helperfield_field_formatter_view().
 */
function _helperfield__helperfield_icon__hook_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {
    case 'helperfield_icon_default':
      foreach ($items as $delta => $item) {
        // @TODO: Move to the formatter configuration form.
        $options = array(
          'height' => '1.5em',
          'width' => '1.5em',
        );
        $markup = helpertheme_get_svg_icons($item['icon'], $options);
        if (!empty($markup)) {
          $element[$delta] = array('#markup' => $markup);
        }
      }
      break;
  }

  return $element;
}
