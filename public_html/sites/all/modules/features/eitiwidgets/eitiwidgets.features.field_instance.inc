<?php
/**
 * @file
 * eitiwidgets.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitiwidgets_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'fieldable_panels_pane-fact_blocks-field_fpp_background_image'.
  $field_instances['fieldable_panels_pane-fact_blocks-field_fpp_background_image'] = array(
    'bundle' => 'fact_blocks',
    'deleted' => 0,
    'description' => 'Upload a relevant image, it should have a landscape orientation and it should be at least 960 pixels wide and 300 pixels tall.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_background_image',
    'label' => 'Background Image',
    'required' => 1,
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
          'value' => 'background_image',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '8 MB',
      'max_resolution' => '4800x1500',
      'min_resolution' => '960x300',
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
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-fact_blocks-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-fact_blocks-field_fpp_widget'] = array(
    'bundle' => 'fact_blocks',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'fact_blocks' => 'fact_blocks',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-fact_blocks-title_field'.
  $field_instances['fieldable_panels_pane-fact_blocks-title_field'] = array(
    'bundle' => 'fact_blocks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_articles-field_fpp_article_list'.
  $field_instances['fieldable_panels_pane-featured_articles-field_fpp_article_list'] = array(
    'bundle' => 'featured_articles',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'links' => 0,
          'use_content_language' => 1,
          'view_mode' => 'teaser_alternative',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_article_list',
    'label' => 'Article List',
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
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_articles-field_fpp_body'.
  $field_instances['fieldable_panels_pane-featured_articles-field_fpp_body'] = array(
    'bundle' => 'featured_articles',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_articles-title_field'.
  $field_instances['fieldable_panels_pane-featured_articles-title_field'] = array(
    'bundle' => 'featured_articles',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A field replacing fieldable panel pane title.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => 1,
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
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_bookmarks-field_fpp_bookmark_list'.
  $field_instances['fieldable_panels_pane-featured_bookmarks-field_fpp_bookmark_list'] = array(
    'bundle' => 'featured_bookmarks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the list of bookmarks you want to use. Each position corresponds to the positions specified in the preview.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_bookmark_list',
    'label' => 'Bookmark List',
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
      'weight' => 5,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_bookmarks-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-featured_bookmarks-field_fpp_icon'] = array(
    'bundle' => 'featured_bookmarks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_bookmarks-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-featured_bookmarks-field_fpp_widget'] = array(
    'bundle' => 'featured_bookmarks',
    'deleted' => 0,
    'description' => 'Bookmark widget configuration.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'bookmarks' => 'bookmarks',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_bookmarks-title_field'.
  $field_instances['fieldable_panels_pane-featured_bookmarks-title_field'] = array(
    'bundle' => 'featured_bookmarks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_persons-field_fpp_body'.
  $field_instances['fieldable_panels_pane-featured_persons-field_fpp_body'] = array(
    'bundle' => 'featured_persons',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_persons-field_fpp_person_list'.
  $field_instances['fieldable_panels_pane-featured_persons-field_fpp_person_list'] = array(
    'bundle' => 'featured_persons',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'links' => 0,
          'use_content_language' => TRUE,
          'view_mode' => 'teaser',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_person_list',
    'label' => 'Person List',
    'required' => 1,
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
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_persons-title_field'.
  $field_instances['fieldable_panels_pane-featured_persons-title_field'] = array(
    'bundle' => 'featured_persons',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => 0,
        'page' => 0,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_publications-field_fpp_body'.
  $field_instances['fieldable_panels_pane-featured_publications-field_fpp_body'] = array(
    'bundle' => 'featured_publications',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_publications-field_fpp_publication_list'.
  $field_instances['fieldable_panels_pane-featured_publications-field_fpp_publication_list'] = array(
    'bundle' => 'featured_publications',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'links' => 0,
          'use_content_language' => 1,
          'view_mode' => 'teaser',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_publication_list',
    'label' => 'Publication List',
    'required' => 1,
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
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-featured_publications-title_field'.
  $field_instances['fieldable_panels_pane-featured_publications-title_field'] = array(
    'bundle' => 'featured_publications',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A field replacing fieldable panel pane title.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => 1,
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
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-header-field_fpp_background_image'.
  $field_instances['fieldable_panels_pane-header-field_fpp_background_image'] = array(
    'bundle' => 'header',
    'deleted' => 0,
    'description' => 'Upload a relevant image, it should have a landscape orientation and it should be at least 960 pixels wide and 300 pixels tall.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_background_image',
    'label' => 'Background Image',
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
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => 'background_image',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '8 MB',
      'max_resolution' => '4800x1500',
      'min_resolution' => '960x300',
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
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-header-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-header-field_fpp_widget'] = array(
    'bundle' => 'header',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 1,
    'settings' => array(
      'available_widgets' => array(
        'header' => 'header',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-header-title_field'.
  $field_instances['fieldable_panels_pane-header-title_field'] = array(
    'bundle' => 'header',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-icon_blocks-field_fpp_body'.
  $field_instances['fieldable_panels_pane-icon_blocks-field_fpp_body'] = array(
    'bundle' => 'icon_blocks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-icon_blocks-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-icon_blocks-field_fpp_icon'] = array(
    'bundle' => 'icon_blocks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-icon_blocks-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-icon_blocks-field_fpp_widget'] = array(
    'bundle' => 'icon_blocks',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'icon_blocks' => 'icon_blocks',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-icon_blocks-title_field'.
  $field_instances['fieldable_panels_pane-icon_blocks-title_field'] = array(
    'bundle' => 'icon_blocks',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-quote-field_fpp_background_image'.
  $field_instances['fieldable_panels_pane-quote-field_fpp_background_image'] = array(
    'bundle' => 'quote',
    'deleted' => 0,
    'description' => 'Upload a relevant image, it should have a landscape orientation and it should be at least 960 pixels wide and 300 pixels tall.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_background_image',
    'label' => 'Background Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'entity_translation_sync' => FALSE,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
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
          'value' => 'background_image',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '8 MB',
      'max_resolution' => '4800x1500',
      'min_resolution' => '960x300',
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
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-quote-field_fpp_quote'.
  $field_instances['fieldable_panels_pane-quote-field_fpp_quote'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the quote (<em>don\'t use the quotation marks, we\'ll do that for you.</em>).',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_quote',
    'label' => 'Quote',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-quote-field_fpp_source'.
  $field_instances['fieldable_panels_pane-quote-field_fpp_source'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Source of the quote: a person, a website, etc.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_source',
    'label' => 'Source',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-quote-field_fpp_source_url'.
  $field_instances['fieldable_panels_pane-quote-field_fpp_source_url'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If this quote leads somewhere, please specify the absolute URL (even if it is a local one).',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_source_url',
    'label' => 'Source URL',
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
      'enable_tokens' => 1,
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
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-quote-title_field'.
  $field_instances['fieldable_panels_pane-quote-title_field'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance: 'fieldable_panels_pane-table-field_fpp_body'.
  $field_instances['fieldable_panels_pane-table-field_fpp_body'] = array(
    'bundle' => 'table',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-table-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-table-field_fpp_icon'] = array(
    'bundle' => 'table',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-table-field_fpp_source_url'.
  $field_instances['fieldable_panels_pane-table-field_fpp_source_url'] = array(
    'bundle' => 'table',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the source of this data (a link to a page or a file).',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helpergeneric',
        'settings' => array(
          'icon' => 'arrow',
          'size' => '1em',
        ),
        'type' => 'link_icon',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_source_url',
    'label' => 'Source URL',
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
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'optional',
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-table-field_fpp_table'.
  $field_instances['fieldable_panels_pane-table-field_fpp_table'] = array(
    'bundle' => 'table',
    'default_value' => array(
      0 => array(
        'tablefield' => array(
          'cell_0_0' => 'Commodity',
          'cell_0_1' => 'Reserves',
          'cell_0_2' => 'Unit',
          'cell_0_3' => 'Significance',
          'cell_1_0' => '',
          'cell_1_1' => '',
          'cell_1_2' => '',
          'cell_1_3' => '',
          'cell_2_0' => '',
          'cell_2_1' => '',
          'cell_2_2' => '',
          'cell_2_3' => '',
          'cell_3_0' => '',
          'cell_3_1' => '',
          'cell_3_2' => '',
          'cell_3_3' => '',
          'cell_4_0' => '',
          'cell_4_1' => '',
          'cell_4_2' => '',
          'cell_4_3' => '',
          'import' => array(
            'file' => '',
            'import' => 'Upload CSV',
          ),
          'rebuild' => array(
            'count_cols' => 4,
            'count_rows' => 5,
            'rebuild' => 'Rebuild Table',
          ),
        ),
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'tablefield',
        'settings' => array(),
        'type' => 'tablefield_default',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_table',
    'label' => 'Table',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'tablefield',
      'settings' => array(),
      'type' => 'tablefield',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-table-title_field'.
  $field_instances['fieldable_panels_pane-table-title_field'] = array(
    'bundle' => 'table',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-tabs_with_widgets-field_fpp_content_widgets'.
  $field_instances['fieldable_panels_pane-tabs_with_widgets-field_fpp_content_widgets'] = array(
    'bundle' => 'tabs_with_widgets',
    'deleted' => 0,
    'description' => 'Please specify a list of widgets that will be used as the content of the tabs.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_content_widgets',
    'label' => 'Content Widgets',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_existing' => 1,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'Widgets',
          'label_singular' => 'Widget',
          'match_operator' => 'CONTAINS',
          'override_labels' => 1,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-tabs_with_widgets-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-tabs_with_widgets-field_fpp_widget'] = array(
    'bundle' => 'tabs_with_widgets',
    'deleted' => 0,
    'description' => 'Tab widget settings.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'tabs' => 'tabs',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-tabs_with_widgets-title_field'.
  $field_instances['fieldable_panels_pane-tabs_with_widgets-title_field'] = array(
    'bundle' => 'tabs_with_widgets',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Tab Collection Title',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => 0,
        'page' => 0,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-text-field_fpp_body'.
  $field_instances['fieldable_panels_pane-text-field_fpp_body'] = array(
    'bundle' => 'text',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
      ),
      'type' => 'text_textarea',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-text-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-text-field_fpp_icon'] = array(
    'bundle' => 'text',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-text-field_fpp_useful_links'.
  $field_instances['fieldable_panels_pane-text-field_fpp_useful_links'] = array(
    'bundle' => 'text',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify any useful links (internal or external).',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helpergeneric',
        'settings' => array(
          'icon' => 'arrow',
          'size' => '1em',
        ),
        'type' => 'link_icon',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_useful_links',
    'label' => 'Useful Links',
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
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'optional',
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
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-text-title_field'.
  $field_instances['fieldable_panels_pane-text-title_field'] = array(
    'bundle' => 'text',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-value_chain-field_fpp_body'.
  $field_instances['fieldable_panels_pane-value_chain-field_fpp_body'] = array(
    'bundle' => 'value_chain',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-value_chain-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-value_chain-field_fpp_icon'] = array(
    'bundle' => 'value_chain',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-value_chain-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-value_chain-field_fpp_widget'] = array(
    'bundle' => 'value_chain',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'value_chain' => 'value_chain',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-value_chain-title_field'.
  $field_instances['fieldable_panels_pane-value_chain-title_field'] = array(
    'bundle' => 'value_chain',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A field replacing fieldable panel pane title.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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

  // Exported field_instance:
  // 'fieldable_panels_pane-visualization-field_fpp_icon'.
  $field_instances['fieldable_panels_pane-visualization-field_fpp_icon'] = array(
    'bundle' => 'visualization',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'helperfield',
        'settings' => array(),
        'type' => 'helperfield_icon_default',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'available_icons' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'helperfield',
      'settings' => array(),
      'type' => 'helperfield_radio_selector',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-visualization-field_fpp_widget'.
  $field_instances['fieldable_panels_pane-visualization-field_fpp_widget'] = array(
    'bundle' => 'visualization',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'contentwidget',
        'settings' => array(),
        'type' => 'cwrendered',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fpp_widget',
    'label' => 'Widget',
    'required' => 1,
    'settings' => array(
      'available_widgets' => array(
        'plotly_bar_chart' => 'plotly_bar_chart',
        'viz_bubble_dynamic' => 'viz_bubble_dynamic',
        'viz_groupedbar_dynamic' => 'viz_groupedbar_dynamic',
        'viz_groupedbar_static' => 'viz_groupedbar_static',
        'viz_sankey_dynamic' => 'viz_sankey_dynamic',
        'viz_stackedbar_dynamic' => 'viz_stackedbar_dynamic',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-visualization-title_field'.
  $field_instances['fieldable_panels_pane-visualization-title_field'] = array(
    'bundle' => 'visualization',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'title',
        'settings' => array(
          'title_class' => 'title',
          'title_link' => '',
          'title_style' => 'h2',
        ),
        'type' => 'title_linked',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
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
  t('A field replacing fieldable panel pane title.');
  t('Article List');
  t('Background Image');
  t('Body');
  t('Bookmark List');
  t('Bookmark widget configuration.');
  t('Content Widgets');
  t('Icon');
  t('If this quote leads somewhere, please specify the absolute URL (even if it is a local one).');
  t('Person List');
  t('Please specify a list of widgets that will be used as the content of the tabs.');
  t('Please specify any useful links (internal or external).');
  t('Please specify the list of bookmarks you want to use. Each position corresponds to the positions specified in the preview.');
  t('Please specify the quote (<em>don\'t use the quotation marks, we\'ll do that for you.</em>).');
  t('Please specify the source of this data (a link to a page or a file).');
  t('Publication List');
  t('Quote');
  t('Source');
  t('Source URL');
  t('Source of the quote: a person, a website, etc.');
  t('Tab Collection Title');
  t('Tab widget settings.');
  t('Table');
  t('Title');
  t('Upload a relevant image, it should have a landscape orientation and it should be at least 960 pixels wide and 300 pixels tall.');
  t('Useful Links');
  t('Widget');

  return $field_instances;
}
