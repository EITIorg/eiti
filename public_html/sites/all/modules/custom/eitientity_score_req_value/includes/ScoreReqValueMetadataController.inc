<?php

/**
 */
class ScoreReqValueMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    // A bit more adjustments.
    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['indicator_id'])) {
        $bundle_info['indicator_id'] = array(
          'label' => t('Indicator'),
          'type' => 'indicator',
          'description' => t('Indicator specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'indicator_id',
        );
      }
    }

    return $info;
  }
}
