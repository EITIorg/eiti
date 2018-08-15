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
    $public_fields['type']['process_callbacks'][] = 'ucfirst';
    unset($public_fields['report_status']);

    $public_fields['label'] = array(
      'property' => 'name',
    );
    $public_fields['gfs'] = array(
      'callback' => array($this, 'getGfsApiUrl')
    );
    $public_fields['organisation'] = array(
      'callback' => array($this, 'getOrganisationApiUrl')
    );

    return $public_fields;
  }

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

  /**
   * Gets the gfs code API url.
   */
  function getGfsApiUrl($emw) {
    if (isset($emw->gfs_code_id)) {
      $gfs_code = $emw->gfs_code_id->value();
      if (isset($gfs_code->id)) {
        return url('api/v1.0/gfs_code/' . $gfs_code->id, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the organisation API url.
   */
  function getOrganisationApiUrl($emw) {
    if (isset($emw->organisation_id)) {
      $organisation = $emw->organisation_id->value();
      if (isset($organisation->id)) {
        return url('api/v2.0/organisation/' . $organisation->id, array('absolute' => TRUE));
      }
    }
    return NULL;
  }
}
