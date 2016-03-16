<?php

// Let's create default taxonomy terms for "Country Status".
$default_terms_en = array(
  'Compliant',
  'Candidate',
  'Suspended',
  'Other',
);

$voc = taxonomy_vocabulary_machine_name_load('country_status');
$language = 'en';

if (!empty($voc)) {
  foreach ($default_terms_en as $weight => $term_name) {
    $term = new stdClass();

    $term->name = $term_name;
    $term->vid = $voc->vid;
    $term->weight = $weight;
    $term->language = $language;

    taxonomy_term_save($term);
  }
}



