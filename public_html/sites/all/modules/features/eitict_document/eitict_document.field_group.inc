<?php
/**
 * @file
 * eitict_document.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitict_document_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_doc_details|node|document|default';
  $field_group->group_name = 'group_doc_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Document Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_document_category',
      1 => 'field_doc_image_preview',
      2 => 'field_doc_published_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Document Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'document-details-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_doc_details|node|document|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Document Details');

  return $field_groups;
}
