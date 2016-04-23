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

  $types['ereference'] = array(
    '#input' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#process' => array('form_process_ereference', 'form_process_autocomplete', 'ajax_process_form'),
    '#element_validate' => array('form_process_ereference_validate'),
    '#theme' => 'textfield',
    '#theme_wrappers' => array('form_element'),
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

  $element['#attached']['css'] = array(
    drupal_get_path('module', 'helpergeneric') . '/helpergeneric.admin.css',
  );

  return $element;
}

/**
 * Creates an simple entity reference form element.
 *
 * @see form_process_machine_name()
 *
 * @param $element
 * @param $form_state
 * @return array|null
 */
function form_process_ereference($element, &$form_state) {
  if (empty($element['#referenced_type'])) {
    drupal_set_message('Referenced entity type is missing.', 'warning');
    return $element;
  }

  $entity_info = entity_get_info($element['#referenced_type']);
  if (empty($entity_info)) {
    drupal_set_message('Referenced entity type information is missing.', 'warning');
    return $element;
  }

  if (!empty($element['#default_value'])) {
    /** @var Entity $entity */
    $entity = entity_load_single($element['#referenced_type'], $element['#default_value']);

    if ($entity) {
      $eid = $entity->identifier();
      $element['#value'] = $entity->label() . " [id:$eid]";
    }
    else {
      unset($element['#value']);
      $args = array(
        '%type' => $entity_info['label'],
        '%id' => (int) $element['#default_value'],
      );
      $message = t('The referenced %type entity with ID %id does not exist.', $args);
      form_set_error(implode('][', $element['#parents']), $message);
    }
  }

  return $element;
}

/**
 * Form element validation handler for default group audience elements.
 *
 * @param $element
 * @param $form_state
 */
function form_process_ereference_validate($element, &$form_state) {
  if (empty($element['#referenced_type'])) {
    return;
  }

  preg_match('/\[id:\s*([0-9]+)\s*\]/', $element['#value'], $matches);
  if (!empty($matches[1]) && is_numeric($matches[1])) {
    /** @var Entity $entity */
    $entity = entity_load_single($element['#referenced_type'], $matches[1]);
    if (empty($entity)) {
      preg_match('/(.*)\s+\[id:\s*[0-9]+\s*\]/', $element['#value'], $matches);
      $args = array('%name' => $matches[0]);
      form_error($element, t('%name does not exist.', $args));
    }
    else {
      // Clean-up submitted values.
      form_set_value($element, $entity->identifier(), $form_state);
    }
  }
  elseif (!empty($element['#value'])) {
    $args = array(
      '%value' => $element['#value'],
    );
    form_error($element, t('"%value" is not a valid reference.', $args));
  }
}

/**
 * Returns render array for options.
 *
 * @param $element
 * @return array
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
