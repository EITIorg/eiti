<?php
/**
 * @file
 * Contains form & UI cleanup functions.
 */

/**
 * Page callback for 'admin/settings/ui'.
 */
function helpergeneric_ui_settings_form($form, &$form_state) {
  $cleanup_ui_force = helpergeneric_cleanup_ui();

  $form['cleanup_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('UI settings'),
    '#description' => '<p>' . t('By default the UI is cleaned, you can disable this behaviour and have access to more options. This is only as a UI cleanup functionality and not a security feature.') . '</p><p>' . t('<strong>DO NOT CLICK</strong> on these buttons unless you were told to!') . '</p>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['cleanup_ui']['enable'] = array(
    '#type' => 'button',
    '#value' => 'Enable',
    '#disabled' => $cleanup_ui_force,
    '#submit' => array('helpergeneric_toggle_cleanup_ui_force_submit'),
    '#executes_submit_callback' => TRUE,
  );

  $form['cleanup_ui']['disable'] = array(
    '#type' => 'button',
    '#value' => 'Disable',
    '#disabled' => !$cleanup_ui_force,
    '#submit' => array('helpergeneric_toggle_cleanup_ui_force_submit'),
    '#executes_submit_callback' => TRUE,
  );

  return $form;
}

/**
 * Submit handler for helpergeneric_settings_form().
 */
function helpergeneric_toggle_cleanup_ui_force_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Enable') {
    // Enable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 1, NULL, base_path());
  }
  else {
    // Disable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 0, NULL, base_path());
  }
}

/**
 * Page callback for 'admin/settings/generic'.
 */
function helpergeneric_settings_form($form) {
  $form = array();

  $form['site_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site details'),
  );
  $form['site_information']['site_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name'),
    '#description' => t('The site name will be transformed to uppercase before displaying in the header.'),
    '#default_value' => variable_get('site_name', 'Drupal'),
    '#required' => TRUE
  );
   $form['site_information']['site_slogan'] = array(
     '#type' => 'textfield',
     '#title' => t('Slogan'),
     '#default_value' => variable_get('site_slogan', ''),
     '#description' => t("How this is used depends on your site's theme."),
   );
  $form['site_information']['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
    '#description' => t("The <em>From</em> address in automated e-mails sent during registration and new password requests, and other notifications. (Use an address ending in your site's domain to help prevent this e-mail being flagged as spam.)"),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Page callback: Outputs JSON for project specific group audience autocomplete suggestions.
 *
 * @param string $entity_type
 */
function helpergeneric_ereference_autocomplete($entity_type) {
  $matches = array();
  $bundle = NULL;
  $string = '';

  // @TODO: Pass the form_id and use the cached form information to determine
  //        the entity_type and bundle.
  $args = func_get_args();
  if (count($args) == 2) {
    $string = $args[1];
  }
  if (count($args) == 3) {
    $bundle = $args[1];
    $string = $args[2];
  }

  if (empty($string)) {
    drupal_json_output($matches);
    exit();
  }

  $entity_info = entity_get_info($entity_type);
  $id_key = $entity_info['entity keys']['id'];
  $label_key = $entity_info['entity keys']['label'];

  // Get a list of entity titles that contain the requested string.
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', $entity_type)
    ->propertyCondition($label_key, $string, 'CONTAINS');

  if (!empty($bundle) && in_array($bundle, array_keys($entity_info['bundles']))) {
    $query->entityCondition('bundle', $bundle);
  }

  $results = $query
    ->propertyOrderBy($label_key, 'ASC')
    ->range(0, 10)
    ->execute();

  if (!empty($results[$entity_type])) {
    $entities = entity_load($entity_type, array_keys($results[$entity_type]));

    foreach ($results[$entity_type] as $values) {
      if (empty($entities[$values->$id_key])) {
        continue;
      }

      /** @var Entity $entity */
      $entity = $entities[$values->$id_key];
      $entry = $entity->label() . ' [id:' . $entity->identifier() . ']';
      $matches[$entry] = $entry;
    }
  }

  drupal_json_output($matches);
}
