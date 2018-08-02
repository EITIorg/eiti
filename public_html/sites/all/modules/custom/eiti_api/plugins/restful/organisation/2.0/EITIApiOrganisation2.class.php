<?php

/**
 * @file
 * Contains EITIApiOrganisation2.
 */

/**
 * Class EITIApiOrganisation2
 */
class EITIApiOrganisation2 extends EITIApiOrganisation {

  /**
   * Overrides EITIApiOrganisation::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Expose data.
    $public_fields['country']['process_callbacks'] = array('eitientity_implementing_country_get_iso2');

    return $public_fields;
  }
}
