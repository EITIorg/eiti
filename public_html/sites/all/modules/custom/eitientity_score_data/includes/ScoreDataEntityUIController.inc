<?php

/**
 * @file
 * Controller for providing the UI
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class ScoreDataEntityUIController extends HelperEntityBundleableUIController {
  /**
   * Define menu items and page callbacks.
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    $defaults = array(
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' =>  isset($this->entityInfo['admin ui']['file path']) ? $this->entityInfo['admin ui']['file path'] : drupal_get_path('module', $this->entityInfo['module']),
    );
//    $items += $defaults;

    return $items;
  }
}
