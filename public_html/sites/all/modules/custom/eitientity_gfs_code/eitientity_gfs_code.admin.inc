<?php
/**
 * @file
 * Forms and helper functions for administrative pages.
 */


/**
 * Form constructor for the survey add/edit form.
 *
 * @see eitientity_gfs_code_entity_info().
 *
 * @param array $form
 * @param array $form_state
 * @param GfsCodeEntity $entity
 * @return array
 */
function gfs_code_form($form, &$form_state, $entity) {
  $entity_type = 'gfs_code';

  if (isset($form_state['op']) && arg(0) != 'admin') {
    drupal_set_title(eitientity_gfs_code_entity_ui_get_page_title($form_state['op'], $entity_type, $entity), PASS_THROUGH);
  }


  $form['code'] = array(
    '#type' => 'textfield',
    '#title' => t('GFS Code'),
    '#default_value' => $entity->code,
    '#required' => TRUE,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $entity->name,
    '#required' => TRUE,
  );

  // Get a list of group gfs_codes sorted by name.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'gfs_code');
  $query->propertyOrderBy('code');
  $results = $query->execute();

  $gfs_code_options = array('' => t('- None -'));
  if (!empty($results['gfs_code'])) {
    foreach ($results['gfs_code'] as $result) {
      $gfs_code = entity_load_single($entity_type, $result->id);

      $gfs_code_options[$gfs_code->identifier()] = filter_xss($gfs_code->code . ' - ' . $gfs_code->label());
    }
  }

  $form['parent'] = array(
    '#type' => 'select',
    '#title' => t('Parent'),
    '#default_value' => $entity->parent,
    '#options' => $gfs_code_options,
    '#description' => t('The gfs code parent.'),
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
      '#submit' => array('_gfs_code_entity_form_delete_submit'),
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
  $form['#validate'][] = '_gfs_code_entity_form_validate';
  $form['#submit'][] = '_gfs_code_entity_form_submit';

  // Always hide the redirect.module fieldset.
  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  return $form;
}

/**
 * Form validation handler for gfs_code_form().
 *
 * @see gfs_code_form()
 * @see entity_form_field_validate()
 */
function _gfs_code_entity_form_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  field_attach_form_validate($entity_type, $entity, $form, $form_state);
}

/**
 * Form API submit callback for gfs_code_form().
 */
function _gfs_code_entity_form_submit($form, &$form_state) {
  $entity_type = $form_state['entity_type'];

  // Remove unneeded values.
  form_state_values_clean($form_state);
  /** @var GfsCodeEntity $entity */
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
  $t_args = array('@type' => eitientity_gfs_code_type_get_name($entity_type), '%title' => $entity_label);
  $entity_uri = entity_uri($entity_type, $entity);
  $entity_link = l(t('view'), $entity_uri['path']);

  if ($entity->identifier()) {
    $form_state['redirect'] = entity_access('view', $entity_type, $entity) ? $entity_uri['path'] : '<front>';
  }

  if (empty($entity->is_new)) {
    watchdog('gfs_code', '@type: updated %title.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
    drupal_set_message(t('@type %title has been updated.', $t_args));
  }
  else {
    watchdog('gfs_code', '@type: added %title.', $watchdog_args, WATCHDOG_NOTICE, $entity_link);
    drupal_set_message(t('@type %title has been created.', $t_args));
  }
}

/**
 * Form submission handler for gfs_code_form().
 *
 * Handles the 'Delete' button on the entity form.
 *
 * @see gfs_code_form()
 */
function _gfs_code_entity_form_delete_submit($form, &$form_state) {
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
