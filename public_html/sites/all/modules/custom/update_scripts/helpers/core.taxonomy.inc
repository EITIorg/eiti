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
  if (!is_object($term)) {
    return;
  }

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

  return taxonomy_term_save($term);
}
