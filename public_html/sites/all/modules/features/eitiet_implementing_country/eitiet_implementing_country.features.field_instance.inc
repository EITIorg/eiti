<?php
/**
 * @file
 * eitiet_implementing_country.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitiet_implementing_country_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'implementing_country-normal-field_ic_change_status_date'.
  $field_instances['implementing_country-normal-field_ic_change_status_date'] = array(
    'bundle' => 'normal',
    'deleted' => 0,
    'description' => 'Please specify when did this country change its EITI Status.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'implementing_country',
    'field_name' => 'field_ic_change_status_date',
    'label' => 'EITI Member Since',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '2003:+1',
      ),
      'type' => 'date_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'implementing_country-normal-field_ic_cover'.
  $field_instances['implementing_country-normal-field_ic_cover'] = array(
    'bundle' => 'normal',
    'deleted' => 0,
    'description' => 'Please upload the background image (cover) for this country: usually it\'s an abstract map with a highlighted map, or any image that represents the country. <em>Make sure to upload a high quality image</em>.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'implementing_country',
    'field_name' => 'field_ic_cover',
    'label' => 'Cover',
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
          'media_internet' => 'media_internet',
          'media_library--audio_library' => 0,
          'media_library--document_library' => 0,
          'media_library--image_library' => 'media_library--image_library',
          'media_library--video_library' => 0,
          'upload' => 'upload',
        ),
      ),
      'type' => 'media_generic',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'implementing_country-normal-field_ic_logo'.
  $field_instances['implementing_country-normal-field_ic_logo'] = array(
    'bundle' => 'normal',
    'deleted' => 0,
    'description' => 'Please specify the local country-specific EITI logo.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'implementing_country',
    'field_name' => 'field_ic_logo',
    'label' => 'Logo',
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
          'media_internet' => 'media_internet',
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

  // Exported field_instance: 'implementing_country-normal-field_ic_status'.
  $field_instances['implementing_country-normal-field_ic_status'] = array(
    'bundle' => 'normal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the country\'s EITI membership status.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'implementing_country',
    'field_name' => 'field_ic_status',
    'label' => 'EITI Status',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'implementing_country-normal-field_ic_website'.
  $field_instances['implementing_country-normal-field_ic_website'] = array(
    'bundle' => 'normal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please specify the local EITI country-specific website.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'implementing_country',
    'field_name' => 'field_ic_website',
    'label' => 'Country Website',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => '_blank',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'value',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => 'EITI [implementing_country:name]',
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Country Website');
  t('Cover');
  t('EITI Member Since');
  t('EITI Status');
  t('Logo');
  t('Please specify the country\'s EITI membership status.');
  t('Please specify the local EITI country-specific website.');
  t('Please specify the local country-specific EITI logo.');
  t('Please specify when did this country change its EITI Status.');
  t('Please upload the background image (cover) for this country: usually it\'s an abstract map with a highlighted map, or any image that represents the country. <em>Make sure to upload a high quality image</em>.');

  return $field_instances;
}