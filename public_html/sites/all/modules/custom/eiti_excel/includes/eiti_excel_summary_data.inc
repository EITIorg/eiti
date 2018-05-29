<?php

/**
 * Page callback for summary data excel downloading.
 */
function eiti_excel_summary_data_page() {
  libraries_load('PHPExcel');
  $excel = new PHPExcel();


  // Sheet 1 (front page).
  /*$sheet = $excel->getSheet();
  $sheet->setTitle('Front page'); // PHPExcel always creates one sheet (index 0).
  $sheet->getStyle('B4:B10')->getFont()->setItalic(TRUE);
  $sheet->getStyle('B2')->getFont()->setBold(TRUE);
  $sheet->setCellValueByColumnAndRow(1, 2, 'Quick Summary Tool for EITI Reports');
  $sheet->setCellValueByColumnAndRow(1, 4, 'Thank you for your interest in EITI data.');
  $sheet->setCellValueByColumnAndRow(1, 5, 'This data file has been exported to compare EITI data according to your selected parameters.');
  $sheet->setCellValueByColumnAndRow(1, 7, 'This file is not comprehensive, but displays information in a format to easily compare EITI data. To view and access more comprehensive EITI data, please see the links below.');
  $sheet->setCellValueByColumnAndRow(1, 8, 'EITI Summary Data:');
  $sheet->setCellValueByColumnAndRow(2, 8, 'https://eiti.org/summary-data');
  $sheet->setCellValueByColumnAndRow(1, 9, 'The information is collected to our websites through EITI Summary Data, which implementing countries fill out using the specified Summary Data Templates found here:');
  $sheet->setCellValueByColumnAndRow(1, 10, 'EITI Summary Data Templates:');
  $sheet->setCellValueByColumnAndRow(2, 10, 'https://eiti.org/summary-data-template');
  $sheet->getStyle('B12')->getFont()->setBold(TRUE);
  $sheet->setCellValueByColumnAndRow(1, 12, 'Parameters selected:');
  $sheet->getStyle('B13:C13')->getFont()->setItalic(TRUE);
  $sheet->setCellValueByColumnAndRow(1, 13, 'Countries:');
  $sheet->setCellValueByColumnAndRow(2, 13, 'Year(s):');*/


  // Get all the summary_data entries from the database.
  $summary_data_db = db_select('eiti_summary_data', 'sd')
    ->condition('sd.status', 1)
    ->fields('sd')
    ->execute()
    ->fetchAll();

  // Get the maximum number of summary data file links.
  $sd_links_subquery = db_select('field_data_field_sd_file_links', 'sd_fl')
    ->groupBy('sd_fl.entity_id');
  $sd_links_subquery->addExpression('COUNT(*)', 'count');
  $sd_links_query = db_select($sd_links_subquery);
  $sd_links_query->addExpression('MAX(count)', 'max');
  $sd_links_max = $sd_links_query->execute()->fetchField();

  $row = 5;
  $extras = array(
    'sd_links_max' => $sd_links_max,
    'row' => $row,
  );

  eiti_excel_add_country_sheet($excel, $extras);
  eiti_excel_add_company_sheet($excel, $extras);

  foreach ($summary_data_db as $s_data) {
    // Get summary data from the API.
    // Use a direct method since http requests are unnecessary overhead.
    $sd_api = eiti_api_restful_get_result(array('q' => "api/v1.0/summary_data/$s_data->id"));
    $sd_api = reset($sd_api);
    if ($sd_api) {
      $sd_entity = entity_load_single('summary_data', $s_data->id);
      $sd_entity_emw = entity_metadata_wrapper('summary_data', $sd_entity);
      $sd_data = array(
        'api' => $sd_api,
        'entity' => $sd_entity,
        'entity_emw' => $sd_entity_emw,
      );
      $extras['row'] = $row;
      eiti_excel_add_country_data($excel, $sd_data, $extras);
      eiti_excel_add_company_data($excel, $sd_data, $extras);
      $row++;
    }
    if ($row > 5) {
      break; // TODO: remove when done testing.
    }
  }


  // Output.
  header('Content-Type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="EITI - summary data.xls"');
  header('Cache-Control: max-age=0');
  $writer = PHPExcel_IOFactory::createWriter($excel, 'Excel5');
  $writer->save('php://output');
}

/**
 * Add country data sheet with titles.
 */
