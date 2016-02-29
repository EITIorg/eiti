<?php

/**
 * @file
 * Contains EITIApiImplementingCountry.
 */

/**
 * Class EITIApiImplementingCountry
 */
class EITIApiImplementingCountry extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
//    $public_fields['indicator_id'] = array(
//      'property' => 'name',
//    );
    $public_fields['iso2'] = array(
      'property' => 'iso',
    );

    return $public_fields;
  }
}
