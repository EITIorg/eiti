<?php
/**
 * @file
 * This is where we define / register all of the migrations.
 */

/**
 * Implements hook_migrate_api().
 */
function eiti_migration_migrate_api() {
  // The basics go here.
  $migrations = array(
    'api' => 2,
    'groups' => array(
      'preparations' => array(
        'title' => t('Excel Demo Migration'),
        'default_format' => 'filtered_html',
      ),
    ),
  );

  // Migrations themselves go here.
  $migrations['migrations'] = array();

  // This is a demo migration.
  $migrations['migrations']['ExcelDemo'] = array(
    'class_name' => 'ExcelDemoEitiMigration',
    'group_name' => 'preparations',
  );

  return $migrations;
}
