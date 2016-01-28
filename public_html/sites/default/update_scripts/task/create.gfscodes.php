<?php

/**
 * @file: Create GFS Codes.
 * @desc: This script can be used to (re)create the GFS Code entities.
 */

/**
 * Import GFS Codes from a CSV file.
 */
function __us_gfs_codes_import_csv($file_path) {
  $handle = fopen($file_path, 'r');
  if (!$handle) {
    watchdog('gfs-codes-import', 'Could not open file.');
    return;
  }

  $headers = fgetcsv($handle, 8192, ',');
  if (reset($headers) != 'code') {
    watchdog('gfs-codes-import', 'Wrong headers?');
    return;
  }

  while (($row = fgetcsv($handle, 8192, ',')) !== FALSE) {
    $row_values = array();

    foreach ($headers as $col_delta => $col_key) {
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
        'type' => 'gfs_code',
      ) + $row_values;

    /** @var GFSCodeEntity $new_entity */
    $new_entity = entity_create('gfs_code', $row_values);
    $new_entity->save();
  }
  fclose($handle);
}

/** @var string $script_directory */
__us_gfs_codes_import_csv($script_directory . '/create.gfscodes.csv');
