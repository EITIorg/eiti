<?php

/**
 * @file
 * eitict_stakeholder.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_stakeholder_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_board|node|stakeholder|full';
  $field_group->group_name = 'group_board';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'stakeholder';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'EITI Board member',
    'weight' => '13',
    'children' => array(
      0 => 'field_fpp_person_list',
      1 => 'board_link',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'EITI Board member',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-board field-group-div',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_board|node|stakeholder|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_quote|node|stakeholder|form';
  $field_group->group_name = 'group_quote';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'stakeholder';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Quote ',
    'weight' => '10',
    'children' => array(
      0 => 'field_stk_quote_title',
      1 => 'field_stk_quote_text',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Quote ',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-quote field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_quote|node|stakeholder|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_quote|node|stakeholder|full';
  $field_group->group_name = 'group_quote';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'stakeholder';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Quote ',
    'weight' => '8',
    'children' => array(
      0 => 'field_stk_quote_title',
      1 => 'field_stk_quote_text',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Quote ',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-quote field-group-fieldset',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_quote|node|stakeholder|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('EITI Board member');
  t('Quote ');

  return $field_groups;
}
