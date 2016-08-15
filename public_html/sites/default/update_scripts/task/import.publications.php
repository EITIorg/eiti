<?php

/**
 * @file: Import Publication Types.
 * @desc: This script can be used to (re)import publication types.
 */

/**
 * Import publication types from a CSV file.
 */
function __us_publication_types_import_csv($file_path) {
  $handle = fopen($file_path, 'r');
  if (!$handle) {
    watchdog('indicators-import', 'Could not open file.');
    return;
  }

  $weight = 0;
  while (($row = fgetcsv($handle, 8192, ',')) !== FALSE) {
    if ($row[0] == 'PUBLIC') {
      $voc_machine_name = 'publication_types_public';
    }
    elseif ($row[0] == 'INTERNAL') {
      $voc_machine_name = 'publication_types_internal';
    }
    if (isset($voc_machine_name)) {
      // Category.
      $term_name = $row[1];

      $term = new stdClass();
      $term->name = $term_name;
      $term->weight = $weight;
      $term->language = 'en';
      $term->vocabulary_machine_name = $voc_machine_name;
      $parent = _us_taxonomy__term_save($term);
      $weight++;

      // Term itself (leaf).
      $parent_tid = !empty($parent->tid) ? $parent->tid : $term->tid;
      if ($parent_tid) {
        $term_name = $row[2];

        $term = new stdClass();
        $term->name = $term_name;
        $term->weight = $weight;
        $term->language = 'en';
        $term->parent = $parent_tid;
        $term->vocabulary_machine_name = $voc_machine_name;
        _us_taxonomy__term_save($term);
      }
    }
  }
  fclose($handle);
}

/** @var string $script_directory */
__us_publication_types_import_csv($script_directory . '/import.publications.csv');
