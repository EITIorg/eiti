<?php
/**
 * @file
 * eitict_stakeholder.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_stakeholder_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|stakeholder|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'stakeholder';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'field_stk_logo' => array(
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
  $export['node|stakeholder|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|stakeholder|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'stakeholder';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
    'field_stk_countries' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
  );
  $export['node|stakeholder|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_stakeholder_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|stakeholder|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'stakeholder';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_stk_logo',
      ),
      'main' => array(
        1 => 'title_field',
      ),
    ),
    'fields' => array(
      'field_stk_logo' => 'side',
      'title_field' => 'main',
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
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|stakeholder|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|stakeholder|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'stakeholder';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'doublelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_stk_logo',
        1 => 'field_stk_category',
        2 => 'field_stk_website',
        3 => 'field_stk_countries',
      ),
      'right' => array(
        4 => 'title_field',
        5 => 'body',
        6 => 'field_stk_form',
        7 => 'field_stk_statement',
        8 => 'field_stk_support',
      ),
    ),
    'fields' => array(
      'field_stk_logo' => 'left',
      'field_stk_category' => 'left',
      'field_stk_website' => 'left',
      'field_stk_countries' => 'left',
      'title_field' => 'right',
      'body' => 'right',
      'field_stk_form' => 'right',
      'field_stk_statement' => 'right',
      'field_stk_support' => 'right',
    ),
    'classes' => array(
      'layout_class' => array(
        'layout-narrow-left-column' => 'layout-narrow-left-column',
      ),
    ),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|stakeholder|full'] = $ds_layout;

  return $export;
}