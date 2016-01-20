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
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_default',
        'weight' => 20,
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
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 18,
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
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 19,
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
        'weight' => 23,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_company',
    'label' => 'By Company',
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
        'weight' => 24,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_project',
    'label' => 'By Project',
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
        'weight' => 22,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_disagg_revenue_stream',
    'label' => 'By Revenue Stream',
    'required' => FALSE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 17,
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
        'weight' => 15,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_file_links',
    'label' => 'File Links',
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
      'weight' => 13,
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
        'weight' => 10,
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
        'weight' => 13,
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
      'weight' => 2,
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
        'module' => 'entityreference',
        'settings' => array(),
        'type' => 'entityreference_entity_id',
        'weight' => 21,
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
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'summary_data-summary_data-field_sd_mining_sector'.
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
        'weight' => 11,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_mining_sector',
    'label' => 'Mining',
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
        'weight' => 17,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_no_reporting_com',
    'label' => 'Number of reporting companies',
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
      'weight' => 7,
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
        'weight' => 16,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_no_reporting_gov',
    'label' => 'Number of reporting government entities',
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
      'weight' => 6,
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
        'weight' => 9,
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

  // Exported field_instance: 'summary_data-summary_data-field_sd_other_sector'.
  $field_instances['summary_data-summary_data-field_sd_other_sector'] = array(
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
        'weight' => 12,
      ),
    ),
    'entity_type' => 'summary_data',
    'field_name' => 'field_sd_other_sector',
    'label' => 'Other',
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
      'weight' => 11,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('By Company');
  t('By Project');
  t('By Revenue Stream');
  t('Email address');
  t('File Links');
  t('Gas');
  t('Independent Administrator');
  t('Indicator Values');
  t('Mining');
  t('Name');
  t('Number of reporting companies');
  t('Number of reporting government entities');
  t('Oil');
  t('Organisation');
  t('Other');

  return $field_instances;
}
