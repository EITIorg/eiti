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
   * Gets the indicator.
   */
  public function getIndicator($value_emw) {
    $indicator = $value_emw->indicator_id->value();
    // For some reason this function is called more than once so we need to make sure the value stays correct.
    if (is_numeric($indicator->created)) {
      $indicator->created = eiti_api_timestamp_to_iso_8601($indicator->created);
    }
    return $indicator;
  }
}
