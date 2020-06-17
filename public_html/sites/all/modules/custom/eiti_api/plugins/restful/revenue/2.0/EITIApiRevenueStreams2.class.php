<?php

/**
 * @file
 * Contains EITIApiRevenueStreams2.
 */

/**
 * Class EITIApiRevenueStreams2
 */
class EITIApiRevenueStreams2 extends EITIApiRevenueStreams {

  /**
   * Overrides EITIApiRevenueStreams::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id']['process_callbacks'][] = 'eiti_api_numeric_string_to_int';
    $public_fields['revenue']['process_callbacks'][] = 'eiti_api_numeric_string_to_float';
    //$public_fields['type']['process_callbacks'][] = 'ucfirst';
    unset($public_fields['report_status']);

    $public_fields['label'] = array(
      'property' => 'name',
    );
    $public_fields['gfs'] = array(
      'property' => 'gfs_code_id',
      'callback' => array($this, 'getGfsApiUrl')
    );
    $public_fields['summary_data'] = array(
      'callback' => array($this, 'getSummaryData'),
    );
    $public_fields['sector'] = array(
      'property' => 'field_o_sector',
      'callback' => array($this, 'getSector')
    );
    $public_fields['project_name'] = array(
      'property' => 'field_project_name',
      'callback' => array($this, 'getProjectName')
    );
    $public_fields['levied_on_project'] = array(
      'property' => 'field_levied_on_project',
      'callback' => array($this, 'getLeviedOnProject')
    );
    $public_fields['goverment_entity'] = array(
      'property' => 'field_goverment_entity',
      'callback' => array($this, 'getGovermentEntity')
    );
    $public_fields['reported_by_project'] = array(
      'property' => 'field_reported_by_project',
      'callback' => array($this, 'getReportedByProject')
    );
    $public_fields['reporting_currency'] = array(
      'property' => 'field_currency',
      'callback' => array($this, 'getReportingCurrency')
    );
    $public_fields['payment_made_in_kind'] = array(
      'property' => 'field_payment_made_in_kind',
      'callback' => array($this, 'getPaymentMadeInKind')
    );
    $public_fields['in_kind_volume'] = array(
      'property' => 'field_in_kind_volume',
      'callback' => array($this, 'getInKindVolume')
    );
    $public_fields['unit'] = array(
      'property' => 'field_unit',
      'callback' => array($this, 'getUnit')
    );
    $public_fields['comments'] = array(
      'property' => 'field_comments',
      'callback' => array($this, 'getComment')
    );

    return $public_fields;
  }

  /**
   * Get the Sector value.
   */
  function getSector($emw) {
    if (isset($emw->field_sector)) {
        $sector = $emw->field_sector->value();
        if (isset($sector)) {
          return $sector;
        }

    } else {
      $type = $emw->type->value();
      if ($type == 'company') {
        $organisation = $emw->organisation_id->value();

        if (isset($organisation->field_o_sector['und'][0]['target_id'])) {
          $sector_tid = $organisation->field_o_sector['und'][0]['target_id'];
          $sector = taxonomy_term_load($sector_tid);
          if ($sector) {
            return $sector->name;
          }
        }
      }
    }
    return NULL;
  }

  /**
   * Get the Project Name value.
   */
  function getProjectName($emw) {
    if (isset($emw->field_project_name)) {
      $project_name = $emw->field_project_name->value();
      if (isset($project_name)) {
        return $project_name;
      }
    }
    return NULL;
  }

  /**
   * Get the Levied On Project value.
   */
  function getLeviedOnProject($emw) {
    if (isset($emw->field_levied_on_project)) {
      $levied_on_project = $emw->field_levied_on_project->value();
      if (isset($levied_on_project)) {
        return $levied_on_project;
      }
    }
    return NULL;
  }

  /**
   * Get the Goverment Entity value.
   */
  function getGovermentEntity($emw) {
    if (isset($emw->field_goverment_entity)) {
      $goverment_entity = $emw->field_goverment_entity->value();
      if (isset($goverment_entity)) {
        return $goverment_entity;
      }
    }
    return NULL;
  }

  /**
   * Get the Reported By Project value.
   */
  function getReportedByProject($emw) {
    if (isset($emw->field_reported_by_project)) {
      $reported_by_project = $emw->field_reported_by_project->value();
      if (isset($reported_by_project)) {
        return $reported_by_project;
      }
    }
    return NULL;
  }

  /**
   * Get the Reporting Currency value.
   */
  function getReportingCurrency($emw) {
    if (isset($emw->field_currency)) {
      $currency = $emw->field_currency->value();
      if (isset($currency)) {
        return $currency;
      }
    }
    return NULL;
  }

  /**
   * Get the Payment Made In Kind value.
   */
  function getPaymentMadeInKind($emw) {
    if (isset($emw->field_payment_made_in_kind)) {
      $payment_made_in_kind = $emw->field_payment_made_in_kind->value();
      if (isset($payment_made_in_kind)) {
        return $payment_made_in_kind;
      }
    }
    return NULL;
  }

  /**
   * Get the In Kind Volume value.
   */
  function getInKindVolume($emw) {
    if (isset($emw->field_in_kind_volume)) {
      $in_kind_volume = $emw->field_in_kind_volume->value();
      if (isset($in_kind_volume)) {
        return $in_kind_volume;
      }
    }
    return NULL;
  }

