<?php

/**
 * @file: Create Stakeholder Types.
 * @desc: This script can be used to create the Stakeholder Types vocabulary terms.
 */

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
