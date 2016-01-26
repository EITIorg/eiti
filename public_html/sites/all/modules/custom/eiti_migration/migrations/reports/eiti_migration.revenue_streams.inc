<?php

/**
 * @file
 *
 * Holds classes related to the summary data import process.
 *
 */

class EITIRevenueStreamsGovernmentMigration extends EITISpreadsheetMigration {
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    parent::__construct($arguments);

    // Prepare the Source.
    $path = drupal_get_path('module', 'eiti_migration') . '/sources';
    $files_xlsx = file_scan_directory($path, '/.*\.xlsx$/');
    $files_xls = file_scan_directory($path, '/.*\.xls$/');
    $files = $files_xlsx + $files_xls;
    $real_paths = array();
    foreach ($files as $file_path => $file) {
      $real_paths[] = drupal_realpath($file_path);
    }
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_REVENUE_GOVERNMENT);
    $this->destination = new EITIMigrateDestinationIndicatorValue();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'row_id' => array(
          'type' => 'varchar',
          'description' => t('Row ID'),
          'length' => 64,
          'not null' => TRUE,
          'default' => '',
         )
      ),
      EITIMigrateDestinationSummaryData::getKeySchema()
    );

    // Mappings go here.
//    $this->addFieldMapping('indicator_id', 'subgroup');
//    $this->addFieldMapping('value_boolean', 'value_boolean');

  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    return FALSE;
  }

  /**
   * Pre-final callback which allows us both check and alter the entity
   * before it's actually saved in the database.
   */
  public function prepare($entity, $row) {
    // Extra data processing?
    // Not that we need to do anything here for now.
  }

  /**
   * Finally the entity is saved, we have the id and we can now do some
   * of the post-processing.
   */
  public function complete($entity, $row) {
    // One thing we need to do, is to look-up the summary_data id, load it and
    // save the indicator id in the field "field_sd_indicator_values".
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);
    $summary_data_emw->field_sd_indicator_values[] = $entity->id;
    $summary_data_emw->save();
  }

}
