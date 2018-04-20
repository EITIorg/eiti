<?php
/**
 * @file
 * eitiet_score_data.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiet_score_data_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_scd_pdf|score_data|standard|form';
  $field_group->group_name = 'group_scd_pdf';
  $field_group->entity_type = 'score_data';
  $field_group->bundle = 'standard';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PDF data',
    'weight' => '34',
    'children' => array(
      0 => 'field_scd_pdf_date',
      1 => 'field_scd_pdf_decision_ref',
      2 => 'field_scd_pdf_news',
      3 => 'field_scd_pdf_text1',
      4 => 'field_scd_pdf_text2',
      5 => 'field_scd_pdf_title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-scd-pdf field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_scd_pdf|score_data|standard|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('PDF data');

  return $field_groups;
}
