<?php

/**
 * @file: Scoredata and scorecard update.
 * @desc: Update the score data categories and requirements.
 */
// New terms.
$terms_to_create = array();
$terms_to_create[] = array(
  'name' => 'Overall Progress',
  'weight' => 10,
);

// Create the term.
$voc = taxonomy_vocabulary_machine_name_load('score_requirement_category');
foreach ($terms_to_create as $term_details) {
  $terms = taxonomy_get_term_by_name($term_details['name'], 'score_requirement_category');
  // Only if those don't exist any.
  if (empty($terms)) {
    $term = new stdClass();
    $term->name = $term_details['name'];
    $term->name_field[LANGUAGE_NONE][0]['value'] = $term_details['name'];
    $term->weight = $term_details['weight'];
    $term->vid = $voc->vid;
    taxonomy_term_save($term);
  }
}

// Create the new requirement.
$row_values = array(
  'status' => NODE_PUBLISHED,
  'created' => REQUEST_TIME,
  'type' => 'standard',
  'field_score_req_category' => 'Overall Progress',
  'name' => 'Overall Progress',
  'code' => '0.0',
);

// Check the taxonomy term.
$terms = taxonomy_get_term_by_name($row_values['field_score_req_category'], 'score_requirement_category');
if (!empty($terms)) {
  $term = reset($terms);
}
else {
  $term = new stdClass();
  $term->name = $row_values['field_score_req_category'];
  $voc = taxonomy_vocabulary_machine_name_load('score_requirement_category');
  $term->vid = $voc->vid;
  taxonomy_term_save($term);
}
unset($row_values['field_score_req_category']);
$row_values['field_score_req_category']['und'][0]['tid'] = $term->tid;
$new_entity = entity_create('score_req', $row_values);
$new_entity->save();
