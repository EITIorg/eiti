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
  $pane->pid = 'new-91d5a5d9-126e-4c69-baf1-204106973fe4';
  $pane->panel = 'main';
  $pane->type = 'board-decision-info';
  $pane->subtype = 'board-decision-info';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '91d5a5d9-126e-4c69-baf1-204106973fe4';
  $display->content['new-91d5a5d9-126e-4c69-baf1-204106973fe4'] = $pane;
  $display->panels['main'][0] = 'new-91d5a5d9-126e-4c69-baf1-204106973fe4';
  $pane = new stdClass();
  $pane->pid = 'new-ecd29663-7f8b-4035-bb3c-a2a5d7ee5b9a';
  $pane->panel = 'main';
  $pane->type = 'validation-decision';
  $pane->subtype = 'validation-decision';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'ecd29663-7f8b-4035-bb3c-a2a5d7ee5b9a';
  $display->content['new-ecd29663-7f8b-4035-bb3c-a2a5d7ee5b9a'] = $pane;
  $display->panels['main'][1] = 'new-ecd29663-7f8b-4035-bb3c-a2a5d7ee5b9a';
  $pane = new stdClass();
  $pane->pid = 'new-22f38487-f872-4075-9c4c-8574d22e0c0a';
  $pane->panel = 'main';
  $pane->type = 'validation-actions';
  $pane->subtype = 'validation-actions';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '22f38487-f872-4075-9c4c-8574d22e0c0a';
  $display->content['new-22f38487-f872-4075-9c4c-8574d22e0c0a'] = $pane;
  $display->panels['main'][2] = 'new-22f38487-f872-4075-9c4c-8574d22e0c0a';
  $display->hide_title = '99';
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:board_decision:default:default'] = $panelizer;

  return $export;
}
