<?php

/**
 */
class HelperEntityMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    // A bit more adjustments.
    foreach ($info[$this->type] as $bundle => &$bundle_info) {
      if (isset($bundle_info['status'])) {
        $bundle_info['status']['type'] = 'boolean';
      }

      // @TODO: Cleanup!
      if (isset($bundle_info['changed'])) {
        $bundle_info['changed']['getter callback'] = 'helperentity_property_getter_method';
      }
      if (isset($bundle_info['created'])) {
        $bundle_info['created']['getter callback'] = 'helperentity_property_getter_method';
      }
      if (isset($bundle_info['year_start'])) {
        $bundle_info['year_start']['getter callback'] = 'helperentity_property_getter_method';
      }
      if (isset($bundle_info['year_end'])) {
        $bundle_info['year_end']['getter callback'] = 'helperentity_property_getter_method';
      }
    }

    return $info;
  }
}
