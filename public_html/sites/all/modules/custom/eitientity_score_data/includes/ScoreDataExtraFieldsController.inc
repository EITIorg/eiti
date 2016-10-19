<?php

/**
 * @file
 * Controller class for providing field API extra fields.
 */

/**
 * Controller for generating extra fields based on property metadata.
 */
class ScoreDataExtraFieldsController extends EntityDefaultExtraFieldsController {
  /**
   * @var array
   */
  protected $propertyInfo;

  public function fieldExtraFields() {
    $extra = array();
    foreach ($this->propertyInfo['properties'] as $name => $property_info) {
      // Skip adding the ID or bundle.
      if ($this->entityInfo['entity keys']['id'] == $name || $this->entityInfo['entity keys']['bundle'] == $name) {
        continue;
      }

      if (empty($property_info['computed'])) {
        if (!in_array($name, array('created', 'changed', 'status'))) {
          $extra[$this->entityType][$this->entityType]['form'][$name] = $this->generateExtraFieldInfo($name, $property_info);
        }
      }
      $extra[$this->entityType][$this->entityType]['display'][$name] = $this->generateExtraFieldInfo($name, $property_info);
    }

    // Handle bundle properties.
    $this->propertyInfo += array('bundles' => array());
    foreach ($this->propertyInfo['bundles'] as $bundle_name => $info) {
      foreach ($info['properties'] as $name => $property_info) {
        if (empty($property_info['field'])) {
          $extra[$this->entityType][$bundle_name]['display'][$name] = $this->generateExtraFieldInfo($name, $property_info);
        }
      }
    }
    return $extra;
  }

  /**
   * Generates the display field info for a given property.
   */
  protected function generateExtraFieldInfo($name, $property_info) {
    $label = ucwords(str_replace('_', ' ', $property_info['label']));

    if ($name == 'published') {
      $label = 'Published Date';
    }
    if ($name == 'status') {
      $label = 'Published';
    }

    $info = array(
      'label' => $label,
      'weight' => 0,
    );
    if (!empty($property_info['description'])) {
      $info['description'] = $property_info['description'];
    }
    return $info;
  }
}
