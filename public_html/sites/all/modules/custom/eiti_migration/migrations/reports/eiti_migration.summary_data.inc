<?php

/**
 * @file
 *
 * Holds classes related to the summary data import process.
 *
 */

class EITISummaryDataMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Some metadata.

    // Prepare the Source.
    $path = drupal_get_path('module', 'eiti_migration') . '/sources/sample.xlsx';
    $path = drupal_realpath($path);
    $this->source = new EITIMigrateSourceSpreadsheet($path, EITI_SOURCE_SUMMARY_DATA);

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

    // Fetch the country name and look-up if we already have such a country,
    // if now, we create the entity on the fly.
    if (is_array($row->country_name)) {
      $country_name = array_pop($row->country_name);
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
      $ic_entity = entity_create('implementing_country', $ic_values);
      $ic_entity->save();
      // Save the reference.
      $row->country_name = $country_name->id;
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
      $oldBooleanValue = reset($row->{$booleanMapping});
      $row->{$booleanMapping} = $this->getBooleanListValue($oldBooleanValue);
    }
    $otherSector = 'sectors:other';
    $otherSectorValue = reset($row->{$otherSector});
    $row->{$otherSector} = ($this->checkEmptyValue($otherSectorValue)) ? NULL : $otherSectorValue;

    // Currency.
    $currencyIso = 'currency:iso';
    $row->{$currencyIso} = reset($row->{$currencyIso});
    $currencyConversion = 'currency:conversion';
    $row->{$currencyConversion} = reset($row->{$currencyConversion});

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

  /**
   * Helper function that transforms existing value to boolean-list.
   */
  private function getBooleanListValue($value) {
    $correct_value = FALSE;
    switch (strtolower($value)) {
      case 'yes':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_YES;
        break;
      case 'no':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_NO;
        break;
      case 'partially':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_PARTIALLY;
        break;
      default:
        $correct_value = NULL;
        break;
    }
    return $correct_value;
  }

  /**
   * Small helper function that checks if the value is empty or not.
   */
  private function checkEmptyValue($value) {
    $is_empty = FALSE;
    switch (strtolower($value)) {
      case 'not applicable':
      case 'not available':
      case 'n/a':
      case '<text>':
      case '<url>':
      case '':
        $is_empty = TRUE;
        break;

      default:
        $is_empty = FALSE;
        break;
    }

    // More checking <tag>.
    if ($is_empty === FALSE) {
      if (preg_match('/<.+?>/', $value)) {
        $is_empty = TRUE;
      }
    }
    return $is_empty;
  }
}
