<?php
/**
 * @file
 * eitiwidgets.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitiwidgets_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'fieldable_panels_pane|quote|default';
  $ds_fieldsetting->entity_type = 'fieldable_panels_pane';
  $ds_fieldsetting->bundle = 'quote';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'field_fpp_source' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'footer',
          'ow-cl' => '',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'cite',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
  );
  $export['fieldable_panels_pane|quote|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitiwidgets_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'fieldable_panels_pane|quote|default';
  $ds_layout->entity_type = 'fieldable_panels_pane';
  $ds_layout->bundle = 'quote';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'simplelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'group_blockquote',
        4 => 'field_fpp_quote',
        5 => 'field_fpp_source',
      ),
      'ds_hidden' => array(
        1 => 'field_fpp_background_image',
        2 => 'title',
        3 => 'field_fpp_source_url',
      ),
    ),
    'fields' => array(
      'group_blockquote' => 'main',
      'field_fpp_background_image' => 'ds_hidden',
      'title' => 'ds_hidden',
      'field_fpp_source_url' => 'ds_hidden',
      'field_fpp_quote' => 'main',
      'field_fpp_source' => 'main',
    ),
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => ' class="xxx"',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['fieldable_panels_pane|quote|default'] = $ds_layout;

  return $export;
}
