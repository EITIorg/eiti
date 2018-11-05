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
   * Overrides EITIApiImplementingCountry::__construct().
   */
  public function __construct(array $plugin, \RestfulAuthenticationManager $auth_manager = NULL, \DrupalCacheInterface $cache_controller = NULL, $language = NULL) {
    // We don't want to process the direct parent as it is doing quite a bit of unnecessary work.
    RestfulEntityBase::__construct($plugin, $auth_manager, $cache_controller, $language);
  }

  /**
   * Overrides EITIApiImplementingCountry::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'iso',
    );
    $public_fields['status'] = array(
      'property' => 'field_ic_status',
      'callback' => array($this, 'getStatusApiUrl')
    );
    $public_fields['latest_validation_date'] = array(
      'callback' => array($this, 'getLatestScoreDataDate')
    );
    $public_fields['validation_data'] = array(
      'callback' => array($this, 'getScoreData')
    );
    $public_fields['summary_data'] = array(
      'callback' => array($this, 'getSummaryData'),
    );
    // Summary data replaces this one.
    unset($public_fields['metadata']);
    // Summary data already provides links to indicator_values.
    unset($public_fields['reports']);
    // Moved to summary_data indicator_values.
    unset($public_fields['licenses']);
    unset($public_fields['contracts']);
    // Moved to summary_data as revenue_government_sum and revenue_company_sum.
    unset($public_fields['revenues']);

    unset($public_fields['latest_validation_link']);
    unset($public_fields['latest_validation_url']);

    $public_fields['status_date']['process_callbacks'] = array('eiti_api_timestamp_to_iso_8601_partial');

    $reordered_fields = array();
    foreach ($public_fields as $key => $val) {
      if ($key == 'status_date') {
        $reordered_fields['member_since'] = $val;
      }
      else {
        $reordered_fields[$key] = $val;
      }
    }

    return $reordered_fields;
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

  /**
   * Get the status API url.
   */
  function getStatusApiUrl($emw) {
    if (isset($emw->field_ic_status)) {
      $status = $emw->field_ic_status->value();
      if ($status) {
        $status_emw = entity_metadata_wrapper('taxonomy_term', $status);
        $status_id = $status_emw->field_country_status_id->value();
        if (isset($status_id)) {
          return url('api/v2.0/country_status/' . $status_id, array('absolute' => TRUE));
        }
      }
    }
    return NULL;
  }

  /**
   * Get summary data API page url-s.
   */
  function getSummaryData($emw) {
    $query = db_select('eiti_summary_data', 'sd');
    $query->fields('sd', array('year_end', 'id2'));
    $query->condition('sd.status', 1);
    $query->condition('sd.country_id', $emw->id->value());
    $results = $query->execute()->fetchAll();

    $urls = array();
    if (is_array($results)) {
      foreach ($results as $result) {
        $urls[date('Y', $result->year_end)] = url('api/v2.0/summary_data/' . $result->id2, array('absolute' => TRUE));
      }
    }

    return $urls;
  }

  /**
   * Get score data API page url-s.
   */
  function getScoreData($emw) {
    $query = db_select('eiti_score_data', 'sd');
    $query->fields('sd', array('year', 'id'));
    $query->condition('sd.status', 1);
    $query->condition('sd.country_id', $emw->id->value());
    $results = $query->execute()->fetchAll();

    $urls = array();
    if (is_array($results)) {
      foreach ($results as $result) {
        $urls[$result->year] = url('api/v2.0/validation_data/' . $result->id, array('absolute' => TRUE));
      }
    }

    return $urls;
  }

  /**
   * Get the latest score data date.
   */
  function getLatestScoreDataDate($emw) {
    $query = db_select('eiti_score_data', 'sd');
    $query->innerJoin('field_data_field_scd_pdf_date', 'scd', 'sd.id = scd.entity_id');
    $query->fields('scd', array('field_scd_pdf_date_value'));
    $query->condition('sd.status', 1);
    $query->condition('sd.country_id', $emw->id->value());
    $query->orderBy('scd.field_scd_pdf_date_value', 'DESC');
    $query->range(0, 1);
    $result = $query->execute()->fetchField();

    $date = NULL;
    if ($result) {
      $date = eiti_api_date_to_iso_8601_partial($result);
    }

    return $date;
  }
}
