<?php
/**
 * @file
 * Forms and helper functions for administrative pages.
 */

module_load_include('inc', 'contentblock', 'contentblock.admin');

/**
 * Implements hook_form_FORM_ID_alter() for contentblock_form().
 */
function _contentblock_form_contentblock_form_alter(&$form, &$form_state, $form_id) {
  // Get the type info.
  $cbreference_info = contentblock_get_fixed_types($form['#entity']->machine_name);

  // Only show available fields for predefined entities.
  foreach (element_children($form) as $element_child) {
    if (substr($element_child, 0, 6) !== 'field_') {
      continue;
    }

    if (!in_array($element_child, $cbreference_info['available_fields'])) {
      $form[$element_child]['#access'] = FALSE;
    }
  }

  // Add a description on add form.
  if ($form_state['op'] == 'add' || !in_array('field_title', $cbreference_info['available_fields'])) {
    $title_suffix = '';
    if (!empty($form['#entity']->language) && $form['#entity']->language != LANGUAGE_NONE) {
      $languages = language_list();
      $title_suffix = ' [' . t($languages[$form['#entity']->language]->name) . ']';
    }
    drupal_set_title($cbreference_info['title'] . $title_suffix);
  }

  // Add a default title value for sections.
  if (!empty($cbreference_info['is section']) && FALSE) {
    $langcode = isset($form['title_field']['#language']) ? $form['title_field']['#language'] : LANGUAGE_NONE;
    $title_element = &$form['title_field'][$langcode][0];
    if (empty($title_element['value']['#value'])) {
      $title_element['value']['#value'] = $cbreference_info['title'];
    }
  }

  // Hide the default title element.
  if (!in_array('title_field', $cbreference_info['available_fields'])) {
    // $form['title_field']['#attributes']['class'][] = 'element-hidden';
  }

  if ($form_state['op'] == 'add' && !empty($_GET['destination'])) {
    drupal_set_message(t('If you only want to remove the instructions for this block/section you can just click "Save" without adding/configuring any content.'));
    drupal_set_message(t('You can later configure this block/section from the "Settings > Content Sections" page.'));
  }

  // Attach validate callbacks.
  switch ($form['#entity']->machine_name) {
    case 'footer':
      $form['#validate'][] = '_contentblock_cbreference_entity_form_footer_validate';
      break;
  }
}

/**
 * Count the number of text character in a string of HTML markup.
 */
function _contentblock_cbreference_count_markup($markup) {
  // Strip HTML markup.
  $markup = strip_tags($markup);

  // Strip media.module tokens and whitespace around.
  $markup = preg_replace('/\s*\[\[.*?\]\]\s*/', '', $markup);

  return drupal_strlen(trim($markup));
}
