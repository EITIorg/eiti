<?php

/**
 * @file
 * Contains EITIApiGFSCode.
 */

/**
 * Class EITIApiGFSCode
 */
class EITIApiGFSCode extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
    $public_fields['code'] = array(
      'property' => 'code',
    );
    $public_fields['parent'] = array(
      'property' => 'parent',
    );

    return $public_fields;
  }
}
