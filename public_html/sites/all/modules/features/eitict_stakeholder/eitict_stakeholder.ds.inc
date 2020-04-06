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
    'field_stk_membership' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_fpp_person_list' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_stk_quote_title' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clearfix',
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
          'lb-col' => TRUE,
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
    'field_contact_eiti' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-col' => TRUE,
          'ow' => TRUE,
          'ow-el' => 'div',
          'ow-cl' => 'stk-type-contact',
          'ow-def-cl' => TRUE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
        ),
      ),
    ),
    'field_fpp_useful_links' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'div',
          'ow-cl' => '',
          'ow-def-cl' => TRUE,
          'ow-at' => '',
          'ow-def-at' => TRUE,
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'field-items',
          'fis-at' => '',
          'fis-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'field-item',
          'fi-at' => '',
          'fi-def-at' => TRUE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
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
  $ds_field->field = 'board_link';
  $ds_field->label = 'Board link';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'stakeholder|*';
  $ds_field->properties = array(
    'block' => 'block|1',
    'block_render' => '3',
    'block_visibility' => 0,
  );
  $export['board_link'] = $ds_field;

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
        6 => 'field_stk_membership',
        7 => 'field_stk_quote_title',
        8 => 'group_quote',
        9 => 'body',
        10 => 'group_board',
        11 => 'field_fpp_person_list',
        12 => 'board_link',
        13 => 'field_stk_quote_source',
        14 => 'field_stk_quote_text',
      ),
    ),
    'fields' => array(
      'field_stk_logo' => 'left',
      'field_stk_countries' => 'left',
      'title_field' => 'right',
      'field_stk_website' => 'right',
      'field_short_intro' => 'right',
      'field_supporter_since' => 'right',
      'field_stk_membership' => 'right',
      'field_stk_quote_title' => 'right',
      'group_quote' => 'right',
      'body' => 'right',
      'group_board' => 'right',
      'field_fpp_person_list' => 'right',
      'board_link' => 'right',
      'field_stk_quote_source' => 'right',
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
      'left' => array(
        0 => 'name_field',
        1 => 'description_field',
        2 => 'field_fpp_useful_links',
      ),
      'right' => array(
        3 => 'field_contact_eiti',
      ),
    ),
    'fields' => array(
      'name_field' => 'left',
      'description_field' => 'left',
      'field_fpp_useful_links' => 'left',
      'field_contact_eiti' => 'right',
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
