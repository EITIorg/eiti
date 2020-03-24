<?php

require_once DRUPAL_ROOT . '/sites/all/libraries/PHPExcel/Classes/PHPExcel.php';
include_once 'EITISummaryDataMapping.inc';

/**
 * Define class for Summary data import
 */
class EITISummaryDataImporter {

  /**
   * Process Summary data import
   */
  public function importSummaryData($uri) {
    $result = FALSE;

    if ($uri) {
      $xls = $this->loadXLS($uri);

      if ($xls) {
        $is_valid = $this->validateXLS($xls);

        if ($is_valid) {
          $this->processDataImport($xls);
        }
      }
    }

    return $result;
  }

  /**
   * Load PHPExcel object by uri
   */
  private function loadXLS($uri) {
    $path = drupal_realpath($uri);
    return PHPExcel_IOFactory::load($path);
  }

  /**
   * Validate XLS by spreadsheets list
   */
  private function validateXLS($xls) {
    $is_valid = FALSE;
    $list = $xls->getSheetNames();

    if (sizeof($list == 7)) {
      if ($list[0] == 'Introduction' && $list[1] == 'Part 1 - About'
        && $list[2] == 'Part 2 - Disclosure checklist' && $list[3] == 'Part 3 - Reporting entities'
        && $list[4] == 'Part 4 - Government revenues' && $list[5] == 'Part 5 - Company data' && $list[6] == 'Lists') {
        $is_valid = TRUE;
      }
    }

    return $is_valid;
  }

  /**
   * Load Summary data spreadsheet
   */
  private function getSpreadsheet($xls,  $sheet_index) {
    return $xls->getSheet($sheet_index);
  }

  /**
   * Process data import for Summary Data
   */
  private function processDataImport($xls) {

    // Process About section
    $about = $this->getSpreadsheet($xls, 1);
    if ($about) {
      $max_row = $xls->setActiveSheetIndex(1)->getHighestRow();
      $parsed_data = $this->parseAboutSection($about, $max_row);
      $entity = $this->buildSummaryDataReportFromXls($parsed_data);
    }
  }

  /**
   * Parse About section for getting data
   */
  private function parseAboutSection($sheet, $max_row) {
    $data = array();

    // Skip table header and start onlu from
    $i = 14;
    $dataMapping = new EITISummaryDataMapping();
    $about_fields = $dataMapping->getAboutSectionFields();

    while ($i < $max_row) {
      $cell = $sheet->getCellByColumnAndRow(2,$i)->getFormattedValue();

      if (isset($about_fields[$cell])) {
        $value_cell = $sheet->getCellByColumnAndRow(4,$i);

        if ($value_cell->isFormula()) {
          $value = $value_cell->getOldCalculatedValue();
        } else {
          $value = $value_cell->getFormattedValue();
        }

        $data[$about_fields[$cell]] = $value;
      }

      $i++;
    }

    return $data;
  }

  /**
   * Build Summary data report item entity from parsed data from xlsx datasheet
   */
  private function buildSummaryDataReportFromXls($data) {

    if (isset($data['country_id']) && isset($data['year_start']) && isset($data['year_end'])) {
      $start = $this->getYearByDate($data['year_start']);
      $end = $this->getYearByDate($data['year_end']);

      $is_entity_exists = $this->checkSummaryDataRerpotExists($data['country_id'], $start, $end);

      if ($is_entity_exists) {
        $entity_item = entity_load('summary_data', array($is_entity_exists));
      } else {
        $entity_item = entity_create('summary_data', array('type' => 'summary_data'));

        // Set global values
        $entity_item->year_start = strtotime($data['year_start']);
        $entity_item->year_end = strtotime($data['year_end']);
        $entity_item->published = strtotime($data['published']);
        $entity_item->status = 1;
        $entity_item->created = time();
        $entity_item->changed = time();
        $entity_item->currency_code = $data['currency_code'];
        $entity_item->currency_rate = $data['currency_rate'];
      }
      
      $entity_item = $this->mappingAboutSection($entity_item, $data);

      $entity = entity_metadata_wrapper('summary_data', $entity_item);

      entity_save('summary_data', $entity);
    }

    return $entity;
  }

