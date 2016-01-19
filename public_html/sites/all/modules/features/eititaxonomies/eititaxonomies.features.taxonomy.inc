<?php
/**
 * @file
 * eititaxonomies.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function eititaxonomies_taxonomy_default_vocabularies() {
  return array(
    'company_commodities' => array(
      'name' => 'Company Commodities',
      'machine_name' => 'company_commodities',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'document_category' => array(
      'name' => 'Document Category',
      'machine_name' => 'document_category',
      'description' => 'Categories used to classify documents.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'person_positions' => array(
      'name' => 'Person Positions',
      'machine_name' => 'person_positions',
      'description' => 'Work-position and titles people can get in the Person content-type.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => 'Tags are used for tagging such content as News, Blog Posts, Events.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
