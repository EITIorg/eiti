<?php
/**
 * @file
 * eitict_document.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_document_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|document|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'document';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_doc_image_preview' => array(
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
  $export['node|document|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|document|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'document';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'field_document_category' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
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
    'field_attachments' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
          'classes' => 'field-highlighted',
        ),
      ),
    ),
    'field_doc_published_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
  );
  $export['node|document|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_document_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|document|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'document';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_doc_image_preview',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'field_doc_published_date',
        3 => 'body',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_doc_image_preview' => 'side',
      'title_field' => 'main',
      'field_doc_published_date' => 'main',
      'body' => 'main',
      'node_link' => 'main',
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
  $export['node|document|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|document|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'document';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'doublelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_doc_image_preview',
        1 => 'field_doc_published_date',
        2 => 'field_document_category',
      ),
      'right' => array(
        3 => 'title_field',
        4 => 'body',
        5 => 'field_attachments',
      ),
    ),
    'fields' => array(
      'field_doc_image_preview' => 'left',
      'field_doc_published_date' => 'left',
      'field_document_category' => 'left',
      'title_field' => 'right',
      'body' => 'right',
      'field_attachments' => 'right',
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
  $export['node|document|full'] = $ds_layout;

  return $export;
}
