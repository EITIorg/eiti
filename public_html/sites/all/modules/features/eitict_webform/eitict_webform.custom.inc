<?php

/**
 * Returns the feedback webform node nid.
 */
function eitict_webform_get_feedback_nid() {
  $nid = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'webform')
    ->condition('status', 1)
    ->condition('title', 'Feedback')
    ->execute()
    ->fetchField();
  return $nid;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function eitict_webform_preprocess_webform_confirmation(&$vars) {
  $fb_nid = eitict_webform_get_feedback_nid();
  if (isset($vars['node']->nid) && $vars['node']->nid == $fb_nid) {
    // There are some issues with plain text format, translations and p tags.
    $vars['confirmation_message'] = trim(strip_tags(html_entity_decode($vars['confirmation_message'])));
  }
}
