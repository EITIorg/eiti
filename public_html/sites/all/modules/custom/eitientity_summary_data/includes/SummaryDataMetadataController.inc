<?php

/**
 */
class SummaryDataMetadataController extends HelperEntityMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    // A bit more adjustments.
    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['country_id'])) {
        $bundle_info['country_id'] = array(
          'label' => t('Implementing Country'),
          'type' => 'implementing_country',
          'description' => t('Implementing Country specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'country_id',
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

        if ($name == 'published') {
          $label = 'Published Date';
        }
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
