<?php

/**
 * @file
 * Contains EITIApiImplementingCountry.
 */

/**
 * Class EITIApiImplementingCountry
 */
class EITIApiImplementingCountry extends RestfulEntityBase {
  public $reports;
  public $licenses;
  public $contracts;
  public $revenues;
  public $metadata;

  /**
   * Overriding the defaults.
   * @var int
   */
  protected $range = 200;

  /**
   * Overrides RestfulDataProviderEFQ::__construct().
   */
  public function __construct(array $plugin, \RestfulAuthenticationManager $auth_manager = NULL, \DrupalCacheInterface $cache_controller = NULL, $language = NULL) {
    parent::__construct($plugin, $auth_manager, $cache_controller, $language);

    // This is the point where we make the extra query and then the callback
    // will fetch the extra reports from this 2nd query.
    $data = $this->queryIndicatorValues();

    $this->reports = $data['reports'];
    $this->licenses = $data['licenses'];
    $this->contracts = $data['contracts'];

    $this->revenues = $this->queryRevenues();
    $this->metadata = $this->querySummaryDataInfo();
  }

  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
    $public_fields['iso2'] = array(
      'property' => 'iso',
    );
    $public_fields['iso3'] = array(
      'callback' => array($this, 'getISO3'),
    );
    $public_fields['status'] = array(
      'property' => 'field_ic_status',
      'process_callbacks' => array(array($this, 'prepareStatus')),
    );
    $public_fields['status_date'] = array(
      'property' => 'field_ic_change_status_date',
    );
    $public_fields['leave_date'] = array(
      'property' => 'field_ic_leave_date',
    );
    $public_fields['local_website'] = array(
      'property' => 'field_ic_website',
      'sub_property' => 'url',
    );
    $public_fields['annual_report_file'] = array(
      'property' => 'field_ic_annual_reports',
      'process_callbacks' => array(array($this, 'prepareAnnualReport')),
    );
    $public_fields['reports'] = array(
      'callback' => array($this, 'getReports'),
    );
    $public_fields['metadata'] = array(
      'callback' => array($this, 'getMetadata'),
    );
    $public_fields['licenses'] = array(
      'callback' => array($this, 'getLicenses'),
    );
    $public_fields['contracts'] = array(
      'callback' => array($this, 'getContracts'),
    );
    $public_fields['revenues'] = array(
      'callback' => array($this, 'getRevenues'),
    );
    $public_fields['latest_validation_date'] = array(
      'property' => 'field_ic_validation_date',
      'process_callbacks' => array(array($this, 'prepareLatestValidationDate')),
    );
    $public_fields['latest_validation_link'] = array(
      'property' => 'field_ic_validation_link',
      'sub_property' => 'url',
    );
    $public_fields['latest_validation_url'] = array(
      'property' => 'field_ic_validation_url',
      'sub_property' => 'url',
    );

