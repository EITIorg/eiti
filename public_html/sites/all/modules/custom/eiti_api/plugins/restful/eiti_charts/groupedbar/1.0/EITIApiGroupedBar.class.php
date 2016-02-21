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
      'label' => t('Production per Country per Year'),
      'description' => t('Production volumes grouped by commodities and filtered per year.'),
      'query_builder' => 'getProductionQuery',
      'public_fields_info' => 'processProductionFields',
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
    $query->fields('ic', array('iso', ' name'));
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
    foreach ($request['filter'] as $id => $filter) {
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
          $filer_arr = explode(',', $filter);
          $query->condition('indicator_id', $filer_arr , 'IN');
          break;
      }
    }
  }

  /**
   * Polishes the production grouped bar chart fields.
   */
  public function processProductionFields($data) {
    $output = array();
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
    }
    $output = array_values($output);
    return $output;
  }
}
