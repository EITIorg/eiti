<?php

/**
 * @file
 * Contains EITIApiScoreData2.
 */

/**
 * Class EITIApiScoreData2
 */
class EITIApiScoreData2 extends EITIApiScoreData {

  /**
   * Overrides EITIApiScoreData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['country'] = array(
      'property' => 'country_id',
      'callback' => array($this, 'getCountryApiUrl')
    );
    $public_fields['validation_date'] = array(
      'property' => 'published',
      'process_callbacks' => array('eiti_api_timestamp_to_iso_8601_partial')
    );

    $public_fields['score_req_values']['process_callbacks'] = array(array($this, 'prepareScoreReqValues'));

    return $public_fields;
  }

  /**
   * A standard processing callback for score_req_values.
   */
  function prepareScoreReqValues($score_req_values) {
    foreach ($score_req_values as $key => $sq) {
      if (isset($sq->score_req->created) && is_numeric($sq->score_req->created)) {
        $score_req_values[$key]->score_req->created = eiti_api_timestamp_to_iso_8601($sq->score_req->created);
      }
    }
    return $score_req_values;
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
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
}
