<?php

/**
 * @file
 * eitiet_summary_data.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiet_summary_data_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_about|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_about';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '0',
    'children' => array(
      0 => 'group_sd_data_access_open_data',
      1 => 'group_sd_data_source',
      2 => 'group_sd_fiscal_year',
      3 => 'group_sd_overview_requirement',
      4 => 'group_sd_contact_details',
      5 => 'group_sd_country_or_area',
      6 => 'group_sd_data_coverage',
      7 => 'group_sd_data_disaggregation',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-about field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_about|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_contact_details|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_contact_details';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Name and contact information of the person submitting this file',
    'weight' => '31',
    'children' => array(
      0 => 'field_sd_contact_organisation',
      1 => 'field_sd_contact_email_address',
      2 => 'field_sd_contact_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Name and contact information of the person submitting this file',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-sd-contact-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_sd_contact_details|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_country_or_area|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_country_or_area';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Country or area',
    'weight' => '24',
    'children' => array(
      0 => 'field_sd_iso_alpha_3_code',
      1 => 'field_sd_nation_currency_iso4217',
      2 => 'field_sd_national_currency_name',
      3 => 'country_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-country-or-area field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_country_or_area|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_data_access_open_data|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_data_access_open_data';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Data accessibility and open data',
    'weight' => '27',
    'children' => array(
      0 => 'field_sd_goverm_open_data_policy',
      1 => 'field_sd_open_data_portal_files',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-data-access-open-data field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_data_access_open_data|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_data_coverage|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_data_coverage';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Data coverage / scope',
    'weight' => '28',
    'children' => array(
      0 => 'group_sd_reporting_currency',
      1 => 'group_sd_sectors_covered',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-data-coverage field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_data_coverage|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_data_disaggregation|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_data_disaggregation';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Disaggregation of Data',
    'weight' => '29',
    'children' => array(
      0 => 'field_sd_disagg_project',
      1 => 'field_sd_disagg_company',
      2 => 'field_sd_disagg_gover_agg',
      3 => 'field_sd_disagg_revenue_stream',
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
  $field_groups['group_sd_data_disaggregation|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_data_source|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_data_source';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Data source',
    'weight' => '26',
    'children' => array(
      0 => 'field_sd_file_links',
      1 => 'field_sd_gov_system_discl_locat',
      2 => 'field_sd_other_files_relecance',
      3 => 'field_sd_report_prep_independent',
      4 => 'field_sd_site_link_url_eiti_data',
      5 => 'field_sd_public_date_eiti_data',
      6 => 'field_sd_company_name',
      7 => 'field_sd_url_eiti_report',
      8 => 'field_sd_date_other_file_public',
      9 => 'field_sd_report_file',
      10 => 'published',
      11 => 'company_id_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-data-source field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_data_source|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_fiscal_year|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_fiscal_year';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Fiscal Year Covered in the Report',
    'weight' => '25',
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
  $field_groups['group_sd_fiscal_year|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_overview_requirement|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_overview_requirement';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_about';
  $field_group->data = array(
    'label' => 'Data overview / requirement',
    'weight' => '30',
    'children' => array(
      0 => 'field_sd_not_applicable',
      1 => 'field_sd_not_available',
      2 => 'field_sd_systematic_disclosed',
      3 => 'field_sd_through_eiti_reporting',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sd-overview-requirement field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sd_overview_requirement|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_reporting_currency|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_reporting_currency';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_data_coverage';
  $field_group->data = array(
    'label' => 'Reporting currency',
    'weight' => '12',
    'children' => array(
      0 => 'field_sd_exchange_rate_src_url',
      1 => 'currency_code',
      2 => 'currency_rate',
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
  $field_groups['group_sd_reporting_currency|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sd_sectors_covered|summary_data|summary_data|form';
  $field_group->group_name = 'group_sd_sectors_covered';
  $field_group->entity_type = 'summary_data';
  $field_group->bundle = 'summary_data';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sd_data_coverage';
  $field_group->data = array(
    'label' => 'Sectors Covered',
    'weight' => '10',
    'children' => array(
      0 => 'field_sd_mining_sector',
      1 => 'field_sd_no_reporting_com',
      2 => 'field_sd_oil_sector',
      3 => 'field_sd_gas_sector',
      4 => 'field_sd_no_reporting_gov',
      5 => 'field_sd_other_non_upstr_sectors',
      6 => 'field_sd_other_sector_name',
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
  $field_groups['group_sd_sectors_covered|summary_data|summary_data|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
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
  $field_groups['group_sd_web_links|summary_data|summary_data|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Country or area');
  t('Data accessibility and open data');
  t('Data coverage / scope');
  t('Data overview / requirement');
  t('Data source');
  t('Disaggregation of Data');
  t('Fiscal Year Covered in the Report');
  t('Name and contact information of the person submitting this file');
  t('Reporting currency');
  t('Sectors Covered');
  t('Web links to EITI Report, on the national EITI website');

  return $field_groups;
}
