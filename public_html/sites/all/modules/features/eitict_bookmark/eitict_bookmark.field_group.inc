<?php
/**
 * @file
 * eitict_bookmark.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_bookmark_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_reference|node|bookmark|form';
  $field_group->group_name = 'group_reference';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bookmark';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reference',
    'weight' => '5',
    'children' => array(
      0 => 'field_bm_link',
      1 => 'field_bm_reference_type',
      2 => 'field_bm_reference',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-reference field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_reference|node|bookmark|form'] = $field_group;

  return $export;
}
