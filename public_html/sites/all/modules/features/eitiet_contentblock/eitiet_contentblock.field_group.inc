<?php
/**
 * @file
 * eitiet_contentblock.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiet_contentblock_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_bookmark|contentblock|predefined|form';
  $field_group->group_name = 'group_bookmark';
  $field_group->entity_type = 'contentblock';
  $field_group->bundle = 'predefined';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bookmarks',
    'weight' => '2',
    'children' => array(
      0 => 'field_bookmark_list',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bookmarks',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-bookmark field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_bookmark|contentblock|predefined|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_wide_image|contentblock|predefined|form';
  $field_group->group_name = 'group_wide_image';
  $field_group->entity_type = 'contentblock';
  $field_group->bundle = 'predefined';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Wide Image',
    'weight' => '3',
    'children' => array(
      0 => 'field_cbw_wide_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-wide-image field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_wide_image|contentblock|predefined|form'] = $field_group;

  return $export;
}
