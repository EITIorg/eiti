<?php

/**
 * @file
 * eitiet_score_data.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function eitiet_score_data_taxonomy_default_vocabularies() {
  return array(
    'standards' => array(
      'name' => 'Standards',
      'machine_name' => 'standards',
      'description' => 'Standards for validation',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
      'base_i18n_mode' => 1,
      'base_language' => 'und',
    ),
  );
}
