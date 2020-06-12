<?php

/**
 * @file
 * eitiet_score_data.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitiet_score_data_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'score_data-standard-field_assessment_date'.
  $field_instances['score_data-standard-field_assessment_date'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => 'The Validation commencement date	',
    'display' => array(
      'default' => array(
        'label' => 'inline',
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
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_assessment_date',
    'label' => 'Assessment date',
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
        'increment' => 15,
        'input_format' => 'd.m.Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 45,
    ),
  );

  // Exported field_instance:
  // 'score_data-standard-field_corrective_actions_num'.
  $field_instances['score_data-standard-field_corrective_actions_num'] = array(
    'bundle' => 'standard',
    'default_value' => array(
      0 => array(
        'value' => 50,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
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
    'entity_type' => 'score_data',
    'field_name' => 'field_corrective_actions_num',
    'label' => 'Number of corrective actions',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max' => '',
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'numberfield',
      'weight' => 47,
    ),
  );

  // Exported field_instance:
  // 'score_data-standard-field_field_validation_against'.
  $field_instances['score_data-standard-field_field_validation_against'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The Standard value of Score  Requirements',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 6,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_field_validation_against',
    'label' => 'Validation against',
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
      'weight' => 49,
    ),
  );

  // Exported field_instance:
  // 'score_data-standard-field_next_validation_commences'.
  $field_instances['score_data-standard-field_next_validation_commences'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
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
        'weight' => 5,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_next_validation_commences',
    'label' => 'Next Validation commences',
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
        'increment' => 30,
        'input_format' => 'd.m.Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+10',
      ),
      'type' => 'date_popup',
      'weight' => 48,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_overall_assessment'.
  $field_instances['score_data-standard-field_overall_assessment'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_overall_assessment',
    'label' => 'Overall assessment',
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
      'weight' => 44,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_date'.
  $field_instances['score_data-standard-field_scd_pdf_date'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_date',
    'label' => 'Date',
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
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 34,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_decision_ref'.
  $field_instances['score_data-standard-field_scd_pdf_decision_ref'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This field will be pre-populated by Board decision data if it already related to current Validation.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_decision_ref',
    'label' => 'Decision reference',
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
      'weight' => 40,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_news'.
  $field_instances['score_data-standard-field_scd_pdf_news'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_news',
    'label' => 'News',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 38,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_text1'.
  $field_instances['score_data-standard-field_scd_pdf_text1'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_text1',
    'label' => 'The Board\'s decision',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 41,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_text2'.
  $field_instances['score_data-standard-field_scd_pdf_text2'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 14,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_text2',
    'label' => 'Corrective actions',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 43,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_text3'.
  $field_instances['score_data-standard-field_scd_pdf_text3'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_text3',
    'label' => 'Background',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 42,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_title'.
  $field_instances['score_data-standard-field_scd_pdf_title'] = array(
    'bundle' => 'standard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The title of PDF will be: "Validation of (Country name)"',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_title',
    'label' => 'Country name',
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
      'weight' => 37,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_pdf_title_prefix'.
  $field_instances['score_data-standard-field_scd_pdf_title_prefix'] = array(
    'bundle' => 'standard',
    'default_value' => array(
      0 => array(
        'value' => 'Validation of',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_pdf_title_prefix',
    'label' => 'Title prefix',
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
      'weight' => 36,
    ),
  );

  // Exported field_instance: 'score_data-standard-field_scd_score_req_values'.
  $field_instances['score_data-standard-field_scd_score_req_values'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 7,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_score_req_values',
    'label' => 'Score Requirements Values',
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
          'allow_clone' => 0,
          'allow_existing' => 0,
          'allow_new' => 1,
          'delete_references' => 1,
          'label_plural' => 'Score Requirement Values',
          'label_singular' => 'Score Requirement Value',
          'match_operator' => 'CONTAINS',
          'override_labels' => 0,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'score_data-standard-field_validation_fiscal_year'.
  $field_instances['score_data-standard-field_validation_fiscal_year'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
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
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => 'theme_field',
    'entity_type' => 'score_data',
    'field_name' => 'field_validation_fiscal_year',
    'label' => 'Fiscal year reviewed for Validation',
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
        'increment' => 30,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-5:+10',
      ),
      'type' => 'date_select',
      'weight' => 46,
    ),
  );

  // Exported field_instance: 'score_req-standard-field_score_req_standard'.
  $field_instances['score_req-standard-field_score_req_standard'] = array(
    'bundle' => 'standard',
    'default_value' => array(
      0 => array(
        'tid' => 10394,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_req',
    'field_name' => 'field_score_req_standard',
    'label' => 'Standard',
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
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'taxonomy_term-score_requirement_category-field_score_req_standard'.
  $field_instances['taxonomy_term-score_requirement_category-field_score_req_standard'] = array(
    'bundle' => 'score_requirement_category',
    'default_value' => array(
      0 => array(
        'tid' => 10394,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_score_req_standard',
    'label' => 'Standard',
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
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'taxonomy_term-standards-description_field'.
  $field_instances['taxonomy_term-standards-description_field'] = array(
    'bundle' => 'standards',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'description_field',
    'label' => 'Description',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => 0,
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => 'entity',
        'page' => 0,
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'taxonomy_term-standards-name_field'.
  $field_instances['taxonomy_term-standards-name_field'] = array(
    'bundle' => 'standards',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'name_field',
    'label' => 'Name',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => 'entity',
        'page' => 0,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assessment date');
  t('Background');
  t('Corrective actions');
  t('Country name');
  t('Date');
  t('Decision reference');
  t('Description');
  t('Fiscal year reviewed for Validation');
  t('Name');
  t('News');
  t('Next Validation commences');
  t('Number of corrective actions');
  t('Overall assessment');
  t('Score Requirements Values');
  t('Standard');
  t('The Board\'s decision');
  t('The Standard value of Score  Requirements');
  t('The Validation commencement date	');
  t('The title of PDF will be: "Validation of (Country name)"');
  t('This field will be pre-populated by Board decision data if it already related to current Validation.');
  t('Title prefix');
  t('Validation against');

  return $field_instances;
}
