<?php
/**
 * @file
 * eitifiles.file_type.inc
 */

/**
 * Implements hook_file_default_types().
 */
function eitifiles_file_default_types() {
  $export = array();

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'report';
  $file_type->label = 'Summary Data Report';
  $file_type->description = 'Use this file type to upload reports / summary data spreadsheet files. Note: all reports will be imported into the system, sooner or later.';
  $file_type->mimetypes = array(
    0 => 'application/vnd.ms-excel',
    1 => 'application/vnd.ms-excel.addin.macroEnabled.12',
    2 => 'application/vnd.ms-excel.sheet.binary.macroEnabled.12',
    3 => 'application/vnd.ms-excel.sheet.macroEnabled.12',
    4 => 'application/vnd.ms-excel.template.macroEnabled.12',
    5 => 'application/vnd.oasis.opendocument.spreadsheet',
    6 => 'application/vnd.oasis.opendocument.spreadsheet-template',
    7 => 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet',
    8 => 'application/vnd.openxmlformats-officedocument.spreadsheetml.template',
  );
  $export['report'] = $file_type;

  return $export;
}
