<?php

/**
 * @file
 * eitict_bookmark.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_bookmark_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay|node|bookmark|bm_large_tile';
  $field_group->group_name = 'group_overlay';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bookmark';
  $field_group->mode = 'bm_large_tile';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Overlay',
    'weight' => '1',
    'children' => array(
      0 => 'title_field',
      1 => 'field_bm_bookmark_type',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Overlay',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'overlay-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_overlay|node|bookmark|bm_large_tile'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay|node|bookmark|bm_medium_tile';
  $field_group->group_name = 'group_overlay';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bookmark';
  $field_group->mode = 'bm_medium_tile';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Overlay',
    'weight' => '15',
    'children' => array(
      0 => 'title_field',
      1 => 'field_bm_bookmark_type',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Overlay',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'overlay-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_overlay|node|bookmark|bm_medium_tile'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay|node|bookmark|bm_small_tile';
  $field_group->group_name = 'group_overlay';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bookmark';
  $field_group->mode = 'bm_small_tile';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Overlay',
    'weight' => '3',
    'children' => array(
      0 => 'title_field',
      1 => 'field_bm_bookmark_type',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Overlay',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'overlay-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_overlay|node|bookmark|bm_small_tile'] = $field_group;

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
      0 => 'field_bm_reference_type',
      1 => 'field_bm_reference',
      2 => 'field_bm_link',
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
  $field_groups['group_reference|node|bookmark|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Overlay');
  t('Reference');

  return $field_groups;
}
