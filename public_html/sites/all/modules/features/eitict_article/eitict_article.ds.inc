<?php

/**
 * @file
 * eitict_article.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function eitict_article_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|article|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'article';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'article_info' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_reset',
        ),
      ),
    ),
    'field_event_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
  );
  $export['node|article|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|article|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'article';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'article_header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'article_info' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'article_summary' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
    ),
    'addtoany' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_image_gallery' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
          'classes' => 'field-highlighted',
        ),
      ),
    ),
    'field_featured_image' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
    'field_authors' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
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
    'field_tags' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
    'field_event_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
  );
  $export['node|article|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|article|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'article';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'field_featured_image' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
  );
  $export['node|article|teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|article|teaser_alternative';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'article';
  $ds_fieldsetting->view_mode = 'teaser_alternative';
  $ds_fieldsetting->settings = array(
    'article_header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'article_info' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'node_link' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
    'field_tags' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_featured_image' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
        ),
      ),
    ),
    'field_event_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
  );
  $export['node|article|teaser_alternative'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function eitict_article_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'article_header';
  $ds_field->label = 'Article Header';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'article|*';
  $ds_field->properties = array();
  $export['article_header'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'article_info';
  $ds_field->label = 'Article Info';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'article|*';
  $ds_field->properties = array();
  $export['article_info'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'article_summary';
  $ds_field->label = 'Article Summary';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'article|full';
  $ds_field->properties = array();
  $export['article_summary'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function eitict_article_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|article|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'article';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_featured_image',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'article_info',
        3 => 'body',
        4 => 'node_link',
      ),
      'ds_hidden' => array(
        5 => 'post_date',
        6 => 'author',
        7 => 'field_event_date',
        8 => 'field_event_location',
        9 => 'field_tags',
      ),
    ),
    'fields' => array(
      'field_featured_image' => 'side',
      'title_field' => 'main',
      'article_info' => 'main',
      'body' => 'main',
      'node_link' => 'main',
      'post_date' => 'ds_hidden',
      'author' => 'ds_hidden',
      'field_event_date' => 'ds_hidden',
      'field_event_location' => 'ds_hidden',
      'field_tags' => 'ds_hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
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
  $export['node|article|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|article|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'article';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'widelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'above' => array(
        0 => 'article_header',
        1 => 'article_info',
      ),
      'main' => array(
        2 => 'article_summary',
        3 => 'body',
        4 => 'field_attachments',
        5 => 'field_image_gallery',
        6 => 'field_mailchimp_signup_form',
        7 => 'field_authors',
      ),
      'ds_hidden' => array(
        8 => 'field_featured_image',
        9 => 'field_article_type',
        10 => 'title_field',
        11 => 'post_date',
        12 => 'field_event_date',
        13 => 'field_event_location',
        14 => 'field_tags',
        15 => 'addtoany',
      ),
    ),
    'fields' => array(
      'article_header' => 'above',
      'article_info' => 'above',
      'article_summary' => 'main',
      'body' => 'main',
      'field_attachments' => 'main',
      'field_image_gallery' => 'main',
      'field_mailchimp_signup_form' => 'main',
      'field_authors' => 'main',
      'field_featured_image' => 'ds_hidden',
      'field_article_type' => 'ds_hidden',
      'title_field' => 'ds_hidden',
      'post_date' => 'ds_hidden',
      'field_event_date' => 'ds_hidden',
      'field_event_location' => 'ds_hidden',
      'field_tags' => 'ds_hidden',
      'addtoany' => 'ds_hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'main' => array(
        'clearfix' => 'clearfix',
        'single-narrow-row-wrapper' => 'single-narrow-row-wrapper',
      ),
    ),
    'wrappers' => array(
      'above' => 'header',
      'main' => 'div',
      'below' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '1',
    'page_option_title' => '',
  );
  $export['node|article|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|article|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'article';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'widelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'above' => array(
        0 => 'field_featured_image',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'post_date',
        3 => 'field_article_type',
        4 => 'body',
      ),
    ),
    'fields' => array(
      'field_featured_image' => 'above',
      'title_field' => 'main',
      'post_date' => 'main',
      'field_article_type' => 'main',
      'body' => 'main',
    ),
    'classes' => array(
      'layout_class' => array(
        'single-fluid-row-wrapper' => 'single-fluid-row-wrapper',
      ),
    ),
    'wrappers' => array(
      'above' => 'div',
      'main' => 'div',
      'below' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|article|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|article|teaser_alternative';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'article';
  $ds_layout->view_mode = 'teaser_alternative';
  $ds_layout->layout = 'widelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'above' => array(
        0 => 'article_header',
        1 => 'article_info',
      ),
      'main' => array(
        2 => 'body',
        3 => 'node_link',
      ),
      'ds_hidden' => array(
        4 => 'field_featured_image',
        5 => 'title_field',
        6 => 'post_date',
        7 => 'author',
        8 => 'field_event_date',
        9 => 'field_event_location',
        10 => 'field_tags',
      ),
    ),
    'fields' => array(
      'article_header' => 'above',
      'article_info' => 'above',
      'body' => 'main',
      'node_link' => 'main',
      'field_featured_image' => 'ds_hidden',
      'title_field' => 'ds_hidden',
      'post_date' => 'ds_hidden',
      'author' => 'ds_hidden',
      'field_event_date' => 'ds_hidden',
      'field_event_location' => 'ds_hidden',
      'field_tags' => 'ds_hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'main' => array(
        'clearfix' => 'clearfix',
        'single-narrow-row-wrapper' => 'single-narrow-row-wrapper',
      ),
    ),
    'wrappers' => array(
      'above' => 'header',
      'main' => 'div',
      'below' => 'div',
      'ds_hidden' => 'div',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|article|teaser_alternative'] = $ds_layout;

  return $export;
}
