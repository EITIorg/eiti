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
    'node_link' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '18',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
          'classes' => 'single-fluid-row-wrapper',
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
    'field_tags' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_event_location' => array(
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
    'author' => array(
      'weight' => '18',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'ds_post_date_shortest',
    ),
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_helpertheme_ds_field_simple',
          'classes' => 'single-fluid-row-wrapper',
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
    'field_related_country' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_image_gallery' => array(
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
    'field_attachments' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_event_location' => array(
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
  $ds_fieldsetting->id = 'node|article|teaser_alternative';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'article';
  $ds_fieldsetting->view_mode = 'teaser_alternative';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '8',
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
    'body' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|article|teaser_alternative'] = $ds_fieldsetting;

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
  $ds_layout->layout = 'widelayout';
  $ds_layout->settings = array(
    'regions' => array(
      'above' => array(
        0 => 'group_featured_image_header',
        1 => 'field_featured_image',
        2 => 'group_article_info_wrapper',
        3 => 'title_field',
        4 => 'group_article_info',
        9 => 'author',
        10 => 'post_date',
        11 => 'field_tags',
      ),
      'main' => array(
        5 => 'field_event_date',
        6 => 'field_event_location',
        7 => 'body',
        8 => 'node_link',
      ),
    ),
    'fields' => array(
      'group_featured_image_header' => 'above',
      'field_featured_image' => 'above',
      'group_article_info_wrapper' => 'above',
      'title_field' => 'above',
      'group_article_info' => 'above',
      'field_event_date' => 'main',
      'field_event_location' => 'main',
      'body' => 'main',
      'node_link' => 'main',
      'author' => 'above',
      'post_date' => 'above',
      'field_tags' => 'above',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'main' => array(
        'clearfix' => 'clearfix',
        'single-fluid-row-wrapper' => 'single-fluid-row-wrapper',
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
        0 => 'group_featured_image_header',
        1 => 'group_article_info_wrapper',
        2 => 'field_featured_image',
        3 => 'group_article_info',
        5 => 'title_field',
        11 => 'author',
        12 => 'post_date',
        13 => 'field_tags',
      ),
      'main' => array(
        4 => 'field_related_country',
        6 => 'field_event_date',
        7 => 'field_event_location',
        8 => 'body',
        9 => 'field_attachments',
        10 => 'field_image_gallery',
      ),
    ),
    'fields' => array(
      'group_featured_image_header' => 'above',
      'group_article_info_wrapper' => 'above',
      'field_featured_image' => 'above',
      'group_article_info' => 'above',
      'field_related_country' => 'main',
      'title_field' => 'above',
      'field_event_date' => 'main',
      'field_event_location' => 'main',
      'body' => 'main',
      'field_attachments' => 'main',
      'field_image_gallery' => 'main',
      'author' => 'above',
      'post_date' => 'above',
      'field_tags' => 'above',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'main' => array(
        'clearfix' => 'clearfix',
        'single-fluid-row-wrapper' => 'single-fluid-row-wrapper',
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
  $ds_layout->id = 'node|article|teaser_alternative';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'article';
  $ds_layout->view_mode = 'teaser_alternative';
  $ds_layout->layout = 'mobject';
  $ds_layout->settings = array(
    'regions' => array(
      'side' => array(
        0 => 'field_featured_image',
      ),
      'main' => array(
        1 => 'title_field',
        2 => 'group_article_info',
        3 => 'field_event_date',
        4 => 'field_event_location',
        5 => 'body',
        6 => 'node_link',
        7 => 'author',
        8 => 'post_date',
        9 => 'field_tags',
      ),
    ),
    'fields' => array(
      'field_featured_image' => 'side',
      'title_field' => 'main',
      'group_article_info' => 'main',
      'field_event_date' => 'main',
      'field_event_location' => 'main',
      'body' => 'main',
      'node_link' => 'main',
      'author' => 'main',
      'post_date' => 'main',
      'field_tags' => 'main',
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
  $export['node|article|teaser_alternative'] = $ds_layout;

  return $export;
}