  /**
   * Get the Unit value.
   */
  function getUnit($emw) {
    if (isset($emw->field_unit)) {
      $unit = $emw->field_unit->value();
      if (isset($unit)) {
        return $unit;
      }
    }
    return NULL;
  }

  /**
   * Get the Unit value.
   */
  function getComment($emw) {
    if (isset($emw->field_comments)) {
      $comments = $emw->field_comments->value();
      if (isset($comments)) {
        return $comments;
      }
    }
    return NULL;
  }

  /**
   * Overrides EITIApiRevenueStreams::getOrganisation().
   */
  public function getOrganisation($emw) {
    if (isset($emw->organisation_id)) {
      $organisation = $emw->organisation_id->value();
      if (isset($organisation->id)) {
        return url('api/v2.0/organisation/' . $organisation->id, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Gets the gfs code API url.
   */
  function getGfsApiUrl($emw) {
    if (isset($emw->gfs_code_id)) {
      $gfs_code = $emw->gfs_code_id->value();
      if (isset($gfs_code->id)) {
        return url('api/v2.0/gfs_code/' . $gfs_code->code, array('absolute' => TRUE));
      }
    }
    return NULL;
  }

  /**
   * Overrides RestfulBase::parseRequestForListFilter().
   */
  protected function parseRequestForListFilter() {
    $filters = parent::parseRequestForListFilter();
    foreach ($filters as $key => $filter) {
      // Gfs code to ID.
      if (isset($filter['public_field'], $filter['value'][0]) && $filter['public_field'] == 'gfs') {
        foreach ($filter['value'] as $k => $v) {
          $filters[$key]['value'][$k] = eitientity_gfs_code_get_id(strtoupper($v));
        }
      }
    }
    return $filters;
  }

  /**
   * Get related summary data API page url.
   */
  function getSummaryData($emw) {
    $query = db_select('eiti_summary_data', 'sd');
    if ($emw->getBundle() == 'company') {
      $query->innerJoin('field_data_field_sd_revenue_company', 'frc', 'sd.id = frc.entity_id');
      $query->condition('frc.field_sd_revenue_company_target_id', $emw->id->value());
    }
    else {
      $query->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
      $query->condition('frg.field_sd_revenue_government_target_id', $emw->id->value());
    }
    $query->fields('sd', array('id2'));
    $query->condition('sd.status', 1);
    $result = $query->execute()->fetchField();

    if ($result) {
      return url('api/v2.0/summary_data/' . $result, array('absolute' => TRUE));
    }

    return NULL;
  }

  /**
   * Overrides RestfulDataProviderEFQ::queryForListFilter().
   *
   * We need custom handling for the summary_data filter.
   */
  protected function queryForListFilter(\EntityFieldQuery $query) {
    $public_fields = $this->getPublicFields();
    foreach ($this->parseRequestForListFilter() as $filter) {
      // Determine if filtering is by field or property.
      $property_name = isset($public_fields[$filter['public_field']]['property']) ? $public_fields[$filter['public_field']]['property'] : NULL;
      if ($filter['public_field'] != 'summary_data' && !$property_name) {
        throw new \RestfulBadRequestException('The current filter selection does not map to any entity property or Field API field.');
      }
      if (field_info_field($property_name)) {
        if (in_array(strtoupper($filter['operator'][0]), array('IN', 'BETWEEN'))) {
          $query->fieldCondition($public_fields[$filter['public_field']]['property'], $public_fields[$filter['public_field']]['column'], $filter['value'], $filter['operator'][0]);
          continue;
        }
        for ($index = 0; $index < count($filter['value']); $index++) {
          $query->fieldCondition($public_fields[$filter['public_field']]['property'], $public_fields[$filter['public_field']]['column'], $filter['value'][$index], $filter['operator'][$index]);
        }
      }
      else {
        if (in_array(strtoupper($filter['operator'][0]), array('IN', 'BETWEEN'))) {
          $query->propertyCondition($property_name, $filter['value'], $filter['operator'][0]);
          continue;
        }
        if ($filter['public_field'] != 'summary_data') {
          $column = $this->getColumnFromProperty($property_name);
        }
        for ($index = 0; $index < count($filter['value']); $index++) {
          if ($filter['public_field'] == 'summary_data') {
            $sd_query1 = db_select('eiti_summary_data', 'sd');
            $sd_query1->innerJoin('field_data_field_sd_revenue_company', 'frc', 'sd.id = frc.entity_id');
            $sd_query1->fields('frc', array('field_sd_revenue_company_target_id'));
            $sd_query1->condition('sd.id2', $filter['value'][$index]);
            $rs_ids1 = $sd_query1->execute()->fetchCol();
            $sd_query2 = db_select('eiti_summary_data', 'sd');
            $sd_query2->innerJoin('field_data_field_sd_revenue_government', 'frg', 'sd.id = frg.entity_id');
            $sd_query2->fields('frg', array('field_sd_revenue_government_target_id'));
            $sd_query2->condition('sd.id2', $filter['value'][$index]);
            $rs_ids2 = $sd_query2->execute()->fetchCol();
            $rs_ids = array_merge($rs_ids1, $rs_ids2);
            if (!$rs_ids) {
              throw new \RestfulBadRequestException('No revenue streams for the given summary data found.');
            }
            $query->entityCondition('entity_id', $rs_ids, 'IN');
          }
          else {
            $query->propertyCondition($column, $filter['value'][$index], $filter['operator'][$index]);
          }
        }
      }
    }
  }
}
