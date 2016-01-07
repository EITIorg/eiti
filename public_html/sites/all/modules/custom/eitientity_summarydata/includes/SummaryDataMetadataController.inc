<?php

/**
 */
class SummaryDataMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['status'])) {
        $bundle_info['status']['type'] = 'boolean';
      }
    }

    return $info;
  }

  /**
   * Return a set of properties for an entity based on the schema definition
   */
  protected function convertSchema() {
    $schema = drupal_get_schema($this->info['base table']);

    $properties = array();
    foreach ($schema['fields'] as $name => $info) {
      if ($type = _entity_metadata_convert_schema_type($info['type'])) {
        $label = ucwords(str_replace('_', ' ', $name));

        $properties[$name] = array(
          'type' => $type,
          'label' => $label,
          'schema field' => $name,
          // As we cannot know about any setter access, leave out the setter
          // callback. For getting usually no further access callback is needed.
        );
        if ($info['type'] == 'serial') {
          $properties[$name]['validation callback'] = 'entity_metadata_validate_integer_positive';
        }
      }
    }
    return $properties;
  }
}
