<?php
//
///**
// * @file
// * Contains Migrations classes used for migrations.
// */
//
///**
// * Class EITIGenericToArticleMigration
// *
// * The generic migration class to Article CT. News, Blog Posts & Events migrations
// * should implement this class.
// */
//abstract class EITIGenericToArticleMigration extends DrupalNode7Migration {
//
//}
//
///**
// * Class EITINewsToArticleMigration
// *
// * The News to Article migration class.
// */
//class EITINewsToArticleMigration extends EITIGenericToArticleMigration {
//  public function __construct($arguments) {
//    parent::__construct($arguments);
//
//    // Let's add some metadata.
//    $this->description = t('This is a demo migration used to show how we can grab data from different sheets.');
//    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));
//
//    // Now setup the migration itself.
//    $sample_path = drupal_get_path('module', 'eiti_migration') . '/sources/sample.xlsx';
//    $this->source = new MigrateSourceSpreadsheet($sample_path, 'Results');
//    $this->destination = new MigrateDestinationNode('excel-demo');
//    $this->map = new MigrateSQLMap($this->machineName,
//      array(
//        'company_name' => array(
//          'type' => 'varchar',
//          'description' => 'Company name',
//          'length' => '255',
//          'not null' => TRUE,
//        )
//      ),
//      MigrateDestinationNode::getKeySchema()
//    );
//
//    //  Mappings.
//  }
//
//  /**
//   * Simple row preparation.
//   */
//  public function prepareRow($row) {
//    // Always include this fragment at the beginning of every prepareRow()
//    // implementation, so parent classes can ignore rows.
//    if (parent::prepareRow($row) === FALSE) {
//      return FALSE;
//    }
//
//    return TRUE;
//  }
//}