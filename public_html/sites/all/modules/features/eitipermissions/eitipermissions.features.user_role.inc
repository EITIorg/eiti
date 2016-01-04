<?php
/**
 * @file
 * eitipermissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function eitipermissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: external editor.
  $roles['external editor'] = array(
    'name' => 'external editor',
    'weight' => 11,
  );

  // Exported role: icanlocalize manager.
  $roles['icanlocalize manager'] = array(
    'name' => 'icanlocalize manager',
    'weight' => 9,
  );

  // Exported role: icanlocalize translator.
  $roles['icanlocalize translator'] = array(
    'name' => 'icanlocalize translator',
    'weight' => 8,
  );

  // Exported role: internal editor.
  $roles['internal editor'] = array(
    'name' => 'internal editor',
    'weight' => 6,
  );

  // Exported role: investor.
  $roles['investor'] = array(
    'name' => 'investor',
    'weight' => 7,
  );

  // Exported role: restricted user.
  $roles['restricted user'] = array(
    'name' => 'restricted user',
    'weight' => 5,
  );

  // Exported role: translation editor.
  $roles['translation editor'] = array(
    'name' => 'translation editor',
    'weight' => 10,
  );

  return $roles;
}
