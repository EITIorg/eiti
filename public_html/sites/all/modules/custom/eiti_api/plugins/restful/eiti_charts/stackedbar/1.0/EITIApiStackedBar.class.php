<?php

/**
 * @file
 * Contains EITIApiStackedBar.
 */

/**
 * Class EITIApiStackedBar
 */
class EITIApiStackedBar extends RestfulDataProviderEITICharts {
  /**
   * {@inheritdoc}
   */
  public function getDefinedChartData() {
    $chartData = parent::getDefinedChartData();
    $chartData['government_revenues'] = array(
      'label' => t('Country Governmental Revenue'),
      'description' => t('Revenue disclosed by a Government of a specific country.'),
      'query_builder' => 'getGovernmentRevenue',
      'public_fields_info' => 'processCountryGovernmentalRevenue',
    );
    return $chartData;
  }

  /**
   * Creates the query for the country-based governmental revenue stacked bar chart.
   */
  public function getGovernmentRevenue() {
    $query = db_select('eiti_summary_data', 'sd');

    // One big query.
    $query->leftJoin('field_data_field_sd_revenue_government', 'fgrs', 'fgrs.entity_id = sd.id');
    $query->leftJoin('eiti_revenue_stream', 'grs', 'fgrs.field_sd_revenue_government_target_id = grs.id');
    $query->leftJoin('eiti_gfs_code', 'gfs', 'grs.gfs_code_id = gfs.id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->fields('sd', array('id', 'year_end', 'status'));
    $query->fields('ic', array('iso', 'name'));
    $query->fields('grs', array('gfs_code_id', 'revenue'));
    $query->fields('gfs', array('name'));
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
          case 'gfs_code':
            $query->condition('gfs_code_id', $filter , 'IN');
            break;

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
  public function processCountryGovernmentalRevenue($data) {
    $output = array();
    // Needed for normalization.
    $x_all = array();
    $x_group = array();
    foreach ($data as $item) {
      $year = format_date($item->year_end, 'custom', 'Y');
      if (!key_exists($item->gfs_code_id, $output)) {
        $output[$item->gfs_code_id] = array(
          'label' => $item->gfs_name,
          'values' => array(),
        );
      }

      // 2 cases: either it's unique and we append the value, or it's not,
      // then we sum the values together.
      if (!key_exists($year, $output[$item->gfs_code_id]['values'])) {
        $output[$item->gfs_code_id]['values'][$year] = array(
          'x' => $year,
          'y' => round(floatval($item->revenue)),
        );
      }
      else {
        $output[$item->gfs_code_id]['values'][$year]['y'] += round(floatval($item->revenue));
      }

      // Used for normalization.
      if (!in_array($year, $x_all)) {
        $x_all[] = $year;
      }
      $x_group[$item->gfs_code_id][] = $year;
    }
    // Make a small normalization.
    foreach ($output as $out_key => $group) {
      $output[$out_key]['values'] = array_values($group['values']);
    }
    foreach ($x_group as $indicator_id => $x_values) {
      $x_diff = array_diff($x_all, $x_values);
      foreach ($x_diff as $x) {
        $output[$indicator_id]['values'][] = array(
          'x' => $x,
          'y' => 0,
        );
      }
    }
    $output = array_values($output);
    return $output;
  }
}

