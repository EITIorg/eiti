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
    $this->addFieldMapping('name', 'company_name');
    $this->addFieldMapping('summary_data_id', 'summary_data_id');
    $this->addFieldMapping('country_id', 'country_id');
    $this->addFieldMapping('identification_number', 'company_id');
    $this->addFieldMapping('field_o_sector', 'sector');
    $this->addFieldMapping('field_o_commodities', 'commodity');
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
    $row->summary_data_id = $summary_data_id;
    $row->country_id = $summary_data_emw->country_id->id->value();

    // Create the sector term if needed.
    if (!$this->checkEmptyValue($row->sector)) {
      $sector_str = trim($row->sector);
      $sector_term = FALSE;
      $vocabulary = taxonomy_vocabulary_machine_name_load('company_sectors');

      if (!empty($sector_str)) {
        // If we still have a candidate, then we try first to re-use
        // possibly existing one.
        $sector_str = ucfirst($sector_str);
        $term = taxonomy_get_term_by_name($sector_str, 'company_sectors');
        if ($term) {
          $sector_term = $term->tid;
        }
        else {
          // And if we have no such term, we create one.
          $term = new stdClass();
          $term->name = $sector_str;
          $term->vid = $vocabulary->vid;
          taxonomy_term_save($term);
          $sector_term = $term->tid;
        }
      }

      $row->sector = $sector_term;
    }

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
          $candidate = ucfirst($candidate);
          $term = taxonomy_get_term_by_name($candidate, 'company_commodities');
          if ($term) {
            $commodities_terms[] = $term->tid;
          }
          else {
            // And if we have no such term, we create one.
            $term = new stdClass();
            $term->name = $candidate;
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
    // Check if the name is there.
    if ($this->checkEmptyValue($entity->name)) {
      // Now cancel the creation of the node.
      throw new MigrateException(t('Companies with no name, are NOT imported (probably that is a sub-totals column).<br/>File: !file', array(
        '!file' => $row->file,
      )), Migration::MESSAGE_NOTICE, MigrateMap::STATUS_IGNORED);
    }
  }
}
