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
  public $value_reporting_type = NULL;

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
    if (empty($this->indicator) && !empty($this->indicator_id)) {
      $this->setUp();
    }

    if (empty($this->indicator)) {
      return NULL;
    }

    switch ($this->indicator->type) {
      case 'boolean':
        return $this->value_boolean;
      case 'enum':
        return $this->value_enum;
      case 'numeric':
        return $this->value_numeric;
      case 'reporting_type':
        return $this->value_reporting_type;
      case 'text':
      default:
        return $this->value_text;
    }
  }

  /**
   * Returns the indicator unit.
   */
  public function getUnit() {
    if (empty($this->indicator) && !empty($this->indicator_id)) {
      $this->setUp();
    }

    if (empty($this->indicator)) {
      return NULL;
    }

    switch ($this->indicator->type) {
      case 'numeric':
        return $this->value_unit;
        break;
      case 'text':
      default:
        return 'N/A';
    }
  }

  /**
   * Getter callback for indicator_id.
   *
   * @return entity
   *   Indicator entity.
   */
  public function indicatorid() {
    return entity_load_single('indicator', $this->indicator_id);
  }

  /**
   * Setter for indicator_id.
   *
   * @param entity $indicator
   *
   *  Indicator entity instance.
   */
  public function setIndicatorid($indicator) {
    $this->indicator_id = is_object($indicator->id) ? $indicator->id : $indicator;
  }
}
