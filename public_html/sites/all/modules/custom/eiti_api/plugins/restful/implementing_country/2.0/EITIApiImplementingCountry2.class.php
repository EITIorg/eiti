<?php

/**
 * @file
 * Contains EITIApiImplementingCountry2.
 */

/**
 * Class EITIApiImplementingCountry2
 */
class EITIApiImplementingCountry2 extends EITIApiImplementingCountry {

  /**
   * Overrides EITIApiImplementingCountry::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    unset($public_fields['iso2']);
    $public_fields['id'] = array(
      'property' => 'iso',
    );

    $public_fields['status_date']['process_callbacks'] = array('eiti_api_timestamp_to_iso_8601_partial');

    return $public_fields;
  }

  /**
   * Overrides \RestfulEntityBase::getList().
   *
   * Entities need to be loaded via their ISO code.
   */
  public function getList() {
    $request = $this->getRequest();
    $autocomplete_options = $this->getPluginKey('autocomplete');
    if (!empty($autocomplete_options['enable']) && isset($request['autocomplete']['string'])) {
      // Return autocomplete list.
      return $this->getListForAutocomplete();
    }

    $entity_type = $this->entityType;
    $result = $this
      ->getQueryForList()
      ->execute();

    if (empty($result[$entity_type])) {
      return array();
    }

    $ids = array_keys($result[$entity_type]);

    // Get the results with their ISO code.
    $iso_query = db_select('eiti_implementing_country', 'c');
    $iso_query->fields('c', array('id', 'iso'));
    $iso_query->condition('id', $ids, 'IN');
    $iso_query_results = $iso_query->execute()->fetchAllKeyed();
    // Get original order with ISO code as the key.
    $iso_results = array();
    foreach ($ids as $id) {
      if (isset($iso_query_results[$id])) {
        $iso_results[$iso_query_results[$id]] = $id;
      }
    }

    // Pre-load all entities if there is no render cache.
    $cache_info = $this->getPluginKey('render_cache');
    if (!$cache_info['render']) {
      entity_load($entity_type, $iso_results);
    }

    $return = array();

    // If no IDs were requested, we should not throw an exception in case an
    // entity is un-accessible by the user.
    foreach ($iso_results as $iso => $id) {
      if ($row = $this->viewEntity($iso)) {
        $return[] = $row;
      }
    }

    return $return;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Wrap viewEntity to load the implementing country via it's ISO code.
   */
  public function viewEntity($iso) {
    $iso = strtoupper($iso);
    $efq = new EntityFieldQuery();
    $efq_results = $efq->entityCondition('entity_type', 'implementing_country')
      ->propertyCondition('type', 'normal')
      ->propertyCondition('status', 1)
      ->propertyCondition('iso', $iso)
      ->range(0, 1)
      ->execute();

    if (empty($efq_results['implementing_country'])) {
      throw new \RestfulBadRequestException(format_string('A country with the given ISO code is not available.'));
    }

    $id = key($efq_results['implementing_country']);
    return parent::viewEntity($id);
  }

  /**
   * Overrides \RestfulEntityBase::getEntitySelf().
   */
  protected function getEntitySelf(\EntityMetadataWrapper $wrapper) {
    return $this->versionedUrl($wrapper->iso->value());
  }

}
