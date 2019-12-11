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
  $form['eiti_migration_files_fieldset']['eiti_migration_legacy_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Legacy Domain'),
    '#description' => t('Please specify the legacy domain (i.e. <strong>eiti.org</strong>).'),
    '#default_value' => variable_get('eiti_migration_legacy_domain', 'eiti.org'),
  );
  $form['eiti_migration_files_fieldset']['eiti_migration_files_public'] = array(
    '#type' => 'textfield',
    '#title' => t('Legacy Public Directory'),
    '#description' => t('Please specify an absolute path towards the legacy\'s <strong>public://</strong> directory.'),
    '#default_value' => variable_get('eiti_migration_files_public', ''),
  );

  return system_settings_form($form);
}

/**
 * Settings form callback for the spreadsheet import process.
 */
function eiti_migration_spreadsheets_import_settings($form, &$form_state) {
  $form['eiti_migration_import_folder'] = array(
    '#type' => 'textfield',
    '#title' => t('Source folder for the spreadsheets'),
    '#description' => t('Please specify the source folder for the spreadsheets. This is from were all the spreadsheets will be uploaded to Drupal.<br/>This is treated like a "public://{value}" subfolder.<br/><strong>Note:</strong> The spreadsheets are just imported into Drupal, not parsed, for parsing go to the Migration page and run the migration.'),
    '#default_value' => variable_get('eiti_migration_import_folder', 'spreadsheets_source'),
  );
  $form['eiti_migration_import_button'] = array(
    '#type' => 'button',
    '#executes_submit_callback' => TRUE,
    '#value' => t('Import Spreadsheets'),
    '#validate' => array('eiti_migration_spreadsheets_import_validate'),
    '#submit' => array('eiti_migration_spreadsheets_import_submit'),
  );
  $form = system_settings_form($form);
  return $form;
}

/**
 * Validate our form (check the path for spreadsheet contents).
 */
function eiti_migration_spreadsheets_import_validate($form, $form_state) {
  $values = $form_state['values'];
  $folder_path = 'public://' . $values['eiti_migration_import_folder'];
  if (!_eiti_migration_s3_is_public_schema() && !file_prepare_directory($folder_path)) {
    form_set_error('eiti_migration_import_folder', t('Specified folder either does not exist or is not writable.'));
  }
}

/**
 * Submit handler that imports the spreadsheets to drupal (not parses them).
 */
function eiti_migration_spreadsheets_import_submit($form, $form_state) {
  $values = $form_state['values'];
  $folder_path = 'public://' . $values['eiti_migration_import_folder'];
  $s3_is_public = _eiti_migration_s3_is_public_schema();
  if (!$s3_is_public) {
    $folder_path = drupal_realpath($folder_path);
  }
  $files_xlsx = file_scan_directory($folder_path, '/.*\.xlsx$/');
  $files_xls = file_scan_directory($folder_path, '/.*\.xls$/');
  $files = $files_xlsx + $files_xls;

  // Make sure we have at least some files.
  if (count($files) == 0) {
    drupal_set_message(t('There are 0 spreadsheet files found. Permission issue?'));
    return;
  }

  $file_paths = array();
  if ($s3_is_public) {
    $file_paths = array_keys($files);
  }
  else {
    foreach ($files as $file_path => $file) {
      $file_paths[] = drupal_realpath($file_path);
    }
  }

  $batch = array(
    'title' => t('Importing to Drupal'),
    'operations' => array(
      array(
        'eiti_migration_spreadsheets_import', array($file_paths),
      ),
    ),
    'finished' => 'eiti_migration_spreadsheets_import_finished',
  );
  batch_set($batch);
  batch_process('admin/content/migrate/groups/spreadsheets');
}
