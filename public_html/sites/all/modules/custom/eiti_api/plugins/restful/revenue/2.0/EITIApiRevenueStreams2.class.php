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
    $public_fields['summary_data'] = array(
      'callback' => array($this, 'getSummaryData'),
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

  /**
   * Get related summary data API page url.
   */
  function getSummaryData($emw) {
    $query = db_select('eiti_summary_data', 'sd');
    if ($emw->getBundle() == 'company') {
      $query->innerJoin('field_data_field_sd_revenue_company', 'frc', 'sd.id = frc.entity_id');
      $query->condition('frc.field_sd_revenue_company_target_id', $emw->id->value());
    }
    else {
      $query->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
      $query->condition('frg.field_sd_revenue_government_target_id', $emw->id->value());
    }
    $query->fields('sd', array('id2'));
    $query->condition('sd.status', 1);
    $result = $query->execute()->fetchField();

    if ($result) {
      return url('api/v2.0/summary_data/' . $result, array('absolute' => TRUE));
    }

    return NULL;
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
            $sd_query1->innerJoin('field_data_field_sd_revenue_company', 'frc', 'sd.id = frc.entity_id');
            $sd_query1->fields('frc', array('field_sd_revenue_company_target_id'));
            $sd_query1->condition('sd.id2', $filter['value'][$index]);
            $iv_ids1 = $sd_query1->execute()->fetchCol();
            $sd_query2 = db_select('eiti_summary_data', 'sd');
            $sd_query2->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
            $sd_query2->fields('frg', array('field_sd_revenue_government_target_id'));
            $sd_query2->condition('sd.id2', $filter['value'][$index]);
            $iv_ids2 = $sd_query2->execute()->fetchCol();
            $iv_ids = array_merge($iv_ids1, $iv_ids2);
            $query->entityCondition('entity_id', $iv_ids, 'IN');
          }
          else {
            $query->propertyCondition($column, $filter['value'][$index], $filter['operator'][$index]);
          }
        }
      }
    }
  }
}
