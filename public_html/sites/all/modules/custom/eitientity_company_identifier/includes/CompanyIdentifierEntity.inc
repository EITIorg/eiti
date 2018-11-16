<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class CompanyIdentifierEntity extends Entity {
  // Define some default values.
  public $id = NULL;
  public $summary_data_id = NULL;
  public $name = '';
  public $register = '';
  public $register_url = '';

  /**
   * Set up the object instance on construction or unserializiation.
   */
  protected function setUp() {
    parent::setUp();

    if (!empty($this->summary_data_id)) {
      $this->summary_data = entity_load_single('summary_data', $this->summary_data_id);
      if (empty($this->summary_data)) {
        throw new Exception('Cannot create a Company Identifier without a valid Summary Data.');
      }
    }

  }

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    return NULL;
  }
}
