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
  // 'fieldable_panels_pane-key_facts-field_fppq_widget'.
  $field_instances['fieldable_panels_pane-key_facts-field_fppq_widget'] = array(
    'bundle' => 'key_facts',
    'deleted' => 0,
    'description' => '',
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
    'field_name' => 'field_fppq_widget',
    'label' => 'Widget',
    'required' => 0,
    'settings' => array(
      'available_widgets' => array(
        'key_facts' => 'key_facts',
      ),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-key_facts-title_field'.
  $field_instances['fieldable_panels_pane-key_facts-title_field'] = array(
    'bundle' => 'key_facts',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A field replacing fieldable panel pane title.',
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
    'label' => 'Title',
    'required' => FALSE,
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
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-quote-field_fppq_background_image'.
  $field_instances['fieldable_panels_pane-quote-field_fppq_background_image'] = array(
    'bundle' => 'quote',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'large',
        ),
        'type' => 'image',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fppq_background_image',
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
            'pathauto' => 0,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => 0,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => '',
        ),
        'redirect' => 0,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'report' => 0,
          'video' => 0,
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 'media_default--media_browser_1',
          'media_default--media_browser_my_files' => 'media_default--media_browser_my_files',
          'upload' => 'upload',
        ),
      ),
      'type' => 'media_generic',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-quote-field_fppq_quote'.
  $field_instances['fieldable_panels_pane-quote-field_fppq_quote'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fppq_quote',
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
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-quote-field_fppq_source'.
  $field_instances['fieldable_panels_pane-quote-field_fppq_source'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Source of the quote: a person, a website, etc.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fppq_source',
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
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-quote-field_fppq_source_url'.
  $field_instances['fieldable_panels_pane-quote-field_fppq_source_url'] = array(
    'bundle' => 'quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If this quote leads somewhere, please specify the absolute URL (even if it is a local one).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_fppq_source_url',
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
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'fieldable_panels_pane-visualization-field_fppq_widget'.
  $field_instances['fieldable_panels_pane-visualization-field_fppq_widget'] = array(
    'bundle' => 'visualization',
    'deleted' => 0,
    'description' => '',
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
    'field_name' => 'field_fppq_widget',
    'label' => 'Widget',
    'required' => 1,
    'settings' => array(
      'available_widgets' => array(),
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'contentwidget',
      'settings' => array(),
      'type' => 'cwsettings',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-visualization-title_field'.
  $field_instances['fieldable_panels_pane-visualization-title_field'] = array(
    'bundle' => 'visualization',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A field replacing fieldable panel pane title.',
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
    'label' => 'Title',
    'required' => FALSE,
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
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A field replacing fieldable panel pane title.');
  t('Background Image');
  t('If this quote leads somewhere, please specify the absolute URL (even if it is a local one).');
  t('Quote');
  t('Source');
  t('Source URL');
  t('Source of the quote: a person, a website, etc.');
  t('Title');
  t('Widget');

  return $field_instances;
}