  /**
   * Helper method for getting year by date
   */
  private function getYearByDate($date) {
    return strtotime($date);
  }

  /**
   * Helper function for checking of the Summary data report existance
   */
  private function checkSummaryDataRerpotExists($country_id, $start, $end) {
    $exists = FALSE;
    $id = FALSE;

    $countries = eitientity_implementing_country_lookup_by_name($country_id);
    if ($countries) {
      $country = array_shift($countries);

      // Fill county data
      if (isset($country->id)) {
        $id = $country->id;
      }
    }

    if ($id) {
      $query = db_query("SELECT esd.id FROM {eiti_summary_data} esd
      WHERE esd.type = :type AND esd.country_id = :country_id
      AND esd.year_start = :year_start AND esd.year_end = :year_end", array(':type' => 'summary_data', ':country_id' => $id, ':year_start' => $start, ':year_end' => $end))->fetchAll();
    }

    if (!empty($query)) {
      $query_item = array_shift($query);
      if (isset($query_item->id)) {
        $exists = $query_item->id;
      }
    }

    return $exists;
  }

  /**
   * Implements mapping for About section for new or existing entity
   */
  private function mappingAboutSection($entity, $data) {

    // Process countries data
    $countries = eitientity_implementing_country_lookup_by_name($data['country_id']);
    if ($countries) {
      $country = array_shift($countries);

      // Fill county data
      if (isset($country->id)) {
        $entity->country_id = $country->id;
      }
    }

    // Process text and numeric fields
    if (isset($data['field_sd_iso_alpha_3_code'])) {
      $entity->field_sd_iso_alpha_3_code['und'][0]['value'] = $data['field_sd_iso_alpha_3_code'];
    }

    if (isset($data['field_sd_national_currency_name'])) {
      $entity->field_sd_national_currency_name['und'][0]['value'] = $data['field_sd_national_currency_name'];
    }

    if (isset($data['field_sd_nation_currency_iso4217'])) {
      $entity->field_sd_nation_currency_iso4217['und'][0]['value'] = $data['field_sd_nation_currency_iso4217'];
    }

    if (isset($data['field_sd_site_link_url_eiti_data'])) {
      $entity->field_sd_site_link_url_eiti_data['und'][0]['value'] = $data['field_sd_site_link_url_eiti_data'];
    }

    if (isset($data['field_sd_open_data_portal_files'])) {
      $entity->field_sd_open_data_portal_files['und'][0]['value'] = $data['field_sd_open_data_portal_files'];
    }

    if (isset($data['field_sd_other_sector_name'])) {
      $entity->field_sd_other_sector_name['und'][0]['value'] = $data['field_sd_other_sector_name'];
    }

    if (isset($data['field_sd_no_reporting_gov'])) {
      $entity->field_sd_no_reporting_gov['und'][0]['value'] = $data['field_sd_no_reporting_gov'];
    }

    if (isset($data['field_sd_no_reporting_com'])) {
      $entity->field_sd_no_reporting_com['und'][0]['value'] = $data['field_sd_no_reporting_com'];
    }

    if (isset($data['field_sd_exchange_rate_src_url'])) {
      $entity->field_sd_exchange_rate_src_url['und'][0]['value'] = $data['field_sd_exchange_rate_src_url'];
    }

    if (isset($data['field_sd_systematic_disclosed'])) {
      $entity->field_sd_systematic_disclosed['und'][0]['value'] = round($data['field_sd_systematic_disclosed'] * 100, 2);
    }

    if (isset($data['field_sd_through_eiti_reporting'])) {
      $entity->field_sd_through_eiti_reporting['und'][0]['value'] = round($data['field_sd_through_eiti_reporting'] * 100, 2);
    }

    if (isset($data['field_sd_not_applicable'])) {
      $entity->field_sd_not_applicable['und'][0]['value'] = round($data['field_sd_not_applicable'] * 100, 2);
    }

    if (isset($data['field_sd_not_available'])) {
      $entity->field_sd_not_available['und'][0]['value'] = round($data['field_sd_not_available'] * 100, 2);
    }

    if (isset($data['field_sd_contact_name'])) {
      $entity->field_sd_contact_name['und'][0]['value'] = $data['field_sd_contact_name'];
    }

    if (isset($data['field_sd_contact_organisation'])) {
      $entity->field_sd_contact_organisation['und'][0]['value'] = $data['field_sd_contact_organisation'];
    }

    if (isset($data['field_sd_contact_email_address'])) {
      $entity->field_sd_contact_email_address['und'][0]['email'] = $data['field_sd_contact_email_address'];
    }

    // Process integer lists
    if (isset($data['field_sd_report_prep_independent'])) {
      $entity->field_sd_report_prep_independent['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_report_prep_independent']);
    }

    if (isset($data['field_sd_gov_system_discl_locat'])) {
      $entity->field_sd_gov_system_discl_locat['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_gov_system_discl_locat']);
    }

