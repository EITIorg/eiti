<?php
/**
 * @file
 * eitiet_summary_data.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiet_summary_data_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_contact_details|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_contact_details';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact details',
    'weight' => '11',
    'children' => array(
      0 => 'field_sd_contact_organisation',
      1 => 'field_sd_contact_email_address',
      2 => 'field_sd_contact_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Contact details',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-sd-contact-details field-group-fieldset',
        'description' => 'Contact details to person who has completed this template',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_sd_contact_details|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_data_disaggregation|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_data_disaggregation';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Disaggregation of Data',
    'weight' => '10',
    'children' => array(
      0 => 'field_sd_disagg_project',
      1 => 'field_sd_disagg_revenue_stream',
      2 => 'field_sd_disagg_company',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-data-disaggregation field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sd_data_disaggregation|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_fiscal_year|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_fiscal_year';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Fiscal Year Covered in the Report',
    'weight' => '2',
    'children' => array(
      0 => 'year_start',
      1 => 'year_end',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-fiscal-year field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sd_fiscal_year|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_reporting_currency|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_reporting_currency';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reporting currency',
    'weight' => '9',
    'children' => array(
      0 => 'currency_code',
      1 => 'currency_rate',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-reporting-currency field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sd_reporting_currency|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_sectors_covered|summary_data|summary_data|default';
  $field_group->group_name = 'group_sd_sectors_covered';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sectors Covered',
    'weight' => '11',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-sectors-covered field-group-fieldset',
      ),
    ),
  );
  $export['group_sd_sectors_covered|summary_data|summary_data|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_sectors_covered|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_sectors_covered';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sectors Covered',
    'weight' => '5',
    'children' => array(
      0 => 'field_sd_gas_sector',
      1 => 'field_sd_mining_sector',
      2 => 'field_sd_oil_sector',
      3 => 'field_sd_other_sector',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-sectors-covered field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sd_sectors_covered|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_web_links|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_web_links';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Web links to EITI Report, on the national EITI website',
    'weight' => '6',
    'children' => array(
      0 => 'field_sd_file_links',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-web-links field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sd_web_links|summary_data|summary_data|form'] = $field_group;

  return $export;
}
