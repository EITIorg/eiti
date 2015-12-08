<?php
/**
 * @file
 * Enables modules and site configuration for a minimal installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function eitibase_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  // Hide the update.module settings.
  // $form['update_notifications']['#access'] = FALSE;
}
