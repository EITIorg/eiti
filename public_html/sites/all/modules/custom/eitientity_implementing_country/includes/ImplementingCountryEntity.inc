<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class ImplementingCountryEntity extends Entity {
  // Define some default values.
  public $id = NULL;
  public $name = '';
  public $language = LANGUAGE_NONE;
  public $type = '';
  public $user_id = NULL;
  public $status = TRUE;
  public $created = NULL;
  public $changed = NULL;

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    if (!isset($this->{$this->nameKey})) {
      return NULL;
    }

    return array(
      'path' => $this->entityInfo['admin ui']['entity path'] . '/' . $this->identifier(),
    );
  }
}
