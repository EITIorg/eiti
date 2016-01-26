<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class HelperEntity extends Entity {
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
