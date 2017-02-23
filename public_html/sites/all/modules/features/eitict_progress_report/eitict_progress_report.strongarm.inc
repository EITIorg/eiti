<?php
/**
 * @file
 * eitict_progress_report.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitict_progress_report_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_progress_report';
  $strongarm->value = '4';
  $export['language_content_type_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_progress_report';
  $strongarm->value = array();
  $export['menu_options_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_progress_report';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_progress_report';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_progress_report';
  $strongarm->value = '0';
  $export['node_preview_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_progress_report';
  $strongarm->value = 0;
  $export['node_submitted_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_node_view_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_node_view_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_progress_report';
  $strongarm->value = array(
    'status' => 1,
    'help' => '',
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'substitute' => '',
        'default' => 1,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'substitute' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'substitute' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_progress_report'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:progress_report_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:30:"panelizer_node:progress_report";s:23:"allowed_layout_settings";a:13:{s:8:"flexible";b:1;s:25:"threecol_25_50_25_stacked";b:1;s:6:"onecol";b:1;s:25:"threecol_33_34_33_stacked";b:1;s:13:"twocol_bricks";b:1;s:14:"twocol_stacked";b:1;s:17:"threecol_25_50_25";b:1;s:17:"threecol_33_34_33";b:1;s:6:"twocol";b:1;s:11:"bricklayout";b:1;s:10:"widelayout";b:1;s:12:"doublelayout";b:1;s:12:"simplelayout";b:1;}s:10:"form_state";N;}';
  $export['panelizer_node:progress_report_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:progress_report_allowed_layouts_default';
  $strongarm->value = 1;
  $export['panelizer_node:progress_report_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:progress_report_allowed_types_default';
  $strongarm->value = 1;
  $export['panelizer_node:progress_report_allowed_types_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:progress_report_default';
  $strongarm->value = array(
    'entity_form_field' => 'entity_form_field',
    'token' => 'token',
    'block' => 'block',
    'custom' => 'custom',
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'entity_view' => 'entity_view',
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'views' => 'views',
    'views_panes' => 'views_panes',
    'other' => 'other',
  );
  $export['panelizer_node:progress_report_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:progress_report:default_selection';
  $strongarm->value = 0;
  $export['panelizer_node:progress_report:default_selection'] = $strongarm;

  return $export;
}
