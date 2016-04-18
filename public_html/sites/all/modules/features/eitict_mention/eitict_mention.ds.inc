<?php
/**
 * @file
 * eitict_mention.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_mention_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|mention|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'mention';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
  );
  $export['node|mention|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_mention_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|mention|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'mention';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'title_field',
        1 => 'group_details',
        2 => 'field_published_date',
        3 => 'field_source_link',
        4 => 'body',
      ),
    ),
    'fields' => array(
      'title_field' => 'main',
      'group_details' => 'main',
      'field_published_date' => 'main',
      'field_source_link' => 'main',
      'body' => 'main',
    ),
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|mention|default'] = $ds_layout;

  return $export;
}