    if (isset($data['field_sd_other_files_relecance'])) {
      $entity->field_sd_other_files_relecance['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_other_files_relecance']);
    }

    if (isset($data['field_sd_oil_sector'])) {
      $entity->field_sd_oil_sector['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_oil_sector']);
    }

    if (isset($data['field_sd_gas_sector'])) {
      $entity->field_sd_gas_sector['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_gas_sector']);
    }

    if (isset($data['field_sd_mining_sector'])) {
      $entity->field_sd_mining_sector['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_mining_sector']);
    }

    if (isset($data['field_sd_other_non_upstr_sectors'])) {
      $entity->field_sd_other_non_upstr_sectors['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_other_non_upstr_sectors']);
    }

    if (isset($data['field_sd_disagg_revenue_stream'])) {
      $entity->field_sd_disagg_revenue_stream['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_disagg_revenue_stream']);
    }

    if (isset($data['field_sd_disagg_gover_agg'])) {
      $entity->field_sd_disagg_gover_agg['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_disagg_gover_agg']);
    }

    if (isset($data['field_sd_disagg_company'])) {
      $entity->field_sd_disagg_company['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_disagg_company']);
    }

    if (isset($data['field_sd_disagg_project'])) {
      $entity->field_sd_disagg_project['und'][0]['value'] = $this->getIntegerListItemByValue($data['field_sd_disagg_project']);
    }

    if (isset($data['field_sd_goverm_open_data_policy'])) {
      $entity->field_sd_goverm_open_data_policy['und'][0]['value'] = $this->getIntegerPolicyListItemByValue($data['field_sd_goverm_open_data_policy']);
    }

    // Process date fields
    if (isset($data['field_sd_public_date_eiti_data'])) {
      $timestamp = strtotime($data['field_sd_public_date_eiti_data']);
      if ($timestamp) {
        $entity->field_sd_public_date_eiti_data['und'][0]['value'] = $timestamp;
      }
    }

    if (isset($data['field_sd_date_other_file_public'])) {
      $timestamp = strtotime($data['field_sd_date_other_file_public']);
      if ($timestamp) {
        $entity->field_sd_date_other_file_public['und'][0]['value'] = $timestamp;
      }
    }

    return $entity;
  }

  /**
   * Helper function for parsing integer list items
   */
  private function getIntegerListItemByValue($value) {
    $item = '';

    switch ($value) {
      case 'No':
        $item = '0';
        break;
      case 'Yes':
        $item = '1';
        break;
      case 'Partially':
        $item = '2';
        break;
      case 'Not applicable':
        $item = '3';
        break;
    }

    return $item;
  }

  /**
   * Helper function for parsing integer policy list items
   */
  private function getIntegerPolicyListItemByValue($value) {
    $item = '';

    switch ($value) {
      case 'Yes, systematically disclosed':
        $item = '0';
        break;
      case 'Yes, through EITI reporting':
        $item = '1';
        break;
      case 'Not applicable':
        $item = '2';
        break;
      case 'Not available':
        $item = '3';
        break;
    }

    return $item;
  }



}
