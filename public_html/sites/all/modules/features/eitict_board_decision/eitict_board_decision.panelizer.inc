<?php
/**
 * @file
 * eitict_board_decision.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function eitict_board_decision_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'board_decision';
  $panelizer->access = array();
  $panelizer->view_mode = 'default';
  $panelizer->name = 'node:board_decision:default:default';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'h1';
  $panelizer->link_to_entity = FALSE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'widelayout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'd24caa40-2f50-4c8f-a9f1-2c2aee9d132f';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:board_decision:default:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-e46828c4-618d-4d78-a69c-c06950ff3277';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'The Board\'s decision',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'e46828c4-618d-4d78-a69c-c06950ff3277';
  $display->content['new-e46828c4-618d-4d78-a69c-c06950ff3277'] = $pane;
  $display->panels['main'][0] = 'new-e46828c4-618d-4d78-a69c-c06950ff3277';
  $display->hide_title = '99';
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:board_decision:default:default'] = $panelizer;

  return $export;
}
