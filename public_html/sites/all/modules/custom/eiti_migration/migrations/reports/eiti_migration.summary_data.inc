<?php

/**
 * @file
 *
 * Holds classes related to the summary data import process.
 *
 */

class EITISummaryDataMigration extends EITISpreadsheetMigration {

  /**
   * Overrides the default constructor.
   */
  public function __construct($arguments) {
    $this->sourceFields['file_fid'] = t('File from which the import was done.');
    parent::__construct($arguments);

    // Prepare the Source.
    if (isset($arguments['single_file'])) {
      $file = $arguments['single_file'];
      $real_path = drupal_realpath($file->uri);
      $real_paths = array($real_path);
      $this->importingFiles[$file->fid] = $real_path;
    }
    else {
      $real_paths = $this->getSpreadsheetFiles();
      $this->importingFiles = $real_paths;
    }

    // Check the validity.
    if (!$real_paths) {
      throw new MigrateException(t("No files in the system to import from."), Migration::MESSAGE_ERROR, MigrateMap::STATUS_FAILED);
    }
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_SUMMARY_DATA);

    $bundle = 'summary_data';
    $this->destination = new EITIMigrateDestinationSummaryData($bundle);

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'summary_id' => array(
          'type' => 'varchar',
          'description' => t('Summary ID'),
          'length' => 32,
          'not null' => TRUE,
          'default' => '',
         )
      ),
      EITIMigrateDestinationSummaryData::getKeySchema()
    );

    // Mappings go here.
    $this->addFieldMapping('country_id', 'country_name');
    $this->addFieldMapping('year_start', 'start_date');
    $this->addFieldMapping('year_end', 'end_date');
    $this->addFieldMapping('published', 'publish_date');
    $this->addFieldMapping('currency_code', 'currency:iso');
    $this->addFieldMapping('currency_rate', 'currency:conversion');

    // Contact person mappings.
    $this->addFieldMapping('field_sd_contact_email_address', 'contact:email');
    $this->addFieldMapping('field_sd_contact_name', 'contact:name');
    $this->addFieldMapping('field_sd_contact_organisation', 'contact:organization');

    $this->addFieldMapping('field_sd_independent_admin', 'independent_administrator');

    $this->addFieldMapping('field_sd_file_links', 'web_links');
    $this->addFieldMapping('field_sd_no_reporting_gov', 'number:reporting_gov');
    $this->addFieldMapping('field_sd_no_reporting_com', 'number:reporting_comp');

    $this->addFieldMapping('field_sd_oil_sector', 'sectors:oil');
    $this->addFieldMapping('field_sd_mining_sector', 'sectors:mining');
    $this->addFieldMapping('field_sd_gas_sector', 'sectors:gas');
    $this->addFieldMapping('field_sd_other_sector', 'sectors:other');

    $this->addFieldMapping('field_sd_report_file', 'file_fid');
    $this->addFieldMapping('field_sd_report_file:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_sd_report_file:preserve_files')
      ->defaultValue(TRUE);
    $this->addFieldMapping('field_sd_report_file:file_class')
      ->defaultValue('MigrateFileFid');

    // Unmigrated mappings.
    $this->addUnmigratedSources(array(
      'dissaggregation:revenue_stream',
      'dissaggregation:company',
      'dissaggregation:project',
    ));

    $this->addUnmigratedDestinations(array(
      'status',
      'created',
      'changed',
      'migrate_redirects',
      'path',
      'field_sd_indicator_values',
    ));
  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Prepare the file.
    $row->file_fid = array_search($row->file, $this->importingFiles);

    // Fetch the country name and look-up if we already have such a country,
    // if now, we create the entity on the fly.
    if (is_array($row->country_name)) {
      $country_name = reset($row->country_name);
    }
    else {
      $country_name = $row->country_name;
    }
    $countries = eitientity_implementing_country_lookup_by_name($country_name);
    if ($countries == FALSE) {
      $ic_values = array(
        'name' => $country_name,
        'language' => 'en',
        'type' => 'normal',
        'user_id' => 1,
        'status' => NODE_PUBLISHED,
        'created' => REQUEST_TIME,
        'changed' => REQUEST_TIME,
      );

      // Find the ISO2 standard.
      $country_object = countries_country_lookup($country_name);
      if ($country_object) {
        $ic_values['iso'] = $country_object->iso2;
      }
      else {
        $msg = t('Could not figure out the <strong>ISO2</strong> for !country', array(
          '!country' => $country_name
        ));
        $this->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
      }

      $ic_entity = entity_create('implementing_country', $ic_values);
      $ic_entity->save();
      // Save the reference.
      $row->country_name = $ic_entity->id;
    }
    else {
      $existing_country = reset($countries);
      $row->country_name = $existing_country->id;
    }

    // Normalize the sectors.
    $booleanMappings = array(
      'sectors:oil',
      'sectors:gas',
      'sectors:mining',
    );
    foreach ($booleanMappings as $booleanMapping) {
      if (isset($row->{$booleanMapping})) {
        $oldBooleanValue = reset($row->{$booleanMapping});
        $row->{$booleanMapping} = $this->getBooleanListValue($oldBooleanValue);
      }
    }
    $otherSector = 'sectors:other';
    if (isset($row->{$otherSector})) {
      $otherSectorValue = reset($row->{$otherSector});
      $row->{$otherSector} = ($this->checkEmptyValue($otherSectorValue)) ? NULL : $otherSectorValue;
    }

    // Currency.
    $currencyIso = 'currency:iso';
    if (isset($row->{$currencyIso})) {
      $row->{$currencyIso} = reset($row->{$currencyIso});
      $row->{$currencyIso} = $this->normalizeUnit($row->{$currencyIso});
      $match = NULL;

      // Try and fetch the 3 char currency.
      if (preg_match('/([A-Za-z])\w+/', $row->{$currencyIso}, $match)) {
        $row->{$currencyIso} = $match[0];
      }
      elseif (preg_match('/([0-9])\w+/', $row->{$currencyIso}, $match)) {
        $currency_ISO4217Number = $match[0];
        $found_currency = FALSE;
        foreach ($this->allCurrencies as $code => $currency) {
          if ($currency->ISO4217Number == $currency_ISO4217Number) {
            $row->{$currencyIso} = $code;
            $found_currency = TRUE;
            break;
          }
        }
        if (!$found_currency) {
          $msg = t('Could not figure out the currency: !value', array(
            '!value' => $row->{$currencyIso}
          ));
          $this->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
          $row->{$currencyIso} = '';
        }
      }
    }
    $currencyConversion = 'currency:conversion';
    if (isset($row->{$currencyConversion})) {
      $row->{$currencyConversion} = reset($row->{$currencyConversion});
    }

    // Check if links are empty.
    foreach ($row->web_links as $key => $web_link) {
      if ($this->checkEmptyValue($web_link)) {
        unset($row->web_links[$key]);
      }
    }
  }

  /**
   * Pre-final callback which allows us both check and alter the entity
   * before it's actually saved in the database.
   */
  public function prepare($entity, $row) {
    // Extra data processing?
    // dsm.
  }

}
