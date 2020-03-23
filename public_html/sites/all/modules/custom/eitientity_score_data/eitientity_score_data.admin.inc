<?php
/**
 * @file
 * Forms and helper functions for administrative pages.
 */

/**
 * Form constructor for the survey add/edit form.
 *
 * @TODO: Add proper validation!
 *
 * @see eitientity_score_data_entity_info().
 *
 * @param array $form
 * @param array $form_state
 * @param ScoreDataEntity $entity
 * @param string $op
 * @return array
 */
function score_data_form($form, &$form_state, $entity, $op) {
  // We have to decide on the form type by the operation.
  if ($op == 'edit' || ($op == 'add')) {
    $form = score_data_default_form($form, $form_state, $entity);
  }
  return $form;
}

/**
 * Summary data default edit form.
 *
 * @param array $form
 * @param array $form_state
 * @param ScoreDataEntity $entity
 * @return array
 */
function score_data_default_form($form, &$form_state, $entity) {
  $entity_type = $entity->entityType();

  // If the it's a new entity, we want a custom approach.
//  if (isset($entity->is_new) && $entity->is_new == TRUE) {
//    //    $entity->field_scd_score_req_values[LANGUAGE_NONE]['entities'][0]
//    $ief_key = key($form_state['inline_entity_form']);
//    $form_state['inline_entity_form'][$ief_key]['entities'][] = array(
//      'entity' => entity_create('score_req', array('type' => 'standard')),
//      'weight' => 0,
//      'form' => 0,
//      'needs_save' => FALSE,
//    );
//  }

  $query = new EntityFieldQuery();
  $countries_count = $query
    ->entityCondition('entity_type', 'implementing_country')
    ->count()
    ->execute();
  if (empty($countries_count)) {
    drupal_set_message(t('No implementing countries exist.'), 'warning');
  }

  $query = new EntityFieldQuery();
  $score_reqs_count = $query
    ->entityCondition('entity_type', 'score_req')
    ->count()
    ->execute();
  if (empty($score_reqs_count)) {
    drupal_set_message(t('No score requirements exist. Import default via task-script?'), 'warning');
  }

  // Denny access to the form if no implementing countries or score_reqs exist.
  if (empty($countries_count) || empty($score_reqs_count)) {
    return drupal_access_denied();
  }

  if (isset($form_state['op']) && arg(0) != 'admin') {
    drupal_set_title(eitientity_score_data_entity_ui_get_page_title($form_state['op'], $entity_type, $entity), PASS_THROUGH);
  }

  // Entity options for administrators
  $form['options'] = [
    '#type' => 'fieldset',
    '#title' => t('Publishing options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#attributes' => [
      'class' => ["{$entity_type}-form-options"],
    ],
    '#weight' => 95,
  ];

  $form['country_id'] = [
    '#type' => 'ereference',
    '#title' => t('Implementing Country'),
    '#default_value' => $entity->country_id,
    '#required' => TRUE,
    '#referenced_type' => 'implementing_country',
    '#autocomplete_path' => 'helpergeneric/ereference/implementing_country',
  ];

//  $year_start_value = date('Y');
//  if (!empty($entity->year_start)) {
//    $year_start_date = new DateObject($entity->year, NULL);
//    $year_start_value = $year_start_date->format(EITIENTITY_SUMMARYDATA_DATE_FORMAT);
//  }
  $form['year'] = [
    '#type' => 'date_select',
    '#title' => t('Year'),
    '#required' => TRUE,
    '#default_value' => $entity->year,
    '#date_format' => 'Y',
    '#date_label_position' => 'none',
    '#date_year_range' => '-20:+2',
  ];

  $published_value = 0;

  if (!empty($entity->published)) {
    $published_date = new DateObject($entity->published, NULL);
    $published_value = $published_date->format(EITIENTITY_SUMMARYDATA_DATE_FORMAT);
  }
  $form['published'] = [
    '#type' => 'date_popup',
    '#title' => t('Published on'),
    '#description' => t('Date the Validation decision was taken bu the EITI Board.'),
    '#required' => TRUE,
    '#default_value' => $published_value,
    '#date_format' => EITIENTITY_SUMMARYDATA_DATE_FORMAT,
    '#date_label_position' => 'invisible',
    '#date_year_range' => '-16:+2',
  ];
  $form['board_decision_url'] = [
    '#type' => 'textfield',
    '#title' => t('Link to Board decision URL'),
    '#default_value' => $entity->board_decision_url,
  ];
  $form['validation_documentation_url'] = [
    '#type' => 'textfield',
    '#title' => t('Link to Validation documentation'),
    '#default_value' => $entity->validation_documentation_url,
  ];

  $form['options']['status'] = [
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => $entity->status,
    '#weight' => 98,
  ];

  // Add the buttons.
  $form['actions'] = ['#type' => 'actions', '#weight' => 99];
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
    '#validate' => ['_score_data_form_validate'],
    '#submit' => ['_score_data_form_submit'],
  ];

  if ($entity->identifier() && entity_access('delete', $entity_type, $entity)) {
    $form['actions']['delete'] = [
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => ['_score_data_form_delete_submit'],
    ];
  }

  // Setup the destination and cancel link URL.
  $form_state['destination'] = drupal_get_destination();
  $entity_uri = $entity->uri();
  if ($entity_uri) {
    $form['actions']['cancel'] = [
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => $entity_uri['path'],
      '#weight' => 100,
    ];
  }

  if (!empty($_GET['destination'])) {
    $destination_parts = drupal_parse_url($_GET['destination']);
    $form['actions']['cancel']['#href'] = $destination_parts['path'];
    $form['actions']['cancel']['#options']['query'] = $destination_parts['query'];
  }

  // Attach fields, if any, and allow DS to order form items.
  field_attach_form($entity_type, $entity, $form, $form_state, entity_language($entity_type, $entity));

  // Create our prepopulate button.
  $ief_id = $form['field_scd_score_req_values']['und']['#ief_id'];
  if ($form_state['submitted'] == FALSE || !in_array('score_data_form_prepopulate_ief', $form_state['submit_handlers'])) {
    $form['field_scd_score_req_values']['und']['actions']['ief_add']['#weight'] = 5;
    $form['field_scd_score_req_values']['und']['actions']['prepopulate'] = [
      '#type' => 'submit',
      '#weight' => 0,
      '#value' => t('Prepopulate with Standard Requirements'),
      '#name' => 'ief-' . $ief_id . '-prepopulate',
      '#ief_form' => 'prepopulate',
      '#submit' => ['score_data_form_prepopulate_ief'],
      '#ajax' => [
        'callback' => 'inline_entity_form_get_element',
        'wrapper' => 'inline-entity-form-' . $ief_id,
      ],
      '#limit_validation_errors' => $form['field_scd_score_req_values']['und']['actions']['ief_add']['#limit_validation_errors'],
    ];

    // Pre-populate PDF Title value.
    if (isset($form['field_scd_pdf_title_prefix'])) {
      $lan = $form['field_scd_pdf_title_prefix']['#language'];
      if (empty($form['field_scd_pdf_title_prefix'][$lan][0]['value']['#default_value'])) {
        $form['field_scd_pdf_title_prefix'][$lan][0]['value']['#default_value'] = t('Validation of');
      }
      $form['field_scd_pdf_title_prefix']['#disabled'] = TRUE;
    }
    if (!empty($form['field_scd_pdf_title'])) {
      if (!empty($form['country_id']['#default_value'])) {
        $lan = $form['field_scd_pdf_title']['#language'];
        $country = entity_load_single('implementing_country', $form['country_id']['#default_value']);
        if ($country) {
          $default = '';
          $form['field_scd_pdf_title'][$lan][0]['value']['#description'] = t('The title of Validation in PDF will be: Validation of (country_name)');
          if (!empty($entity->field_scd_pdf_title[$lan][0]['value'])) {
            $default = $entity->field_scd_pdf_title[$lan][0]['value'];
          }
          elseif (!empty($country->name_field[$lan][0]['value'])) {
            $default = $country->name_field[$lan][0]['value'];
          }
          $form['field_scd_pdf_title'][$lan][0]['value']['#default_value'] = $default;
        }
      }
    }
    // Pre-populate Decision reference by data from Board decision.
    if (isset($form['field_scd_pdf_decision_ref'])) {
      $lan = $form['field_scd_pdf_decision_ref']['#language'];
      if (!empty($decision = _get_board_decision_data($entity))) {
        $form['field_scd_pdf_decision_ref'][$lan][0]['value']['#default_value'] = $decision['field_bd_number_value'] . '/' . $decision['field_board_meeting_circular_value'];
        $form['field_scd_pdf_decision_ref']['#disabled'] = TRUE;
      }

    }
  }
  // Hide PDF-date, it will be pre-populated by published value on validate.
  if (isset($form["field_scd_pdf_date"])) {
    $form['field_scd_pdf_date']['#access'] = FALSE;
  }
  if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
    if (isset($form['redirect'])) {
      $form['redirect']['#access'] = FALSE;
    }
  }

  return $form;
}

