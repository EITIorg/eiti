<?php

/**
 * @file
 * Contains EITIApiOrganisation.
 */

/**
 * Class EITIApiOrganisation
 */
class EITIApiOrganisation extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Expose data.
    $public_fields['type'] = array(
      'property' => 'type',
    );
    $public_fields['country'] = array(
      'property' => 'country_id',
    );
    $public_fields['summary_data'] = array(
      'property' => 'summary_data_id',
    );
    $public_fields['identification'] = array(
      'property' => 'identification_number',
    );
    $public_fields['sector'] = array(
      'callback' => array($this, 'getSector'),
    );
    $public_fields['commodities'] = array(
      'callback' => array($this, 'getCommodities'),
    );
    return $public_fields;
  }

  /**
   * Gets the sector related to this organisation.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Organisation).
   *
   * @return mixed
   *   Either NULL or the sector string.
   */
  function getSector($emw) {
    // Can't use property directly since government agencies do not have this field.
    if (isset($emw->field_o_sector)) {
      $sector = $emw->field_o_sector->value();
      if ($sector) {
        return $sector->name;
      }
    }
    return NULL;
  }

  /**
   * Gets the commodities related to this organisation.
   *
   * @param $emw
   *   EntityMetadataWrapper object (Organisation).
   *
   * @return mixed
   *   Either NULL or an array of commodity strings.
   */
  function getCommodities($emw) {
    // Can't use property directly since government agencies do not have this field.
    if (isset($emw->field_o_commodities)) {
      $commodities = $emw->field_o_commodities->value();
      if ($commodities) {
        $result = array();
        foreach ($commodities as $commodity) {
          $result[] = $commodity->name;
        }
        return $result;
      }
    }
    return NULL;
  }
}
