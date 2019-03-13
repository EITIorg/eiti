<?php

/**
 * Returns the feedback webform node nid.
 */
function eitict_webform_get_feedback_nid() {
  $nid = &drupal_static(__FUNCTION__);
  if (!isset($nid)) {
    $nid = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('type', 'webform')
      ->condition('status', 1)
      ->condition('title', 'Feedback')
      ->execute()
      ->fetchField();
  }
  return $nid;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function eitict_webform_preprocess_webform_confirmation(&$vars) {
  $f_nid = eitict_webform_get_feedback_nid();
  if (isset($vars['node']->nid) && $vars['node']->nid == $f_nid) {
    // There are some issues with plain text format, translations and p tags.
    $vars['confirmation_message'] = trim(strip_tags(html_entity_decode($vars['confirmation_message'])));
  }
}

/**
 * Implements hook_form_BASE_FORM_ID_alter() for webform_client_form().
 */
function eitict_webform_form_webform_client_form_alter(&$form, &$form_state, $form_id) {
  $fb_nid = eitict_webform_get_feedback_nid();
  if (isset($form['#node']->nid) && $form['#node']->nid == $fb_nid) {
    $path = drupal_get_path('module', 'eitict_webform');
    drupal_add_js($path . '/eitict_webform_feedback.js');
    // Hide some elements (visibility is toggled with js).
    $form['submitted']['feedback']['#wrapper_attributes']['style'] = 'display: none;';
    $form['submitted']['email']['#wrapper_attributes']['style'] = 'display: none;';
    $form['actions']['#attributes']['style'] = 'display: none;';
    $form['submitted']['rate']['#attributes']['style'] = 'display: none;';
  }
}