/**
 * Helper to get Board decision data by it validation.
 *
 * @param object $validation
 *   The validation entity.
 *
 * @return array
 *   Board decision data
 */
function _get_board_decision_data($validation) {
  $query = db_select('field_data_field_validation', 'v');
  $query->condition('v.field_validation_target_id', $validation->id);
  $query->innerJoin('field_data_field_bd_number', 'bd', 'v.entity_id = bd.entity_id');
  $query->addField('bd', 'field_bd_number_value');
  $query->innerJoin('field_data_field_board_meeting_circular', 'bmc', 'v.entity_id = bmc.entity_id');
  $query->addField('bmc', 'field_board_meeting_circular_value');
  $result = $query->execute()->fetchAssoc();
  return !empty($result) ? $result : [];
}

/**
 * Function that prepopulates the IEF for Score Data.
 */
function score_data_form_prepopulate_ief(&$form, &$form_state) {
  $element = inline_entity_form_get_element($form, $form_state);
  $ief_id = $element['#ief_id'];

  $form_state['rebuild'] = TRUE;
  $form_state['inline_entity_form'][$ief_id]['entities'] = array();
  $requirements_info = eitientity_score_req_value_get_score_req_information();
  $weight = 0;
  $default_score_req_values = array(
    'description' => '',
    'value' => (string) EITIENTITY_SCORE_REQ_VALUE_NO,
    'is_applicable' => TRUE,
    'type' => 'standard',
    'progress_value' => EITIENTITY_SCORE_REQ_DIR_OF_PROGRESS_EMPTY,
  );
  // Move overall progress to the bottom.
  foreach ($requirements_info['options'] as $score_req_id => $label) {
    if ($requirements_info['attributes'][$score_req_id]['data-score_req-code'] === '0.0') {
      $overall_progress = $requirements_info['options'][$score_req_id];
      unset($requirements_info['options'][$score_req_id]);
      $requirements_info['options'][$score_req_id] = $overall_progress;
      break;
    }
  }
  foreach ($requirements_info['options'] as $score_req_id => $label) {
    $form_state['inline_entity_form'][$ief_id]['entities'][] = array(
      'entity' => entity_create('score_req_value', array(
        'score_req_id' => $score_req_id,
      ) + $default_score_req_values),
      'weight' => $weight,
      'form' => NULL,
      'needs_save' => TRUE,
    );
    $weight++;
  }
}

