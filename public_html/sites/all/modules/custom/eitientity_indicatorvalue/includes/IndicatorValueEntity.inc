<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class IndicatorValueEntity extends Entity {
  // Define some default values.
  public $id = NULL;

  public $indicator_id = NULL;
  /** @var IndicatorEntity $indicator */
  public $indicator = NULL;

  public $value_boolean = NULL;
  public $value_enum = NULL;
  public $value_numeric = NULL;
  public $value_unit = NULL;
  public $original_value_numeric = NULL;
  public $original_value_unit = NULL;
  public $value_text = NULL;

  public $source = NULL;
  public $comments = NULL;

  /**
   * Set up the object instance on construction or unserializiation.
   */
  protected function setUp() {
    parent::setUp();

    if (!empty($this->indicator_id)) {
      $this->indicator = entity_load_single('indicator', $this->indicator_id);
      if (empty($this->indicator)) {
        throw new Exception('Cannot create an Indicator Value without a valid Indicator.');
      }
    }

  }

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    return NULL;
  }

  /**
   * Returns the indicator value.
   */
  public function getValue() {
    switch ($this->indicator->type) {
      case 'boolean':
        return $this->value_boolean;
        break;
      case 'enum':
        return $this->value_enum;
        break;
      case 'numeric':
        return $this->value_numeric;
        break;
      case 'text':
      default:
        return $this->value_text;
    }
  }

  /**
   * Returns the indicator unit.
   */
  public function getUnit() {
    switch ($this->indicator->type) {
      case 'numeric':
        return $this->value_unit;
        break;
      case 'text':
      default:
        return 'N/A';
    }
  }
}
