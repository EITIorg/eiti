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
    'board_link' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
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
    'field_stk_countries' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_stk_content_title' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clearfix',
          'lbw' => 1,
        ),
      ),
    ),
    'field_supporter_since' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Founding supporter since',
        ),
      ),
    ),
  );
  $export['node|stakeholder|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|stakeholder_types|default';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'stakeholder_types';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'stakehoder_listing' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|stakeholder_types|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function eitict_stakeholder_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'stakehoder_listing';
  $ds_field->label = 'Stakehoder Listing';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'taxonomy_term' => 'taxonomy_term',
  );
  $ds_field->ui_limit = 'stakeholder_types|*';
  $ds_field->properties = array();
  $export['stakehoder_listing'] = $ds_field;

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
        'layout-separator' => 'layout-separator',
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
        1 => 'field_stk_countries',
      ),
      'right' => array(
        2 => 'title_field',
        3 => 'field_stk_website',
        4 => 'field_short_intro',
        5 => 'field_supporter_since',
        6 => 'field_stk_category',
        7 => 'field_stk_content_title',
        8 => 'group_quote',
        9 => 'body',
        10 => 'field_stk_statement',
        11 => 'field_stk_form',
        12 => 'field_stk_support',
        13 => 'field_fpp_person_list',
        14 => 'board_link',
        15 => 'field_stk_quote_title',
        16 => 'group_board',
        17 => 'field_stk_quote_text',
      ),
    ),
    'fields' => array(
      'field_stk_logo' => 'left',
      'field_stk_countries' => 'left',
      'title_field' => 'right',
      'field_stk_website' => 'right',
      'field_short_intro' => 'right',
      'field_supporter_since' => 'right',
      'field_stk_category' => 'right',
      'field_stk_content_title' => 'right',
      'group_quote' => 'right',
      'body' => 'right',
      'field_stk_statement' => 'right',
      'field_stk_form' => 'right',
      'field_stk_support' => 'right',
      'field_fpp_person_list' => 'right',
      'board_link' => 'right',
      'field_stk_quote_title' => 'right',
      'group_board' => 'right',
      'field_stk_quote_text' => 'right',
    ),
    'classes' => array(
      'layout_class' => array(
        'layout-narrow-left-column' => 'layout-narrow-left-column',
      ),
    ),
    'wrappers' => array(
      'above' => 'div',
      'left' => 'div',
      'right' => 'div',
      'below' => 'div',
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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|stakeholder_types|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'stakeholder_types';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'doublelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'above' => array(
        0 => 'name_field',
      ),
      'left' => array(
        1 => 'description_field',
        2 => 'stakehoder_listing',
      ),
      'right' => array(
        3 => 'field_stakeholder_type_sidebar',
      ),
    ),
    'fields' => array(
      'name_field' => 'above',
      'description_field' => 'left',
      'stakehoder_listing' => 'left',
      'field_stakeholder_type_sidebar' => 'right',
    ),
    'classes' => array(
      'layout_class' => array(
        'clearfix' => 'clearfix',
        'layout-narrow-right-column' => 'layout-narrow-right-column',
      ),
      'above' => array(
        'single-fluid-row-wrapper' => 'single-fluid-row-wrapper',
      ),
    ),
    'wrappers' => array(
      'above' => 'div',
      'left' => 'div',
      'right' => 'div',
      'below' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['taxonomy_term|stakeholder_types|default'] = $ds_layout;

  return $export;
}