/**
 * Convert the date_popup date string to timestamp.
 *
 * @param $element
 * @param $form_state
 */
function _score_data_form_date_popup_date_validate($element, &$form_state, $form) {
  // Get the date format and value.;
  $date_value = drupal_array_get_nested_value($form_state['values'], $element['#parents']);

  $timezone = NULL;
  $date = new DateObject($date_value, $timezone, $element['#date_format']);
  $date->limitGranularity(array(
    'year',
    'month',
    'day',
  ));
  $date_value_timestamp = $date->format('U');

  // Update the form value.
  if (!empty($date_value_timestamp) && is_numeric($date_value_timestamp)) {
    form_set_value($element, $date_value_timestamp, $form_state);
  }
}

/**
 * Form validation handler for score_data_form().
 *
 * @see score_data_form()
 * @see entity_form_field_validate()
 */
function _score_data_form_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];

  // Let's manually clean-up the IEF without values.
  $ief_key = key($form_state['inline_entity_form']);
  $ief_entities = $form_state['inline_entity_form'][$ief_key]['entities'];
  foreach ($ief_entities as $ief_entity_key => $ief_entity) {
    if (!isset($ief_entity['entity']->value) || $ief_entity['entity']->value == NULL) {
      unset($form_state['inline_entity_form'][$ief_key]['entities'][$ief_entity_key]);
      unset($form_state['values']['field_scd_score_req_values']['und']['entities'][$ief_entity_key]);
    }
  }
  $form_state['inline_entity_form'][$ief_key]['entities'] = array_values($form_state['inline_entity_form'][$ief_key]['entities']);
  if (!empty($form_state['values']['field_scd_score_req_values']['und']['entities'])) {
    $form_state['values']['field_scd_score_req_values']['und']['entities'] = array_values($form_state['values']['field_scd_score_req_values']['und']['entities']);
  }
  // Pre-populate Pdf-date field by Published on value.
  if (!empty($form_state['values']['published']) && isset($form["field_scd_pdf_date"])) {
    $date = date(EITIENTITY_SUMMARYDATA_DATE_FORMAT, $form_state['values']['published']);
    $lan = $form['field_scd_pdf_date']['#language'];
    $form_state['values']['field_scd_pdf_date'][$lan][0]['value'] = $date . ' 00:00:00';
  }

  field_attach_form_validate($entity_type, $entity, $form, $form_state);
}

