<?php

/**
 * @file
 * Contains EITIApiScoreData2.
 */

/**
 * Class EITIApiScoreData2
 */
class EITIApiScoreData2 extends EITIApiScoreData {

  /**
   * Overrides EITIApiScoreData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // References.
    $public_fields['country']['resource']['normal']['major_version'] = 2;

    $public_fields['score_req_values']['process_callbacks'] = array(array($this, 'prepareScoreReqValues'));

    return $public_fields;
  }

  /**
   * A standard processing callback for score_req_values.
   */
  function prepareScoreReqValues($score_req_values) {
    foreach ($score_req_values as $key => $sq) {
      if (is_numeric($sq->score_req->created)) {
        $score_req_values[$key]->score_req->created = eiti_api_timestamp_to_iso_8601($sq->score_req->created);
      }
    }
    return $score_req_values;
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
      // Country ISO to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'country') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_implementing_country_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
  }
}
