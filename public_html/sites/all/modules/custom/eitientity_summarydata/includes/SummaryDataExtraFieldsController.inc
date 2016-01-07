<?php

/**
 * @file
 * Controller class for providing field API extra fields.
 */

/**
 * Controller for generating extra fields based on property metadata.
 */
class SummaryDataExtraFieldsController extends EntityDefaultExtraFieldsController {

  public function fieldExtraFields() {
    $extra = parent::fieldExtraFields();

    return $extra;
  }

  /**
   * Generates the display field info for a given property.
   */
  protected function generateExtraFieldInfo($name, $property_info) {
    $label = ucwords(str_replace('_', ' ', $property_info['label']));

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
