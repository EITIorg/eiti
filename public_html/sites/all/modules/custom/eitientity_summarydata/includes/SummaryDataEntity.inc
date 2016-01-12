<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class SummaryDataEntity extends Entity {
  // Define some default values.
  public $id = NULL;
  public $type = '';
  public $country_id = NULL;

  public $year_start = NULL;
  public $year_end = NULL;
  public $published = NULL;
  public $currency_code = NULL;
  public $currency_rate = NULL;

  public $status = TRUE;
  public $created = NULL;
  public $changed = NULL;

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    if (!isset($this->{$this->idKey})) {
      return NULL;
    }

    return array(
      'path' => $this->entityInfo['admin ui']['entity path'] . '/' . $this->identifier(),
    );
  }
}
