<?php

/**
 * @file: Update old URLs.
 * @desc: This script can be used to update all instances of *beta.eiti.org/* to relative ones.
 */

/**
 * Helper updating functions that removes all Pattern-matching absolute URLs to relative ones.
 *
 * @param $old_pattern
 *  Example: "beta.eiti.org"
 *
 * @param $table
 *  Table to lookup, i.e. "field_data_body"
 *
 * @param $update_field
 *  The string of the field that should undergo the updating process.
 *
 * @param $matching_fields
 *  An array of matching fields, just to make sure we don't screw up something.
 */
function __us_update_urls_to_relative($old_pattern, $table, $update_field, $matching_fields) {
  $select = db_select($table, 't');

  $select_fields = $matching_fields;
  $select_fields[] = $update_field;
  $old_url = '%' . $old_pattern . '/%';
  $select->condition($update_field, $old_url, 'LIKE');
  $select->fields('t', $select_fields);
  $result = $select->execute();

  $updated_count = 0;
  while ($row = $result->fetchAssoc()) {
    $old_updating_field_value = $row[$update_field];

    $new_updating_field_value = str_replace($old_pattern . '/', '/', $old_updating_field_value);
    $update = db_update($table);
    $update->fields(array(
      $update_field => $new_updating_field_value
    ));

    foreach ($matching_fields as $matching_field) {
      $update->condition($matching_field, $row[$matching_field]);
    }

    $affected_rows = $update->execute();
    $updated_count += $affected_rows;
  }

  // Notify the user.
  drupal_set_message(t('Successfully updated %count items.', array('%count' => $updated_count)));
}

// ############### INIT ###########.
// Update all of the instances of "*beta.eiti.org/*" to relative ones "/*".
$table_options = array(
  'field_data_body' => array(
    'update' => 'body_value',
    'match' => array('entity_type', 'entity_id', 'revision_id', 'delta', 'language')
  ),
  'field_data_description_field' => array(
    'update' => 'description_field_value',
    'match' => array('entity_type', 'entity_id', 'revision_id', 'delta', 'language')
  ),
  'field_data_field_fpp_body' => array(
    'update' => 'field_fpp_body_value',
    'match' => array('entity_type', 'entity_id', 'revision_id', 'delta', 'language')
  ),
);

// Loop through all the options and call our function on all the fields.
foreach ($table_options as $table => $fields) {
  __us_update_urls_to_relative('beta.eiti.org', $table, $fields['update'], $fields['match']);
}
