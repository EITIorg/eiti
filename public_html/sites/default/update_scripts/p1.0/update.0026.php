<?php

/**
 * @file: Update Country Status.
 * @desc: Update country statuses to new ones.
 */
// Updated from 20161014.67.01 to update.0026.
// Replacement terms.
$terms_to_rename = array(
  'Compliant' => array(
    'name' => 'Meaningful progress',
    'color' => '2D8B2A',
    'weight' => 0
  ),
  'Candidate' => array(
    'name' => 'Satisfactory progress',
    'color' => '84AD42',
    'weight' => 1
  ),
  'Suspended' => array(
    'name' => 'Suspended',
    'color' => 'FF6600',
    'weight' => 9
  ),
  'Other' => array(
    'name' => 'Other',
    'color' => '808080',
    'weight' => 10
  ),
);
// New terms.
$terms_to_create = array();
$terms_to_create[] = array(
  'name' => 'Inadequate progress',
  'color' => 'FAC433',
  'weight' => 3
);
$terms_to_create[] = array(
  'name' => 'No progress',
  'color' => '000000',
  'weight' => 4
);
$terms_to_create[] = array(
  'name' => 'Yet to be assessed to the 2016 Standard',
  'color' => '00919B',
  'weight' => 5
);

// Change.
foreach ($terms_to_rename as $old_term_name => $new_term) {
  $terms = taxonomy_get_term_by_name($old_term_name, 'country_status');
  $term = reset($terms);
  if (!empty($term)) {
    $term_emw = entity_metadata_wrapper('taxonomy_term', $term);
    $term_emw->name->set($new_term['name']);
    $term_emw->weight->set($new_term['weight']);
    $term_emw->name_field->set($new_term['name']);
    $term_emw->field_tx_country_color->set($new_term['color']);
    $term_emw->save();
  }
}

// Create.
$voc = taxonomy_vocabulary_machine_name_load('country_status');
foreach ($terms_to_create as $term_details) {
  $term = new stdClass();
  $term->name = $term_details['name'];
  $term->name_field[LANGUAGE_NONE][0]['value'] = $term_details['name'];
  $term->weight = $term_details['weight'];
  $term->field_tx_country_color[LANGUAGE_NONE][0]['value'] = $term_details['color'];
  $term->vid = $voc->vid;
  taxonomy_term_save($term);
}
