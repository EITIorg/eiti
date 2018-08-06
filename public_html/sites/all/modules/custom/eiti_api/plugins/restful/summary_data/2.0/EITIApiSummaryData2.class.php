<?php

/**
 * @file
 * Contains EITIApiSummaryData2.
 */

/**
 * Class EITIApiSummaryData2
 */
class EITIApiSummaryData2 extends EITIApiSummaryData {

  /**
   * Overrides EITIApiSummaryData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'id2',
    );
    $public_fields['label']['process_callbacks'][] = array($this, 'processLabel');
    $public_fields['government_entities_nr']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['company_entities_nr']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['year_start']['process_callbacks'][] = 'eiti_api_date_to_iso_8601_partial';
    $public_fields['year_end']['process_callbacks'][] = 'eiti_api_date_to_iso_8601_partial';
    $public_fields['sector_oil']['process_callbacks'][] = 'eiti_api_value_to_boolean';
    $public_fields['sector_mining']['process_callbacks'][] = 'eiti_api_value_to_boolean';
    $public_fields['sector_gas']['process_callbacks'][] = 'eiti_api_value_to_boolean';

    $public_fields['country']['resource']['normal']['major_version'] = 2;
    $public_fields['indicator_values']['resource']['indicator_value']['major_version'] = 2;

    return $public_fields;
  }

  /**
   * Overrides RestfulEntityBase::getValueFromResource().
   */
  protected function getValueFromResource(EntityMetadataWrapper $wrapper, $property, $resource, $public_field_name = NULL, $host_id = NULL) {
    $handlers = $this->staticCache->get(__CLASS__ . '::' . __FUNCTION__, array());

    if (!$entity = $wrapper->value()) {
      return;
    }

    $target_type = $this->getTargetTypeFromEntityReference($wrapper, $property);
    list($id,, $bundle) = entity_extract_ids($target_type, $entity);

    if (empty($resource[$bundle])) {
      // Bundle not mapped to a resource.
      return;
    }

    if (!$resource[$bundle]['full_view']) {
      // Show only the ID(s) of the referenced resource.
      return $wrapper->value(array('identifier' => TRUE));
    }

    if ($public_field_name) {
      $this->valueMetadata[$host_id][$public_field_name][] = array(
        'id' => $id,
        'entity_type' => $target_type,
        'bundle' => $bundle,
        'resource_name' => $resource[$bundle]['name'],
      );
    }

    if (empty($handlers[$bundle])) {
      $handlers[$bundle] = restful_get_restful_handler($resource[$bundle]['name'], $resource[$bundle]['major_version'], $resource[$bundle]['minor_version']);
    }
    $bundle_handler = $handlers[$bundle];

    // Pipe the parent request and account to the sub-request.
    $piped_request = $this->getRequestForSubRequest();
    $bundle_handler->setAccount($this->getAccount());
    $bundle_handler->setRequest($piped_request);

    // Countries require the ISO code rather than ID.
    if ($target_type == 'implementing_country') {
      return $bundle_handler->viewEntity(eitientity_implementing_country_get_iso2($id));
    }
    return $bundle_handler->viewEntity($id);
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      if (isset($filter['public_field'], $filter['value'][0])) {
        // Date to timestamp.
        if ($filter['public_field'] == 'year_start') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        elseif ($filter['public_field'] == 'year_end') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        // Note that with ISO 8601 (YYYY-MM-DDThh:mm:ss+hh:mm) format the + symbol has to be encoded in the url (%2B).
        // "2016-06-06T11:04:36%2B00:00" and "2016-06-06T11:04:36" give the same result.
        elseif ($filter['public_field'] == 'created') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        elseif ($filter['public_field'] == 'changed') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = strtotime($v);
          }
        }
        // Country ISO to ID.
        elseif ($filter['public_field'] == 'country') {
          foreach ($filter['value'] as $k => $v) {
            $filters[$key]['value'][$k] = eitientity_implementing_country_get_id(strtoupper($v));
          }
        }
      }
    }
    return $filters;
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

    // Get the results with their ID2 code.
    $id2_query = db_select('eiti_summary_data', 'sd');
    $id2_query->fields('sd', array('id', 'id2'));
    $id2_query->condition('id', $ids, 'IN');
    $id2_query_results = $id2_query->execute()->fetchAllKeyed();
    // Get original order with ID2 code as the key.
    $id2_results = array();
    foreach ($ids as $id) {
      if (isset($id2_query_results[$id])) {
        $id2_results[$id2_query_results[$id]] = $id;
      }
    }

    // Pre-load all entities if there is no render cache.
    $cache_info = $this->getPluginKey('render_cache');
    if (!$cache_info['render']) {
      entity_load($entity_type, $id2_results);
    }

    $return = array();

    // If no IDs were requested, we should not throw an exception in case an
    // entity is un-accessible by the user.
    foreach ($id2_results as $id2 => $id) {
      if ($row = $this->viewEntity($id2)) {
        $return[] = $row;
      }
    }

    return $return;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Wrap viewEntity to load the summary data via it's id2 code.
   */
  public function viewEntity($id2) {
    $id2 = strtoupper($id2);
    $efq = new EntityFieldQuery();
    $efq_results = $efq->entityCondition('entity_type', 'summary_data')
      ->propertyCondition('type', 'summary_data')
      ->propertyCondition('status', 1)
      ->propertyCondition('id2', $id2)
      ->range(0, 1)
      ->execute();

    if (empty($efq_results['summary_data'])) {
      throw new \RestfulBadRequestException(format_string('Summary data with the given ID is not available.'));
    }

    $id = key($efq_results['summary_data']);
    return parent::viewEntity($id);
  }

  /**
   * Overrides \RestfulEntityBase::getEntitySelf().
   */
  protected function getEntitySelf(\EntityMetadataWrapper $wrapper) {
    return $this->versionedUrl($wrapper->id2->value());
  }

  /**
   * A standard processing callback for the label.
   */
  function processLabel($label) {
    $label = str_replace(':', '', $label);
    return $label;
  }
}