/**
 * Form API submit callback for score_data_form().
 */
function _score_data_form_submit($form, &$form_state) {
  $entity_type = $form_state['entity_type'];

  // Remove unneeded values.
  form_state_values_clean($form_state);

  /** @var ScoreDataEntity $entity */
  $entity = entity_ui_form_submit_build_entity($form, $form_state);

  // Set the timestamp fields.
  if (empty($entity->created)) {
    $entity->created = REQUEST_TIME;
  }
  $entity->changed = REQUEST_TIME;

  // Save the entity.
  entity_save($entity_type, $entity);

  // Prepare the messages.
  $watchdog_args = array('@type' => $entity->entityType(), '%id' => $entity->identifier());
  $entity_uri = entity_uri($entity_type, $entity);
  $entity_link = l(t('view'), $entity_uri['path']);

  if ($entity->identifier()) {
    $form_state['redirect'] = entity_access('view', $entity_type, $entity) ? $entity_uri['path'] : '<front>';
  }

  if (empty($entity->is_new)) {
    watchdog('score_data', '@type: updated %id.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
  }
  else {
    watchdog('score_data', '@type: added %id.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
  }

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Form submission handler for score_data_form().
 *
 * Handles the 'Delete' button on the entity form.
 *
 * @see score_data_form()
 */
function _score_data_form_delete_submit($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];

  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }

  $entity_uri = entity_uri($entity_type, $entity);
  $form_state['redirect'] = array($entity_uri['path'] . '/delete', array('query' => $destination));
}

/**
 * Menu callback: Creates overview page for custom identifier entities at admin/structure/%.
 *
 * @param $entity_type
 * @return array
 */
function eitientity_score_data_entity_overview_types($entity_type) {
  $entity_info = entity_get_info($entity_type);

  $build = array();
  if (empty($entity_info)) {
    return $build;
  }

  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => '2'));
  $rows = array();

  if (module_exists('field_ui') && !empty($entity_info['fieldable'])) {
    foreach ($entity_info['bundles'] as $bundle) {
      $url_path = $bundle['admin']['path'];
      if (isset($bundle['admin']['real path'])) {
        $url_path = $bundle['admin']['real path'];
      }

      $row = array();
      $row[] = $bundle['label'];
      $row[] = array('data' => l(t('manage fields'), $url_path . '/fields'));
      $row[] = array('data' => l(t('manage display'), $url_path . '/display'));

      $rows[] = $row;
    }
  }

  $build['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No entity types available.'),
  );

  return $build;
}
