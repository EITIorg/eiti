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
  $field_group->identifier = 'group_article_info_wrapper|node|article|default';
  $field_group->group_name = 'group_article_info_wrapper';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Article Info Wrapper',
    'weight' => '1',
    'children' => array(
      0 => 'group_article_info',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Article Info Wrapper',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'article-info-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_article_info_wrapper|node|article|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_info_wrapper|node|article|full';
  $field_group->group_name = 'group_article_info_wrapper';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Article Info Wrapper',
    'weight' => '1',
    'children' => array(
      0 => 'group_article_info',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Article Info Wrapper',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'article-info-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_article_info_wrapper|node|article|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_info|node|article|default';
  $field_group->group_name = 'group_article_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_article_info_wrapper';
  $field_group->data = array(
    'label' => 'Article Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_tags',
      1 => 'author',
      2 => 'post_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Article Info',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'article-info single-fluid-row-wrapper clearfix',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_article_info|node|article|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_info|node|article|full';
  $field_group->group_name = 'group_article_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'full';
  $field_group->parent_name = 'group_article_info_wrapper';
  $field_group->data = array(
    'label' => 'Article Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_tags',
      1 => 'author',
      2 => 'post_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Article Info',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'article-info single-fluid-row-wrapper clearfix',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_article_info|node|article|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_info|node|article|teaser_alternative';
  $field_group->group_name = 'group_article_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'teaser_alternative';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Article Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_tags',
      1 => 'author',
      2 => 'post_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Article Info',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'article-info',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_article_info|node|article|teaser_alternative'] = $field_group;

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
  $field_groups['group_event_details|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_featured_image_header|node|article|default';
  $field_group->group_name = 'group_featured_image_header';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Featured Image Header',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
      1 => 'field_featured_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Featured Image Header',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'featured-image-header-wrapper  clearfix',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_featured_image_header|node|article|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_featured_image_header|node|article|full';
  $field_group->group_name = 'group_featured_image_header';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Featured Image Header',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
      1 => 'field_featured_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Featured Image Header',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'featured-image-header-wrapper  clearfix',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_featured_image_header|node|article|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Article Info');
  t('Article Info Wrapper');
  t('Event Details');
  t('Featured Image Header');

  return $field_groups;
}
