<?php
/**
 * @file
 * eitiet_implementing_country.custom.inc
 */

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function eitiet_implementing_country_features_component_export_alter(&$component_export, $component) {
  $entries_list = array();
  switch ($component) {
    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // We use "the same allowed layouts as standard Panels pages".
        'panelizer_implementing_country:normal_allowed_layouts',

        // We use "the same allowed content as standard Panels pages".
        'panelizer_implementing_country:normal_allowed_types',
      );
  }

  $removed_entries_list = array();
  foreach ($entries_list as $name) {
    if (isset($component_export['options']['sources'][$name])) {
      unset($component_export['options']['sources'][$name]);
      $removed_entries_list[] = check_plain($name);
    }

    if ($component == 'dependencies') {
      if (isset($component_export['options']['detected'][$name])) {
        unset($component_export['options']['detected'][$name]);
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for taxonomy_form_term.
 */
function eitiet_implementing_country_form_taxonomy_form_term_alter(&$form, &$form_state, $form_id) {
  if ($form['#vocabulary']->machine_name == 'country_status') {
    if (isset($form_state['term']->field_country_status_id['und'][0]['value']) && strlen($form_state['term']->field_country_status_id['und'][0]['value'])) {
      $form['field_country_status_id']['und'][0]['value']['#disabled'] = TRUE;
    }
    else {
      $form['#validate'][] = 'eitiet_implementing_country_status_validate';
    }
  }
}

/**
 * Custom validation handler for country status terms.
 */
function eitiet_implementing_country_status_validate($form, &$form_state) {
  // Only allow lowercase letters, numbers, dashes, underlines and make sure it is unique.
  // Changing of existing ID-s is not expected (should be disallowed).
  if (isset($form_state['values']['field_country_status_id']['und'][0]['value'])) {
    $status_id = trim($form_state['values']['field_country_status_id']['und'][0]['value']);
    $form_state['values']['field_country_status_id']['und'][0]['value'] = $status_id;
    if (!preg_match('/^[a-z0-9_-]+$/', $status_id)) {
      form_set_error('field_country_status_id', t('The ID must consist of only lowercase letters, numbers, dashes, underlines.'));
    }
    else {
      $entity_id = db_select('field_data_field_country_status_id', 'csid')
        ->fields('csid', array('entity_id'))
        ->condition('field_country_status_id_value', $status_id)
        ->execute()
        ->fetchField();
      if ($entity_id) {
        form_set_error('field_country_status_id', t('The entered ID already exists.'));
      }
    }
  }
}
