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
    $public_fields['summary_data']['process_callbacks'] = array('eitientity_summary_data_get_id2');

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
}
