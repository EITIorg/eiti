<?php

/**
 * @file
 * Contains EITIApiGFSCode2.
 */

/**
 * Class EITIApiGFSCode2
 */
class EITIApiGFSCode2 extends EITIApiGFSCode {

  /**
   * Overrides EITIApiGFSCode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'code',
    );
    $public_fields['parent']['process_callbacks'][] = 'eitientity_gfs_code_get_code';

    return $public_fields;
  }

  /**
   * Overrides \RestfulEntityBase::getList().
   *
   * Entities need to be loaded via their code.
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

    // Get the results with their code.
    $code_query = db_select('eiti_gfs_code', 'g');
    $code_query->fields('g', array('id', 'code'));
    $code_query->condition('id', $ids, 'IN');
    $code_query_results = $code_query->execute()->fetchAllKeyed();
    // Get original order with code as the key.
    $code_results = array();
    foreach ($ids as $id) {
      if (isset($code_query_results[$id])) {
        $code_results[$code_query_results[$id]] = $id;
      }
    }

    // Pre-load all entities if there is no render cache.
    $cache_info = $this->getPluginKey('render_cache');
    if (!$cache_info['render']) {
      entity_load($entity_type, $code_results);
    }

    $return = array();

    // If no IDs were requested, we should not throw an exception in case an
    // entity is un-accessible by the user.
    foreach ($code_results as $code => $id) {
      if ($row = $this->viewEntity($code)) {
        $return[] = $row;
      }
    }

    return $return;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Wrap viewEntity to load the gfs code via it's code.
   */
  public function viewEntity($code) {
    $code = strtoupper($code);
    $efq = new EntityFieldQuery();
    $efq_results = $efq->entityCondition('entity_type', 'gfs_code')
      ->propertyCondition('type', 'gfs_code')
      ->propertyCondition('status', 1)
      ->propertyCondition('code', $code)
      ->range(0, 1)
      ->execute();

    if (empty($efq_results['gfs_code'])) {
      throw new \RestfulBadRequestException(format_string('A gfs code with the given code is not available.'));
    }

    $id = key($efq_results['gfs_code']);
    return parent::viewEntity($id);
  }

  /**
   * Overrides \RestfulEntityBase::getEntitySelf().
   */
  protected function getEntitySelf(\EntityMetadataWrapper $wrapper) {
    return $this->versionedUrl($wrapper->code->value());
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Gfs code to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'parent') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_gfs_code_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
  }
}
