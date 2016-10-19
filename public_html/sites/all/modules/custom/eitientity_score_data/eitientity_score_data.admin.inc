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

  $query = new EntityFieldQuery();
  $countries_count = $query
    ->entityCondition('entity_type', 'implementing_country')
    ->count()
    ->execute();
  if (empty($countries_count)) {
    drupal_set_message(t('No implementing countries exist.'), 'warning');
  }

  $query = new EntityFieldQuery();
  $indicators_count = $query
    ->entityCondition('entity_type', 'indicator')
    ->count()
    ->execute();
  if (empty($indicators_count)) {
    drupal_set_message(t('No indicators exist.'), 'warning');
  }

  // Denny access to the form if no implementing countries or indicators exist.
  if (empty($countries_count) || empty($indicators_count)) {
    return drupal_access_denied();
  }

  if (isset($form_state['op']) && arg(0) != 'admin') {
    drupal_set_title(eitientity_score_data_entity_ui_get_page_title($form_state['op'], $entity_type, $entity), PASS_THROUGH);
  }

  // $form['additional_settings'] = array(
  //   '#type' => 'vertical_tabs',
  //   '#weight' => 99,
  // );

  // Entity options for administrators
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Publishing options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#attributes' => array(
      'class' => array("{$entity_type}-form-options"),
    ),
    '#weight' => 95,
  );

  $form['country_id'] = array(
    '#type' => 'ereference',
    '#title' => t('Implementing Country'),
    '#default_value' => $entity->country_id,
    '#required' => TRUE,
    '#referenced_type' => 'implementing_country',
    '#autocomplete_path' => 'helpergeneric/ereference/implementing_country',
  );

  $year_start_value = date('Y');
  if (!empty($entity->year_start)) {
    $year_start_date = new DateObject($entity->year, NULL);
    $year_start_value = $year_start_date->format(EITIENTITY_SUMMARYDATA_DATE_FORMAT);
  }
  $form['year'] = array(
    '#type' => 'date_select',
    '#title' => t('Year'),
    '#required' => TRUE,
    '#default_value' => $year_start_value,
    '#date_format' => 'Y',
    '#date_label_position' => 'none',
    '#date_year_range' => '-20:+2',
  );

  $published_value = 0;
  if (!empty($entity->published)) {
    $published_date = new DateObject($entity->published, NULL);
    $published_value = $published_date->format(EITIENTITY_SUMMARYDATA_DATE_FORMAT);
  }
  $form['published'] = array(
    '#type' => 'date_popup',
    '#title' => t('Published on'),
    '#description' => t('Date that the EITI Report was published (i.e., made publicly available)'),
    '#required' => TRUE,
    '#default_value' => $published_value,
    '#date_format' => EITIENTITY_SUMMARYDATA_DATE_FORMAT,
    '#date_label_position' => 'invisible',
    '#date_year_range' => '-16:+2',
  );

  $form['options']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => $entity->status,
    '#weight' => 98,
  );

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions', '#weight' => 99);
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#validate' => array('_score_data_form_validate'),
    '#submit' => array('_score_data_form_submit'),
  );

  if ($entity->identifier() && entity_access('delete', $entity_type, $entity)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('_score_data_form_delete_submit'),
    );
  }

  // Setup the destination and cancel link URL.
  $form_state['destination'] = drupal_get_destination();
  $entity_uri = $entity->uri();
  if ($entity_uri) {
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => $entity_uri['path'],
      '#weight' => 100,
    );
  }

  if (!empty($_GET['destination'])) {
    $destination_parts = drupal_parse_url($_GET['destination']);
    $form['actions']['cancel']['#href'] = $destination_parts['path'];
    $form['actions']['cancel']['#options']['query'] = $destination_parts['query'];
  }

  // Attach fields, if any, and allow DS to order form items.
  field_attach_form($entity_type, $entity, $form, $form_state, entity_language($entity_type, $entity));

  if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
    if (isset($form['redirect'])) {
      $form['redirect']['#access'] = FALSE;
    }
  }

  return $form;
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