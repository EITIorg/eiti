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

    // Let's expose some data, as few as needed.
    $public_fields['type'] = array(
      'property' => 'type',
    );
    $public_fields['country'] = array(
      'property' => 'country_id',
    );
    return $public_fields;
  }
}
