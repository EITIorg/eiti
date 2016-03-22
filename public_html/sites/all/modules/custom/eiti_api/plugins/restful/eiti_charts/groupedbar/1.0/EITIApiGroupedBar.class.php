<?php

/**
 * @file
 * Contains EITIApiGroupedBar.
 */

/**
 * Class EITIApiGroupedBar
 */
class EITIApiGroupedBar extends RestfulDataProviderEITICharts {
  /**
   * {@inheritdoc}
   */
  public function getDefinedChartData() {
    $chartData = parent::getDefinedChartData();
    $chartData['production'] = array(
      'label' => t('Global Production of all Countries per Year'),
      'description' => t('Production volumes grouped by commodities and filtered per year.'),
      'query_builder' => 'getProductionQuery',
      'public_fields_info' => 'processGlobalProductionFields',
    );
    $chartData['production_per_country'] = array(
      'label' => t('Country Production of all years'),
      'description' => t('Production volumes grouped by commodities and filtered per country.'),
      'query_builder' => 'getProductionQuery',
      'public_fields_info' => 'processCountryProductionFields',
    );
    $chartData['external_per_country'] = array(
      'label' => t('Country\'s External Indicators for all years'),
      'description' => t('External indicators values per year.'),
      'query_builder' => 'getExternalIndicatorsQuery',
      'public_fields_info' => 'processCountryProductionFields',
    );
    return $chartData;
  }

  /**
   * Creates the query for the production grouped bar chart.
   */
  public function getProductionQuery() {
    $query = db_select('eiti_summary_data', 'sd');

    // One big query.
    $query->leftJoin('field_data_field_sd_indicator_values', 'fiv', 'fiv.entity_id = sd.id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('eiti_indicator_value', 'iv', 'fiv.field_sd_indicator_values_target_id = iv.id');
    $query->leftJoin('eiti_indicator', 'i', 'i.id = iv.indicator_id');
    $query->fields('ic', array('iso', 'name'));
    $query->fields('iv', array('id', 'indicator_id', 'value_numeric', 'value_unit'));
    $query->fields('sd', array('id', 'year_end', 'status'));
    $query->addField('i', 'name', 'commodity_name');
    $query->condition('sd.status', TRUE);
    $query->isNotNull('iv.value_numeric');

    // Check for the filters.
    $this->checkProductionFilters($query);

    return $query;
  }

  /**
   * Creates the query for the external indicators grouped bar chart.
   *
   * It's not very different from the original query, but we use a copy,
   * because maybe later we'll want to make certain changes here.
   */
  public function getExternalIndicatorsQuery() {
    $query = db_select('eiti_summary_data', 'sd');

    // One big query.
    $query->leftJoin('field_data_field_sd_indicator_values', 'fiv', 'fiv.entity_id = sd.id');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('eiti_indicator_value', 'iv', 'fiv.field_sd_indicator_values_target_id = iv.id');
    $query->leftJoin('eiti_indicator', 'i', 'i.id = iv.indicator_id');
    $query->fields('ic', array('iso', 'name'));
    $query->fields('iv', array('id', 'indicator_id', 'value_numeric', 'value_unit'));
    $query->fields('sd', array('id', 'year_end', 'status'));
    $query->addField('i', 'name', 'commodity_name');
    $query->condition('sd.status', TRUE);
    $query->isNotNull('iv.value_numeric');

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
          case 'year':
            // If you know any better way how to get start / end timestamps of a given year, PM me (Nikro).
            $year = reset($filter);
            $startDate = DateTime::createFromFormat('Y-m-d H:i:s', $year . '-01-01 00:00:00');
            $startTimestamp = $startDate->getTimestamp();

            $endDate = DateTime::createFromFormat('Y-m-d H:i:s', ($year + 1) . '-01-01 00:00:00');
            $endTimestamp = $endDate->getTimestamp();

            $query->condition('sd.year_end', array($startTimestamp, $endTimestamp), 'BETWEEN');
            break;

          case 'indicator':
            $query->condition('indicator_id', $filter , 'IN');
            break;

          case 'country_iso':
            $query->condition('iso', $filter, 'IN');
            $query->orderBy('year_end', 'ASC');
            break;
        }
      }
    }
  }

  /**
   * Polishes the global production grouped bar chart fields.
   */
  public function processGlobalProductionFields($data) {
    $output = array();
    // Needed for normalization.
    $x_all = array();
    $x_group = array();
    foreach ($data as $item) {
      if (!key_exists($item->indicator_id, $output)) {
        $output[$item->indicator_id] = array(
          'label' => $item->commodity_name
        );
      }
      $output[$item->indicator_id]['values'][] = array(
        'x' => $item->name,
        'y' => round(floatval($item->value_numeric)),
      );

      // Used for normalization.
      if (!in_array($item->name, $x_all)) {
        $x_all[] = $item->name;
      }
      $x_group[$item->indicator_id][] = $item->name;
    }
    // Make a small normalization.
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

  /**
   * Polishes the global production grouped bar chart fields.
   */
  function processCountryProductionFields($data) {
    $output = array();
    // Needed for normalization.
    $x_all = array();
    $x_group = array();
    foreach ($data as $item) {
      $year = format_date($item->year_end, 'custom', 'Y');
      if (!key_exists($item->indicator_id, $output)) {
        $output[$item->indicator_id] = array(
          'label' => $item->commodity_name
        );
      }
      $output[$item->indicator_id]['values'][] = array(
        'x' => $year,
        'y' => round(floatval($item->value_numeric)),
      );

      // Used for normalization.
      if (!in_array($year, $x_all)) {
        $x_all[] = $year;
      }
      $x_group[$item->indicator_id][] = $year;
    }
    // Make a small normalization.
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


