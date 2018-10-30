<?php

/**
 * @file
 * Contains EITIApiIndicator2.
 */

/**
 * Class EITIApiIndicator2
 */
class EITIApiIndicator2 extends EITIApiIndicator {

  /**
   * Overrides EITIApiIndicator::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    unset($public_fields['status']);
    unset($public_fields['created']);

    return $public_fields;
  }

}
