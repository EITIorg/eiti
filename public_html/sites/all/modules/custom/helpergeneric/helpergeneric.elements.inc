<?php
/**
 * @file
 * Defines custom form elements.
 */

/**
 * Implements hook_element_info().
 *
 * Declare a new custom Form API element type.
 */
function helpergeneric_element_info() {
  $types['radioicons'] = array(
    '#input' => TRUE,
    '#process' => array('form_process_radioicons'),
    '#theme_wrappers' => array('radios'),
    '#pre_render' => array('form_pre_render_conditional_form_element'),
  );
  return $types;
}

/**
 * Expands a radios element into individual radio elements.
 *
 * @see form_process_radios()
 */
function form_process_radioicons($element, &$form_state) {
  if (empty($element['#options'])) {
    return $element;
  }

  $element_name = $element['#name'];
  $option_key = $element_name . '_option';

  // Add a container for all the options.
  $element[$option_key] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );
  $element[$option_key] += _helpergeneric_build_radioicons($element);

  return $element;
}

/**
 * Returns render array for options.
 */
function _helpergeneric_build_radioicons($element) {
  $items = array();

  $count = 0;
  $weight = 0;
  foreach ($element['#options'] as $key => $choice) {
    $count++;
    $weight += 0.001;

    // Generate the parents as the autogenerator does, so we will have a
    // unique id for each radio button.
    $parents_for_id = array_merge($element['#parents'], array('option', $key));

    $items[$key] = array(
      '#type' => 'radio',
      '#title' => $choice,
      '#title_extra_class' => array('radioicon-label'),
      '#return_value' => $key,
      '#default_value' => isset($element['#default_value']) ? $element['#default_value'] : FALSE,
      '#parents' => $element['#parents'],
      '#id' => drupal_html_id('edit-' . implode('-', $parents_for_id)),
      '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
      '#weight' => $weight,
    );

    if (isset($element['#icons'][$key])) {
      $items[$key]['#title_extra_icon'] = $element['#icons'][$key];
    }
  }

  return $items;
}
