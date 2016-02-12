<?php
/**
 * @file
 * eitipanels.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitipanels_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:11:"panels_page";s:23:"allowed_layout_settings";a:12:{s:8:"flexible";b:0;s:6:"onecol";b:0;s:6:"twocol";b:0;s:13:"twocol_bricks";b:0;s:25:"threecol_25_50_25_stacked";b:0;s:25:"threecol_33_34_33_stacked";b:0;s:14:"twocol_stacked";b:0;s:17:"threecol_25_50_25";b:0;s:17:"threecol_33_34_33";b:0;s:12:"doublelayout";b:1;s:12:"simplelayout";b:1;s:11:"bricklayout";b:1;}s:10:"form_state";N;}';
  $export['panels_page_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_types';
  $strongarm->value = array(
    'fieldable_panels_pane-key_facts' => 'fieldable_panels_pane-key_facts',
    'fieldable_panels_pane-quote' => 'fieldable_panels_pane-quote',
    'fieldable_panels_pane-visualization' => 'fieldable_panels_pane-visualization',
    'fieldable_panels_pane-wide_image' => 'fieldable_panels_pane-wide_image',
  );
  $export['panels_page_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_default';
  $strongarm->value = array(
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'entity_field_extra' => 0,
    'entity_field' => 0,
    'custom' => 0,
    'entity_form_field' => 0,
    'block' => 0,
    'token' => 0,
    'entity_view' => 0,
    'other' => 0,
  );
  $export['panels_page_default'] = $strongarm;

  return $export;
}
