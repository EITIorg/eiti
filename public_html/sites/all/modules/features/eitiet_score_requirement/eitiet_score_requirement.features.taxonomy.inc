<?php

/**
 * @file
 * eitiet_score_requirement.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function eitiet_score_requirement_taxonomy_default_vocabularies() {
  return array(
    'score_requirement_category' => array(
      'name' => 'Score Requirement Category',
      'machine_name' => 'score_requirement_category',
      'description' => '',
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
