<?php
/**
 * @file
 * eitict_person.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_person_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|person|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'person';
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
  $export['node|person|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|person|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'person';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|person|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_person_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|person|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'person';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_person_picture',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'field_position',
        3 => 'field_board_member_type',
        4 => 'field_board_membership',
        5 => 'body',
        6 => 'field_phone_number',
        7 => 'field_fax_number',
        8 => 'field_email',
        9 => 'field_website',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'side',
      'title_field' => 'main',
      'field_position' => 'main',
      'field_board_member_type' => 'main',
      'field_board_membership' => 'main',
      'body' => 'main',
      'field_phone_number' => 'main',
      'field_fax_number' => 'main',
      'field_email' => 'main',
      'field_website' => 'main',
    ),
    'classes' => array(),
    'wrappers' => array(
      'side' => 'div',
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
  $export['node|person|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|person|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'person';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_person_picture',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'group_details',
        3 => 'body',
        4 => 'field_position',
        5 => 'node_link',
        6 => 'field_email',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'side',
      'title_field' => 'main',
      'group_details' => 'main',
      'body' => 'main',
      'field_position' => 'main',
      'node_link' => 'main',
      'field_email' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        'clearfix' => 'clearfix',
      ),
    ),
    'wrappers' => array(
      'side' => 'div',
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|person|teaser'] = $ds_layout;

  return $export;
}
