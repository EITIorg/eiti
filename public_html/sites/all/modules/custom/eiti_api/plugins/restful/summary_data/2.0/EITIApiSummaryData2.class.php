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

    // References.
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

}
