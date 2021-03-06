<?php

/**
 */
class RevenueStreamMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['status'])) {
        $bundle_info['status']['type'] = 'boolean';
      }
      if (isset($bundle_info['gfs_code_id'])) {
        $bundle_info['gfs_code_id'] = array(
          'label' => t('GFS Code'),
          'type' => 'gfs_code',
          'description' => t('GFS Code specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'gfs_code_id',
        );
      }
      if (isset($bundle_info['organisation_id'])) {
        $bundle_info['organisation_id'] = array(
          'label' => t('Organisation'),
          'type' => 'organisation',
          'description' => t('Organisation specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'organisation_id',
        );
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

        if ($name == 'status') {
          $label = 'Published';
        }

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
