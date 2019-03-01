<?php

/**
 * Implements hook_form_FORM_ID_alter() for board_decision_node_form.
 */
function eitict_board_decision_form_board_decision_node_form_alter(&$form, &$form_state, $form_id) {
  // Add a default value for field_bd_number if it's empty.
  if (!$form['field_bd_number']['und'][0]['value']['#default_value']) {
    $year = date('Y');
    $numbers = db_select('field_data_field_bd_number', 'fn')
      ->fields('fn', array('field_bd_number_value'))
      ->condition('entity_type', 'node')
      ->condition('bundle', 'board_decision')
      ->condition('field_bd_number_value', db_like($year . '-') . '%', 'LIKE')
      ->execute()
      ->fetchCol();
    $max = 0;
    foreach ($numbers as $number) {
      $parts = explode('-', trim($number));
      if (isset($parts[1]) && is_numeric($parts[1]) && $parts[1] > $max) {
        $max = $parts[1];
      }
    }
    $form['field_bd_number']['und'][0]['value']['#default_value'] = $year . '-' . ($max + 1);
  }
}

/**
 * Implements hook_pathauto_alias_alter().
 */
function eitict_board_decision_pathauto_alias_alter(&$alias, array &$context) {
  // Board decision nodes.
  if (isset($context['data']['node']->type) && $context['data']['node']->type == 'board_decision') {
    // Restore "-" in the alias.
    // We're expecting "BD/[node:field-bd-number]" pattern.
    if (isset($context['data']['node']->field_bd_number['und'][0]['value'])) {
      $parts = explode('/', $alias);
      $number = trim(strip_tags($context['data']['node']->field_bd_number['und'][0]['value']));
      if (count($parts) === 2) {
        $parts[1] = $number;
        $alias = implode('/', $parts);
      }
    }
  }
}
