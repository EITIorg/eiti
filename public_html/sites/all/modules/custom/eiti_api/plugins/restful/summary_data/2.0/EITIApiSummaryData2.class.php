<?php

/**
 * @file
 * Contains EITIApiSummaryData2.
 */

/**
 * Class EITIApiSummaryData2
 */
class EITIApiSummaryData2 extends EITIApiSummaryData {

  public $revenues;

  public $indicator_groups;

  /**
   * Overrides RestfulDataProviderEFQ::__construct().
   */
  public function __construct(array $plugin, \RestfulAuthenticationManager $auth_manager = NULL, \DrupalCacheInterface $cache_controller = NULL, $language = NULL) {
    parent::__construct($plugin, $auth_manager, $cache_controller, $language);

    $this->revenues = $this->queryRevenues();
    $this->indicator_groups = $this->getIndicatorGroupDisplayNames();
  }

  /**
   * Overrides EITIApiSummaryData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'id2',
    );
    $public_fields['label']['process_callbacks'][] = array($this, 'processLabel');
    $public_fields['government_entities_nr']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['company_entities_nr']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['year_start']['process_callbacks'][] = 'eiti_api_date_to_iso_8601_partial';
    $public_fields['year_end']['process_callbacks'][] = 'eiti_api_date_to_iso_8601_partial';
    $public_fields['sector_oil']['process_callbacks'][] = 'eiti_api_value_to_boolean';
    $public_fields['sector_mining']['process_callbacks'][] = 'eiti_api_value_to_boolean';
    $public_fields['sector_gas']['process_callbacks'][] = 'eiti_api_value_to_boolean';

    $public_fields['country'] = array(
      'property' => 'country_id',
      'callback' => array($this, 'getCountryApiUrl')
    );
    $public_fields['indicator_values'] = array(
      'property' => 'field_sd_indicator_values',
      'callback' => array($this, 'getIndicatorValueApiUrls')
    );
    $public_fields['revenue_government']['callback'] = array($this, 'getGovernmentRevenueApiUrls');
    $public_fields['revenue_company']['callback'] = array($this, 'getCompanyRevenueApiUrls');

    unset($public_fields['email']);
    $public_fields['contact'] = array(
      'callback' => array($this, 'getContactInformation'),
    );
    $public_fields['currency_rate'] = array(
      'property' => 'currency_rate',
      'process_callbacks' => array('eiti_api_numeric_string_to_float'),
    );
    $public_fields['currency_code'] = array(
      'property' => 'currency_code',
    );
    $public_fields['disaggregated'] = array(
      'callback' => array($this, 'getDisaggregatedData'),
    );
    $public_fields['revenue_government_sum'] = array(
      'callback' => array($this, 'getRevenueGovernmentSum'),
    );
    $public_fields['revenue_company_sum'] = array(
      'callback' => array($this, 'getRevenueCompanySum'),
    );
    $public_fields['company_identifier_name'] = array(
      'property' => 'company_id_name',
    );
    $public_fields['company_identifier_name_register'] = array(
      'property' => 'company_id_register',
    );
    $public_fields['company_identifier_register_url'] = array(
      'property' => 'company_id_register_url',
    );

    return $public_fields;
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      if (isset($filter['public_field'], $filter['value'][0])) {
        // Date to timestamp.
        if ($filter['public_field'] == 'year_start') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        elseif ($filter['public_field'] == 'year_end') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        // Note that with ISO 8601 (YYYY-MM-DDThh:mm:ss+hh:mm) format the + symbol has to be encoded in the url (%2B).
        // "2016-06-06T11:04:36%2B00:00" and "2016-06-06T11:04:36" give the same result.
        elseif ($filter['public_field'] == 'created') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        elseif ($filter['public_field'] == 'changed') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        // Country ISO to ID.
        elseif ($filter['public_field'] == 'country') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = eitientity_implementing_country_get_id(strtoupper($v));
          }
        }
      }
    }
    return $filters;
  }

  /**
   * Overrides \RestfulEntityBase::getList().
   *
   * Entities need to be loaded via their ID2 code.
   */
  public function getList() {
    $request = $this->getRequest();
    $autocomplete_options = $this->getPluginKey('autocomplete');
    if (!empty($autocomplete_options['enable']) && isset($request['autocomplete']['string'])) {
      // Return autocomplete list.
      return $this->getListForAutocomplete();
    }

    $entity_type = $this->entityType;
    $result = $this
      ->getQueryForList()
      ->execute();

    if (empty($result[$entity_type])) {
      return array();
    }

    $ids = array_keys($result[$entity_type]);

    // Get the results with their ID2 code.
    $id2_query = db_select('eiti_summary_data', 'sd');
    $id2_query->fields('sd', array('id', 'id2'));
    $id2_query->condition('id', $ids, 'IN');
    $id2_query_results = $id2_query->execute()->fetchAllKeyed();
    // Get original order with ID2 code as the key.
    $id2_results = array();
    foreach ($ids as $id) {
      if (isset($id2_query_results[$id])) {
        $id2_results[$id2_query_results[$id]] = $id;
      }
    }

    // Pre-load all entities if there is no render cache.
    $cache_info = $this->getPluginKey('render_cache');
    if (!$cache_info['render']) {
      entity_load($entity_type, $id2_results);
    }

    $return = array();

    // If no IDs were requested, we should not throw an exception in case an
    // entity is un-accessible by the user.
    foreach ($id2_results as $id2 => $id) {
      if ($row = $this->viewEntity($id2)) {
        $return[] = $row;
      }
    }

    return $return;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Wrap viewEntity to load the summary data via it's id2 code.
   */
  public function viewEntity($id2) {
    $id2 = strtoupper($id2);
    $efq = new EntityFieldQuery();
    $efq_results = $efq->entityCondition('entity_type', 'summary_data')
      ->propertyCondition('type', 'summary_data')
      ->propertyCondition('status', 1)
      ->propertyCondition('id2', $id2)
      ->range(0, 1)
      ->execute();

    if (empty($efq_results['summary_data'])) {
      throw new \RestfulBadRequestException(format_string('Summary data with the given ID is not available.'));
    }

    $id = key($efq_results['summary_data']);
    return parent::viewEntity($id);
  }

  /**
   * Overrides \RestfulEntityBase::getEntitySelf().
   */
  protected function getEntitySelf(\EntityMetadataWrapper $wrapper) {
    return $this->versionedUrl($wrapper->id2->value());
  }

  /**
   * A standard processing callback for the label.
   */
  function processLabel($label) {
    $label = str_replace(':', '', $label);
    return $label;
  }

  /**
   * Gets the implementing country API url.
   */
  function getCountryApiUrl($emw) {
    if (isset($emw->country_id)) {
      $country = $emw->country_id->value();
      if (isset($country->iso)) {
        return url('api/v2.0/implementing_country/' . $country->iso, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the indicator value API urls.
   */
  function getIndicatorValueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_indicator_values)) {
      $values = $emw->field_sd_indicator_values->value();
      if (is_array($values)) {
        foreach ($values as $value) {
          $url = url('api/v2.0/indicator_value/' . $value->id, array('absolute' => TRUE));
          if (isset($this->indicator_groups[$value->indicator->parent])) {
            $urls[$this->indicator_groups[$value->indicator->parent]][] = $url;
          }
          else {
            $urls['other'][] = $url;
          }
        }
      }
    }
    return $urls;
  }

  /**
   * Gets the government revenue API urls.
   */
  function getGovernmentRevenueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_revenue_government)) {
      $ids = $emw->field_sd_revenue_government->raw();
      if (is_array($ids)) {
        foreach ($ids as $id) {
          $urls[] = url('api/v2.0/revenue/' . $id, array('absolute' => TRUE));
        }
      }
    }
    return $urls;
  }

  /**
   * Gets the company revenue API urls.
   */
  function getCompanyRevenueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_revenue_company)) {
      $ids = $emw->field_sd_revenue_company->raw();
      if (is_array($ids)) {
        foreach ($ids as $id) {
          $urls[] = url('api/v2.0/revenue/' . $id, array('absolute' => TRUE));
        }
      }
    }
    return $urls;
  }

  /**
   * Gets the contact information.
   */
  function getContactInformation($emw) {
    $info = array(
      'name' => $emw->field_sd_contact_name->value(),
      'email' => $emw->field_sd_contact_email_address->value(),
      'organisation' => $emw->field_sd_contact_organisation->value(),
    );
    return $info;
  }

  /**
   * Gets the disaggregated data.
   */
  function getDisaggregatedData($emw) {
    $info = array(
      'project' => eiti_api_value_to_boolean($emw->field_sd_disagg_project->value()),
      'revenue_stream' => eiti_api_value_to_boolean($emw->field_sd_disagg_revenue_stream->value()),
      'company' => eiti_api_value_to_boolean($emw->field_sd_disagg_company->value()),
    );
    return $info;
  }

  /**
   * Gets government revenue sum.
   */
  function getRevenueGovernmentSum($emw) {
    $country = $emw->country_id->value();
    $year = $emw->year_end->value();
    if (isset($country->iso) && $year) {
      $year = date('Y', strtotime($year));
      if (isset($this->revenues[$country->iso][$year]['government'])) {
        return $this->revenues[$country->iso][$year]['government'];
      }
    }
    return NULL;
  }

  /**
   * Gets company revenue sum.
   */
  function getRevenueCompanySum($emw) {
    $country = $emw->country_id->value();
    $year = $emw->year_end->value();
    if (isset($country->iso) && $year) {
      $year = date('Y', strtotime($year));
      if (isset($this->revenues[$country->iso][$year]['company'])) {
        return $this->revenues[$country->iso][$year]['company'];
      }
    }
    return NULL;
  }

  /**
   * Copied from EITIApiImplementingCountry::queryRevenues().
   *
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
   * Returns group indicator id => display name array.
   */
  function getIndicatorGroupDisplayNames() {
    $query = db_select('eiti_indicator', 'i');
    $query->fields('i', array('id', 'name'));
    $query->condition('i.type', 'group');
    $groups = $query->execute()->fetchAllKeyed();

    $names = array(
      'Allocation of licences (3.10)' => 'license-allocation',
      'Beneficial ownership (3.11)' => 'beneficial-ownership',
      'Contracts (3.12)' => 'contract-disclosure',
      'Contribution of extractive industries to economy (3.4)' => 'economic-contribution',
      'Distribution of revenues from extractive industries (3.7.a)' => 'revenue-distribution',
      'Export volume and value (3.5.b)' => 'exports',
      'External indicators' => 'external',
      'Infrastructure provisions and barter arrangements (4.1.d)?' => 'barter-infrastructure',
      'Production volume and value (3.5.a)' => 'production',
      'Register of licences (3.9)' => 'license-register',
      'Sale of the state’s share of production or other sales collected in-kind (4.1.c)' => 'in-kind-revenues',
      'Social expenditures (4.1.e)' => 'social-expenditures',
      'Sub-national payments (4.2.d)?' => 'subnational-payments',
      'Sub-national transfers (4.2.e)?' => 'subnational-transfers',
      'Transportation revenues (4.1.f)' => 'transportation-revenues',
    );

    $group_id_names = array();
    foreach ($groups as $id => $name) {
      if (isset($names[$name])) {
        $group_id_names[$id] = $names[$name];
      }
    }

    return $group_id_names;
  }

}
