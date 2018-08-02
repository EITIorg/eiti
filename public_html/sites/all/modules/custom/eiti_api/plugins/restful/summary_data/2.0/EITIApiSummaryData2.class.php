<?php

/**
 * @file
 * Contains EITIApiSummaryData2.
 */

/**
 * Class EITIApiSummaryData2
 */
class EITIApiSummaryData2 extends EITIApiSummaryData {

  /**
   * Overrides EITIApiSummaryData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // References.
    $public_fields['country']['resource']['normal']['major_version'] = 2;
    $public_fields['indicator_values']['resource']['indicator_value']['major_version'] = 2;

    return $public_fields;
  }

  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Date to timestamp.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'year_start') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = strtotime($v);
        }
      }
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'year_end') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = strtotime($v);
        }
      }
      // Note that with ISO 8601 (YYYY-MM-DDThh:mm:ss+hh:mm) format the + symbol has to be encoded in the url (%2B).
      // "2016-06-06T11:04:36%2B00:00" and "2016-06-06T11:04:36" give the same result.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'created') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = strtotime($v);
        }
      }
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'changed') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = strtotime($v);
        }
      }
    }
    return $filters;
  }

}
