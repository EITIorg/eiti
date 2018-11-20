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
    //$public_fields['country']['process_callbacks'] = array('eitientity_implementing_country_get_iso2');
    $public_fields['country']['callback'] = array($this, 'getCountryApiUrl');
    $public_fields['summary_data']['process_callbacks'] = array(array($this, 'getSummaryDataApiUrl'));

    return $public_fields;
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
   * Get related summary data API page url.
   */
  function getSummaryDataApiUrl($sd_id) {
    if ($sd_id) {
      $sd_id2 = eitientity_summary_data_get_id2($sd_id);
      return url('api/v2.0/summary_data/' . $sd_id2, array('absolute' => TRUE));
    }

    return NULL;
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
      // Summary data ID2 to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'summary_data') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_summary_data_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
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
