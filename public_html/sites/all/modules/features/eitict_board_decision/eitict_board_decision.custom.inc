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

/**
 * Implements hook_views_query_alter().
 */
function eitict_board_decision_views_query_alter(&$view, &$query) {
  if ($view->name == 'board_decisions') {
    if (isset($view->exposed_raw_input['search'])) {
      $search = trim($view->exposed_raw_input['search']);
      if ($search) {
        foreach ($query->where as $key => $value) {
          if (isset($value['type']) && $value['type'] === 'OR') {
            // Turn search case insensitive.
            if (isset($value['conditions'][0]['field']) && is_object($value['conditions'][0]['field'])) {
              $conditions = &$query->where[$key]['conditions'][0]['field']->conditions();
              if (isset($conditions[0]['field']) && is_string($conditions[0]['field'])) {
                $conditions[0]['field'] = str_replace(' LIKE ', ' ILIKE ', $conditions[0]['field']);
              }
            }
            // Include keywords in search.
            $words = explode(' ', $search);
            $keyword_tids = db_select('field_data_name_field', 'n')
              ->fields('n', array('entity_id'))
              ->condition('entity_type', 'taxonomy_term')
              ->condition('bundle', 'board_decision_keywords')
              ->condition('deleted', 0);
            foreach ($words as $word) {
              $keyword_tids->condition('name_field_value', '%' . db_like(trim($word)) . '%', 'ILIKE');
            }
            $keyword_tids = $keyword_tids->execute()->fetchCol();
            $keyword_tids = $keyword_tids ? array_unique($keyword_tids) : array(0);
            $query->where[$key]['conditions'][] = array(
              'field' => 'field_data_field_bd_keywords.field_bd_keywords_tid',
              'value' => $keyword_tids,
              'operator' => 'IN',
            );
            break;
          }
        }
      }
    }
  }
}

/**
 * Implements hook_init().
 */
function eitict_board_decision_init() {
  if (isset($_SERVER['SCRIPT_URL']) && strpos($_SERVER['SCRIPT_URL'], '/BD/') === 0) {
    $parts = explode('/', $_SERVER['SCRIPT_URL']);
    if (isset($parts[2])) {
      $alias1 = 'board-decision/' . $parts[2];
      $alias2 = 'decision-conseil/' . $parts[2];
      $path = drupal_lookup_path('source', $alias1);
      if (!$path) {
        $path = drupal_lookup_path('source', $alias2);
      }
      if ($path && $path !== $_GET['q']) {
        drupal_goto($path, array(), 301);
      }
    }
  }
}
