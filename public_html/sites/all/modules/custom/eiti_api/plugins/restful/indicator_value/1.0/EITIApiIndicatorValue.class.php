<?php

/**
 * @file
 * Contains EITIApiIndicatorValue.
 */

/**
 * Class EITIApiIndicatorValue
 */
class EITIApiIndicatorValue extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
    $public_fields['value'] = array(
      'callback' => array($this, 'getValue'),
    );
    $public_fields['unit'] = array(
      'callback' => array($this, 'getUnit'),
    );
    $public_fields['indicator'] = array(
      'callback' => array($this, 'getIndicator'),
    );

    return $public_fields;
  }

  /**
   * Gets the value of the indicator.
   */
  public function getValue($value_emw) {
    $entity = $value_emw->value();
    return $entity->getValue();
  }

  /**
   * Gets the unit of the indicator.
   */
  public function getUnit($value_emw) {
    $entity = $value_emw->value();
    return $entity->getUnit();
  }

  /**
   * Gets the indicator.
   */
  public function getIndicator($value_emw) {
    return $value_emw->indicator_id->value();
  }
}
