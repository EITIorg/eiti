<?php
/**
 * @file
 * eitiet_implementing_country.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function eitiet_implementing_country_taxonomy_default_vocabularies() {
  return array(
    'country_status' => array(
      'name' => 'Country Status',
      'machine_name' => 'country_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
    ),
  );
}
