<?php

/**
 * @file
 * A generic mail-chimp sign-up form (selective).
 */

$plugin = array(
  'title' => t('Mailchimp Signup'),
  'description' => t('A generic mailchimp signup widget. Allows to select any of the defined forms.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_mailchimp__signup__render',
  'edit form' => 'eiti_mailchimp__signup__settings_form',
  'admin info' => 'eiti_mailchimp__signup__admin_info',
  'defaults' => array(
    'signup_form' => '',
  ),
);

/**
 * Settings form callback.
 */
function eiti_mailchimp__signup__settings_form($form, $form_status) {
  $conf = $form_state['conf'];

  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'mailchimp_signup');
  $efq->propertyCondition('mode', array(MAILCHIMP_SIGNUP_EITI_WIDGET, MAILCHIMP_SIGNUP_EITI_BOTH), 'IN');
  $results = $efq->execute() ;

  if (empty($results['mailchimp_signup'])) {
    $all_widget_signup_forms = array(
      '' => t('- Please create signup forms - '),
    );
  }
  else {
    $signup_ids = array_keys($results['mailchimp_signup']);
    $signups = mailchimp_signup_load_multiple($signup_ids);

    $all_widget_signup_forms = array();
    foreach ($signups as $sid => $signup) {
      $all_widget_signup_forms[$sid] = $signup->name;
    }
  }

  $form['signup_form'] = array(
    '#type' => 'select',
    '#title' => t('Select the sign-up form'),
    '#description' => t('Please select a sign-up form to render.'),
    '#options' => $all_widget_signup_forms,
    '#default_value' => $conf['signup_form']
  );

  return $form;
}

/**
 * Form submit handler.
 */
function eiti_mailchimp__signup__settings_form_submit($form, $form_state) {
  // A bit of normalization.
  $values = $form_state['values'];
  $form_state['conf']['signup_form'] = $values['signup_form'];
}

/**
 * Output function for the plugin itself.
 * Renders a Mailchimp sign-up form.
 */
function eiti_mailchimp__signup__render($subtype, $conf, $panel_args, $context) {
  if (!empty($conf['signup_form'])) {
    $signup = mailchimp_signup_load($conf['signup_form']);
    if ($signup) {
      $block = new stdClass();
      $block->title = check_plain($signup->title);
      $signup_form = drupal_get_form('mailchimp_signup_subscribe_block_' . $signup->name . '_form', $signup, 'mailchimp_signup_block');
      $signup_form['#attributes']['class'][] = 'single-fluid-row-wrapper';
      $block->content = $signup_form;
      return $block;
    }
  }
  return FALSE;
}

/**
 * Admin info callback function.
 */
function eiti_mailchimp__signup__admin_info($subtype, $conf, $contexts) {
  $block = new stdClass();

  if (!empty($conf['signup_form'])) {
    $signup_id = $conf['signup_form'];
    $signup = mailchimp_signup_load($signup_id);

    $block->title = t('Mailchimp Form');
    $block->content = t('Mailchimp Form: @name.', array('@name' => $signup->name));
    return $block;
  }

  $block->title = t('Mailchimp Form');
  $block->content = t('No forms selected.');
  return $block;
}
