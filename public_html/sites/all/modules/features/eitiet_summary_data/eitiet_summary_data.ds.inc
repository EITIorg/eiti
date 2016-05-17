<?php
/**
 * @file
 * eitiet_summary_data.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitiet_summary_data_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'summary_data|summary_data|default';
  $ds_fieldsetting->entity_type = 'summary_data';
  $ds_fieldsetting->bundle = 'summary_data';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'field_sd_file_links' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
  );
  $export['summary_data|summary_data|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitiet_summary_data_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'summary_data|summary_data|default';
  $ds_layout->entity_type = 'summary_data';
  $ds_layout->bundle = 'summary_data';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'country_id',
        1 => 'year_end',
        2 => 'field_sd_independent_admin',
        3 => 'group_sd_sectors_covered',
        4 => 'field_sd_no_reporting_gov',
        5 => 'field_sd_no_reporting_com',
        6 => 'group_sd_data_disaggregation',
        7 => 'group_sd_contact_details',
        8 => 'field_sd_report_file',
        9 => 'field_sd_file_links',
        10 => 'field_sd_disagg_revenue_stream',
        11 => 'field_sd_disagg_company',
        12 => 'field_sd_disagg_project',
        13 => 'field_sd_oil_sector',
        14 => 'field_sd_gas_sector',
        15 => 'field_sd_mining_sector',
        16 => 'field_sd_other_sector',
      ),
    ),
    'fields' => array(
      'country_id' => 'main',
      'year_end' => 'main',
      'field_sd_independent_admin' => 'main',
      'group_sd_sectors_covered' => 'main',
      'field_sd_no_reporting_gov' => 'main',
      'field_sd_no_reporting_com' => 'main',
      'group_sd_data_disaggregation' => 'main',
      'group_sd_contact_details' => 'main',
      'field_sd_report_file' => 'main',
      'field_sd_file_links' => 'main',
      'field_sd_disagg_revenue_stream' => 'main',
      'field_sd_disagg_company' => 'main',
      'field_sd_disagg_project' => 'main',
      'field_sd_oil_sector' => 'main',
      'field_sd_gas_sector' => 'main',
      'field_sd_mining_sector' => 'main',
      'field_sd_other_sector' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
    ),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['summary_data|summary_data|default'] = $ds_layout;

  return $export;
}
