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
 * @see eitientity_revenue_stream_entity_info().
 *
 * @param array $form
 * @param array $form_state
 * @param RevenueStreamEntity $entity
 * @return array
 */
function revenue_stream_form($form, &$form_state, $entity) {
  $entity_type = $entity->entityType();

  $query = new EntityFieldQuery();
  $gfs_codes_count = $query
    ->entityCondition('entity_type', 'gfs_code')
    ->count()
    ->execute();
  if (empty($gfs_codes_count)) {
    drupal_set_message(t('No GFS Codes exist.'), 'warning');
  }

  // Denny access to the form if no GFS codes exist.
  if (empty($gfs_codes_count)) {
    return drupal_access_denied();
  }

  if (isset($form_state['op']) && arg(0) != 'admin') {
    drupal_set_title(helperentity_entity_ui_get_page_title($form_state['op'], $entity_type, $entity), PASS_THROUGH);
  }

  $gfs_code_information = eitientity_gfs_code_get_gfs_code_information();
  $form['gfs_code_id'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('GFS Code'),
    '#default_value' => $entity->gfs_code_id,
    '#options' => $gfs_code_information['options'],
  );

  $form['organisation_id'] = array(
    '#type' => 'ereference',
    '#title' => t('Organisation'),
    '#default_value' => $entity->organisation_id,
    '#required' => TRUE,
    '#referenced_type' => 'organisation',
  );
  $form['organisation_id']['#autocomplete_path'] = 'helpergeneric/ereference/organisation/' . $entity->type;


  $form['revenue'] = array(
    '#type' => 'textfield',
    '#title' => t('Revenue'),
    '#required' => TRUE,
    '#default_value' => $entity->revenue,
  );

  $form['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#required' => TRUE,
    '#options' => currency_options(),
    '#default_value' => $entity->currency,
  );

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions', '#weight' => 99);
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if ($entity->identifier() && entity_access('delete', $entity_type, $entity)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('_revenue_stream_form_delete_submit'),
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

  // Attach validate and submit callbacks.
  $form['#validate'][] = '_revenue_stream_form_validate';
  $form['#submit'][] = '_revenue_stream_form_submit';

  if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
    if (isset($form['redirect'])) {
      $form['redirect']['#access'] = FALSE;
    }
  }

  return $form;
}

/**
 * Form validation handler for revenue_stream_form().
 *
 * @see revenue_stream_form()
 * @see entity_form_field_validate()
 */
function _revenue_stream_form_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  field_attach_form_validate($entity_type, $entity, $form, $form_state);
}

/**
 * Form API submit callback for revenue_stream_form().
 */
function _revenue_stream_form_submit($form, &$form_state) {
  $entity_type = $form_state['entity_type'];

  // Remove unneeded values.
  form_state_values_clean($form_state);

  /** @var RevenueStreamEntity $entity */
  $entity = entity_ui_form_submit_build_entity($form, $form_state);

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
    watchdog($entity_type, '@type: updated %id.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
  }
  else {
    watchdog($entity_type, '@type: added %id.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
  }

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Form submission handler for revenue_stream_form().
 *
 * Handles the 'Delete' button on the entity form.
 *
 * @see revenue_stream_form()
 */
function _revenue_stream_form_delete_submit($form, &$form_state) {
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
