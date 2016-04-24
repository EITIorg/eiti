<?php

// Let's create default taxonomy terms for "Country Status".

// Prepare a list of ordered taxonomy terms.
$types = array(
  'Compliant',
  'Candidate',
  'Suspended',
  'Other',
);
foreach ($types as $weight => $name) {
  $term = new stdClass();
  $term->name = $name;
  $term->weight = $weight;
  $term->language = 'en';
  $term->vocabulary_machine_name = 'country_status';
  _us_taxonomy__term_save($term);
}
