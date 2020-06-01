<?php

/**
 * @file
 * eiti_webforms.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function eiti_webforms_user_default_roles() {
  $roles = array();

  // Exported role: complaints overviewer.
  $roles['complaints overviewer'] = array(
    'name' => 'complaints overviewer',
    'weight' => 12,
  );

  // Exported role: complaints viewer.
  $roles['complaints viewer'] = array(
    'name' => 'complaints viewer',
    'weight' => 11,
  );

  // Exported role: complaints viewer ceo.
  $roles['complaints viewer ceo'] = array(
    'name' => 'complaints viewer ceo',
    'weight' => 13,
  );

  return $roles;
}
