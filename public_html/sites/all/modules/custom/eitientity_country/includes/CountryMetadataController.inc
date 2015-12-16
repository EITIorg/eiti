<?php

/**
 */
class CountryMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    foreach ($info['country'] as $bundle => &$bundle_info) {
      $bundle_info['name']['label'] = 'Name';

      if (isset($bundle_info['status'])) {
        $bundle_info['status']['type'] = 'boolean';
      }
      if (isset($bundle_info['user_id'])) {
        $bundle_info['user_id']['label'] = 'User ID';
      }
    }

    return $info;
  }
}
