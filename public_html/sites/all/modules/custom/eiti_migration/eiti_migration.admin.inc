<?php

/**
 * @file
 * Holds all of the config forms for the migration process.
 */

/**
 * A callback that builds our settings form.
 */
function eiti_migration_settings($form, $form_state) {
  $form = array();

  // Database settings.
  $form['eiti_migration_db_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Legacy Database settings'),
    '#description' => t('All database settings go here. We\'re using a settings form, because hardcoding things into <strong>settings.php</strong> is not cool.'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );
  $form['eiti_migration_db_fieldset']['eiti_migration_db_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Database Name'),
    '#description' => t('Paste in the legacy db name (source db).'),
    '#default_value' => variable_get('eiti_migration_db_name', ''),
    '#required' => TRUE,
  );
  $form['eiti_migration_db_fieldset']['eiti_migration_db_user_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Database User Name'),
    '#description' => t('Database User Name that can access the database.'),
    '#default_value' => variable_get('eiti_migration_db_user_name', ''),
    '#required' => TRUE,
  );
  $form['eiti_migration_db_fieldset']['eiti_migration_db_user_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('Database User Password'),
    '#description' => t('Database User Password.'),
    '#default_value' => variable_get('eiti_migration_db_user_pass', ''),
    '#required' => TRUE,
  );

  // File-related settings.
  $form['eiti_migration_files_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Legacy File settings'),
    '#description' => t('File migrations require a source directory. Because we don\'t like hardcodings, we use settings form'),
    '#collapsible' => TRUE,
    '#collpased' => FALSE,
  );
  $form['eiti_migration_files_fieldset']['eiti_migration_files_public'] = array(
    '#type' => 'textfield',
    '#title' => t('Legacy Public Directory'),
    '#description' => t('Please specify an absolute path towards the legacy\'s <strong>public://</strong> directory.'),
    '#default_value' => variable_get('eiti_migration_files_public', ''),
  );

  return system_settings_form($form);
}
