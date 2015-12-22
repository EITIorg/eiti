<?php
/**
 * @file
 * Forms and helper functions for administrative pages.
 */


/**
 * Form constructor for the survey add/edit form.
 *
 * @see eitientity_indicator_entity_info().
 *
 * @param array $form
 * @param array $form_state
 * @param IndicatorEntity $entity
 * @return array
 */
function indicator_form($form, &$form_state, $entity) {
  $entity_type = 'indicator';

  if (isset($form_state['op']) && arg(0) != 'admin') {
    drupal_set_title(eitientity_indicator_entity_ui_get_page_title($form_state['op'], $entity_type, $entity), PASS_THROUGH);
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $entity->name,
    '#required' => TRUE,
  );

  // Get a list of group indicators sorted by name.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'indicator');
  $query->entityCondition('bundle', 'group');
  $query->propertyOrderBy('name');
  $results = $query->execute();

  $indicator_options = array('' => t('-Select-'));
  foreach ($results['indicator'] as $result) {
    $indicator = entity_load_single($entity_type, $result->id);

    $indicator_options[$indicator->identifier()] = filter_xss($indicator->label());
  }

  $form['parent'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Parent'),
    '#default_value' => $entity->parent,
    '#options' => $indicator_options,
    '#description' => t('The indicator group.'),
  );

  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => $entity->status,
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
      '#submit' => array('_indicator_entity_form_delete_submit'),
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
  $form['#validate'][] = '_identifier_entity_form_validate';
  $form['#submit'][] = '_identifier_entity_form_submit';

  // Always hide the redirect.module fieldset.
  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  return $form;
}

/**
 * Form validation handler for indicator_form().
 *
 * @see indicator_form()
 * @see entity_form_field_validate()
 */
function _identifier_entity_form_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  field_attach_form_validate($entity_type, $entity, $form, $form_state);
}

/**
 * Form API submit callback for indicator_form().
 */
function _identifier_entity_form_submit($form, &$form_state) {
  $entity_type = $form_state['entity_type'];

  // Remove unneeded values.
  form_state_values_clean($form_state);
  /** @var IndicatorEntity $entity */
  $entity = entity_ui_form_submit_build_entity($form, $form_state);

  // Set the timestamp fields.
  if (empty($entity->created)) {
    $entity->created = REQUEST_TIME;
  }

  // Use NULL for parent; Form API doesn't like NULL.
  if (empty($entity->parent)) {
    $entity->parent = NULL;
  }

  // Save the entity.
  entity_save($entity_type, $entity);

  // Prepare the messages.
  $entity_label = $entity->label();
  $watchdog_args = array('@type' => $entity->entityType(), '%title' => $entity_label);
  $t_args = array('@type' => eitientity_indicator_type_get_name($entity_type), '%title' => $entity_label);
  $entity_uri = entity_uri($entity_type, $entity);
  $entity_link = l(t('view'), $entity_uri['path']);

  if ($entity->identifier()) {
    $form_state['redirect'] = entity_access('view', $entity_type, $entity) ? $entity_uri['path'] : '<front>';
  }

  if (empty($entity->is_new)) {
    watchdog('survey', '@type: updated %title.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
    drupal_set_message(t('@type %title has been updated.', $t_args));
  }
  else {
    watchdog('survey', '@type: added %title.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
    drupal_set_message(t('@type %title has been created.', $t_args));
  }
}

/**
 * Form submission handler for indicator_form().
 *
 * Handles the 'Delete' button on the entity form.
 *
 * @see indicator_form()
 */
function _indicator_entity_form_delete_submit($form, &$form_state) {
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
