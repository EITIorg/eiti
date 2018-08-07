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

    $public_fields['country'] = array(
      'callback' => array($this, 'getCountryApiUrl')
    );
    $public_fields['indicator_values'] = array(
      'callback' => array($this, 'getIndicatorValueApiUrls')
    );
    $public_fields['revenue_government'] = array(
      'callback' => array($this, 'getGovernmentRevenueApiUrls'),
    );
    $public_fields['revenue_company'] = array(
      'callback' => array($this, 'getCompanyRevenueApiUrls'),
    );

    return $public_fields;
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

  /**
   * Gets the implementing country API url.
   */
  function getCountryApiUrl($emw) {
    if (isset($emw->country_id)) {
      $country = $emw->country_id->value();
      if (isset($country->iso)) {
        return url('api/v2.0/implementing_country/' . $country->iso, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the indicator value API urls.
   */
  function getIndicatorValueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_indicator_values)) {
      $ids = $emw->field_sd_indicator_values->raw();
      if (is_array($ids)) {
        foreach ($ids as $id) {
          $urls[] = url('api/v2.0/indicator_value/' . $id, array('absolute' => TRUE));
        }
      }
    }
    return $urls;
  }

  /**
   * Gets the government revenue API urls.
   */
  function getGovernmentRevenueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_revenue_government)) {
      $ids = $emw->field_sd_revenue_government->raw();
      if (is_array($ids)) {
        foreach ($ids as $id) {
          $urls[] = url('api/v2.0/revenue/' . $id, array('absolute' => TRUE));
        }
      }
    }
    return $urls;
  }

  /**
   * Gets the company revenue API urls.
   */
  function getCompanyRevenueApiUrls($emw) {
    $urls = array();
    if (isset($emw->field_sd_revenue_company)) {
      $ids = $emw->field_sd_revenue_company->raw();
      if (is_array($ids)) {
        foreach ($ids as $id) {
          $urls[] = url('api/v2.0/revenue/' . $id, array('absolute' => TRUE));
        }
      }
    }
    return $urls;
  }
}
