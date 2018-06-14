<?php

/**
 * @file
 * Contains EITIApiImplementingCountry2.
 */

/**
 * Class EITIApiImplementingCountry2
 */
class EITIApiImplementingCountry2 extends EITIApiImplementingCountry {

  /**
   * Overrides EITIApiImplementingCountry::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['status_date']['process_callbacks'] = array('eiti_api_timestamp_to_iso_8601_partial');

    return $public_fields;
  }
}
