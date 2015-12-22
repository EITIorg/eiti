<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class IndicatorEntity extends Entity {
  // Define some default values.
  public $id = NULL;
  public $type = '';
  public $name = '';
  public $parent = NULL;
  public $status = TRUE;
  public $created = NULL;

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    if (!isset($this->{$this->idKey})) {
      return NULL;
    }

    return array(
      'path' => EITIENTITY_INDICATOR_UI_PATH . '/' . $this->identifier(),
    );
  }
}
