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
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = FALSE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'simplelayout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%implementing_country:name';
  $display->uuid = '6f0cc01b-7a30-4800-9a35-90a9a807394b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-97a9eecc-1656-4690-99c2-f1e9ad61780d';
    $pane->panel = 'main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'No content message',
      'title' => '',
      'body' => 'No content has been configured for this country page.',
      'format' => 'plain_text',
      'substitute' => 0,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '97a9eecc-1656-4690-99c2-f1e9ad61780d';
    $display->content['new-97a9eecc-1656-4690-99c2-f1e9ad61780d'] = $pane;
    $display->panels['main'][0] = 'new-97a9eecc-1656-4690-99c2-f1e9ad61780d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-97a9eecc-1656-4690-99c2-f1e9ad61780d';
  $panelizer->display = $display;
  $export['implementing_country:normal:default:default'] = $panelizer;

  return $export;
}
