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
  $ds_fieldsetting->id = 'node|person|summary';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'person';
  $ds_fieldsetting->view_mode = 'summary';
  $ds_fieldsetting->settings = array(
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
  );
  $export['node|person|summary'] = $ds_fieldsetting;

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
      'formatter_settings' => array(
        'link text' => 'View profile',
        'link class' => '',
        'wrapper' => '',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'field_person_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
  );
  $export['node|person|teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|person|teaser_alternative';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'person';
  $ds_fieldsetting->view_mode = 'teaser_alternative';
  $ds_fieldsetting->settings = array(
    'field_person_picture' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
  );
  $export['node|person|teaser_alternative'] = $ds_fieldsetting;

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
        3 => 'field_twitter_handle',
        4 => 'field_board_member_type',
        5 => 'body',
        6 => 'field_skype_id',
        7 => 'field_phone_number',
        8 => 'field_fax_number',
        9 => 'field_email',
        10 => 'group_quick_links',
        11 => 'field_website',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'side',
      'title_field' => 'main',
      'field_position' => 'main',
      'field_twitter_handle' => 'main',
      'field_board_member_type' => 'main',
      'body' => 'main',
      'field_skype_id' => 'main',
      'field_phone_number' => 'main',
      'field_fax_number' => 'main',
      'field_email' => 'main',
      'group_quick_links' => 'main',
      'field_website' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'side' => array(
        'image-wrapped' => 'image-wrapped',
      ),
    ),
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
  $ds_layout->id = 'node|person|summary';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'person';
  $ds_layout->view_mode = 'summary';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'field_person_picture',
        1 => 'title_field',
        2 => 'field_position',
        3 => 'body',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'main',
      'title_field' => 'main',
      'field_position' => 'main',
      'body' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
    ),
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
  $export['node|person|summary'] = $ds_layout;

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
        2 => 'group_quick_links',
        3 => 'field_board_membership',
        4 => 'field_twitter_handle',
        5 => 'group_details',
        6 => 'field_position',
        7 => 'field_skype_id',
        8 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'side',
      'title_field' => 'main',
      'group_quick_links' => 'main',
      'field_board_membership' => 'main',
      'field_twitter_handle' => 'main',
      'group_details' => 'main',
      'field_position' => 'main',
      'field_skype_id' => 'main',
      'node_link' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        'clearfix' => 'clearfix',
        'layout-separator' => 'layout-separator',
      ),
      'side' => array(
        'image-wrapped' => 'image-wrapped',
      ),
    ),
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
  $export['node|person|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|person|teaser_alternative';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'person';
  $ds_layout->view_mode = 'teaser_alternative';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'field_person_picture',
        1 => 'title_field',
        2 => 'field_position',
      ),
    ),
    'fields' => array(
      'field_person_picture' => 'main',
      'title_field' => 'main',
      'field_position' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
    ),
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
  $export['node|person|teaser_alternative'] = $ds_layout;

  return $export;
}
