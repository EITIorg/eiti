<?php

/**
 * @file
 * Defines the class for entity question.
 */

/**
 * Main class for question entities.
 */
class ContentBlockEntity extends HelperEntity {
  // Define some default values.
  public $id = NULL;
  public $title = '';
  public $language = LANGUAGE_NONE;
  public $type = '';
  public $machine_name = NULL;
  public $uid = NULL;
  public $status = TRUE;
  public $created = NULL;
  public $changed = NULL;
  public $style = '';
  public $icon = '';
}
