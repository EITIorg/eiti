<?php

/**
 * Page callback for summary data excel downloading.
 */
function eiti_excel_summary_data_page() {
  libraries_load('PHPExcel');
  $excel = new PHPExcel();

  // TODO: comment out front page sheet as it's not included in phase 1 and work on sheets 2-3.

  // Sheets.
  $excel->getSheet()->setTitle('Front page'); // PHPExcel always creates one sheet (index 0).
  $excel->createSheet(1)->setTitle('Country Data');
  $excel->createSheet(2)->setTitle('Company Data');

  // Sheet 1 content.
  $sheet = $excel->getSheet();
  $sheet->getStyle('1:2')->getFont()->setBold(TRUE);
  $sheet->setCellValueByColumnAndRow(1, 2, 'Quick Summary Tool for EITI Reports');
  $sheet->setCellValueByColumnAndRow(1, 4, 'Thank you for your interest in EITI data.');
  $sheet->setCellValueByColumnAndRow(1, 5, 'This data file has been exported to compare EITI data according to your selected parameters.');
  $sheet->setCellValueByColumnAndRow(1, 7, 'This file is not comprehensive, but displays information in a format to easily compare EITI data. To view and access more comprehensive EITI data, please see the links below.');
  $sheet->setCellValueByColumnAndRow(1, 8, 'EITI Summary Data:');
  $sheet->setCellValueByColumnAndRow(2, 8, 'https://eiti.org/summary-data');
  $sheet->setCellValueByColumnAndRow(1, 9, 'The information is collected to our websites through EITI Summary Data, which implementing countries fill out using the specified Summary Data Templates found here:');
  $sheet->setCellValueByColumnAndRow(1, 10, 'EITI Summary Data Templates:');
  $sheet->setCellValueByColumnAndRow(2, 10, 'https://eiti.org/summary-data-template');
  $sheet->getStyle('1:12')->getFont()->setBold(TRUE);
  $sheet->setCellValueByColumnAndRow(1, 12, 'Parameters selected:');
  $sheet->setCellValueByColumnAndRow(1, 13, 'Countries:');
  $sheet->setCellValueByColumnAndRow(2, 13, 'Year(s):');

  // Output.
  header('Content-Type: application/vnd.ms-excel');
  header('Content-Disposition: attachment;filename="EITI - summary data.xls"');
  header('Cache-Control: max-age=0');
  $writer = PHPExcel_IOFactory::createWriter($excel, 'Excel5');
  $writer->save('php://output');
}
