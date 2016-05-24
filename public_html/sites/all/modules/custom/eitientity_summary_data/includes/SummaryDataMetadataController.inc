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
          'type' => 'implementing_country',
          'label' => t('Implementing Country'),
          'description' => t('Implementing Country specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'country_id',
        );
      }

      $bundle_info['sectors_covered'] = array(
        'type' => 'text',
        'label' => t('Sectors Covered'),
        'description' => t('The list of sectors covered in this summary data.'),
        'getter callback' => 'eitientity_summary_data_entity_property_get_sectors_covered',
        'computed' => TRUE,
      );

      $bundle_info['gov_revenue_extractive'] = array(
        'type' => 'text',
        'label' => t('Government revenue - extractive industries'),
        'description' => t('Contribution of extractive industries to economy (3.4) > Government revenue - extractive industries'),
        'getter callback' => 'eitientity_summary_data_entity_property_get_indicator_gov_revenue_extractive',
        'computed' => TRUE,
      );
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
