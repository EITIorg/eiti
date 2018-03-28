<?php
/**
 * @file
 * eitisettings.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function eitisettings_filter_default_formats() {
  $formats = array();

  // Exported format: Clean Summary.
  $formats['clean_summary'] = array(
    'format' => 'clean_summary',
    'name' => 'Clean Summary',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<p> <a>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 0,
        ),
      ),
      'htmlpurifier' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'htmlpurifier_config_name' => 'htmlpurifier_basic',
          'htmlpurifier_help' => 1,
          'htmlpurifier_filter_tips' => 'HTML tags will be transformed to conform to HTML standards.',
          'htmlpurifier_config' => array(
            'Attr.EnableID' => 0,
            'AutoFormat.AutoParagraph' => 1,
            'AutoFormat.Linkify' => 1,
            'AutoFormat.RemoveEmpty' => 0,
            'Null_HTML.Allowed' => 1,
            'HTML.ForbiddenAttributes' => '',
            'HTML.ForbiddenElements' => '',
            'HTML.SafeObject' => 0,
            'Output.FlashCompat' => 0,
            'URI.DisableExternalResources' => 0,
            'URI.DisableResources' => 0,
            'Null_URI.Munge' => 1,
          ),
        ),
      ),
    ),
  );

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'htmlpurifier' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'htmlpurifier_config_name' => 'htmlpurifier_custom',
          'htmlpurifier_help' => 1,
          'htmlpurifier_filter_tips' => 'HTML tags will be transformed to conform to HTML standards.',
          'htmlpurifier_config' => array(
            'Attr.EnableID' => 1,
            'AutoFormat.AutoParagraph' => 1,
            'AutoFormat.Linkify' => 1,
            'Cache.DefinitionImpl' => 'Drupal',
            'Null_Cache.SerializerPath' => 1,
            'Core.AggressivelyFixLt' => 1,
            'HTML.FlashAllowFullScreen' => 1,
            'HTML.SafeEmbed' => 1,
            'HTML.SafeIframe' => 0,
            'HTML.SafeObject' => 1,
            'URI.DisableExternalResources' => 1,
            'Null_URI.SafeIframeRegexp' => 1,
          ),
        ),
      ),
      'media_filter' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Min HTML.
  $formats['min_html'] = array(
    'format' => 'min_html',
    'name' => 'Min HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'htmlpurifier' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'htmlpurifier_config_name' => 'htmlpurifier_custom',
          'htmlpurifier_help' => 1,
          'htmlpurifier_filter_tips' => 'HTML tags will be transformed to conform to HTML standards.',
          'htmlpurifier_config' => array(
            'Attr.EnableID' => 1,
            'AutoFormat.AutoParagraph' => 1,
            'AutoFormat.Linkify' => 1,
            'Cache.DefinitionImpl' => 'Drupal',
            'Null_Cache.SerializerPath' => 1,
            'Core.AggressivelyFixLt' => 1,
            'HTML.FlashAllowFullScreen' => 1,
            'HTML.SafeEmbed' => 1,
            'HTML.SafeIframe' => 0,
            'HTML.SafeObject' => 1,
            'URI.DisableExternalResources' => 1,
            'Null_URI.SafeIframeRegexp' => 1,
          ),
        ),
      ),
    ),
  );

  // Exported format: Plain text.
  $formats['plain_text'] = array(
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => -9,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
