<?php

/**
 * @file
 * Contains EITIApiIndicator2.
 */

/**
 * Class EITIApiIndicator2
 */
class EITIApiIndicator2 extends EITIApiIndicator {

  /**
   * Overrides EITIApiIndicator::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['created']['process_callbacks'] = array('eiti_api_timestamp_to_iso_8601');

    return $public_fields;
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Date to timestamp.
      // Note that with ISO 8601 (YYYY-MM-DDThh:mm:ss+hh:mm) format the + symbol has to be encoded in the url (%2B).
      // "2016-03-08T15:47:59%2B00:00" and "2016-03-08T15:47:59" give the same result.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'created') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = strtotime($v);
        }
      }
    }
    return $filters;
  }
}
