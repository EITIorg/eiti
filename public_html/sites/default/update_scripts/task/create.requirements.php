<?php

/**
 * @file: Create Score Requirements.
 * @desc: This script can be used to (re)create the default score requirements entities.
 */

/**
 * Import service providers from a CSV file.
 */
function __us_score_requirements_import_csv($file_path) {
  $handle = fopen($file_path, 'r');
  if (!$handle) {
    watchdog('score-requirements-import', 'Could not open file.');
    return;
  }

  $mappings = array(
    'field_score_req_category',
    'name',
    'code',
  );


  while (($row = fgetcsv($handle, 8192, ',')) !== FALSE) {
    $row_values = array();

    foreach ($mappings as $col_delta => $col_key) {
      $field_name = $col_key;

      // Trim whitespace.
      $field_value = trim($row[$col_delta]);

      if (!isset($field_value)) {
        continue;
      }

      if ($field_value == 'null') {
        $field_value = NULL;
      }

      $row_values[$field_name] = $field_value;
    }

    $row_values = array(
        'status' => NODE_PUBLISHED,
        'created' => REQUEST_TIME,
        'type' => 'standard',
      ) + $row_values;

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

    /** @var IndicatorEntity $ew_entity */
    $new_entity = entity_create('score_req', $row_values);
    $new_entity->save();
  }
  fclose($handle);
}

/** @var string $script_directory */
__us_score_requirements_import_csv($script_directory . '/create.requirements.csv');
