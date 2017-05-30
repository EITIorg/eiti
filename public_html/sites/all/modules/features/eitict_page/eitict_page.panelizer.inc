<?php
/**
 * @file
 * eitict_page.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function eitict_page_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'page';
  $panelizer->access = array();
  $panelizer->view_mode = 'default';
  $panelizer->name = 'node:page:default:default';
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
  $display->title = '';
  $display->uuid = 'efb8cb46-fccb-4a8f-babc-54b05753da30';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:page:default:default';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = '99';
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:page:default:default'] = $panelizer;

  return $export;
}
