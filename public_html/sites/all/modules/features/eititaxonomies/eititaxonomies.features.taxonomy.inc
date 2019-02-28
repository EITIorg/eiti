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
    'board_decision_bases' => array(
      'name' => 'Board decision bases',
      'machine_name' => 'board_decision_bases',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 32768,
    ),
    'bookmark_type' => array(
      'name' => 'Bookmark Type',
      'machine_name' => 'bookmark_type',
      'description' => 'Types of the bookmarks.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'company_commodities' => array(
      'name' => 'Company Commodities',
      'machine_name' => 'company_commodities',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'company_sectors' => array(
      'name' => 'Company Sectors',
      'machine_name' => 'company_sectors',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'document_category' => array(
      'name' => 'Document Category',
      'machine_name' => 'document_category',
      'description' => 'Categories used to classify documents.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'person_positions' => array(
      'name' => 'Person Positions',
      'machine_name' => 'person_positions',
      'description' => 'Work-position and titles people can get in the Person content-type.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'publication_types_internal' => array(
      'name' => 'Publication Types Internal',
      'machine_name' => 'publication_types_internal',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
    ),
    'publication_types_public' => array(
      'name' => 'Publication Types Public',
      'machine_name' => 'publication_types_public',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
    ),
    'publishers' => array(
      'name' => 'Publishers',
      'machine_name' => 'publishers',
      'description' => 'Used in the documents.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
    ),
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => 'Tags are used for tagging such content as News, Blog Posts, Events.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
  );
}
