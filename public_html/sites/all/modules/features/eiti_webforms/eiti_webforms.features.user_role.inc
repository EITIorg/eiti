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

  // Exported role: complaints viewer.
  $roles['complaints viewer'] = array(
    'name' => 'complaints viewer',
    'weight' => 13,
  );

  return $roles;
}
