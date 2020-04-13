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

    // Process Disclosure checklist section
    $disclosure_checklist = $this->getSpreadsheet($xls, 2);
    $disclosure_parsed_data = array();
    if ($disclosure_checklist) {
      $max_row = $xls->setActiveSheetIndex(2)->getHighestRow();
      $disclosure_parsed_data = $this->parseDisclosureChecklistSection($disclosure_checklist, $max_row);
      $disclosure_parsed_data_items = $disclosure_parsed_data['items'];
      $max = $disclosure_parsed_data['max'];
    }

    // Process Reporting entities section
    $reporting_entities =$this->getSpreadsheet($xls, 3);
    if ($reporting_entities) {
      $max_row = $xls->setActiveSheetIndex(3)->getHighestRow();
      $reporting_entities_parsed_data = $this->parseReportingEntitiesSection($reporting_entities, $max_row);
    }

    // Process Goverment revenues section
    $goverment_revenues = $this->getSpreadsheet($xls, 4);

    if ($goverment_revenues) {
      $max_row = $xls->setActiveSheetIndex(4)->getHighestRow();
      $goverment_revenues_parsed_data = $this->parseGovermentRevenuesSection($goverment_revenues, $max_row);
    }

    // Process Company data section
    $company_data = $this->getSpreadsheet($xls, 5);

    if ($company_data) {
      $max_row = $xls->setActiveSheetIndex(5)->getHighestRow();
      $company_parsed_data = $this->parseCompanySection($company_data, $max_row);
    }

    // Process Batch for iterating Indicators
    $this->processIndicatorBatch($entity, $disclosure_parsed_data_items, $max, $reporting_entities_parsed_data, $goverment_revenues_parsed_data, $company_parsed_data);
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
    $id = NULL;
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
      $id = $entity_item->id;
    }

    return $id;
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

  /**
   * Processing data parsing for Disclosure checklist section
   */
  public function parseDisclosureChecklistSection($sheet, $max_row) {
    $data = array();

    // Skip table header
    $max = 0;
    $i = 17;
    $dataMapping = new EITISummaryDataMapping();

    $sections = $dataMapping->disclosureCheclishGetSubsections();
    $skip_sections = $dataMapping->disclosureCheclishGetSkipItems();
    $active_section = '';

    while ($i < $max_row) {
      $requirement_cell = $sheet->getCellByColumnAndRow(1, $i)->getFormattedValue();

      if (in_array($requirement_cell, $sections)) {
        $active_section = $requirement_cell;

        $data['items'][] = array(
          'parent' => '',
          'requirement_cell' => $requirement_cell,
          'inclusion' => '',
          'source' => '',
        );

        $max++;
      } else {
        if (!empty($requirement_cell) && !in_array($requirement_cell, $skip_sections)) {
          $inclusion_cell = $sheet->getCellByColumnAndRow(3, $i);
          if ($inclusion_cell->isFormula()) {
            $value = $inclusion_cell->getOldCalculatedValue();
          } else {
            $value = $inclusion_cell->getFormattedValue();
          }

          $source_cell = $sheet->getCellByColumnAndRow(5, $i)->getFormattedValue();

          $data['items'][] = array(
            'parent' => $active_section,
            'requirement_cell' => $requirement_cell,
            'inclusion' => $value,
            'source' => $source_cell,
          );
          $max++;
        }
      }

      $i++;
    }

    $data['max'] = $max;

    return $data;
  }

  /**
   * Implements functuon
   */
  private function processIndicatorBatch($entity, $disclosure_parsed_data, $max, $reporting_entities_parsed_data, $goverment_revenues_parsed_data, $company_parsed_data) {
    $batch = array(
      'title' => t('Importing summary data'),
      'operations' => array(
        array(
          'eiti_sdi_batch_process_disclosure_checklist_import',
          array(
            $entity,
            $disclosure_parsed_data,
            $max,
          ),
        ),
        array(
          'eiti_sdi_batch_process_reporting_entities_import',
          array(
            $entity,
            $reporting_entities_parsed_data,
          ),
        ),
        array(
          'eiti_sdi_batch_process_goverment_revenues_import',
          array(
            $entity,
            $goverment_revenues_parsed_data,
          ),
        ),
        array(
          'eiti_sdi_batch_process_company_import',
          array(
            $entity,
            $company_parsed_data,
          ),
        ),
      ),
      'finished' => 'eiti_sdi_batch_process_finish_callback',
    );
    batch_set($batch);
    //batch_process('admin/content/summary_data');
  }

  /**
   * Parse Reporting entities section
   */
  private function parseReportingEntitiesSection($sheet, $max_row) {
    $data = array();

    $i = 13;

    $dataMapping = new EITISummaryDataMapping();
    $reporting_entities_sections = $dataMapping->reportingEntitiesSections();
    $reporting_entities_active_section = '';
    $reporting_entities_skip_rows = $dataMapping->reportingEntitiesSkipRows();

    while ($i < $max_row) {
      $requirement_cell = $sheet->getCellByColumnAndRow(1, $i)->getFormattedValue();

      if (in_array($requirement_cell, $reporting_entities_sections)) {
        switch ($requirement_cell) {
          case "Reporting government entities list":
            $reporting_entities_active_section = 'goverment_entity';
            break;
          case "Reporting companies' list":
            $reporting_entities_active_section = 'company';
            break;
          case "Reporting projects' list":
            $reporting_entities_active_section = 'project';
            break;
        }
      } else {
        if (empty($requirement_cell) && $reporting_entities_active_section == 'project') {
          $i = $max_row;
        } else {
          if (!empty($requirement_cell) && !in_array($requirement_cell, $reporting_entities_skip_rows)) {

            // Doing parsing for subsections
            $item = array();

            switch ($reporting_entities_active_section) {
              case 'goverment_entity':
                $item = array(
                  'full_agency_name' => $sheet->getCellByColumnAndRow(1, $i)->getFormattedValue(),
                  'agency_type' => $sheet->getCellByColumnAndRow(2, $i)->getFormattedValue(),
                  'id_number' => $sheet->getCellByColumnAndRow(3, $i)->getFormattedValue(),
                  'total_reported' => $sheet->getCellByColumnAndRow(4, $i)->getOldCalculatedValue(),
                );
                break;
              case 'company':
                $item = array(
                  'full_company_name' => $sheet->getCellByColumnAndRow(1, $i)->getFormattedValue(),
                  'company_id' => $sheet->getCellByColumnAndRow(2, $i)->getFormattedValue(),
                  'sector' => $sheet->getCellByColumnAndRow(3, $i)->getFormattedValue(),
                  'commodities' => $sheet->getCellByColumnAndRow(4, $i)->getFormattedValue(),
                  'stock_exchange_listing' => $sheet->getCellByColumnAndRow(5, $i)->getFormattedValue(),
                  'audited_financial_statement' => $sheet->getCellByColumnAndRow(6, $i)->getFormattedValue(),
                  'payment_to_goverment_report' => $sheet->getCellByColumnAndRow(7, $i)->getOldCalculatedValue(),
                );
                break;
              case 'project':
                $item = array(
                  'full_project_name' => $sheet->getCellByColumnAndRow(1, $i)->getFormattedValue(),
                  'legal_Agreement_ref_number' => $sheet->getCellByColumnAndRow(2, $i)->getFormattedValue(),
                  'affiliated_companies' => $sheet->getCellByColumnAndRow(3, $i)->getFormattedValue(),
                  'commodities' => $sheet->getCellByColumnAndRow(4, $i)->getFormattedValue(),
                  'status' => $sheet->getCellByColumnAndRow(5, $i)->getFormattedValue(),
                  'production_volume' => $sheet->getCellByColumnAndRow(6, $i)->getFormattedValue(),
                  'unit' => $sheet->getCellByColumnAndRow(7, $i)->getFormattedValue(),
                  'production_value' => $sheet->getCellByColumnAndRow(8, $i)->getFormattedValue(),
                  'currency' => $sheet->getCellByColumnAndRow(9, $i)->getFormattedValue(),
                );
                break;
            }

            $data[$reporting_entities_active_section][] = $item;

          }
        }
      }

      $i++;
    }

    return $data;
  }

  /**
   * Parse Goverment revenues section
   */
  private function parseGovermentRevenuesSection($sheet, $max_row) {
    $data = array();
    $i = 22;

    while ($i < $max_row) {
      $gfs_classification = $sheet->getCellByColumnAndRow(5, $i)->getFormattedValue();

      if (empty($gfs_classification)) {
        $i = $max_row;
      } else {
        $data[] = array(
          'gfs_classification' => $gfs_classification,
          'sector' => $sheet->getCellByColumnAndRow(6, $i)->getFormattedValue(),
          'revenue_stream_name' => $sheet->getCellByColumnAndRow(7, $i)->getFormattedValue(),
          'goverment_entity' => $sheet->getCellByColumnAndRow(8, $i)->getFormattedValue(),
          'revenue_value' => $sheet->getCellByColumnAndRow(9, $i)->getFormattedValue(),
          'currency' => $sheet->getCellByColumnAndRow(10, $i)->getFormattedValue(),
        );
      }

      $i++;
    }

    return $data;
  }

  /**
   * Parse company data
   */
  private function parseCompanySection($sheet, $max_row) {
    $data = array();
    $i = 15;

    while ($i < $max_row) {
      $company = $sheet->getCellByColumnAndRow(2, $i)->getFormattedValue();

      if (empty($company)) {
        $i = $max_row;
      } else {
        $data[] = array(
          'company' => $company,
          'goverment_entity' => $sheet->getCellByColumnAndRow(3, $i)->getFormattedValue(),
          'revenue_stream_name' => $sheet->getCellByColumnAndRow(4, $i)->getFormattedValue(),
          'levied_on_project' => $sheet->getCellByColumnAndRow(5, $i)->getFormattedValue(),
          'reported_by_project' => $sheet->getCellByColumnAndRow(6, $i)->getFormattedValue(),
          'project_name' => $sheet->getCellByColumnAndRow(7, $i)->getFormattedValue(),
          'reporting_currency' => $sheet->getCellByColumnAndRow(8, $i)->getFormattedValue(),
          'revenue_value' => $sheet->getCellByColumnAndRow(9, $i)->getFormattedValue(),
          'payment_made_in_kind' => $sheet->getCellByColumnAndRow(10, $i)->getFormattedValue(),
          'in_kind_volume' => $sheet->getCellByColumnAndRow(11, $i)->getFormattedValue(),
          'unit' => $sheet->getCellByColumnAndRow(12, $i)->getFormattedValue(),
          'comments' => $sheet->getCellByColumnAndRow(13, $i)->getFormattedValue(),
        );
      }

      $i++;
    }

    return $data;
  }
}