    return $public_fields;
  }

  /**
   * Gets the ISO3 for this implementing country (taking in account its iso2 value).
   *
   * @param $emw
   *   EntityMetadataWrapper object (Implementing Country).
   *
   * @return string
   *   ISO3 string value.
   */
  function getISO3($emw) {
    $iso2 = $emw->iso->value();
    $country = country_load($iso2);
    return $country->iso3;
  }

  /**
   * Gets the reports related to this implementing country.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Implementing Country).
   *
   * @return mixed
   *   Either NULL or an array of reports.
   */
  function getReports($emw) {
    $iso2 = $emw->iso->value();
    return isset($this->reports[$iso2]) ? $this->reports[$iso2] : NULL;
  }

  /**
   * Gets licenses related to this implementing country.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Implementing Country).
   *
   * @return mixed
   *   Either NULL or an array of licenses.
   */
  function getLicenses($emw) {
    $iso2 = $emw->iso->value();
    return isset($this->licenses[$iso2]) ? $this->licenses[$iso2] : NULL;
  }

  /**
   * Gets contracts related to this implementing country.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Implementing Country).
   *
   * @return mixed
   *   Either NULL or an array of licenses.
   */
  function getContracts($emw) {
    $iso2 = $emw->iso->value();
    return isset($this->contracts[$iso2]) ? $this->contracts[$iso2] : NULL;
  }

  /**
   * Gets revenues related to this implementing country.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Implementing Country).
   *
   * @return mixed
   *   Either NULL or an array of revenues grouped by ISO2, by year.
   */
  function getRevenues($emw) {
    $iso2 = $emw->iso->value();
    return isset($this->revenues[$iso2]) ? $this->revenues[$iso2] : NULL;
  }

  /**
   * Gets metadata related to this implementing country.
   *
   * @param $emw
   *  EntityMetadataWrapper object (Implementing Country).
   *
   * @return array
   */
  function getMetadata($emw) {
    $iso2 = $emw->iso->value();
    $countrySummaryDataInfo = array();

    foreach ($this->metadata as $summaryData) {
      $summaryDataEmw = entity_metadata_wrapper('summary_data', $summaryData);
      $implementingCountry = $summaryDataEmw->country_id->value();
      if ($implementingCountry && $implementingCountry->iso == $iso2) {
        $year = format_date($summaryData->year_end, 'custom', 'Y');
        $countrySummaryDataInfo[$year]['contact']['name']  = $summaryDataEmw->field_sd_contact_name->value();
        $countrySummaryDataInfo[$year]['contact']['email']  = $summaryDataEmw->field_sd_contact_email_address->value();
        $countrySummaryDataInfo[$year]['contact']['organisation']  = $summaryDataEmw->field_sd_contact_organisation->value();

        $countrySummaryDataInfo[$year]['year_start']  = $summaryDataEmw->year_start->value();
        $countrySummaryDataInfo[$year]['year_end']  = $summaryDataEmw->year_end->value();
        $countrySummaryDataInfo[$year]['currency_rate']  = $summaryDataEmw->currency_rate->value();
        $countrySummaryDataInfo[$year]['currency_code']  = $summaryDataEmw->currency_code->value();

        $sectors = array(
          'field_sd_gas_sector' => 'Gas',
          'field_sd_mining_sector' => 'Mining',
          'field_sd_oil_sector' => 'Oil',
          'field_sd_other_sector' => 'Other Sectors',
        );
        $countrySummaryDataInfo[$year]['sectors_covered'] = array();
        foreach ($sectors as $field_id => $sector) {
          if ($summaryDataEmw->{$field_id}->value()) {
            $countrySummaryDataInfo[$year]['sectors_covered'][] = $sector;
          }
        }

        $countrySummaryDataInfo[$year]['reporting_organisations'] = array();
        $countrySummaryDataInfo[$year]['reporting_organisations']['companies'] = $summaryDataEmw->field_sd_no_reporting_com->value();
        $countrySummaryDataInfo[$year]['reporting_organisations']['governmental_agencies'] = $summaryDataEmw->field_sd_no_reporting_gov->value();
        $countrySummaryDataInfo[$year]['web_report_links'] = $summaryDataEmw->field_sd_file_links->value();
        $countrySummaryDataInfo[$year]['disaggregated']['project'] = $summaryDataEmw->field_sd_disagg_project->value();
        $countrySummaryDataInfo[$year]['disaggregated']['revenue_stream'] = $summaryDataEmw->field_sd_disagg_revenue_stream->value();
        $countrySummaryDataInfo[$year]['disaggregated']['company'] = $summaryDataEmw->field_sd_disagg_company->value();
      }
    }

    return $countrySummaryDataInfo;
  }

  /**
   * A standard processing callback that returns a slim taxonomy term.
   *
   * @param $entity
   *   Implementing Country entity.
   * @return array
   */
  function prepareStatus($entity) {
    $term_emw = entity_metadata_wrapper('taxonomy_term', $entity);
    return array(
      'tid' => $entity->tid,
      'language' => $entity->language,
      'name' => $entity->name,
      'color' => $term_emw->field_tx_country_color->value(),
    );
  }

  /**
   * A standard processing callback that returns just latest (highest delta) report.
   *
   * @param $entity
   *   Implementing Country entity.
   * @return array
   */
  function prepareAnnualReport($values) {
    $last_annual_report = end($values);
    return file_create_url($last_annual_report['uri']);
  }

  /**
   * A standard processing callback that returns latest validation year.
   *
   * @return array
   */
  function prepareLatestValidationDate($date) {
    return date('Y', $date);
  }

  /**
   * Helper function that basically builds and executes the query to retrieve all
   * of the reports.
   */
  function queryIndicatorValues() {
    $version = $this->getVersion();
    $cid_parts_arr[] = 'v' . $version['major'] . '.' . $version['minor'] . '::' . $this->getResourceName();
    $cid_parts_arr[] = 'queryIndicatorValues';
    $cid = implode('::', $cid_parts_arr);

    $cache = $this->getCacheController()->get($cid);
    if (!empty($cache->data)) {
      //return $cache->data;
    }

    $query = db_select('eiti_summary_data', 'sd');
    // One big query.
    $query->leftJoin('field_data_field_sd_indicator_values', 'fiv', 'fiv.entity_id = sd.id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('eiti_indicator_value', 'iv', 'fiv.field_sd_indicator_values_target_id = iv.id');
    $query->leftJoin('eiti_indicator', 'i', 'i.id = iv.indicator_id');
    $query->leftJoin('eiti_indicator', 'ip', 'i.parent = ip.id');

    $query->addField('sd', 'year_end', 'year');
    $query->addField('i', 'name', 'commodity');
    $query->addField('ip', 'name', 'parent');
    $query->addField('ic', 'iso', 'iso2');
    $query->addField('ic', 'id', 'id');
    $query->addField('iv', 'value_numeric', 'value');
    $query->addField('iv', 'value_boolean', 'value_bool');
    $query->addField('iv', 'value_text', 'value_text');
    $query->addField('iv', 'value_unit', 'unit');
    $query->addField('iv', 'source', 'source');

    $query->condition('sd.status', TRUE);

    $result = $query->execute();
    $records = array();

    // Just grab all the data.
    while ($record = $result->fetchAssoc()) {
      $records[] = $record;
    }

    // Now let's polish it.
    $reports = array();
    $licenses = array();
    $contracts = array();
    $licenses_indicators = array(
      'Public registry of licences, oil',
      'Public registry of licences, mining',
      'If incomplete or not available, provide an explanation',
    );
    $contract_indicators = array(
      'Does the report address the government\'s policy on contract disclosure?',
      'Are contracts disclosed?',
      'Publicly available registry of contracts',
      'Registry 2',
    );

    foreach ($records as $record) {
      $year = format_date($record['year'], 'custom', 'Y');
      $iso2 = $record['iso2'];

      // Add simple values.
      if (!is_null($record['value'])) {
        unset($record['year']);
        unset($record['iso2']);
        $reports[$iso2][$year][] = $record;
      }

      // Now let's check for licenses, if they have a valid URL.
      if (in_array($record['commodity'], $licenses_indicators)) {
        if (valid_url($record['value_text'])) {
          $licenses[$iso2][$year][$record['commodity']] = $record['value_text'];
        }
        if (valid_url($record['source'])) {
          $licenses[$iso2][$year][$record['commodity']] = $record['source'];
        }
      }

      // And continuing with the contracts.
      if (in_array($record['commodity'], $contract_indicators)) {
        if (isset($record['value_text'])) {
          $contracts[$iso2][$year][$record['commodity']] = $record['value_text'];
          if ($record['commodity'] === 'Publicly available registry of contracts') {
            $contracts[$iso2][$year]['contract_registry_url'] = $record['source'];
          }
        }
        elseif (isset($record['value_bool'])) {
          $contracts[$iso2][$year][$record['commodity']] = $record['value_bool'];
        }
      }
    }

    $output = array(
      'reports' => $reports,
      'licenses' => $licenses,
      'contracts' => $contracts,
    );
    $this->getCacheController()->set($cid, $output, CACHE_TEMPORARY);
    return $output;
  }

  /**
   * Helper function that basically builds and executes the query to retrieve all
   * of the revenues from the SummaryData.
   */
  function queryRevenues() {
    $revenues = array();
    $version = $this->getVersion();
    $cid_parts_arr[] = 'v' . $version['major'] . '.' . $version['minor'] . '::' . $this->getResourceName();
    $cid_parts_arr[] = 'queryRevenues';
    $cid = implode('::', $cid_parts_arr);

    $cache = $this->getCacheController()->get($cid);
    if (!empty($cache->data)) {
      return $cache->data;
    }

    // First we want to see the sum of all the governmental agencies for each country
    // for each year.
    $query = db_select('eiti_summary_data', 'sd');

    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('field_data_field_sd_revenue_government', 'fgrs', 'fgrs.entity_id = sd.id');
    $query->leftJoin('eiti_revenue_stream', 'grs', 'fgrs.field_sd_revenue_government_target_id = grs.id');

    // Now let's add some expressions.
    $query->addExpression("date_part('year', to_timestamp(sd.year_end))", 'year');
    $query->addExpression("sum(grs.revenue)", 'sum');
    $query->addField('ic', 'iso', 'iso2');

    $query->condition('sd.status', TRUE);
    $query->condition('grs.type', 'agency');
    $query->condition('grs.revenue', 0, '>');

    $query->groupBy('year');
    $query->groupBy('iso2');

    $results = $query->execute();
    $records = array();
    while ($record = $results->fetchAssoc()) {
      $records[] = $record;
    }

    // Now let's form a well-polished array: iso2 > year > revenues (government).
    foreach ($records as $record) {
      $revenues[$record['iso2']][$record['year']]['government'] = $record['sum'];
    }

    // Second we want to see the sum of all the reporting companies for each country
    // for each year.
    $query = db_select('eiti_summary_data', 'sd');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('field_data_field_sd_revenue_company', 'cgrs', 'cgrs.entity_id = sd.id');
    $query->leftJoin('eiti_revenue_stream', 'crs', 'cgrs.field_sd_revenue_company_target_id = crs.id');

    // Now let's add some expressions.
    $query->addExpression("date_part('year', to_timestamp(sd.year_end))", 'year');
    $query->addExpression("sum(crs.revenue)", 'sum');
    $query->addField('ic', 'iso', 'iso2');

    $query->condition('sd.status', TRUE);
    $query->condition('crs.type', 'company');
    $query->condition('crs.revenue', 0, '>');

    $query->groupBy('year');
    $query->groupBy('iso2');

    $results = $query->execute();
    $records = array();
    while ($record = $results->fetchAssoc()) {
      $records[] = $record;
    }

    // Now let's form a well-polished array: iso2 > year > revenues (company).
    foreach ($records as $record) {
      $revenues[$record['iso2']][$record['year']]['company'] = $record['sum'];
    }
    $this->getCacheController()->set($cid, $revenues, CACHE_TEMPORARY);
    return $revenues;
  }

  /**
   * Helper function that basically builds and executes the query to retrieve all
   * of Info MetaData from the SummaryData.
   */
  public function querySummaryDataInfo() {
    $output = array();
    $version = $this->getVersion();
    $cid_parts_arr[] = 'v' . $version['major'] . '.' . $version['minor'] . '::' . $this->getResourceName();
    $cid_parts_arr[] = 'querySummaryDataInfo';
    $cid = implode('::', $cid_parts_arr);

    $cache = $this->getCacheController()->get($cid);
    if (!empty($cache->data)) {
      return $cache->data;
    }

    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'summary_data')
      ->propertyCondition('status', '1')
      ->execute();

    if (!empty($result['summary_data'])) {
      $entity_ids = array_keys($result['summary_data']);
      $entities = entity_load('summary_data', $entity_ids);
      $output = array_values($entities);
    }
    $this->getCacheController()->set($cid, $output, CACHE_TEMPORARY);
    return $output;
  }
}
