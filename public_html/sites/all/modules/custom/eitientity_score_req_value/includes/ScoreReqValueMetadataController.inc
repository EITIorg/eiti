<?php

/**
 */
class ScoreReqValueMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    // A bit more adjustments.
    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['score_req_id'])) {
        $bundle_info['score_req_id'] = array(
          'label' => t('Score Requirement'),
          'type' => 'score_req',
          'description' => t('Score Requirement specified.'),
          'getter callback' => 'entity_property_getter_method',
          'setter callback' => 'entity_property_setter_method',
          'required' => TRUE,
          'schema field' => 'score_req_id',
        );
      }
    }

    return $info;
  }
}
