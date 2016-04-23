<?php
/**
 * @file
 * eitict_stakeholder.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function eitict_stakeholder_taxonomy_default_vocabularies() {
  return array(
    'stakeholder_types' => array(
      'name' => 'Stakeholder Types',
      'machine_name' => 'stakeholder_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
  );
}
