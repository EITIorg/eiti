<?php

// Let's create default taxonomy terms for "Country Status".
$default_terms_en = array(
  'Compliant',
  'Candidate',
  'Suspended',
  'Other',
);

$vocabulary_name = 'country_status';
$vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
$language = 'en';

if (!empty($vocabulary)) {
  foreach ($default_terms_en as $weight => $term_name) {
    $existing = taxonomy_get_term_by_name($term_name, $vocabulary_name);
    if (!empty($existing)) {
      continue;
    }

    $term = new stdClass();
    $term->name = $term_name;
    $term->vid = $vocabulary->vid;
    $term->weight = $weight;
    $term->language = $language;

    taxonomy_term_save($term);
  }
}
