<?php

/**
 * @file
 * eitict_article.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_article_field_group_info() {
  $field_groups = array();

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
    'weight' => '6',
    'children' => array(
      0 => 'field_event_location',
      1 => 'field_event_date',
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
  $field_groups['group_event_details|node|article|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event Details');

  return $field_groups;
}
