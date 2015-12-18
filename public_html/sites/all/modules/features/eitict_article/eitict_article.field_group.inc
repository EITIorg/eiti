<?php
/**
 * @file
 * eitict_article.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_article_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_details|node|article|form';
  $field_group->group_name = 'group_event_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Event Details',
    'weight' => '7',
    'children' => array(
      0 => 'field_event_date',
      1 => 'field_event_location',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-event-details field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_event_details|node|article|form'] = $field_group;

  return $export;
}
