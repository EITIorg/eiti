<?php
/**
 * @file
 * Defines custom field formatters.
 */

/**
 * Implements hook_field_formatter_info().
 */
function helpergeneric_field_formatter_info() {
  $formatters = array();
  $formatters['helpergeneric_clean_summary'] = array(
    'label' => t('HelperGeneric: Clean summary or trimmed'),
    'field types' => array('text_with_summary'),
    'settings' => array(
      'trim_length' => variable_get('teaser_length', 600),
    ),
  );

  $formatters['helpergeneric_list'] = array(
    'label' => t('HelperGeneric: List'),
    'field types' => array(
      'text',
      'list_text',
    ),
    'settings' => array(
      'list_type' => 'ul',
      'separator' => '',
    ),
  );

  if (function_exists('helpertheme_get_svg_icons')) {
    $formatters['link_icon'] = array(
      'label' => t('Title, with icon'),
      'field types' => array('link_field'),
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
      'settings' => array(
        'icon' => '',
        'size' => '',
      ),
    );
  }

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 *
 * @param $field
 * @param $instance
 * @param $view_mode
 * @param $form
 * @param $form_state
 * @return array
 */
function helpergeneric_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'helpergeneric_clean_summary') {
    $element['trim_length'] = array(
      '#title' => t('Trim length'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $settings['trim_length'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#required' => TRUE,
    );
  }

  if ($display['type'] == 'helpergeneric_list') {
    if ($field['cardinality'] != '1') {
      $element['list_type'] = array(
        '#type' => 'radios',
        '#title' => t('list type'),
        '#options' => array(
          'ul' => t('Unordered list'),
          'ol' => t('Ordered list'),
          'separator' => t('Simple separator'),
        ),
        '#default_value' => $settings['list_type'],
      );

      $element['separator'] = array(
        '#type' => 'textfield',
        '#title' => t('Separator'),
        '#default_value' => $settings['separator'],
        '#states' => array(
          'visible' => array(
            ':input[name$="[list_type]"]' => array('value' => 'separator'),
          ),
        ),
      );
    }
  }

  if ($display['type'] == 'link_icon') {
    // @TODO: Get full list of available icons.
    $icons = helpertheme_get_svg_icons(NULL, array('sprite_name' => 'icons'));
    $options = array('' => t('No Icon'));
    $options += drupal_map_assoc(array_keys($icons));
    $element['icon'] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $options,
      '#icons' => $icons,
      '#default_value' => $settings['icon'],
    );

    $element['size'] = array(
      '#type' => 'textfield',
      '#title' => t('Size'),
      '#description' => t('Provide the size of the icon in EMs. Eg: 2em'),
      '#default_value' => $settings['size'],
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 *
 * @param $field
 * @param $instance
 * @param $view_mode
 * @return string
 */
function helpergeneric_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  if ($display['type'] == 'helpergeneric_clean_summary') {
    $summary[] = t('Trim length') . ': ' . check_plain($settings['trim_length']);
  }

  if ($display['type'] == 'helpergeneric_list') {
    if ($settings['list_type'] == 'separator') {
      $summary[] = t('List Separator') . ': "' . check_plain($settings['separator']) . '"';
    }
    else {
      $summary[] = t('List Type') . ': "' . check_plain($settings['list_type']) . '"';
    }
  }

  if ($display['type'] == 'link_icon') {
    $summary[] = t('Icon') . ': ' . check_plain($settings['icon']);
    $summary[] = t('Size') . ': ' . check_plain($settings['size']);
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 *
 * @param $entity_type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 * @return array
 */
function helpergeneric_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $result = array();

  $function = '__' . __FUNCTION__ . '__' . $display['type'];

  switch ($display['type']) {
    default:
      if (function_exists($function)) {
        $result = $function($entity_type, $entity, $field, $instance, $langcode, $items, $display);
      }
      break;
  }

  return $result;
}

/**
 * Implements hook_field_formatter_view() for 'helpergeneric_clean_summary'.
 *
 * @param $entity_type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 * @return array
 */
function __helpergeneric_field_formatter_view__helpergeneric_clean_summary($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $result = array();

  foreach ($items as $delta => $item) {
    if (!empty($item['summary'])) {
      $output = _text_sanitize($instance, $langcode, $item, 'summary');
    }
    else {
      $output = _text_sanitize($instance, $langcode, $item, 'value');
      $output = _helpergeneric_clean_text_summary($output, $instance['settings']['text_processing'] ? $item['format'] : NULL, $display['settings']['trim_length']);
    }

    $result[$delta] = array('#markup' => $output);
  }

  return $result;
}

/**
 * Implements hook_field_formatter_view() for 'helpergeneric_list'.
 *
 * @param $entity_type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 * @return array
 */
function __helpergeneric_field_formatter_view__helpergeneric_list($entity_type, $entity, $field, $instance, $langcode, $items, $display) {

  if (empty($items)) {
    return array();
  }

  $settings = $display['settings'];

  $values = array();
  foreach ($items as $delta => $item) {
    if (!empty($item['safe_value'])) {
      $values[] = $item['safe_value'];
    }
    else if (!empty($item['value']) && !empty($field['settings']['allowed_values'])) {
      if (isset($field['settings']['allowed_values'][$item['value']])) {
        $values[] = $field['settings']['allowed_values'][$item['value']];
      }
    }
  }

  if ($settings['list_type'] == 'separator') {
    $result[] = array(
      '#markup' => implode($settings['separator'], $values),
    );
  }
  else {
    $result[] = array(
      '#theme' => 'item_list',
      '#items' => $values,
      '#title' => NULL,
      '#type' => $settings['list_type'],
    );
  }

  return $result;
}

/**
 * Generate a trimmed, formatted version of a text field value.
 *
 * @see: text_summary().
 *
 * @param $text
 * @param string $format
 * @param int $size
 * @return string
 */
function _helpergeneric_clean_text_summary($text, $format = NULL, $size = NULL) {
  // We don't really care about the input format filter so we change it here!
  $format = 'clean_summary';

  // Check for a cached version of the cleaned version of this piece of text.
  $cache_id = $format . ':cts:' . hash('sha256', $text);
  if ($cached = cache_get($cache_id, 'cache_filter')) {
    return $cached->data;
  }

  // Make sure only some HTML tags are allowed.
  $text = check_markup($text, $format, '', TRUE);
  if (!isset($size)) {
    // What used to be called 'teaser' is now called 'summary', but
    // the variable 'teaser_length' is preserved for backwards compatibility.
    $size = variable_get('teaser_length', 600);
  }

  // Remove all empty anchor tags.
  $text = preg_replace('@\s*<a[^>]*>\W*</a>\s*@', ' ', $text);

  // Remove any paragraph tags that do not contain at least 5 words and all the space around them.
  $text = preg_replace('@\s*<p>(?:\W*\w*\W*){0,4}</p>\s*@', '', $text);

  // Remove extra whitespace between tags.
  $text = preg_replace('@>[\s\W]+<@', '> <', $text);

  // Remove extra whitespace
  // $text = preg_replace('@\s*@', ' ', $text);

  // Get a trimmed summary and count the characters not displayed to the user: tag attributes.
  $trimmed_text = truncate_utf8($text, $size);

  // Count the number of 'irrelevant' characters.
  $extra = 0;
  if (preg_match_all('/<[a-z]+(\ ?[^>]+)>/', $trimmed_text, $matches)) {
    if (!empty($matches[1])) {
      foreach ($matches[1] as $value) {
        $extra += drupal_strlen($value);
      }
    }
  }

  // The summary may not be longer than maximum length specified. Initial slice.
  $size += $extra;
  $summary = truncate_utf8($text, $size);

  // Remove opening anchor tags that are not closed.
  if (preg_match('/<a[^>]+$/', $summary, $matches)) {
    $summary = preg_replace('/\s+<a[^>]+$/', '', $summary);
  }

  // Store the actual length of the UTF8 string -- which might not be the same
  // as $size.
  $max_rpos = strlen($summary);

  // How much to cut off the end of the summary so that it doesn't end in the
  // middle of a paragraph, sentence, or word.
  // Initialize it to maximum in order to find the minimum.
  $min_rpos = $max_rpos;

  // Store the reverse of the summary. We use strpos on the reversed needle and
  // haystack for speed and convenience.
  $reversed = strrev($summary);

  // Build an array of arrays of break points grouped by preference.
  $break_points = array();

  // A paragraph near the end of sliced summary is most preferable.
  $break_points[] = array('</p>' => 0);

  // If no complete paragraph then treat line breaks as paragraphs.
  $line_breaks = array('<br />' => 6, '<br>' => 4);

  // If the first paragraph is too long, split at the end of a sentence.
  $break_points[] = array('. ' => 1, '! ' => 1, '? ' => 1, ', ' => 1, ': ' => 1, '; ' => 1);

  // Iterate over the groups of break points until a break point is found.
  foreach ($break_points as $points) {
    // Look for each break point, starting at the end of the summary.
    foreach ($points as $point => $offset) {
      // The summary is already reversed, but the break point isn't.
      $rpos = strpos($reversed, strrev($point));
      if ($rpos !== FALSE && $rpos < $size / 3) {
        // Only trim if the break point is located in the last third of the string.
        $min_rpos = min($rpos + $offset, $min_rpos);
      }
    }

    // If a break point was found in this group, slice and stop searching.
    if ($min_rpos !== $max_rpos) {
      // Don't slice with length 0. Length must be <0 to slice from RHS.
      $summary = ($min_rpos === 0) ? $summary : substr($summary, 0, 0 - $min_rpos);
      break;
    }
  }

  // Apply the HTML corrector filter to the generated summary.
  $summary = _filter_htmlcorrector(trim($summary));

  // Cache the clean summary.
  cache_set($cache_id, $summary, 'cache_filter');

  return $summary;
}

/**
 * Implements hook_field_formatter_view() for 'helpergeneric_clean_summary'.
 *
 * @param $entity_type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 * @return array
 */
function __helpergeneric_field_formatter_view__link_icon($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = array();

  foreach ($items as $delta => $item) {
    $elements[$delta] = array(
      '#theme' => 'helpergeneric_formatter_' . $display['type'],
      '#element' => $item,
      '#field' => $instance,
      '#display' => $display,
    );
  }

  return $elements;
}

/**
 * Implements hook_theme().
 */
function helpergeneric_theme() {
  return array(
    'helpergeneric_formatter_link_icon' => array(
      'variables' => array('element' => NULL, 'field' => NULL, 'display' => NULL),
    ),
  );
}

/**
 * Formats a link.
 *
 * @param $variables
 * @return string
 */
function theme_helpergeneric_formatter_link_icon($variables) {
  $link_options = $variables['element'];
  $display_settings = $variables['display'];
  unset($link_options['title']);
  unset($link_options['url']);

  if (isset($link_options['attributes']['class']) && is_string($link_options['attributes']['class'])) {
    $link_options['attributes']['class'] = array($link_options['attributes']['class']);
  }

  // Add an SVG icon.
  $svgicon = '';
  if (!empty($display_settings['settings']['icon'])) {
    $icon = $display_settings['settings']['icon'];
    $size = $display_settings['settings']['size'];
    $options = array(
      'width' => $size,
      'height' => $size,
      'sprite_name' => 'icons',  // @TODO: FIX!
    );
    $svgicon = helpertheme_get_svg_icon($icon, $options);
    $link_options['attributes']['class'][] = 'link-title-with-icon';
  }

  // Display a normal link if both title and URL are available.
  if (!empty($variables['element']['title']) && !empty($variables['element']['url'])) {
    return l($svgicon . $variables['element']['title'], $variables['element']['url'], $link_options);
  }
  // If only a title, display the title.
  elseif (!empty($variables['element']['title'])) {
    return $link_options['html'] ? $svgicon . $variables['element']['title'] : $svgicon . check_plain($variables['element']['title']);
  }
  elseif (!empty($variables['element']['url'])) {
    return l($svgicon . $variables['element']['title'], $variables['element']['url'], $link_options);
  }
}
