<?php

/**
 * @file
 * Update Scripts helper functions for the core Taxonomy module.
 */

/**
 * Create a new vocabulary.
 */
function _us_taxonomy__vocabulary_save($vocabulary) {
  $vocabulary = is_object($vocabulary) ? $vocabulary : (object) $vocabulary;
  return taxonomy_vocabulary_save($vocabulary);
}

/**
 * Delete a vocabulary.
 */
function _us_taxonomy__vocabulary_delete($vid) {
  return taxonomy_vocabulary_delete($vid);
}

/**
 * Create a new taxonomy term.
 */
function _us_taxonomy__term_save($term) {
  /* USAGE:
  // Prepare a list of ordered taxonomy terms.
  $types = array(
    'Civil-Society',
    'Companies',
    'Countries',
    'Partner Organisations',
    'Investors',
  );
  foreach ($types as $weight => $name) {
    $term = new stdClass();
    $term->name = $name;
    $term->weight = $weight;
    $term->language = 'en';
    $term->vocabulary_machine_name = 'stakeholder_types';
    _us_taxonomy__term_save($term);
  }
   */
  if (!is_object($term)) {
    return;
  }
  $entity_type = 'taxonomy_term';

  // Load vocabulary info.
  if (isset($term->vocabulary_machine_name)) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
    $term->vid = $vocabulary->vid;
  }

  // Allow script to run multiple times.
  $conditions = array(
    'name' => $term->name,
    'vid' => $term->vid,
  );
  $existing_term = entity_load('taxonomy_term', FALSE, $conditions);
  if (!empty($existing_term)) {
    return reset($existing_term);
  }

  // Set the language if it was not provided.
  if (isset($term->language)) {
    // Use entity_translation info to get the default language for the term.
    $term->language = _us_taxonomy__term_get_default_language($entity_type, $term->vocabulary_machine_name);
  }

  // If title.module is in use, update the replacement field values.
  if (function_exists('title_field_replacement_info')) {
    $legacy_field = 'name';
    $replacement_info = title_field_replacement_info($entity_type, $legacy_field);
    title_field_sync_set($entity_type, $term, $legacy_field, $replacement_info, $term->language);
  }

  return taxonomy_term_save($term);
}

/**
 * Return the default language for a new taxonomy term.
 *
 * @see: EntityTranslationDefaultHandler::getDefaultLanguage()
 *
 * @param string $entity_type
 * @param string $vocabulary_machine_name
 * @return string
 */
function _us_taxonomy__term_get_default_language($entity_type, $vocabulary_machine_name) {
  if (!function_exists('entity_translation_settings')) {
    return LANGUAGE_NONE;
  }

  $bundle = $vocabulary_machine_name;
  $settings = variable_get('entity_translation_settings_' . $entity_type . '__' . $bundle, array());

  if (!empty($settings['default_language'])) {
    switch ($settings['default_language']) {
      case ENTITY_TRANSLATION_LANGUAGE_DEFAULT:
        $langcode = language_default()->language;
        break;

      case ENTITY_TRANSLATION_LANGUAGE_CURRENT:
        $langcode = $GLOBALS[LANGUAGE_TYPE_CONTENT]->language;
        break;

      case ENTITY_TRANSLATION_LANGUAGE_AUTHOR:
        $langcode = $GLOBALS['user']->language;
        break;

      default:
        // An actual language code has been explicitly configured.
        $langcode = $settings['default_language'];
    }
  }
  else {
    // Fall back to the default language to keep backward compatibility.
    $langcode = language_default()->language;
  }

  return $langcode;
}
