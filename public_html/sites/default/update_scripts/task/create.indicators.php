<?php

/**
 * @file: Create Indicators.
 * @desc: This script can be used to (re)create the indicator entities.
 */

/**
 * Import service providers from a CSV file.
 */
function __us_indicators_import_csv($file_path) {
  $handle = fopen($file_path, 'r');
  if (!$handle) {
    watchdog('indicators-import', 'Could not open file.');
    return;
  }

  $headers = fgetcsv($handle, 8192, ',');
  if (reset($headers) != 'id') {
    watchdog('indicators-import', 'Wrong headers?');
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
      ) + $row_values;

    /** @var IndicatorEntity $new_entity */
    $new_entity = entity_create('indicator', $row_values);
    $new_entity->save();
  }
  fclose($handle);
}

/** @var string $script_directory */
__us_indicators_import_csv($script_directory . '/create.indicators.csv');
