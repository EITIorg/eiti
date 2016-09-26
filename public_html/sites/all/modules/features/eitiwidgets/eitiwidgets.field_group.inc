<?php
/**
 * @file
 * eitiwidgets.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function eitiwidgets_field_group_info() {
  $field_groups = array();

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
  $field_groups['group_blockquote|fieldable_panels_pane|quote|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|featured_bookmarks|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'featured_bookmarks';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|featured_bookmarks|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|icon_blocks|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'icon_blocks';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|icon_blocks|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|table|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'table';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|table|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|text|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'text';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|text|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|value_chain|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'value_chain';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|value_chain|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_display|fieldable_panels_pane|visualization|form';
  $field_group->group_name = 'group_title_display';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'visualization';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Display',
    'weight' => '2',
    'children' => array(
      0 => 'field_fpp_icon',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Title Display',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-title-display field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_title_display|fieldable_panels_pane|visualization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|fact_blocks|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'fact_blocks';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Wrapper',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|fact_blocks|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|featured_bookmarks|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'featured_bookmarks';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Wrapper',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
      1 => 'field_fpp_icon',
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|featured_bookmarks|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|featured_persons|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'featured_persons';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Wrapper',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|featured_persons|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|featured_publications|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'featured_publications';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Title Wrapper',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|featured_publications|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|icon_blocks|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'icon_blocks';
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|icon_blocks|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|table|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'table';
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|table|default'] = $field_group;

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
      0 => 'title_field',
      1 => 'field_fpp_icon',
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|text|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|value_chain|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'value_chain';
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|value_chain|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_title_wrapper|fieldable_panels_pane|visualization|default';
  $field_group->group_name = 'group_title_wrapper';
  $field_group->entity_type = 'fieldable_panels_pane';
  $field_group->bundle = 'visualization';
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
  $field_groups['group_title_wrapper|fieldable_panels_pane|visualization|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blockquote');
  t('Title Display');
  t('Title Wrapper');

  return $field_groups;
}
