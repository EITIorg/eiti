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

    $public_fields['indicator'] = array(
      'property' => 'indicator_id',
      'callback' => array($this, 'getIndicatorApiUrl'),
    );
    $public_fields['value_boolean'] = array(
      'property' => 'value_boolean',
    );
    $public_fields['value_text'] = array(
      'property' => 'value_text',
    );
    $public_fields['source'] = array(
      'property' => 'source',
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
}
