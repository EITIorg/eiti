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
        'title' => t('Demo Migrations'),
        'default_format' => 'filtered_html',
      ),
      'core' => array(
        'title' => t('Core Migrations: Users, Taxonomies, others'),
      ),
      'articles' => array(
        'title' => t('Migration to the Article CT'),
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

  // Core Migrations include: users, taxonomies.
  $migrations['migrations']['EITIUsersMigration'] = array(
    'class_name' => 'EITIUsersMigration',
    'group_name' => 'core',
  );
  $migrations['migrations']['EITITaxonomyTagsNewsMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_news',
    'destination_vocabulary' => 'tags',
  );
  $migrations['migrations']['EITITaxonomyTagsBlogMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_blog',
    'destination_vocabulary' => 'tags',
  );
  $migrations['migrations']['EITITaxonomyTagsEventsMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_events',
    'destination_vocabulary' => 'tags',
  );

  // Article Migrations goes here: News articles, Blog Posts and Events.
  $migrations['migrations']['EITINewsToArticleMigration'] = array(
    'class_name' => 'EITINewsToArticleMigration',
    'group_name' => 'articles',
  );
  $migrations['migrations']['EITIBlogToArticleMigration'] = array(
    'class_name' => 'EITIBlogToArticleMigration',
    'group_name' => 'articles',
  );
  $migrations['migrations']['EITIEventsToArticleMigration'] = array(
    'class_name' => 'EITIEventsToArticleMigration',
    'group_name' => 'articles',
  );

  return $migrations;
}
