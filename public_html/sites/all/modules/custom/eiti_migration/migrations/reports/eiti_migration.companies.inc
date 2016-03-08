<?php

/**
 * @file
 *
 * Holds classes related to the summary data import process.
 *
 */

class EITICompaniesMigration extends EITISpreadsheetMigration {

  /**
   * Overrides the default constructor.
   */
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['country'] = t('Pulled country value');

    parent::__construct($arguments);

    // Prepare the Source.
    if (isset($arguments['single_file'])) {
      $file = $arguments['single_file'];
      $real_path = drupal_realpath($file->uri);
      $real_paths = array($real_path);
    }
    else {
      $real_paths = $this->getSpreadsheetFiles();
    }

    // Check the validity.
    if (!$real_paths) {
      throw new MigrateException(t("No files in the system to import from."), Migration::MESSAGE_ERROR, MigrateMap::STATUS_FAILED);
    }
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_COMPANY);
    $this->destination = new EITIMigrateDestinationCompanies();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'column_id' => array(
          'type' => 'varchar',
          'description' => t('Column ID'),
          'length' => 64,
          'not null' => TRUE,
          'default' => '',
         )
      ),
      EITIMigrateDestinationSummaryData::getKeySchema()
    );

    // Mappings go here.
    $this->addFieldMapping('field_c_identification_number', 'company_id');
    $this->addFieldMapping('field_c_commodities', 'commodity');
    $this->addFieldMapping('name', 'company_name');
    $this->addFieldMapping('country_id', 'country_id');
  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Let's fetch the summary data so we can have the country id.
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    if (empty($summary_data_id)) {
      $msg = t('Companies not imported because there were issues with the Summary Data import.<br/>File: !file', array(
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);
    $row->country_id = $summary_data_emw->country_id->id->value();

    // Create the commodity term if needed.
    if (!$this->checkEmptyValue($row->commodity)) {
      $commodities_str = $row->commodity;
      $vocabulary = taxonomy_vocabulary_machine_name_load('company_commodities');

      $commodities_str = str_replace('and', ',', $commodities_str);
      $commodities_str = str_replace('or', ',', $commodities_str);
      $commodities_str = str_replace('/', ',', $commodities_str);
      $commodities_str = str_replace(';', ',', $commodities_str);
      $candidates = explode(',', $commodities_str);
      $commodities_terms = array();
      foreach ($candidates as $candidate) {
        $candidate = trim($candidate);
        if (!empty($candidate)) {
          // If we still have a candidate, then we try first to re-use
          // possibly existing one.
          $term = taxonomy_get_term_by_name($candidate, 'company_commodities');
          if ($term) {
            $commodities_terms[] = $term->tid;
          }
          else {
            // And if we have no such term, we create one.
            $term = new stdClass();
            $term->name = ucfirst($candidate);
            $term->vid = $vocabulary->vid;
            taxonomy_term_save($term);
            $commodities_terms[] = $term->tid;
          }
        }
      }
      $row->commodity = $commodities_terms;
    }
  }

  /**
   * Pre-final callback which allows us both check and alter the entity
   * before it's actually saved in the database.
   */
  public function prepare($entity, $row) {
    // Extra data processing?
    // Not that we need to do anything here for now.
  }
}
