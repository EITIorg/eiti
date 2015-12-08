<?php

/**
 * @file
 * Update Scripts helper functions for the core Menu module.
 */

/**
 * Delete field instances.
 */
function _us_fields__delete_instances($field_names, $entity_type, $bundle) {
  /* USAGE:
  // Prepare a list of field instances to be deleted.
  $field_instances = array(
    'provider-simple-field_prv_involved_with',
    'provider-simple-field_prv_services_for',
  );
  foreach ($field_instances as $field_instance) {
    list($entity_type, $bundle, $field_name) = explode('-', $field_instance);
    // Delete the field instance.
    _us_fields__delete_instances($field_name, $entity_type, $bundle);
  }
  */

  if (is_string($field_names)) {
    $field_names = array($field_names);
  }

  foreach ($field_names as $field_name) {
    $field = field_info_field($field_name);
    $instance = field_info_instance($entity_type, $field_name, $bundle);

    if (!empty($bundle) && $field && !$field['locked']) {
      field_delete_instance($instance);
    }

    // Call field_purge_batch() to remove the field and field data from the
    // system. If there are more than 1000 entries, the field will be removed at
    // cron.
    field_purge_batch(1000);
  }
}
