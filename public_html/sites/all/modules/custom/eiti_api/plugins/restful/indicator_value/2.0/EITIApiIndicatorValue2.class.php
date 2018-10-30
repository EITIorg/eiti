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
   * Overrides EITIApiIndicatorValue::getIndicator().
   */
  /*public function getIndicator($value_emw) {
    $indicator = $value_emw->indicator_id->value();
    // For some reason this function is called more than once so we need to make sure the value stays correct.
    if (is_numeric($indicator->created)) {
      $indicator->created = eiti_api_timestamp_to_iso_8601($indicator->created);
    }
    return $indicator;
  }*/

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
}
