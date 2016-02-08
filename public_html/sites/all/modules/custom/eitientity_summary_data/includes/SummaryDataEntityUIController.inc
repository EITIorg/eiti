<?php

/**
 * @file
 * Controller for providing the UI
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class SummaryDataEntityUIController extends HelperEntityBundleableUIController {
  /**
   * Define menu items and page callbacks.
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    $defaults = array(
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' =>  isset($this->entityInfo['admin ui']['file path']) ? $this->entityInfo['admin ui']['file path'] : drupal_get_path('module', $this->entityInfo['module']),
    );

    $items[$this->entity_path . '/' . $this->wildcard . '/re-upload'] = array(
        'page callback' => 'drupal_get_form',
        'page arguments' => array('summary_data_spreadsheet_upload_form', $this->entity_id_count),
        'load arguments' => array($this->entityType),
        'access callback' => 'entity_access',
        'access arguments' => array('edit', $this->entityType, $this->entity_id_count),
        'title' => 'Upload',
        'type' => MENU_LOCAL_TASK,
        'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
        'weight' => 0,
      ) + $defaults;

    return $items;
  }
}
