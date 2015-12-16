<?php
/**
 * @file
 * Provides a handler class for the panelizer entity plugin.
 */

/**
 * Panelizer Entity plugin class.
 *
 * Handles country specific functionality for Panelizer.
 */
class CountryPanelizerEntity extends PanelizerEntityDefault {
  public $supports_revisions = FALSE;
  public $entity_admin_root = 'admin/structure/country/%';
  public $entity_admin_bundle = 3;
  public $views_table = 'eiticountry';
  //public $uses_page_manager = TRUE;

  public function entity_access($op, $entity) {
    // This must be implemented by the extending class.
    return eitientity_country_access($op, $entity, NULL, 'country');
  }

  public function entity_save($entity) {
    entity_save('country', $entity);
  }

  /**
   * Implements a delegated hook_page_manager_handlers().
   *
   * This makes sure that all panelized entities have the proper entry
   * in page manager for rendering.
   */
  public function hook_default_page_manager_handlers(&$handlers) {
    $handler = new stdClass;
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'country_view_panelizer';
    $handler->task = 'country_view';
    $handler->subtask = '';
    $handler->handler = 'panelizer_country';
    $handler->weight = -100;
    $handler->conf = array(
      'title' => t('country panelizer'),
      'context' => 'argument_entity_id:country_1',
      'access' => array(),
    );
    $handlers['country_view_panelizer'] = $handler;

    return $handlers;
  }

}
