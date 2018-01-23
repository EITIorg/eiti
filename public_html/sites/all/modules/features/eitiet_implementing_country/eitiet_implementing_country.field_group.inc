<?php
/**
 * @file
 * eitiet_implementing_country.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiet_implementing_country_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata|implementing_country|normal|form';
  $field_group->group_name = 'group_metadata';
  $field_group->entity_type = 'implementing_country';
  $field_group->bundle = 'normal';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '4',
    'children' => array(
      0 => 'field_ic_change_status_date',
      1 => 'field_ic_status',
      2 => 'field_ic_validation_date',
      3 => 'field_ic_validation_link',
      4 => 'field_ic_validation_url',
      5 => 'field_ic_website',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-metadata field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_metadata|implementing_country|normal|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Metadata');

  return $field_groups;
}
