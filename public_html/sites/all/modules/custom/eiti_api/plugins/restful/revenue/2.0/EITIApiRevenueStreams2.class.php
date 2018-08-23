<?php

/**
 * @file
 * Contains EITIApiRevenueStreams2.
 */

/**
 * Class EITIApiRevenueStreams2
 */
class EITIApiRevenueStreams2 extends EITIApiRevenueStreams {

  /**
   * Overrides EITIApiRevenueStreams::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['revenue']['process_callbacks'][] = 'eiti_api_numeric_string_to_float';
    //$public_fields['type']['process_callbacks'][] = 'ucfirst';
    unset($public_fields['report_status']);

    $public_fields['label'] = array(
      'property' => 'name',
    );
    $public_fields['gfs'] = array(
      'property' => 'gfs_code_id',
      'callback' => array($this, 'getGfsApiUrl')
    );

    return $public_fields;
  }

  /**
   * Overrides EITIApiRevenueStreams::getOrganisation().
   */
  public function getOrganisation($emw) {
    if (isset($emw->organisation_id)) {
      $organisation = $emw->organisation_id->value();
      if (isset($organisation->id)) {
        return url('api/v2.0/organisation/' . $organisation->id, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the gfs code API url.
   */
  function getGfsApiUrl($emw) {
    if (isset($emw->gfs_code_id)) {
      $gfs_code = $emw->gfs_code_id->value();
      if (isset($gfs_code->id)) {
        return url('api/v2.0/gfs_code/' . $gfs_code->code, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Gfs code to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'gfs') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_gfs_code_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
  }
}
