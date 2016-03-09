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

  /**
   * $var array
   *
   * Stores the pre-loaded summary-data entity metadata wrappers, with hash-keys
   * pointing at them.
   */
  public $summary_data_emws;

  /**
   * Overrides the default constructor.
   */
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['original_revenue'] = t('Original Numeric Revenue Value.');
    $this->sourceFields['original_currency'] = t('Original Currency');

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
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_REVENUE_GOVERNMENT);
    $this->destination = new EITIMigrateDestinationRevenues('agency');

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
    $this->addFieldMapping('original_revenue', 'original_revenue');
    $this->addFieldMapping('original_currency', 'original_currency');

    // Store all the codes here.
    $this->codes = eitientity_gfs_code_get_by_bundle('gfs_code');
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
    if (!empty($this->summary_data_emws) && in_array($row->summary_id, array_keys($this->summary_data_emws))) {
      $summary_data_emw = $this->summary_data_emws[$row->summary_id];
    }
    else {
      $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
      if (empty($summary_data_id)) {
        $msg = t('Revenue streams not imported because there were issues with the Summary Data import.<br/>File: !file', array(
          '!file' => $row->file,
        ));
        $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
        return FALSE;
      }
      $summary_data = entity_load_single('summary_data', $summary_data_id);
      $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

      // Store for others to retrieve it later.
      $this->summary_data_emws[$row->summary_id] = $summary_data_emw;
    }

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

    // We don't want to skip the not applicable and not included values. Just inform.
    if ((strtolower($row->gfs_status) == 'not applicable') || (strtolower($row->gfs_status) == 'not included')) {
      $msg = t('Revenue stream !name - is not applicable or not included.<br/>Skipped this item.<br/>File: !file', array(
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_WARNING);
      return FALSE;
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
        $country_id = $summary_data_emw->country_id->id->value();
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

    // Normalize the currency to USD (but keep the originals in the original fields).
    $row->original_revenue = $row->revenue;
    $row->original_currency = $row->currency;

    $multiplier = $this->getCurrencyMultiplier($row->currency);
    $row->revenue *= $multiplier;
    if ($row->currency !== 'USD') {
      $row->currency = 'USD';
      $rate = $summary_data_emw->currency_rate->value();
      $row->revenue = round($row->revenue / $rate);
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
    // One thing we need to do, is to look-up the summary_data id, load it and
    // save the revenue stream id in the field "field_sd_revenue_government".
    if (!empty($this->summary_data_emws) && in_array($row->summary_id, array_keys($this->summary_data_emws))) {
      $summary_data_emw = &$this->summary_data_emws[$row->summary_id];
      // Append the revenue.
      $summary_data_emw->field_sd_revenue_government[] = $entity->id;
    }
    else {
      $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
      $summary_data = entity_load_single('summary_data', $summary_data_id);
      $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

      // Append the revenue.
      $summary_data_emw->field_sd_revenue_government[] = $entity->id;

      // Store for others to retrieve it later.
      $this->summary_data_emws[$row->summary_id] = $summary_data_emw;
    }
  }


  /**
   * Move expensive things here.
   */
  public function postImport() {
    parent::postImport();

    // Save previously updated summary data.
    if (!empty($this->summary_data_emws)) {
      foreach ($this->summary_data_emws as $hash => $summary_data_emw) {
        $summary_data_emw->save();
      }
    }
  }
}


/**
 * Class EITIRevenueStreamsCompaniesMigration
 *
 * Migrates the Revenue Streams for the Companies.
 */
class EITIRevenueStreamsCompaniesMigration extends EITIRevenueStreamMigration {

  /**
   * $var array
   *
   * Stores the pre-loaded summary-data entity metadata wrappers, with hash-keys
   * pointing at them.
   */
  public $summary_data_emws;

  /**
   * Overrides the default constructor.
   */
  public function __construct($arguments) {
    $this->sourceFields['original_revenue'] = t('Original Numeric Revenue Value.');
    $this->sourceFields['original_currency'] = t('Original Currency');

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
    $this->addFieldMapping('original_revenue', 'original_revenue');
    $this->addFieldMapping('original_currency', 'original_currency');

    // Store all the codes here.
    $this->codes = eitientity_gfs_code_get_by_bundle('gfs_code');
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
    if (!empty($this->summary_data_emws) && in_array($row->summary_id, array_keys($this->summary_data_emws))) {
      $summary_data_emw = $this->summary_data_emws[$row->summary_id];
    }
    else {
      $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
      if (empty($summary_data_id)) {
        $msg = t('Revenue streams not imported because there were issues with the Summary Data import.<br/>File: !file', array(
          '!file' => $row->file,
        ));
        $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
        return FALSE;
      }
      $summary_data = entity_load_single('summary_data', $summary_data_id);
      $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

      // Store for others to retrieve it later.
      $this->summary_data_emws[$row->summary_id] = $summary_data_emw;
    }

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

    // We don't want to skip the not applicable and not included values. Just inform.
    if ((strtolower($row->gfs_status) == 'not applicable') || (strtolower($row->gfs_status) == 'not included')) {
      $msg = t('Revenue stream !name - is not applicable or not included.<br/>Skipped this item.<br/>File: !file', array(
        '!name' => '<strong>' . $code->code . ' (' . $code->name . ') ' . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_WARNING);
      return FALSE;
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

    // Normalize the currency to USD (but keep the originals in the original fields).
    $row->original_revenue = $row->revenue;
    $row->original_currency = $row->currency;
    $multiplier = $this->getCurrencyMultiplier($row->currency);
    $row->revenue *= $multiplier;
    if ($row->currency !== 'USD') {
      $row->currency = 'USD';
      $rate = $summary_data_emw->currency_rate->value();
      $row->revenue = round($row->revenue / $rate);
    }
  }

  /**
   * Pre-final callback which allows us both check and alter the entity
   * before it's actually saved in the database.
   */
  public function prepare($entity, $row) {
    // We don't want import streams that don't have organisation_id.
    if (empty($entity->organisation_id)) {
      // Now cancel the creation of the node.
      throw new MigrateException(t('Revenue streams not imported because organisation_id is empty (probably it is related to sub-totals column).<br/>File: !file', array(
        '!file' => $row->file,
      )), Migration::MESSAGE_NOTICE, MigrateMap::STATUS_IGNORED);
    }
  }

  /**
   * Finally the entity is saved, we have the id and we can now do some
   * of the post-processing.
   */
  public function complete($entity, $row) {
    // One thing we need to do, is to look-up the summary_data id, load it and
    // save the revenue stream id in the field "field_sd_revenue_government".
    if (!empty($this->summary_data_emws) && in_array($row->summary_id, array_keys($this->summary_data_emws))) {
      $summary_data_emw = &$this->summary_data_emws[$row->summary_id];
      // Append the revenue.
      $summary_data_emw->field_sd_revenue_company[] = $entity->id;
    }
    else {
      $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
      $summary_data = entity_load_single('summary_data', $summary_data_id);
      $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);

      // Append the revenue.
      $summary_data_emw->field_sd_revenue_company[] = $entity->id;

      // Store for others to retrieve it later.
      $this->summary_data_emws[$row->summary_id] = $summary_data_emw;
    }
  }

  /**
   * Move expensive things here.
   */
  public function postImport() {
    parent::postImport();

    // Save previously updated summary data.
    if (!empty($this->summary_data_emws)) {
      foreach ($this->summary_data_emws as $hash => $summary_data_emw) {
        $summary_data_emw->save();
      }
    }
  }
}
