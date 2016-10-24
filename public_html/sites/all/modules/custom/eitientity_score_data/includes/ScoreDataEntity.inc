<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class ScoreDataEntity extends Entity {
  // Define some default values.
  public $id = NULL;
  public $type = '';

  public $country_id = NULL;
  public $year = NULL;

  public $published = NULL;
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

  /**
   * Getter callback for country_id.
   *
   * @return entity
   *   Implementing Country entity.
   */
  public function countryid() {
    return entity_load_single('implementing_country', $this->country_id);
  }

  /**
   * Setter for country_id.
   *
   * @param entity $country
   *
   *  Implementing Country entity instance.
   */
  public function setCountryid($country) {
    $this->country_id = is_object($country->id) ? $country->id : $country;
  }
}
