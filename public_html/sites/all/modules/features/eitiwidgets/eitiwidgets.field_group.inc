<?php
/**
 * @file
 * eitiwidgets.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiwidgets_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_blockquote|fieldable_panels_pane|quote|default';
  $field_group->group_name = 'group_blockquote';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'quote';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Blockquote',
    'weight' => '0',
    'children' => array(
      0 => 'field_fpp_quote',
      1 => 'field_fpp_source',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'Blockquote',
      'instance_settings' => array(
        'classes' => '',
        'element' => 'blockquote',
        'show_label' => '0',
        'label_element' => '',
        'attributes' => '',
      ),
    ),
  );
  $export['group_blockquote|fieldable_panels_pane|quote|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|text|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'text';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Wrapper',
    'weight' => '0',
    'children' => array(
      0 => 'field_fpp_icon',
      1 => 'title_field',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Title Wrapper',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'pane-title-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_title_wrapper|fieldable_panels_pane|text|default'] = $field_group;

  return $export;
}