function eiti_excel_add_country_sheet(\PHPExcel $excel, $extras) {
  //$excel->createSheet(1);
  //$sheet = $excel->getSheet(1);
  $sheet = $excel->getSheet();
  $sheet->setTitle('Country Data');

  // Titles.
  $sheet->getStyle('A1:A2')->getFont()->setBold(TRUE);
  $sheet->getStyle('A1:A2')->getFont()->setItalic(TRUE);
  $sheet->setCellValue('A1','Sections');
  $sheet->setCellValue('A2','Indicator Level 1');
  $sheet->getStyle('A3:DL4')->getFont()->setItalic(TRUE);
  $sheet->setCellValue('A3','Indicator Level 2');
  $sheet->setCellValue('A4','Unit / Description');
  $sheet->getStyle('B1:DL1')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
  $sheet->getStyle('B1:DL1')->getFont()->setBold(TRUE);
  $sheet->mergeCells('B1:X1'); // TODO: account for links and possibly other data length.
  $sheet->setCellValue('B1','About');
  $sheet->setCellValue('B2','Implementing country');
  $sheet->setCellValue('B4','Text');
  $sheet->mergeCells('C2:D2');
  $sheet->setCellValue('C2','Fiscal Year Covered in the Report');
  $sheet->setCellValue('C3','Start Date');
  $sheet->setCellValue('C4','Date');
  $sheet->setCellValue('D3','End Date');
  $sheet->setCellValue('D4','Date');
  $sheet->setCellValue('E2','Independent Administrator');
  $sheet->setCellValue('E4','Text');
  $sheet->setCellValue('F2','EITI Report published on');
  $sheet->setCellValue('F4','Date');
  $sheet->setCellValue('F4','Date');
  $sheet->mergeCells('G2:J2');
  $sheet->setCellValue('G2','Sectors Covered');
  $sheet->setCellValue('G3','Oil');
  $sheet->setCellValue('G4','Text');
  $sheet->setCellValue('H3','Gas');
  $sheet->setCellValue('H4','Text');
  $sheet->setCellValue('I3','Mining');
  $sheet->setCellValue('I4','Text');
  $sheet->setCellValue('J3','Other');
  $sheet->setCellValue('J4','Text');

  // Add link titles.
  // First one in column 10 (K) - columns start with 0, rows with 1.
  $column = 10;
  $column_end = $column + $extras['sd_links_max'] - 1;
  $sheet->getStyleByColumnAndRow($column, 2, $column_end, 2)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
  $sheet->mergeCellsByColumnAndRow($column, 2, $column_end, 2);
  $sheet->setCellValueByColumnAndRow($column, 2, 'Web links to EITI Report, on the national EITI website');
  for ($i = $column; $i <= $column_end; $i++) {
    $sheet->setCellValueByColumnAndRow($i, 4, 'Hyperlink');
  }

  // Get the right column after all the added links.
  $column = $column + $extras['sd_links_max'];

  $sheet->setCellValueByColumnAndRow($column, 2, 'Number of reporting government entities');
  $sheet->setCellValueByColumnAndRow($column, 4, 'Number');
  $column++;
  $sheet->setCellValueByColumnAndRow($column, 2, 'Number of reporting companies');
  $sheet->setCellValueByColumnAndRow($column, 4, 'Number');
  $column++;
  $column_end = $column + 1;
  $sheet->getStyleByColumnAndRow($column, 2, $column_end, 2)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
  $sheet->mergeCellsByColumnAndRow($column, 2, $column_end, 2);
  $sheet->setCellValueByColumnAndRow($column, 2, 'Reporting currency');
  $sheet->setCellValueByColumnAndRow($column, 3, 'ISO currency code');
  $sheet->setCellValueByColumnAndRow($column, 4, 'Text');
  $sheet->setCellValueByColumnAndRow($column_end, 3, 'Conversion rate utilised.  US $ 1 =');
  $sheet->setCellValueByColumnAndRow($column_end, 4, 'Number');
  $column = $column_end + 1;
}

/**
 * Add country data.
 */
function eiti_excel_add_country_data(\PHPExcel $excel, $sd_data, $extras) {
  //$sheet = $excel->getSheet(1);
  $sheet = $excel->getSheet();
  $row = $extras['row'];

  $country = $sd_data['api']['country']['label'] . '[id:' . $sd_data['api']['country']['id'] . ']';
  $sheet->setCellValue("B$row", $country);
  $sheet->setCellValue("C$row", date('Y-m-d', $sd_data['entity']->year_start));
  $sheet->setCellValue("D$row", date('Y-m-d', $sd_data['entity']->year_end));
  $sheet->setCellValue("E$row", $sd_data['entity_emw']->field_sd_independent_admin->value());
  $sheet->setCellValue("F$row", date('Y-m-d', $sd_data['entity']->published));
  $sheet->setCellValue("G$row", ($sd_data['api']['sector_oil'] ? 'Yes' : 'No'));
  $sheet->setCellValue("H$row", ($sd_data['api']['sector_gas'] ? 'Yes' : 'No'));
  $sheet->setCellValue("I$row", ($sd_data['api']['sector_mining'] ? 'Yes' : 'No'));
  $sheet->setCellValue("J$row", ($sd_data['api']['sector_other'] ? 'Yes' : 'No'));

  // Add links.
  // First one in column 10 (K) - columns start with 0, rows with 1.
  $column = 10;
  if (isset($sd_data['api']['links']) && $sd_data['api']['links']) {
    $links_column = $column;
    foreach ($sd_data['api']['links'] as $link) {
      $sheet->setCellValueByColumnAndRow($links_column, $row, $link);
      $links_column++;
    }
  }

  // Get the right column after all the added links.
  $column = $column + $extras['sd_links_max'];

  $sheet->setCellValueByColumnAndRow($column, $row, $sd_data['api']['government_entities_nr']);
  $column++;
  $sheet->setCellValueByColumnAndRow($column, $row, $sd_data['api']['company_entities_nr']);
  $column++;
  $sheet->setCellValueByColumnAndRow($column, $row, $sd_data['entity']->currency_code);
  $column++;
  $sheet->setCellValueByColumnAndRow($column, $row, $sd_data['entity']->currency_rate);
}

/**
 * Add company data sheet with titles.
 */
function eiti_excel_add_company_sheet(\PHPExcel $excel, $extras) {
  //$excel->createSheet(2);
  //$sheet = $excel->getSheet(2);
  $excel->createSheet(1);
  $sheet = $excel->getSheet(1);
  $sheet->setTitle('Company Data');

  // Titles.
}

/**
 * Add company data.
 */
function eiti_excel_add_company_data(\PHPExcel $excel, $sd_data, $extras) {
  //$sheet = $excel->getSheet(2);
  $sheet = $excel->getSheet(1);
}
