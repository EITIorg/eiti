<?php

/**
 * @file
 * Contains EITIApiTermCountryStatus2.
 */

class EITIApiTermCountryStatus2 extends EITIApiTermCountryStatus {

  /**
   * Overrides the default public fields, adds others.
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'field_country_status_id',
    );

    return $public_fields;
  }

  /**
   * Overrides \RestfulEntityBase::getList().
   *
   * Entities need to be loaded via their ID field.
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

    // Get the results with their ID field.
    $id_query = db_select('field_data_field_country_status_id', 'csid');
    $id_query->fields('csid', array('entity_id', 'field_country_status_id_value'));
    $id_query->condition('entity_id', $ids, 'IN');
    $id_query_results = $id_query->execute()->fetchAllKeyed();
    // Get original order with ID field as the key.
    $id_results = array();
    foreach ($ids as $id) {
      if (isset($id_query_results[$id])) {
        $id_results[$id_query_results[$id]] = $id;
      }
    }

    // Pre-load all entities if there is no render cache.
    $cache_info = $this->getPluginKey('render_cache');
    if (!$cache_info['render']) {
      entity_load($entity_type, $id_results);
    }

    $return = array();

    // If no IDs were requested, we should not throw an exception in case an
    // entity is un-accessible by the user.
    foreach ($id_results as $cs_id => $id) {
      if ($row = $this->viewEntity($cs_id)) {
        $return[] = $row;
      }
    }

    return $return;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Wrap viewEntity to load the country status via it's ID field.
   */
  public function viewEntity($cs_id) {
    $efq = new EntityFieldQuery();
    $efq_results = $efq->entityCondition('entity_type', 'taxonomy_term')
      ->entityCondition('bundle', 'country_status')
      ->fieldCondition('field_country_status_id', 'value', $cs_id)
      ->range(0, 1)
      ->execute();

    if (empty($efq_results['taxonomy_term'])) {
      throw new \RestfulBadRequestException(format_string('A country status with the given ID is not available.'));
    }

    $id = key($efq_results['taxonomy_term']);
    return parent::viewEntity($id);
  }

  /**
   * Overrides \RestfulEntityBase::getEntitySelf().
   */
  protected function getEntitySelf(\EntityMetadataWrapper $wrapper) {
    return $this->versionedUrl($wrapper->field_country_status_id->value());
  }
}
