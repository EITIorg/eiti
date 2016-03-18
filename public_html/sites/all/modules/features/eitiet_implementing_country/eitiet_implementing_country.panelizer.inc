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
    $pane = new stdClass();
    $pane->pid = 'new-90084924-f683-4edf-83a7-aa048d067343';
    $pane->panel = 'main';
    $pane->type = 'country-header';
    $pane->subtype = 'country-header';
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
    $pane->uuid = '90084924-f683-4edf-83a7-aa048d067343';
    $display->content['new-90084924-f683-4edf-83a7-aa048d067343'] = $pane;
    $display->panels['main'][0] = 'new-90084924-f683-4edf-83a7-aa048d067343';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['implementing_country:normal:default:default'] = $panelizer;

  return $export;
}
