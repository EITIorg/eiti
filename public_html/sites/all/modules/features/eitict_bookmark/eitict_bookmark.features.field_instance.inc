<?php

/**
 * @file
 * eitict_bookmark.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitict_bookmark_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-bookmark-field_bm_bookmark_type'.
  $field_instances['node-bookmark-field_bm_bookmark_type'] = array(
    'bundle' => 'bookmark',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the bookmark type. Make sure you re-use existing terms (suggestions appear while you\'re typing).',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 1,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 1,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 1,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bm_bookmark_type',
    'label' => 'Bookmark Type',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-bookmark-field_bm_hide_title'.
  $field_instances['node-bookmark-field_bm_hide_title'] = array(
    'bundle' => 'bookmark',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'In certain cases, you might want to hide the title. If you choose to hide the title, the bookmark image SHOULD have an "Alt Text" for screen readers.',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_bm_hide_title',
    'label' => 'Hide Title',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-bookmark-field_bm_image'.
  $field_instances['node-bookmark-field_bm_image'] = array(
    'bundle' => 'bookmark',
    'deleted' => 0,
    'description' => 'Upload a relevant image, it should either be a square image that is 480 pixels wide, or one that is in landscape orientation with the image height half the size of the width.',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'bm-large',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'bm-medium',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'bm-small',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 6,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_bm_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'entity_translation_sync' => FALSE,
      'file_directory' => '',
      'file_extensions' => 'png jpg jpeg',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => 0,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'bookmark_images',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '4 MB',
      'max_resolution' => '2400x2400',
      'min_resolution' => '480x480',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'vimeo' => 0,
          'youtube' => 0,
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'report' => 0,
          'video' => 0,
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 0,
          'media_library--audio_library' => 0,
          'media_library--document_library' => 0,
          'media_library--image_library' => 'media_library--image_library',
          'media_library--video_library' => 0,
          'upload' => 'upload',
        ),
      ),
      'type' => 'media_generic',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-bookmark-field_bm_link'.
  $field_instances['node-bookmark-field_bm_link'] = array(
    'bundle' => 'bookmark',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'For Internal (relative) URLs don\'t include the domain or a preceding slash, e.g.: <b>search</b> and not <b>/search</b>.<br>
For External URLs include the full domain name and protocoal, e.g.: <b>https://www.example.org/page</b> and not <b>www.example.org/page</b>',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 12,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 14,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_bm_link',
    'label' => 'Link',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 0,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-bookmark-field_bm_reference'.
  $field_instances['node-bookmark-field_bm_reference'] = array(
    'bundle' => 'bookmark',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'You can reference any of the following content: Article, Document, Internal Page, Mention, Page, Person, Stakeholder.',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_bm_reference',
    'label' => 'Reference',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-bookmark-field_bm_reference_type'.
  $field_instances['node-bookmark-field_bm_reference_type'] = array(
    'bundle' => 'bookmark',
    'default_value' => array(
      0 => array(
        'value' => 'internal',
      ),
    ),
    'deleted' => 0,
    'description' => 'Please specify whether this bookmark leads to an <strong>internal page</strong> (<em>eiti.org page</em>) or to some <strong>external website\'s page</strong>.',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'bm_medium_tile' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'bm_small_tile' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 6,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_bm_reference_type',
    'label' => 'Reference Type',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-bookmark-title_field'.
  $field_instances['node-bookmark-title_field'] = array(
    'bundle' => 'bookmark',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'bm_large_tile' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h3',
        ),
        'type' => 'title_linked',
        'weight' => 2,
      ),
      'bm_medium_tile' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h3',
        ),
        'type' => 'title_linked',
        'weight' => 2,
      ),
      'bm_small_tile' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h3',
        ),
        'type' => 'title_linked',
        'weight' => 2,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'title',
        'settings' => array(
          'title_class' => '',
          'title_link' => '',
          'title_style' => '',
        ),
        'type' => 'title_linked',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => 'entity',
        'page' => 0,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Bookmark Type');
  t('For Internal (relative) URLs don\'t include the domain or a preceding slash, e.g.: <b>search</b> and not <b>/search</b>.<br>
For External URLs include the full domain name and protocoal, e.g.: <b>https://www.example.org/page</b> and not <b>www.example.org/page</b>');
  t('Hide Title');
  t('Image');
  t('In certain cases, you might want to hide the title. If you choose to hide the title, the bookmark image SHOULD have an "Alt Text" for screen readers.');
  t('Link');
  t('Please specify the bookmark type. Make sure you re-use existing terms (suggestions appear while you\'re typing).');
  t('Please specify whether this bookmark leads to an <strong>internal page</strong> (<em>eiti.org page</em>) or to some <strong>external website\'s page</strong>.');
  t('Reference');
  t('Reference Type');
  t('Title');
  t('Upload a relevant image, it should either be a square image that is 480 pixels wide, or one that is in landscape orientation with the image height half the size of the width.');
  t('You can reference any of the following content: Article, Document, Internal Page, Mention, Page, Person, Stakeholder.');

  return $field_instances;
}
