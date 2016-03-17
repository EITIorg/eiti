<?php

/**
 * @file
 * Contains EITIApiImplementingCountry.
 */

/**
 * Class EITIApiImplementingCountry
 */
class EITIApiImplementingCountry extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
//    $public_fields['indicator_id'] = array(
//      'property' => 'name',
//    );
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

    return $public_fields;
  }


  /**
   * Overrides the default getList method.
   */
  public function getList() {
    // This is the point where we make the extra query and then the callback
    // will fetch the extra reports from this 2nd query.
    $this->reports = $this->queryForReports();

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
    if (isset($this->reports[$iso2])) {
      return $this->reports[$iso2];
    }
    else return NULL;
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
  function queryForReports() {
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
    $query->addField('iv', 'value_unit', 'unit');

    $query->condition('sd.status', TRUE);
    $query->isNotNull('iv.value_numeric');

    $result = $query->execute();
    $output = array();

    while ($record = $result->fetchAssoc()) {
      $year = format_date($record['year'], 'custom', 'Y');
      $output[$record['iso2']][$year] = $record;
    }

    return $output;
  }
}
