<?php

/**
 * @file
 * eitiet_summary_data.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitiet_summary_data_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_contact_email_address'.
  $field_instances['summary_data-summary_data-field_sd_contact_email_address'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_contact_email_address',
    'label' => 'Email address',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_contact_name'.
  $field_instances['summary_data-summary_data-field_sd_contact_name'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_contact_name',
    'label' => 'Name',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 14,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_contact_organisation'.
  $field_instances['summary_data-summary_data-field_sd_contact_organisation'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_contact_organisation',
    'label' => 'Organisation',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 15,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_date_other_file_public'.
  $field_instances['summary_data-summary_data-field_sd_date_other_file_public'] = array(
    'bundle' => 'summary_data',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => FALSE,
        ),
        'type' => 'date_default',
        'weight' => 36,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_date_other_file_public',
    'label' => 'Date that other file was made public',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 29,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_disagg_company'.
  $field_instances['summary_data-summary_data-field_sd_disagg_company'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_company',
    'label' => '...by company',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 19,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_disagg_gover_agg'.
  $field_instances['summary_data-summary_data-field_sd_disagg_gover_agg'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 43,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_gover_agg',
    'label' => '… by government agency',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 18,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_disagg_project'.
  $field_instances['summary_data-summary_data-field_sd_disagg_project'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_project',
    'label' => '...by project',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 20,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_disagg_revenue_stream'.
  $field_instances['summary_data-summary_data-field_sd_disagg_revenue_stream'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 6,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_revenue_stream',
    'label' => '...by revenue stream',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 17,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_exchange_rate_src_url'.
  $field_instances['summary_data-summary_data-field_sd_exchange_rate_src_url'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 41,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_exchange_rate_src_url',
    'label' => 'Exchange rate source (URL,…)',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'urlwidget',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_file_links'.
  $field_instances['summary_data-summary_data-field_sd_file_links'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 10,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_file_links',
    'label' => 'Other data files',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'optional',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 30,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_gas_sector'.
  $field_instances['summary_data-summary_data-field_sd_gas_sector'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_gas_sector',
    'label' => 'Gas',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 9,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_gov_system_discl_locat'.
  $field_instances['summary_data-summary_data-field_sd_gov_system_discl_locat'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 32,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_gov_system_discl_locat',
    'label' => 'Does the government systematically disclose EITI data at a single location?',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 25,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_goverm_open_data_policy'.
  $field_instances['summary_data-summary_data-field_sd_goverm_open_data_policy'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 37,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_goverm_open_data_policy',
    'label' => 'Does the government have an open data policy?',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 31,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_independent_admin'.
  $field_instances['summary_data-summary_data-field_sd_independent_admin'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_independent_admin',
    'label' => 'Independent Administrator',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_indicator_values'.
  $field_instances['summary_data-summary_data-field_sd_indicator_values'] = array(
    'bundle' => 'summary_data',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_indicator_values',
    'label' => 'Indicator Values',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_existing' => 0,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'indicator values',
          'label_singular' => 'indicator value',
          'match_operator' => 'CONTAINS',
          'override_labels' => 0,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 17,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_iso_alpha_3_code'.
  $field_instances['summary_data-summary_data-field_sd_iso_alpha_3_code'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 29,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_iso_alpha_3_code',
    'label' => 'ISO Alpha-3 Code',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_mining_sector'.
  $field_instances['summary_data-summary_data-field_sd_mining_sector'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 13,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_mining_sector',
    'label' => 'Mining (incl. Quarrying)',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 10,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_nation_currency_iso4217'.
  $field_instances['summary_data-summary_data-field_sd_nation_currency_iso4217'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 42,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_nation_currency_iso4217',
    'label' => 'National currency ISO-4217',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_national_currency_name'.
  $field_instances['summary_data-summary_data-field_sd_national_currency_name'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 30,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_national_currency_name',
    'label' => 'National currency name',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_no_reporting_com'.
  $field_instances['summary_data-summary_data-field_sd_no_reporting_com'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_no_reporting_com',
    'label' => 'Number of reporting companies (incl SOEs if payer)',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 14,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_no_reporting_gov'.
  $field_instances['summary_data-summary_data-field_sd_no_reporting_gov'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_no_reporting_gov',
    'label' => 'Number of reporting government entities (incl SOEs if recipient)',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 13,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_not_applicable'.
  $field_instances['summary_data-summary_data-field_sd_not_applicable'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 46,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_not_applicable',
    'label' => 'Not applicable',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 35,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_not_available'.
  $field_instances['summary_data-summary_data-field_sd_not_available'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 47,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_not_available',
    'label' => 'Not available',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 36,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_oil_sector'.
  $field_instances['summary_data-summary_data-field_sd_oil_sector'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_oil_sector',
    'label' => 'Oil',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 8,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_open_data_portal_files'.
  $field_instances['summary_data-summary_data-field_sd_open_data_portal_files'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 38,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_open_data_portal_files',
    'label' => 'Open data portal / files',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'urlwidget',
      'weight' => 32,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_other_files_relecance'.
  $field_instances['summary_data-summary_data-field_sd_other_files_relecance'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 35,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_other_files_relecance',
    'label' => 'Are there other files of relevance?',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 28,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_other_non_upstr_sectors'.
  $field_instances['summary_data-summary_data-field_sd_other_non_upstr_sectors'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 39,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_other_non_upstr_sectors',
    'label' => 'Other, non-upstream sectors',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 11,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_other_sector_name'.
  $field_instances['summary_data-summary_data-field_sd_other_sector_name'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 40,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_other_sector_name',
    'label' => 'If yes, please specify name (insert new rows if multiple)',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 12,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_public_date_eiti_data'.
  $field_instances['summary_data-summary_data-field_sd_public_date_eiti_data'] = array(
    'bundle' => 'summary_data',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => FALSE,
        ),
        'type' => 'date_default',
        'weight' => 33,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_public_date_eiti_data',
    'label' => 'Publication date of the EITI data',
    'required' => 1,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_report_file'.
  $field_instances['summary_data-summary_data-field_sd_report_file'] = array(
    'bundle' => 'summary_data',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 9,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_report_file',
    'label' => 'Summary Data Report File',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'entity_translation_sync' => FALSE,
      'file_directory' => 'spreadsheets',
      'file_extensions' => 'xls xlsx',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => 0,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => 0,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'spreadsheets',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 0,
      'max_filesize' => '32 MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'vimeo' => 0,
          'youtube' => 0,
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 0,
          'report' => 'report',
          'video' => 0,
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 0,
          'media_library--audio_library' => 0,
          'media_library--document_library' => 0,
          'media_library--image_library' => 0,
          'media_library--video_library' => 0,
          'upload' => 'upload',
        ),
      ),
      'type' => 'media_generic',
      'weight' => 24,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_report_prep_independent'.
  $field_instances['summary_data-summary_data-field_sd_report_prep_independent'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 31,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_report_prep_independent',
    'label' => 'Has an EITI Report been prepared by an Independent Administrator?',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 21,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_revenue_company'.
  $field_instances['summary_data-summary_data-field_sd_revenue_company'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_revenue_company',
    'label' => 'Reconciled Revenue Streams per Company',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_existing' => 0,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'revenue streams',
          'label_singular' => 'revenue stream',
          'match_operator' => 'CONTAINS',
          'override_labels' => 0,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 19,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_revenue_government'.
  $field_instances['summary_data-summary_data-field_sd_revenue_government'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_revenue_government',
    'label' => 'Revenue Stream as Disclosed by Government',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_existing' => 0,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'revenue streams',
          'label_singular' => 'revenue stream',
          'match_operator' => 'CONTAINS',
          'override_labels' => 0,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 18,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_site_link_url_eiti_data'.
  $field_instances['summary_data-summary_data-field_sd_site_link_url_eiti_data'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 34,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_site_link_url_eiti_data',
    'label' => 'Website link (URL) to EITI data',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'urlwidget',
      'weight' => 27,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_systematic_disclosed'.
  $field_instances['summary_data-summary_data-field_sd_systematic_disclosed'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 44,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_systematic_disclosed',
    'label' => 'Systematically disclosed',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 33,
    ),
  );

  // Exported field_instance:
  // 'summary_data-summary_data-field_sd_through_eiti_reporting'.
  $field_instances['summary_data-summary_data-field_sd_through_eiti_reporting'] = array(
    'bundle' => 'summary_data',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 45,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_through_eiti_reporting',
    'label' => 'Through EITI Reporting',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 34,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('...by company');
  t('...by project');
  t('...by revenue stream');
  t('Are there other files of relevance?');
  t('Date that other file was made public');
  t('Does the government have an open data policy?');
  t('Does the government systematically disclose EITI data at a single location?');
  t('Email address');
  t('Exchange rate source (URL,…)');
  t('Gas');
  t('Has an EITI Report been prepared by an Independent Administrator?');
  t('ISO Alpha-3 Code');
  t('If yes, please specify name (insert new rows if multiple)');
  t('Independent Administrator');
  t('Indicator Values');
  t('Mining (incl. Quarrying)');
  t('Name');
  t('National currency ISO-4217');
  t('National currency name');
  t('Not applicable');
  t('Not available');
  t('Number of reporting companies (incl SOEs if payer)');
  t('Number of reporting government entities (incl SOEs if recipient)');
  t('Oil');
  t('Open data portal / files');
  t('Organisation');
  t('Other data files');
  t('Other, non-upstream sectors');
  t('Publication date of the EITI data');
  t('Reconciled Revenue Streams per Company');
  t('Revenue Stream as Disclosed by Government');
  t('Summary Data Report File');
  t('Systematically disclosed');
  t('Through EITI Reporting');
  t('Website link (URL) to EITI data');
  t('… by government agency');

  return $field_instances;
}
