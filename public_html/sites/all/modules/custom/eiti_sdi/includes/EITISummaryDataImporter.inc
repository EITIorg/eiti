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

    // Process Batch for iterating Indicators
    $this->processIndicatorBatch($entity, $disclosure_parsed_data_items, $max);
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
  private function processIndicatorBatch($entity, $disclosure_parsed_data, $max) {
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
      ),
      'finished' => 'eiti_sdi_batch_process_finish_callback',
    );
    batch_set($batch);
    //batch_process('admin/content/summary_data');
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
