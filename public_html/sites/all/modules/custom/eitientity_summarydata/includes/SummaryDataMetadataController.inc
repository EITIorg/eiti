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
}
