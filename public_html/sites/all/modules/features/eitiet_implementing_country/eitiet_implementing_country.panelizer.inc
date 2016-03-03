<?php
/**
 * @file
 * eitiet_implementing_country.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function eitiet_implementing_country_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'implementing_country:normal:default:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'implementing_country';
  $panelizer->panelizer_key = 'normal';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = array();
  $panelizer->view_mode = 'default';
  $panelizer->css_class = '';
  $panelizer->title_element = 'h1';
  $panelizer->link_to_entity = FALSE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'widelayout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '6f0cc01b-7a30-4800-9a35-90a9a807394b';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = '99';
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['implementing_country:normal:default:default'] = $panelizer;

  return $export;
}
