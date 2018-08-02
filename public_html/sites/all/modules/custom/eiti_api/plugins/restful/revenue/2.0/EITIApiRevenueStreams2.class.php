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
   * Overrides EITIApiRevenueStreams::getOrganisation().
   */
  public function getOrganisation($value_emw) {
    $organisation = parent::getOrganisation($value_emw);
    // If the ID hasn't been converted (this function may be called several times).
    if (is_numeric($organisation->country_id)) {
      $organisation->country_id = eitientity_implementing_country_get_iso2($organisation->country_id);
    }
    return $organisation;
  }
}