/**
 * Implements Batch process for Disclosure checklist
 */
function eiti_sdi_batch_process_disclosure_checklist_import($entity, $disclosure_parsed_data, $max, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['disclosure_parsed_data'] = $disclosure_parsed_data;
    $context['sandbox']['entity'] = $entity;
    $context['sandbox']['max'] = $max;
  }

  if (isset($context['sandbox']['disclosure_parsed_data'][$context['sandbox']['progress']])) {
    $disclosure = $context['sandbox']['disclosure_parsed_data'][$context['sandbox']['progress']];

    $indicator_id = '';
    if ($disclosure['requirement_cell']) {
      $indicator_id = eiti_sdi_create_indicator_item($disclosure);
    }

    if (!empty($disclosure['parent']) && is_numeric($indicator_id)) {
      $summary_data = entity_load('summary_data', array($entity));
      if ($summary_data) {
        $summary_data = array_shift($summary_data);
        $summary_data->field_sd_indicator_values['und'][]['target_id'] = $indicator_id;
        entity_save('summary_data', $summary_data);
      }
    }
  }

  $context['sandbox']['progress']++;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Implements Batch process for Reporting entities
 */
function eiti_sdi_batch_process_reporting_entities_import($entity, $reporting_entities_parsed_data, &$context) {

  if (empty($context['sandbox'])) {

    $max = 0;
    $context['sandbox']['goverment_entity_max'] = 0;
    $context['sandbox']['goverment_entity_progress'] = 0;
    $context['sandbox']['company_max'] = 0;
    $context['sandbox']['company_progress'] = 0;
    $context['sandbox']['project_max'] = 0;
    $context['sandbox']['project_progress'] = 0;
    $context['sandbox']['active_subsection'] = '';
    $context['sandbox']['country_id'] = '';

    $country_query = db_query("SELECT esd.country_id FROM {eiti_summary_data} esd WHERE esd.id = :entity_id", array(':entity_id' => $entity))->fetchAll();
    if ($country_query) {
      $country_query = array_shift($country_query);
      if (isset($country_query->country_id)) {
        $context['sandbox']['country_id'] = $country_query->country_id;
      }
    }

    if ($reporting_entities_parsed_data['goverment_entity'] && !empty($reporting_entities_parsed_data['goverment_entity'])) {
      $context['sandbox']['goverment_entity_max'] = sizeof($reporting_entities_parsed_data['goverment_entity']) - 1;
      $max += $context['sandbox']['goverment_entity_max'];
    }

    if ($reporting_entities_parsed_data['company'] && !empty($reporting_entities_parsed_data['company'])) {
      $context['sandbox']['company_max'] = sizeof($reporting_entities_parsed_data['company']) - 1;
      $max += $context['sandbox']['company_max'];
    }

    if ($reporting_entities_parsed_data['company'] && !empty($reporting_entities_parsed_data['company'])) {
      $context['sandbox']['company_max'] = sizeof($reporting_entities_parsed_data['company']) - 1;
      $max += $context['sandbox']['company_max'];
    }

    if ($reporting_entities_parsed_data['project'] && !empty($reporting_entities_parsed_data['project'])) {
      $context['sandbox']['project_max'] = sizeof($reporting_entities_parsed_data['project']) - 1;
      $max += $context['sandbox']['project_max'];
    }

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['reporting_entities_parsed_data'] = $reporting_entities_parsed_data;
    $context['sandbox']['entity'] = $entity;
    $context['sandbox']['max'] = $max;
  }

  if (empty($context['sandbox']['active_subsection'])) {
    $context['sandbox']['active_subsection'] = 'goverment_entity';
  }

  switch ($context['sandbox']['active_subsection']) {
    case 'goverment_entity':
      if (isset($reporting_entities_parsed_data['goverment_entity'][$context['sandbox']['goverment_entity_progress']])) {
        $item = $reporting_entities_parsed_data['goverment_entity'][$context['sandbox']['goverment_entity_progress']];

        if (isset($item['id_number'])) {

          if ($item['id_number'] != 'Not applicable') {
            $entity_id_query = db_query("SELECT eo.id FROM {eiti_organisation} eo WHERE eo.identification_number = :id_number and eo.type = :type", array(':id_number' => $item['id_number'], ':type' => 'goverment_entity'))->fetchAll();
          } else {
            $entity_id_query = FALSE;
          }

          if ($entity_id_query) {
            $entity_id_query = array_shift($entity_id_query);

            if (isset($entity_id_query->id)) {
              $reporting_entity = entity_load('organisation', array($entity_id_query->id));

              if ($reporting_entity) {
                $reporting_entity = array_shift($reporting_entity);
                $reporting_entity->summary_data_id = $entity;
                $reporting_entity->country_id = $context['sandbox']['country_id'];
                $reporting_entity->name = $item['full_agency_name'];
                $reporting_entity->field_agency_type['und'][0]['value'] = $item['agency_type'];
                $reporting_entity->field_total_reported['und'][0]['value'] = $item['total_reported'];
                $reporting_entity->changed = time();
                entity_save('organisation', $reporting_entity);
              }
            }
          } else {
            $reporting_entity = entity_get_controller('organisation')->create();
            $reporting_entity->type = 'agency';
            $reporting_entity->name = $item['full_agency_name'];

            if ($item['id_number'] == 'Not applicable') {
              $item['id_number'] = '';
            }

            $reporting_entity->identification_number = $item['id_number'];
            $reporting_entity->summary_data_id = $entity;
            $reporting_entity->country_id = $context['sandbox']['country_id'];
            $reporting_entity->field_agency_type['und'][0]['value'] = $item['agency_type'];
            $reporting_entity->field_total_reported['und'][0]['value'] = $item['total_reported'];
            $reporting_entity->status = 1;
            $reporting_entity->created = time();
            $reporting_entity->changed = time();
            entity_save('organisation', $reporting_entity);
          }
        }
      }

      $context['sandbox']['goverment_entity_progress']++;
      if ($context['sandbox']['goverment_entity_progress'] > $context['sandbox']['goverment_entity_max']) {
        $context['sandbox']['active_subsection'] = 'company';
      }
      break;
    case 'company':
      if (isset($reporting_entities_parsed_data['company'][$context['sandbox']['company_progress']])) {
        $item = $reporting_entities_parsed_data['company'][$context['sandbox']['company_progress']];

        if (isset($item['company_id'])) {
          if ($item['company_id'] != 'Not applicable') {
            $entity_id_query = db_query("SELECT eo.id FROM {eiti_organisation} eo WHERE eo.identification_number = :id_number and eo.type = :type", array(':id_number' => $item['company_id'], ':type' => 'company'))->fetchAll();
          } else {
            $entity_id_query = FALSE;
          }

          if ($entity_id_query) {
            $entity_id_query = array_shift($entity_id_query);

            if (isset($entity_id_query->id)) {
              $reporting_entity = entity_load('organisation', array($entity_id_query->id));

              if ($reporting_entity) {
                $reporting_entity = array_shift($reporting_entity);
                $reporting_entity->summary_data_id = $entity;
                $reporting_entity->country_id = $context['sandbox']['country_id'];
                $reporting_entity->name = $item['full_company_name'];
                $reporting_entity->changed = time();

                $sector = eitientity_organisation_get_sector_tid($item['sector']);
                if ($sector) {
                  $reporting_entity->field_o_sector['und'][0]['target_id'] = $sector;
                }

                $comodity = eitientity_organisation_get_commodity_tid($item['commodities']);
                if ($comodity) {
                  $reporting_entity->	field_o_commodities['und'][0]['target_id'] = $comodity;
                }

                $reporting_entity->field_stock_exchange_listing = $item['stock_exchange_listing'];
                $reporting_entity->field_audited_financial_state = $item['audited_financial_statement'];
                $reporting_entity->field_payments_to_governments = $item['payment_to_goverment_report'];

                entity_save('organisation', $reporting_entity);
              }
            }
          } else {
            $reporting_entity = entity_get_controller('organisation')->create();
            $reporting_entity->type = 'company';
            $reporting_entity->name = $item['full_company_name'];

            if ($item['company_id'] == 'Not applicable') {
              $item['company_id'] = '';
            }

            $reporting_entity->identification_number = $item['company_id'];
            $reporting_entity->summary_data_id = $entity;
            $reporting_entity->country_id = $context['sandbox']['country_id'];
            $reporting_entity->status = 1;
            $reporting_entity->created = time();
            $reporting_entity->changed = time();

            $sector = eitientity_organisation_get_sector_tid($item['sector']);
            if ($sector) {
              $reporting_entity->field_o_sector['und'][0]['target_id'] = $sector;
            }

            $comodity = eitientity_organisation_get_commodity_tid($item['commodities']);
            if ($comodity) {
              $reporting_entity->	field_o_commodities['und'][0]['target_id'] = $comodity;
            }

            $reporting_entity->field_stock_exchange_listing = $item['stock_exchange_listing'];
	          $reporting_entity->field_audited_financial_state = $item['audited_financial_statement'];
            $reporting_entity->field_payments_to_governments = $item['payment_to_goverment_report'];

            entity_save('organisation', $reporting_entity);
          }
        }
      }

      $context['sandbox']['company_progress']++;
      if ($context['sandbox']['company_progress'] > $context['sandbox']['company_max']) {
        $context['sandbox']['active_subsection'] = 'project';
      }
      break;
    case 'project':
      if (isset($reporting_entities_parsed_data['project'][$context['sandbox']['project_progress']])) {
        $item = $reporting_entities_parsed_data['project'][$context['sandbox']['project_progress']];

        $reporting_entity = entity_get_controller('organisation')->create();
        $reporting_entity->type = 'project';
        $reporting_entity->name = $item['full_project_name'];

        $reporting_entity->summary_data_id = $entity;
        $reporting_entity->country_id = $context['sandbox']['country_id'];
        $reporting_entity->status = 1;
        $reporting_entity->created = time();
        $reporting_entity->changed = time();

        $reporting_entity->field_legal_agreem_ref_num['und'][0]['value'] = $item['legal_Agreement_ref_number'];
        $reporting_entity->field_affiliated_companies_start['und'][0]['value'] = $item['affiliated_companies'];
	      $reporting_entity->field_commodities['und'][0]['value'] = $item['commodities'];
	      $reporting_entity->field_status['und'][0]['value'] = $item['status'];
	      $reporting_entity->field_production_volume['und'][0]['value'] = $item['production_volume'];
	      $reporting_entity->field_unit['und'][0]['value'] = $item['unit'];
	      $reporting_entity->field_production['und'][0]['value'] = $item['production_value'];
        $reporting_entity->field_currency['und'][0]['value'] = $item['currency'];

        entity_save('organisation', $reporting_entity);
      }

      $context['sandbox']['project_progress']++;
      break;
  }

  $context['sandbox']['progress']++;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Implements Batch process for Goverment revenues
 */
function eiti_sdi_batch_process_goverment_revenues_import($entity, $goverment_revenues_parsed_data, &$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['max'] = sizeof($goverment_revenues_parsed_data ) - 1;
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['entity_id'] = $entity;
    $context['sandbox']['goverment_revenues'] = $goverment_revenues_parsed_data;
  }

  if (isset($goverment_revenues_parsed_data[$context['sandbox']['progress']])) {
    $item = $goverment_revenues_parsed_data[$context['sandbox']['progress']];

    $entity_item = entity_get_controller('revenue_stream')->create();
    $entity_item->type = 'agency';
    $gfs = '';
    $gfs_parsed = explode(' ', $item['gfs_classification']);
    $gfs = end($gfs_parsed);
    $gfs = str_replace('(', '', $gfs);
    $gfs = str_replace(')', '', $gfs);
    $entity_item->gfs_code_id = $gfs;
    $entity_item->field_sector['und'][0]['value'] = $item['sector'];
    $entity_item->name = $item['revenue_stream_name'];
    $entity_item->report_status = 1;

    $organisation_id = '';
    $organisation_query = db_query("SELECT eo.id FROM {eiti_organisation} eo WHERE eo.type = :type and eo.name = :name ", array(":type" => 'goverment_entity', ':name' => $item['goverment_entity']))->fetchAll();

    if ($organisation_query) {
      $organisation_query = array_shift($organisation_query);

      if (isset($organisation_query->id)) {
        $organisation_id = $organisation_query->id;
      }
    }

    $entity_item->organisation_id = $organisation_id;
    $entity_item->revenue = preg_replace('/[^\d.]/', '', $item['revenue_value']);
    $entity_item->field_currency['und'][0]['value'] = $item['currency'];
    $entity_item->currency = $item['currency'];

    entity_save('revenue_stream', $entity_item);

    $entity = entity_load('summary_data', array($context['sandbox']['entity_id']));
    if ($entity) {
      $entity = array_shift($entity);
      $entity->field_sd_revenue_government['und'][] = array('target_id' => $entity_item->id);
      entity_save('summary_data', $entity);
    }
  }

  $context['sandbox']['progress']++;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Implements Batch process for Companies
 */
function eiti_sdi_batch_process_company_import($entity, $company_parsed_data, &$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['max'] = sizeof($company_parsed_data) - 1;
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['entity_id'] = $entity;
    $context['sandbox']['company'] = $company_parsed_data;
  }

  if (isset($company_parsed_data[$context['sandbox']['progress']])) {
    $item = $company_parsed_data[$context['sandbox']['progress']];

    $entity_item = entity_get_controller('revenue_stream')->create();
    $entity_item->type = 'company';
    $entity_item->report_status = 1;

    $organisation_id = '';
    $organisation_query = db_query("SELECT eo.id FROM {eiti_organisation} eo WHERE eo.type = :type and eo.name = :name ", array(":type" => 'company', ':name' => $item['company']))->fetchAll();

    if ($organisation_query) {
      $organisation_query = array_shift($organisation_query);

      if (isset($organisation_query->id)) {
        $organisation_id = $organisation_query->id;
      }
    }

    $entity_item->organisation_id = $organisation_id;
    $entity_item->field_goverment_entity['und'][0]['value'] = $item['goverment_entity'];
    $entity_item->name = $item['revenue_stream_name'];
    $entity_item->field_levied_on_project['und'][0]['value'] = $item['levied_on_project'];
    $entity_item->field_reported_by_project['und'][0]['value'] = $item['reported_by_project'];
    $entity_item->field_project_name['und'][0]['value'] = $item['project_name'];
    $entity_item->field_currency['und'][0]['value'] = $item['reporting_currency'];
    $entity_item->currency = $item['reporting_currency'];
    $entity_item->revenue = preg_replace('/[^\d.]/', '', $item['revenue_value']);
    $entity_item->field_revenue_value['und'][0]['value'] = preg_replace('/[^\d.]/', '', $item['revenue_value']);
    $entity_item->field_payment_made_in_kind['und'][0]['value'] = $item['payment_made_in_kind'];
    $entity_item->field_in_kind_volume['und'][0]['value'] = $item['in_kind_volume'];
    $entity_item->field_unit['und'][0]['value'] = $item['unit'];
    $entity_item->field_comments['und'][0]['value'] = $item['comments'];

    entity_save('revenue_stream', $entity_item);

    $entity = entity_load('summary_data', array($context['sandbox']['entity_id']));
    if ($entity) {
      $entity = array_shift($entity);
      $entity->field_sd_revenue_company['und'][] = array('target_id' => $entity_item->id);
      entity_save('summary_data', $entity);
    }
  }

  $context['sandbox']['progress']++;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Implements Batch process finish callback for Summary data import
 */
function eiti_sdi_batch_process_finish_callback($uid, $type, &$context) {
  $message = t('Summary data import completed');
  drupal_set_message($message);
}

/**
 * Create indicator item
 */
function eiti_sdi_create_indicator_item($values) {
  $indicator_id = NULL;
  $id = eiti_sdi_get_indicator_type_by_name($values['requirement_cell'], $values['parent']);

  if (!$id) {
    $id = eiti_sdi_create_indicator_type($values);
  }

  if ($id) {
    // Load indicator
    $indicator = entity_load('indicator', array($id));

    if ($indicator) {
      $indicator = array_shift($indicator);

      if ($indicator->type != 'group' && !empty($values['inclusion'])) {
        // Create indicator value there
        $entity_item = entity_get_controller('indicator_value')->create();

        $entity_item->indicator_id = $indicator->id;

        switch ($indicator->type) {
          case 'boolean':
            $entity_item->value_boolean = $values['inclusion'];
            break;
          case 'numeric':
            $entity_item->value_numeric = $values['inclusion'];
            break;
          case 'text':
            $entity_item->value_text = $values['inclusion'];
            break;
          case 'reporting_type':

            $value_reporting_type = '';

            switch ($values['inclusion']) {
              case 'Yes, systematically disclosed':
                $value_reporting_type = 'EITIENTITY_INDICATOR_VALUE_VALUE_SYSTEMATICALLY_DISCLOSED';
                break;
              case 'Yes, through EITI reporting':
                $value_reporting_type = 'EITIENTITY_INDICATOR_VALUE_VALUE_THROUGH_EITI_REPORTING';
                break;
              case 'Not applicable':
                $value_reporting_type = 'EITIENTITY_INDICATOR_VALUE_VALUE_NOT_APPLICABLE';
                break;
              case 'Not available':
                $value_reporting_type = 'EITIENTITY_INDICATOR_VALUE_VALUE_NOT_AVAILABLE';
                break;
            }

            $entity_item->value_reporting_type = $value_reporting_type;
            break;
        }

        if (!empty($values['source'])) {
          $values['source'] = trim($values['source']);

          if (strlen($values['source']) < 32) {
            $entity_item->value_unit = $values['source'];
          } else {
            $values['source'] = substr($values['source'], 0, 255);
            $entity_item->source = $values['source'];
          }
        }

        entity_save('indicator_value', $entity_item);
        $indicator_id = $entity_item->id;
      }
    }
  }

  return $indicator_id;
}

/**
 * Get indicator type by name
 */
function eiti_sdi_get_indicator_type_by_name($name, $parent) {
  $id = NULL;

  if ($name) {

    if ($parent) {
      $parent_id_query = db_query("SELECT ei.id FROM {eiti_indicator} ei WHERE ei.name = :name", array(':name' => $parent))->fetchAll();

      if ($parent_id_query) {
        $parent_id_result = array_shift($parent_id_query);

        if (isset($parent_id_result->id)) {
          $query = db_query("SELECT ei.id FROM {eiti_indicator} ei WHERE ei.name = :name AND ei.parent = :parent", array(':name' => $name, ':parent' => $parent_id_result->id))->fetchAll();
        }
      }
    } else {
      $query = db_query("SELECT ei.id FROM {eiti_indicator} ei WHERE ei.name = :name", array(':name' => $name))->fetchAll();
    }

    if (!empty($query)) {
      $result = array_shift($query);
      if (isset($result->id)) {
        $id = $result->id;
      }
    }
  }

  return $id;
}



/**
 * Implements indicator type by source data
 */
function eiti_sdi_create_indicator_type($values) {
  $id = NULL;

  if (empty($values['parent'])) {
    $type = 'group';
  } else {
    $type = eiti_sdi_get_indicator_data_type_by_value($values['inclusion']);
  }

  if ($type) {
    $entity_item = entity_get_controller('indicator')->create();
    $entity_item->type = $type;
    $entity_item->name = $values['requirement_cell'];

    if (!empty($values['parent'])) {
      $parent_id = eiti_sdi_get_indicator_type_by_name($values['parent'], '');

      if ($parent_id) {
        $entity_item->parent = $parent_id;
      }
    }

    $entity_item->status = 1;
    $entity_item->created = time();

    entity_save('indicator', $entity_item);
    $id = $entity_item->id;
  }

  return $id;
}

/**
 * Parse indicator type by value
 */
function eiti_sdi_get_indicator_data_type_by_value($value) {

  if (empty($value)) {
    return NULL;
  }

  if ($value == 'Yes, systematically disclosed' || $value == 'Yes, through EITI reporting'
    || $value == 'Not available' || $value == 'Not applicable') {
    return 'reporting_type';
  }

  if (is_numeric($value)) {
    return 'numeric';
  }

  if (is_bool($value)) {
    return 'boolean';
  }

  return 'text';
}
