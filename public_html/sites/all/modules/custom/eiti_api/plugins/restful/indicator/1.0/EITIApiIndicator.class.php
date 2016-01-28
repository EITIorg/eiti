<?php

/**
 * @file
 * Contains EITIApiIndicator.
 */

/**
 * Class EITIApiIndicator
 */
class EITIApiIndicator extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
    $public_fields['type'] = array(
      'property' => 'type',
    );
    $public_fields['parent'] = array(
      'property' => 'parent',
    );
    $public_fields['status'] = array(
      'property' => 'status',
    );
    $public_fields['created'] = array(
      'property' => 'created',
    );

    return $public_fields;
  }
}
