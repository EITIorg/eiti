<?php

/**
 * @file
 * Contains EITIApiOrganisation2.
 */

/**
 * Class EITIApiOrganisation2
 */
class EITIApiOrganisation2 extends EITIApiOrganisation {

  /**
   * Overrides EITIApiOrganisation::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Expose data.
    $public_fields['country']['callback'] = array($this, 'getCountryApiUrl');
    $public_fields['summary_data'] = array(
      'callback' =>  array($this, 'getSummaryDataApiUrls'),
    );
    $public_fields['company_type'] = array(
      'property' => 'field_company_type',
      'callback' => array($this, 'getCompanyType')
    );
    $public_fields['stock_exchange_listing'] = array(
      'property' => 'field_stock_exchange_listing',
      'callback' => array($this, 'getStockExchangeListing')
    );
    $public_fields['audited_financial_state'] = array(
      'property' => 'field_audited_financial_state',
      'callback' => array($this, 'getAuditedFinancialStatement')
    );

    return $public_fields;
  }

  /**
   * Get the Audited Financial Statement value.
   */
  function getAuditedFinancialStatement($emw) {
    if (isset($emw->field_audited_financial_state)) {
      $audited_financial_state = $emw->field_audited_financial_state->value();
      if (isset($audited_financial_state)) {
        return $audited_financial_state;
      }
    }
    return NULL;
  }

  /**
   * Get the Stock Exchange Listing value.
   */
  function getStockExchangeListing($emw) {
    if (isset($emw->field_stock_exchange_listing)) {
      $stock_exchange_listing = $emw->field_stock_exchange_listing->value();
      if (isset($stock_exchange_listing)) {
        return $stock_exchange_listing;
      }
    }
    return NULL;
  }

  /**
   * Get the Company Type value.
   */
  function getCompanyType($emw) {
    if (isset($emw->field_company_type)) {
      $company_type = $emw->field_company_type->value();
      if (isset($company_type)) {
        return $company_type;
      }
    }
    return NULL;
  }

  /**
   * Gets the implementing country API url.
   */
  function getCountryApiUrl($emw) {
    if (isset($emw->country_id)) {
      $country_id = $emw->country_id->value();
      if (is_numeric($country_id)) {
        $iso = eitientity_implementing_country_get_iso2($country_id);
        if ($iso) {
          return url('api/v2.0/implementing_country/' . $iso, array('absolute' => TRUE));
        }
      }
    }
    return NULL;
  }

  /**
   * Get related summary data API page urls.
   */
  function getSummaryDataApiUrls($emw) {
    $urls = array();
    // All company entries should have a direct 1:1 relationship with their parent summary data.
    // This is due to how the migrations were built.
    if ($emw->type->value() == 'company') {
      $sd_id = $emw->summary_data_id->value();
      if (is_numeric($sd_id)) {
        $sd_id2 = eitientity_summary_data_get_id2($sd_id);
        if ($sd_id2) {
          $urls[] = url('api/v2.0/summary_data/' . $sd_id2, array('absolute' => TRUE));
        }
      }
    }
    // Agencies can have multiple related summary data entries without a direct relationship.
    elseif ($emw->type->value() == 'agency') {
      $id = $emw->id->value();
      $sd_query = db_select('eiti_summary_data', 'sd')->distinct();
      $sd_query->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
      $sd_query->innerJoin('eiti_revenue_stream', 'rt', 'frg.field_sd_revenue_government_target_id = rt.id');
      $sd_query->fields('sd', array('id2'));
      $sd_query->condition('rt.organisation_id', $id);
      $sd_query->orderBy('sd.id2', 'ASC');
      $sd_id2s = $sd_query->execute()->fetchCol();
      if ($sd_id2s) {
        foreach ($sd_id2s as $sd_id2) {
          $urls[] = url('api/v2.0/summary_data/' . $sd_id2, array('absolute' => TRUE));
        }
      }
    }

    return $urls;
  }

