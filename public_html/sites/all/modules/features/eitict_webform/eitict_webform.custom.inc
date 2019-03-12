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
