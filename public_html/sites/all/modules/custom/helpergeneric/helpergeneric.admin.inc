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
    '#description' => t('This is not used anywhere.'),
    '#disabled' => TRUE,
  );

  $form['site_information']['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
    '#description' => t("The <em>From</em> address in automated e-mails sent during registration and new password requests, and other notifications. (Use an address ending in your site's domain to help prevent this e-mail being flagged as spam.)"),
    '#required' => TRUE,
  );

  $form['site_information']['site_frontpage'] = array(
    '#type' => 'textfield',
    '#title' => t('Default front page'),
    '#default_value' => (variable_get('site_frontpage')!='node'?drupal_get_path_alias(variable_get('site_frontpage', 'node')):''),
    '#size' => 40,
    '#description' => t('Optionally, specify a relative URL to display as the front page.  Leave blank to display the default content feed.'),
    '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
  );

  $form['footer_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer details'),
  );

  $form['footer_details']['site_footer_slogan'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer Slogan'),
    '#default_value' => variable_get('site_footer_slogan', ''),
    '#description' => t('This slogan is shown next to the site log in the page footer.'),
  );

  $form['footer_details']['site_footer_contact'] = array(
    '#type' => 'textarea',
    '#title' => t('Footer Contact Information'),
    '#default_value' => variable_get('site_footer_contact', ''),
    '#description' => t('This contact information is shown in the page footer.'),
  );

  $form['footer_details']['site_footer_legal'] = array(
    '#type' => 'textarea',
    '#title' => t('Footer Legal Information'),
    '#default_value' => variable_get('site_footer_legal', ''),
    '#description' => t('This legal information is shown in the page footer.'),
  );

  $form['other'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // We want to allow people add exceptions for link validations via UI.
  if (module_exists('link')) {
    $default_arr = explode('|', LINK_DOMAINS);
    $default_arr = variable_get('link_extra_domains', $default_arr);
    $default_str = list_allowed_values_string($default_arr);
    $form['other']['eiti_url_domains'] = array(
      '#type' => 'textarea',
      '#title' => t('Allowed domains (URL validations)'),
      '#description' => t("Please specify <strong>one domain per line</strong> (numbers don't matter). Don't bother of sorting and duplicates, those will be cleared when you save the form.<br/><br/>Defaults to: <em>!default</em>", array('!default' => LINK_DOMAINS)),
      '#default_value' => $default_str,
      '#element_validate' => array('helpergeneric_settings_url_domains_validate'),
    );
  }

  $system_form = system_settings_form($form);
  $system_form['#submit'][] = 'helpergeneric_settings_form_extra_submit';

  // Now, we can return the form.
  return $system_form;
}

/**
 * A small textarea validation / massages the value as well.
 *
 * @param $element
 *   Text-area FAPI element.
 *
 * @param $form_state
 *   Form-state of the form during validation.
 */
function helpergeneric_settings_url_domains_validate($element, &$form_state) {
  // Check our links.
  if (!empty($form_state['values']['eiti_url_domains'])) {
    $allowed_domain_value = $form_state['values']['eiti_url_domains'];
    $allowed_domain_value = strtolower($allowed_domain_value);
    $form_state['values']['eiti_url_domains'] = list_extract_allowed_values($allowed_domain_value, 'list_text', TRUE);
    $form_state['values']['eiti_url_domains'] = array_unique($form_state['values']['eiti_url_domains']);
    sort($form_state['values']['eiti_url_domains']);
  }
  else {
    $default_arr = explode('|', LINK_DOMAINS);
    $form_state['values']['eiti_url_domains'] = $default_arr;
  }
}

/**
 * Post submit handler - a place where we do some extra magic.
 */
function helpergeneric_settings_form_extra_submit($form, &$form_state) {
  // We check if we have insert any values for the URL Domains, if we did, we use other variable (of the link.module).
  if (module_exists('link') && !empty($form_state['values']['eiti_url_domains'])) {
    variable_set('link_extra_domains', $form_state['values']['eiti_url_domains']);
    drupal_set_message(t('Global LINK domains are changed.'));
  }
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
