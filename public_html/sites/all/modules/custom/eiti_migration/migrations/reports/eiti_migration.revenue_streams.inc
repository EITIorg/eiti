<?php

/**
 * Class EITIRevenueStreamMigration
 *
 * Common small class with some functions shared between both Gov and Company
 * revenue stream migrations.
 */
class EITIRevenueStreamMigration extends EITISpreadsheetMigration {
  /**
   * Small function that looks up the code.
   */
  public function GFSCodeLookup($code) {
    foreach($this->codes as $code_obj) {
      if (strtolower($code_obj->code) == strtolower($code)) {
        return $code_obj;
      }
    }
    return FALSE;
  }

  /**
   * Small function that looks up the code.
   */
  public function parseReportStatus($status) {
    $status = strtolower($status);
    switch ($status) {
      case 'included and reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_RECONCILED;
        break;
      case 'included partially reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_PARTIALLY_RECONCILED;
        break;
      case 'included not reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_NOT_RECONCILED;
        break;
    }
    return FALSE;
  }
}


/**
 * Class EITIRevenueStreamsGovernmentMigration
 *
 * Migrates the Revenue Streams for Government Organizations.
 */
class EITIRevenueStreamsGovernmentMigration extends EITIRevenueStreamMigration {
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
    $this->destination = new EITIMigrateDestinationRevenues('government_agency');

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
    $this->addFieldMapping('gfs_code_id', 'gfs_id');
    $this->addFieldMapping('report_status', 'gfs_status');
    $this->addFieldMapping('name', 'revenue_stream');
    $this->addFieldMapping('organisation_id', 'organization');
    $this->addFieldMapping('revenue', 'revenue');
    $this->addFieldMapping('currency', 'currency');
    $this->addFieldMapping('original_revenue', 'revenue');
    $this->addFieldMapping('original_currency', 'currency');

    // Store all the codes here.
    $this->codes = eitientity_gfs_code_get_by_code('gfs_code');
  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Let's fetch the summary data so we can fetch additional data from it.
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

    // Look-up the GFS code.
    if ($code = $this->GFSCodeLookup($row->gfs_id)) {
      $row->gfs_id = $code->id;
    }
    else {
      $msg = t('Code !code - was not found!.<br/>File: !file', array(
        '!code' => '<strong>' . $row->gfs_id . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    // We want to skip the not applicable and not included values.
    if ((strtolower($row->gfs_status) == 'not applicable') || (strtolower($row->gfs_status) == 'not included')) {
      $msg = t('Revenue stream !name - is not applicable or not included, therefore, skipped.<br/>File: !file', array(
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
    }

    // Let's go on with the status.
    $row->report_status = $this->parseReportStatus($row->gfs_status);

    // Find the organization or create one.
    if (!empty($row->organization)) {
      if ($orgs = eitientity_organisation_lookup_by_name($row->organization)) {
        $org = reset($orgs);
        $row->organization = $org->id;
      }
      else {
        $country_id = $summary_data_emw->country_id->value();
        $values = array(
          'type' => 'agency',
          'name' => $row->organization,
          'country_id' => $country_id,
          'status' => NODE_PUBLISHED,
          'created' => REQUEST_TIME,
          'changed' => REQUEST_TIME,
        );
        $org = entity_create('organisation', $values);
        $org->save();
        $row->organization = $org->id;
      }
    }

    // Now polish the currency, if it's empty, grab it from the Summary Data.
    if (empty($row->currency) || strpos(strtolower($row->currency), 'example') !== FALSE) {
      $row->currency = $summary_data_emw->currency_code->value();
    }

    // And now the revenues themselves.
    // We skip the ones with the weird value.
    if (!$this->checkEmptyValue($row->revenue) && !is_numeric($row->revenue)) {
      $msg = t('Revenue stream !name - has a non-numeric value: !value.<br/>File: !file', array(
        '!value' => $row->revenue,
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
  }

  /**
   * Small function that looks up the code.
   */
  public function GFSCodeLookup($code) {
    foreach($this->codes as $code_obj) {
      if (strtolower($code_obj->code) == strtolower($code)) {
        return $code_obj;
      }
    }
    return FALSE;
  }

  /**
  /**
   * Small function that looks up the code.
   */
  public function parseReportStatus($status) {
    $status = strtolower($status);
    switch ($status) {
      case 'included and reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_RECONCILED;
        break;
      case 'included partially reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_PARTIALLY_RECONCILED;
        break;
      case 'included not reconciled':
        return EITIENTITY_REVENUE_STREAM_REPORT_INCLUDED_NOT_RECONCILED;
        break;
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
//    // One thing we need to do, is to look-up the summary_data id, load it and
//    // save the indicator id in the field "field_sd_indicator_values".
//    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
//    $summary_data = entity_load_single('summary_data', $summary_data_id);
//    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);
//    $summary_data_emw->field_sd_indicator_values[] = $entity->id;
//    $summary_data_emw->save();
  }
}


/**
 * Class EITIRevenueStreamsCompaniesMigration
 *
 * Migrates the Revenue Streams for the Companies.
 */
class EITIRevenueStreamsCompaniesMigration extends EITIRevenueStreamMigration {
  public function __construct($arguments) {
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
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_REVENUE_COMPANY);
    $this->destination = new EITIMigrateDestinationRevenues('company');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'position_id' => array(
          'type' => 'varchar',
          'description' => t('Position ID (row:column)'),
          'length' => 64,
          'not null' => TRUE,
          'default' => '',
        )
      ),
      EITIMigrateDestinationSummaryData::getKeySchema()
    );

    // Mappings go here.
    $this->addFieldMapping('gfs_code_id', 'gfs_id');
    $this->addFieldMapping('report_status', 'gfs_status');
    $this->addFieldMapping('name', 'revenue_stream');
    $this->addFieldMapping('organisation_id', 'column_id')->sourceMigration(array('EITICompaniesMigration'));
    $this->addFieldMapping('revenue', 'revenue');
    $this->addFieldMapping('currency', 'currency');
    $this->addFieldMapping('original_revenue', 'revenue');
    $this->addFieldMapping('original_currency', 'currency');

    // Store all the codes here.
    $this->codes = eitientity_gfs_code_get_by_code('gfs_code');
  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Let's fetch the summary data so we can fetch additional data from it.
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

    // Look-up the GFS code.
    if ($code = $this->GFSCodeLookup($row->gfs_id)) {
      $row->gfs_id = $code->id;
    }
    else {
      $msg = t('Code !code - was not found!.<br/>File: !file', array(
        '!code' => '<strong>' . $row->gfs_id . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    // We want to skip the not applicable and not included values.
    if ((strtolower($row->gfs_status) == 'not applicable') || (strtolower($row->gfs_status) == 'not included')) {
      $msg = t('Revenue stream !name - is not applicable or not included, therefore, skipped.<br/>File: !file', array(
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
    }

    // Let's go on with the status.
    $row->report_status = $this->parseReportStatus($row->gfs_status);

    // Now polish the currency, if it's empty, grab it from the Summary Data.
    if (empty($row->currency) || strpos(strtolower($row->currency), 'example') !== FALSE) {
      $row->currency = $summary_data_emw->currency_code->value();
    }

    // And now the revenues themselves.
    // We skip the ones with the weird value.
    if (!$this->checkEmptyValue($row->revenue) && !is_numeric($row->revenue)) {
      $msg = t('Revenue stream !name - has a non-numeric value: !value.<br/>File: !file', array(
        '!value' => $row->revenue,
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
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
