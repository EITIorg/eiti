<?php

/**
 * @file
 * Contains EITIApiBubble.
 */

/**
 * Class EITIApiBubble
 */
class EITIApiBubble extends RestfulDataProviderEITICharts {
  /**
   * {@inheritdoc}
   */
  public function getDefinedChartData() {
    $chartData = parent::getDefinedChartData();
    $chartData['disbursed_revenues'] = array(
      'label' => t('Country Disbursed Revenues'),
      'description' => t('Revenue Disbursed by Governmental Agencies of a specific country.'),
      'query_builder' => 'getDisbursedRevenues',
      'public_fields_info' => 'processCountryDisbursedRevenues',
    );
    return $chartData;
  }

  /**
   * Creates the query for the country-based disbursed revenues bubble chart.
   */
  public function getDisbursedRevenues() {
    $query = db_select('eiti_summary_data', 'sd');

    // One big query.
    $query->leftJoin('field_data_field_sd_revenue_government', 'fgrs', 'fgrs.entity_id = sd.id');
    $query->leftJoin('eiti_revenue_stream', 'grs', 'fgrs.field_sd_revenue_government_target_id = grs.id');
    $query->leftJoin('eiti_organisation', 'org', 'org.id = grs.organisation_id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->fields('sd', array('id', 'year_end', 'status'));
    $query->fields('ic', array('iso', 'name'));
    $query->fields('grs', array('gfs_code_id', 'revenue'));
    $query->fields('org', array('name', 'id'));
    $query->condition('sd.status', TRUE);
    $query->condition('grs.type', 'agency');
    $query->condition('grs.revenue', 0, '>');
    $query->orderBy('year_end', 'ASC');

    // Check for the filters.
    $this->checkProductionFilters($query);

    return $query;
  }

  /**
   * Check if we have any filters specified and if we do, apply those.
   */
  protected function checkProductionFilters($query) {
    $request = $this->getRequest();
    if (!empty($request['filter'])) {
      foreach ($request['filter'] as $id => $filter) {
        // Normalize the filter.
        if (!is_array($filter)) {
          $filter = explode(',', $filter);
        }
        switch ($id) {
          case 'country_iso':
            $query->condition('iso', $filter, 'IN');
            break;
        }
      }
    }
  }

  /**
   * Polishes the country governmental stacked bar chart fields.
   */
  public function processCountryDisbursedRevenues($data) {
    $output = array();
    // Needed for normalization.
    $child_count = 0;
    foreach ($data as $item) {
      $child_count++;
      if (!in_array($item->org_id, array_keys($output))) {
        $output[$item->org_id] = array(
          'name' => 'child' . $child_count,
          'children' => array(
            array(
              'name' => $item->org_name,
              'size' => $item->revenue,
            )
          ),
        );
      }
      else {
        $output[$item->org_id]['children'][0]['size'] += $item->revenue;
      }
    }
    $output = array_values($output);

    return array(
      'name' => 'disbursement',
      'children' => $output,
    );
  }
}

