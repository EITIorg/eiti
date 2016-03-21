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
  public $revenues;

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
    $public_fields['local_website'] = array(
      'property' => 'field_ic_website',
      'sub_property' => 'url',
    );
    $public_fields['reports'] = array(
      'callback' => array($this, 'getReports'),
    );
    $public_fields['licenses'] = array(
      'callback' => array($this, 'getLicenses'),
    );
    $public_fields['revenues'] = array(
      'callback' => array($this, 'getRevenues'),
    );

    return $public_fields;
  }

  /**
   * Overrides the default getList method.
   */
  public function getList() {
    // This is the point where we make the extra query and then the callback
    // will fetch the extra reports from this 2nd query.
    $data = $this->queryIndicatorValues();

    $this->reports = $data['reports'];
    $this->licenses = $data['licenses'];
    $this->revenues = $this->queryRevenues();

    $return = parent::getList();
    return $return;
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
   * A standard processing callback that returns a slim taxonomy term.
   *
   * @param $entity
   *   Implementing Country entity.
   * @return array
   */
  function prepareStatus($entity) {
    return array(
      'tid' => $entity->tid,
      'language' => $entity->language,
      'name' => $entity->name,
    );
  }

  /**
   * Helper function that basically builds and executes the query to retrieve all
   * of the reports.
   */
  function queryIndicatorValues() {
    $query = db_select('eiti_summary_data', 'sd');

    // One big query.
    $query->leftJoin('field_data_field_sd_indicator_values', 'fiv', 'fiv.entity_id = sd.id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('eiti_indicator_value', 'iv', 'fiv.field_sd_indicator_values_target_id = iv.id');
    $query->leftJoin('eiti_indicator', 'i', 'i.id = iv.indicator_id');

    $query->addField('sd', 'year_end', 'year');
    $query->addField('i', 'name', 'commodity');
    $query->addField('ic', 'iso', 'iso2');
    $query->addField('ic', 'id', 'id');
    $query->addField('iv', 'value_numeric', 'value');
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
    $licenses_indicators = array(
      'Public registry of licences, oil',
      'Public registry of licences, mining',
      'If incomplete or not available, provide an explanation',
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
        if (valid_url($record['value_text'], TRUE)) {
          $licenses[$iso2][$year][] = $record['value_text'];
        }
        elseif (valid_url($record['source'], TRUE)) {
          $licenses[$iso2][$year][] = $record['source'];
        }
      }
    }

    return array(
      'reports' => $reports,
      'licenses' => $licenses,
    );
  }

  /**
   * Helper function that basically builds and executes the query to retrieve all
   * of the revenues from the SummaryData.
   */
  function queryRevenues() {
    $revenues = array();

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

    return $revenues;
  }
}
