<?php

/**
 * @file
 * eitict_bookmark.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_bookmark_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bookmark|bm_large_tile';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bookmark';
  $ds_fieldsetting->view_mode = 'bm_large_tile';
  $ds_fieldsetting->settings = array(
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
  );
  $export['node|bookmark|bm_large_tile'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bookmark|bm_medium_tile';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bookmark';
  $ds_fieldsetting->view_mode = 'bm_medium_tile';
  $ds_fieldsetting->settings = array(
    'field_bm_image' => array(
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
  $export['node|bookmark|bm_medium_tile'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bookmark|bm_small_tile';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bookmark';
  $ds_fieldsetting->view_mode = 'bm_small_tile';
  $ds_fieldsetting->settings = array(
    'field_bm_image' => array(
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
  $export['node|bookmark|bm_small_tile'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_bookmark_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bookmark|bm_large_tile';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bookmark';
  $ds_layout->view_mode = 'bm_large_tile';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'field_bm_image',
        1 => 'field_bm_bookmark_type',
        2 => 'group_overlay',
        4 => 'title_field',
      ),
      'ds_hidden' => array(
        3 => 'field_bm_hide_title',
        5 => 'field_bm_reference',
        6 => 'field_bm_reference_type',
      ),
    ),
    'fields' => array(
      'field_bm_image' => 'main',
      'field_bm_bookmark_type' => 'main',
      'group_overlay' => 'main',
      'field_bm_hide_title' => 'ds_hidden',
      'title_field' => 'main',
      'field_bm_reference' => 'ds_hidden',
      'field_bm_reference_type' => 'ds_hidden',
    ),
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|bookmark|bm_large_tile'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bookmark|bm_medium_tile';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bookmark';
  $ds_layout->view_mode = 'bm_medium_tile';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'regions' => array(
      'main' => array(
        0 => 'field_bm_image',
        1 => 'field_bm_bookmark_type',
        2 => 'title_field',
        3 => 'group_overlay',
      ),
      'ds_hidden' => array(
        0 => 'field_bm_hide_title',
        1 => 'field_bm_reference',
        2 => 'field_bm_reference_type',
      ),
    ),
    'fields' => array(
      'field_bm_image' => 'main',
      'field_bm_bookmark_type' => 'main',
      'title_field' => 'main',
      'group_overlay' => 'main',
      'field_bm_hide_title' => 'ds_hidden',
      'field_bm_reference' => 'ds_hidden',
      'field_bm_reference_type' => 'ds_hidden',
    ),
  );
  $export['node|bookmark|bm_medium_tile'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bookmark|bm_small_tile';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bookmark';
  $ds_layout->view_mode = 'bm_small_tile';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'regions' => array(
      'main' => array(
        0 => 'field_bm_image',
        1 => 'field_bm_bookmark_type',
        2 => 'title_field',
        3 => 'group_overlay',
      ),
      'ds_hidden' => array(
        0 => 'field_bm_hide_title',
        1 => 'field_bm_reference',
        2 => 'field_bm_reference_type',
      ),
    ),
    'fields' => array(
      'field_bm_image' => 'main',
      'field_bm_bookmark_type' => 'main',
      'title_field' => 'main',
      'group_overlay' => 'main',
      'field_bm_hide_title' => 'ds_hidden',
      'field_bm_reference' => 'ds_hidden',
      'field_bm_reference_type' => 'ds_hidden',
    ),
  );
  $export['node|bookmark|bm_small_tile'] = $ds_layout;

  return $export;
}