  /**
   * Overrides EITIApiOrganisation::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Country ISO to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'country') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_implementing_country_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
  }

  /**
   * Overrides RestfulDataProviderEFQ::queryForListFilter().
   *
   * We need custom handling for the summary_data filter.
   */
  protected function queryForListFilter(\EntityFieldQuery $query) {
    $public_fields = $this->getPublicFields();
    foreach ($this->parseRequestForListFilter() as $filter) {
      // Determine if filtering is by field or property.
      $property_name = isset($public_fields[$filter['public_field']]['property']) ? $public_fields[$filter['public_field']]['property'] : NULL;
      if ($filter['public_field'] != 'summary_data' && !$property_name) {
        throw new \RestfulBadRequestException('The current filter selection does not map to any entity property or Field API field.');
      }
      if (field_info_field($property_name)) {
        if (in_array(strtoupper($filter['operator'][0]), array('IN', 'BETWEEN'))) {
          $query->fieldCondition($public_fields[$filter['public_field']]['property'], $public_fields[$filter['public_field']]['column'], $filter['value'], $filter['operator'][0]);
          continue;
        }
        for ($index = 0; $index < count($filter['value']); $index++) {
          $query->fieldCondition($public_fields[$filter['public_field']]['property'], $public_fields[$filter['public_field']]['column'], $filter['value'][$index], $filter['operator'][$index]);
        }
      }
      else {
        if (in_array(strtoupper($filter['operator'][0]), array('IN', 'BETWEEN'))) {
          $query->propertyCondition($property_name, $filter['value'], $filter['operator'][0]);
          continue;
        }
        if ($filter['public_field'] != 'summary_data') {
          $column = $this->getColumnFromProperty($property_name);
        }
        for ($index = 0; $index < count($filter['value']); $index++) {
          if ($filter['public_field'] == 'summary_data') {
            $sd_query1 = db_select('eiti_summary_data', 'sd');
            $sd_query1->innerJoin('eiti_organisation', 'o', 'sd.id = o.summary_data_id');
            $sd_query1->fields('o', array('id'));
            $sd_query1->condition('o.type', 'company');
            $sd_query1->condition('sd.id2', $filter['value'][$index]);
            $o_ids1 = $sd_query1->execute()->fetchCol();
            $sd_query2 = db_select('eiti_summary_data', 'sd')->distinct();
            $sd_query2->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
            $sd_query2->innerJoin('eiti_revenue_stream', 'rt', 'frg.field_sd_revenue_government_target_id = rt.id');
            $sd_query2->fields('rt', array('organisation_id'));
            $sd_query2->condition('sd.id2', $filter['value'][$index]);
            $o_ids2 = $sd_query2->execute()->fetchCol();
            $o_ids = array_merge($o_ids1, $o_ids2);
            if (!$o_ids) {
              throw new \RestfulBadRequestException('No organisations for the given summary data found.');
            }
            $query->entityCondition('entity_id', $o_ids, 'IN');
          }
          else {
            $query->propertyCondition($column, $filter['value'][$index], $filter['operator'][$index]);
          }
        }
      }
    }
  }

  /**
   * Gets various organisation counts.
   */
  public function getAdditionalListData() {
    $data = array(
      'agencies' => NULL,
      'companies' => NULL,
      'companies_with_identification' => NULL,
      'companies_with_sector' => NULL,
      'companies_with_commodities' => NULL,
    );
    $agencies = db_select('eiti_organisation')
      ->condition('type', 'agency')
      ->countQuery()->execute()->fetchField();
    if (is_numeric($agencies)) {
      $data['agencies'] = (int) $agencies;
    }
    $companies = db_select('eiti_organisation')
      ->condition('type', 'company')
      ->countQuery()->execute()->fetchField();
    if (is_numeric($companies)) {
      $data['companies'] = (int) $companies;
    }
    $companies_w_id = db_select('eiti_organisation')
      ->condition('type', 'company')
      ->isNotNull('identification_number')
      ->countQuery()->execute()->fetchField();
    if (is_numeric($companies_w_id)) {
      $data['companies_with_identification'] = (int) $companies_w_id;
    }
    $companies_w_s = db_select('eiti_organisation', 'o')
      ->distinct()
      ->fields('o', array('id'))
      ->condition('o.type', 'company');
    $companies_w_s->innerJoin('field_data_field_o_sector', 's', 'o.id = s.entity_id');
    $companies_w_s = $companies_w_s->countQuery()->execute()->fetchField();
    if (is_numeric($companies_w_s)) {
      $data['companies_with_sector'] = (int) $companies_w_s;
    }
    $companies_w_c = db_select('eiti_organisation', 'o')
      ->distinct()
      ->fields('o', array('id'))
      ->condition('o.type', 'company');
    $companies_w_c->innerJoin('field_data_field_o_commodities', 'c', 'o.id = c.entity_id');
    $companies_w_c = $companies_w_c->countQuery()->execute()->fetchField();
    if (is_numeric($companies_w_c)) {
      $data['companies_with_commodities'] = (int) $companies_w_c;
    }

    return $data;
  }
}
