<?php

/**
 * @file
 * Contains EITIApiIndicatorValue2.
 */

/**
 * Class EITIApiIndicatorValue2
 */
class EITIApiIndicatorValue2 extends EITIApiIndicatorValue {

  /**
   * Overrides EITIApiIndicatorValue::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['label'] = array(
      'callback' => array($this, 'getIndicatorLabel'),
    );
    $public_fields['indicator'] = array(
      'property' => 'indicator_id',
      'callback' => array($this, 'getIndicatorApiUrl'),
    );
    $public_fields['value_boolean'] = array(
      'property' => 'value_boolean',
      'process_callbacks' => array(array($this, 'booleanToText')),
    );
    $public_fields['value_text'] = array(
      'property' => 'value_text',
    );
    $public_fields['source'] = array(
      'property' => 'source',
    );
    $public_fields['summary_data'] = array(
      'callback' => array($this, 'getSummaryData'),
    );

    return $public_fields;
  }

  /**
   * Gets the indicator API url.
   */
  function getIndicatorApiUrl($emw) {
    if (isset($emw->indicator_id)) {
      $indicator = $emw->indicator_id->value();
      if (isset($indicator->id)) {
        return url('api/v2.0/indicator/' . $indicator->id, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the indicator label as indicator_value label.
   */
  function getIndicatorLabel($emw) {
    $label = $emw->indicator_id->label();
    if ($label) {
      return $label;
    }
    return NULL;
  }

  /**
   * Converts value_boolean to text.
   *
   * Based on getBooleanListValue() in eiti_migration.generic.inc.
   */
  function booleanToText($value_boolean) {
    switch ($value_boolean) {
      case EITIENTITY_INDICATOR_VALUE_VALUE_YES:
        return 'yes';
      case EITIENTITY_INDICATOR_VALUE_VALUE_NO:
        return 'no';
      case EITIENTITY_INDICATOR_VALUE_VALUE_PARTIALLY:
        return 'partially';
      default:
        return NULL;
    }
  }

  /**
   * Get related summary data API page url.
   */
  function getSummaryData($emw) {
    $query = db_select('eiti_summary_data', 'sd');
    $query->innerJoin('field_data_field_sd_indicator_values', 'fiv', 'sd.id = fiv.entity_id');
    $query->fields('sd', array('id2'));
    $query->condition('sd.status', 1);
    $query->condition('fiv.field_sd_indicator_values_target_id', $emw->id->value());
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
            $sd_query = db_select('eiti_summary_data', 'sd');
            $sd_query->innerJoin('field_data_field_sd_indicator_values', 'fiv', 'sd.id = fiv.entity_id');
            $sd_query->fields('fiv', array('field_sd_indicator_values_target_id'));
            $sd_query->condition('sd.id2', $filter['value'][$index]);
            $iv_ids = $sd_query->execute()->fetchCol();
            if (!$iv_ids) {
              throw new \RestfulBadRequestException('No indicator values for the given summary data found.');
            }
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
