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
    //$public_fields['country']['process_callbacks'] = array('eitientity_implementing_country_get_iso2');
    $public_fields['country'] = array(
      'callback' => array($this, 'getCountryApiUrl')
    );

    return $public_fields;
  }

  /**
   * Gets the implementing country API url.
   */
  function getCountryApiUrl($emw) {
    if (isset($emw->country_id)) {
      $country_id = $emw->country_id->value();
      if (is_numeric($country_id)) {
        $iso = eitientity_implementing_country_get_iso2($country_id);
        if ($iso) {
          return url('api/v2.0/implementing_country/' . $iso, array('absolute' => TRUE));
        }
      }
    }
    return NULL;
  }
}
