<?php

/**
 * @file
 * Contains EITIApiSankey.
 */

/**
 * Class EITIApiSankey
 */
class EITIApiSankey extends RestfulDataProviderEITICharts {
  /**
   * {@inheritdoc}
   */
  public function getDefinedChartData() {
    $chartData = parent::getDefinedChartData();
    $chartData['disbursed_by_companies_per_country'] = array(
      'label' => t('Country Disbursed Revenues by Companies'),
      'description' => t('Revenue Disbursed by Companies of a specific country.'),
      'query_builder' => 'getDisbursedRevenues',
      'public_fields_info' => 'processCountryDisbursedRevenues',
    );
    return $chartData;
  }

  /**
   * Creates the query for the country-based disbursed revenues sankey chart.
   */
  public function getDisbursedRevenues() {

    // Two big queries, intersected.
    $query = db_select('eiti_summary_data', 'sd');
    $query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $query->leftJoin('field_data_field_sd_revenue_company', 'fcrs', 'fcrs.entity_id = sd.id');
    $query->leftJoin('eiti_revenue_stream', 'crs', 'fcrs.field_sd_revenue_company_target_id = crs.id');
    $query->leftJoin('eiti_organisation', 'org_c', 'org_c.id = crs.organisation_id');
    $query->leftJoin('eiti_gfs_code', 'gfs', 'crs.gfs_code_id = gfs.id');

    $second_query = db_select('eiti_summary_data', 'sd');
    $second_query->leftJoin('eiti_implementing_country', 'ic', 'ic.id = sd.country_id');
    $second_query->leftJoin('field_data_field_sd_revenue_government', 'fgrs', 'fgrs.entity_id = sd.id');
    $second_query->leftJoin('eiti_revenue_stream', 'grs', 'fgrs.field_sd_revenue_government_target_id = grs.id');
    $second_query->leftJoin('eiti_organisation', 'org_g', 'org_g.id = grs.organisation_id');
    $second_query->addField('org_g', 'name', 'agency');
    $second_query->addField('grs', 'gfs_code_id', 'gfs_code_id');
    $second_query->condition('sd.status', TRUE);

    $query->join($second_query, 'sq', 'sq.gfs_code_id = crs.gfs_code_id');
    $query->fields('sd', array('id', 'year_end', 'status'));
    $query->fields('ic', array('iso', 'name'));
    $query->fields('sq', array('agency'));
    $query->fields('crs', array('revenue'));
    $query->addField('org_c', 'name', 'company');
    $query->addField('gfs', 'name', 'gfs_name');

    $query->condition('sd.status', TRUE);
    $query->condition('crs.revenue', 0, '>');
    $query->orderBy('crs.revenue', 'DESC');

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

          case 'years_from':
            $year = reset($filter);
            $startDate = DateTime::createFromFormat('Y-m-d H:i:s', $year . '-01-01 00:00:00');
            $startTimestamp = $startDate->getTimestamp();

            $query->condition('sd.year_end', $startTimestamp, '>=');
            break;

          case 'years_to':
            $year = reset($filter);
            $endDate = DateTime::createFromFormat('Y-m-d H:i:s', ($year + 1) . '-01-01 00:00:00');
            $endTimestamp = $endDate->getTimestamp();

            $query->condition('sd.year_end', $endTimestamp, '<');
            break;
        }
      }
    }
  }

  /**
   * Polishes the country governmental stacked bar chart fields.
   */
  public function processCountryDisbursedRevenues($data) {
    $request = $this->getRequest();
    $limit = $request['filter']['limit'];

    $output = array();
    // Get all the nodes first.
    $nodes = array();
    foreach ($data as $item) {
      $lookup_haystack = array_column($nodes, 'name');
      if (!in_array($item->company, $lookup_haystack)) {
        $nodes[] = array(
          'name' => $item->company,
        );
      }
      if (!in_array($item->agency, $lookup_haystack)) {
        $nodes[] = array(
          'name' => $item->agency,
        );
      }
      if (!in_array($item->gfs_name, $lookup_haystack)) {
        $nodes[] = array(
          'name' => $item->gfs_name,
        );
      }
    }

    // Now let's create the links.
    $lookup_haystack = array_column($nodes, 'name');
    $links = array();
    foreach ($data as $item) {
      $company_index = array_search($item->company, $lookup_haystack);
      $gfs_name_index = array_search($item->gfs_name, $lookup_haystack);

      $c_g_flux = $company_index . ':' . $gfs_name_index;
      // Append the value or sum it to existing fluxes.
      if (!in_array($c_g_flux, array_keys($links))) {
        $links[$c_g_flux] = array(
          'source' => $company_index,
          'target' => $gfs_name_index,
          'value' => floatval($item->revenue),
        );
      }
      else {
        $links[$c_g_flux]['value'] += floatval($item->revenue);
      }
    }

    // Now we can filter out (limit) the companies.
    $company_values = array_column($links, 'value', 'source');
    arsort($company_values);
    $filtered_c_sources = array_slice($company_values, 0, $limit, TRUE);
    $filtered_c_sources = array_keys($filtered_c_sources);
    $all_c_sources = array_keys($company_values);
    $excluded_c_sources = array_diff($all_c_sources, $filtered_c_sources);
    $excluded_c_sources = array_flip($excluded_c_sources);
    $nodes = array_diff_key($nodes, $excluded_c_sources);

    // Reset the keys so it will appear as an array in JS rather than object.
    $nodes = array_values($nodes);
    $lookup_haystack = array_column($nodes, 'name');
    $links = array();

    // Now that we know that we want to limit to certain companies, let's put together
    // the second part of the flows.
    foreach ($data as $item) {
      $company_index = array_search($item->company, $lookup_haystack);
      $gfs_name_index = array_search($item->gfs_name, $lookup_haystack);
      $agency_index = array_search($item->agency, $lookup_haystack);
      $c_g_flux = $company_index . ':' . $gfs_name_index;
      $g_a_flux = $gfs_name_index . ':' . $agency_index;

      // Added GFS -> Government Agency
      if ($company_index) {
        // Yes we do it again, because the lookup haystack is now refreshed.
        if (!in_array($c_g_flux, array_keys($links))) {
          $links[$c_g_flux] = array(
            'source' => $company_index,
            'target' => $gfs_name_index,
            'value' => floatval($item->revenue),
          );
        }
        else {
          $links[$c_g_flux]['value'] += floatval($item->revenue);
        }

        // Append the value or sum it to existing fluxes.
        if (!in_array($g_a_flux, array_keys($links))) {
          $links[$g_a_flux] = array(
            'source' => $gfs_name_index,
            'target' => $agency_index,
            'value' => floatval($item->revenue),
          );
        }
        else {
          $links[$g_a_flux]['value'] += floatval($item->revenue);
        }
      }
    }

    return array(
      'nodes' => $nodes,
      'links' => array_values($links),
    );
  }
}

