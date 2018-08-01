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

}
