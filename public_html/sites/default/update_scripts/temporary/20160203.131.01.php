<?php


// Prepare a list of field instances to be deleted.
$field_instances = array(
  'node-page-body',
);
foreach ($field_instances as $field_instance) {
  list($entity_type, $bundle, $field_name) = explode('-', $field_instance);
  // Delete the field instance.
  _us_fields__delete_instances($field_name, $entity_type, $bundle);
}
