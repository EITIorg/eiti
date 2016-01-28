<?php

/**
 * @file
 * Holds MigrateSource implementation for importing spreadsheet reports.
 * Inspired from the original spreadsheet.inc from migrate module.
 */

// Source types.
define('EITI_SOURCE_SUMMARY_DATA', 'summary_data');
define('EITI_SOURCE_INDICATOR_VALUE', 'indicator_value');
define('EITI_SOURCE_COMPANY', 'company');
define('EITI_SOURCE_REVENUE_GOVERNMENT', 'revenue_government');
define('EITI_SOURCE_REVENUE_COMPANY', 'revenue_company');

// Sheet types.
define('EITI_SHEET_TYPE_ABOUT', 'about');
define('EITI_SHEET_TYPE_CONTEXTUAL', 'context');
define('EITI_SHEET_TYPE_REVENUES', 'revenues');


/**
 * This is a tweaked version, adjusted to multiple sheets, specifically for the
 * EITI import process.
 */
class EITIMigrateSourceSpreadsheet extends MigrateSource {
  /**
   * All of the file paths.
   * @var array
   */
  protected $filePaths;

  /**
   * All of the processed file paths.
   * @var array
   */
  protected $filePathsProcessed;

  /**
   * All the file objects.
   */
  protected $files;

  /**
   * Currently processed file object.
   */
  protected $currentFile;

  /**
   * PHPExcel object for storing the workbook data.
   *
   * @var PHPExcel
   */
  protected $currentWorkbook;

  /**
   * Report Version
   *
   * @var string
   */
  protected $currentReportVersion;

  /**
   * PHPExcel object for storing the worksheet data.
   *
   * @var PHPExcel_Worksheet
   */
  protected $currentWorksheet;

  /**
   * Current position in the worksheet.
   *
   * @var array
   */
  protected $currentPosition;

  /**
   * List of available source fields.
   *
   * @var array
   */
  protected $fields = array();

  /**
   * Defines the current import source type.
   * @var constant
   */
  protected $sourceType;

  /**
   * Parsed rows, temporary storage.
   * @var array
   */
  protected $migrateRows;

  /**
   * Migration Row.
   *
   * @var int
   */
  protected $migrateRowIndex;

  /**
   * Migration Row Count.
   *
   * @var int
   */
  protected $migrateRowsCountInFile;

  /**
   * Migration Row Count.
   *
   * @var int
   */
  protected $migrateRowsInTotal;

  /**
   * Simple initialization.
   *
   * @param string|array $paths
   *   The path to the source file or an array of paths to source files.
   * @param constant
   *   Please specify what type of data are you looking for, in these sheets.
   * @param array $options
   *   Options inherited from MigrateSource.
   */
  public function __construct($paths, $source_type, array $options = array()) {
    parent::__construct($options);

    // Normalize, make sure it's stored as an array.
    if (!is_array($paths)) {
      $this->filePaths = array($paths);
    }
    else {
      // We like nicely reseted keys, because those will be used for walking.
      $this->filePaths = array_values($paths);
    }

    // The whole process depends on this variable.
    $this->sourceType = $source_type;

    // To be memory-efficient, we don't want to load all the files on
    // the construct.
  }

  /**
   * Loads the specified spreadsheet.
   *
   * @param $path
   *   Path to the spreadsheet that needs to be loaded.
   *
   * @return bool
   *   Indicates if the spreadsheet was loaded successfully or not.
   */
  public function loadSpreadsheet($path) {
    // Check that the file exists.
    if (!file_exists($path)) {
      Migration::displayMessage(t('The file !filename does not exist.', array('!filename' => $path)));
      return FALSE;
    }

    // Check that required modules are enabled.
    if (!module_exists('libraries')) {
      Migration::displayMessage(t('The Libraries API module is not enabled.'));
      return FALSE;
    }
    if (!module_exists('phpexcel')) {
      Migration::displayMessage(t('The PHPExcel module is not enabled.'));
      return FALSE;
    }

    $library = libraries_load('PHPExcel');
    if (empty($library['loaded'])) {
      Migration::displayMessage(t('The PHPExcel library could not be found.'));
      return FALSE;
    }

    // Load the workbook.
    try {
      // Identify the type of the input file.
      $type = PHPExcel_IOFactory::identify($path);
      // Create a new Reader of the file type.
      $reader = PHPExcel_IOFactory::createReader($type);
      // Advise the Reader that we want to load all the sheets.
      $reader->setLoadAllSheets();
      // Load the source file.
      $this->currentWorkbook = $reader->load($path);
      // We also want to save the file, if successful, as current.
      $this->currentFile = $path;
      // Also we want to fetch the version of the report.
      $this->updateReportVersion();
    }
    catch (Exception $e) {
      Migration::displayMessage(t('Error loading file: %message', array('%message' => $e->getMessage())));
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Unloads the specified workbook (by default, the current workbook).
   *
   * @param $workbook
   *   Workbook that you wish to unload (disconnect).
   *
   * @return void
   */
  public function unloadSpreadsheet($workbook = NULL) {
    if (!isset($workbook) && isset($this->currentWorkbook)) {
      $this->currentWorkbook->disconnectWorksheets();
      unset($this->currentWorkbook);
    }
    elseif (isset($workbook)) {
      $workbook->disconnectWorksheets();
    }
  }


  /**
   * Returns a list of fields available to be mapped from the source query.
   *
   * @return array
   *   Keys: machine names of the fields (to be passed to addFieldMapping).
   *   Values: Human-friendly descriptions of the fields.
   */
  public function fields() {
    $this->fields = self::generateFields($this->sourceType);
    return $this->fields;
  }

  /**
   * Returns a count of all available source records.
   */
  public function computeCount() {
    while ($this->getNextFile()) {
      $this->parseFile();
    }
    $this->unloadSpreadsheet();
    return $this->migrateRowsInTotal;
  }

  /**
   * Implements MigrateSource::performRewind().
   *
   * @return void
   */
  public function performRewind() {
    $this->resetPosition();
    // Make sure we're on the 1st file-path.
    $this->filePathsProcessed = array();
    $this->migrateRowIndex = 0;
    $this->migrateRowsInTotal = 0;
    unset($this->migrateRows);
  }

  /**
   * Just reset the current position.
   */
  protected function resetPosition() {
    $this->currentPosition = array(
      'column' => 0,
      'row' => 0,
    );
  }

  /**
   * Implements MigrateSource::getNextRow().
   *
   * @return null|object
   */
  public function getNextRow() {
    // In case we're just starting.
    if (!$this->migrateRowsInTotal || $this->migrateRowsInTotal == 0) {
      if ($this->getNextFile()) {
        $this->parseFile();
      }
    }

    // Make sure we have a loaded and parsed file.
    if ($this->migrateRowIndex < $this->migrateRowsInTotal) {
        $row_values = array();

        // Get the parsed row.
        $row_values = $this->getParsedRow($this->migrateRowIndex);
        $this->migrateRowIndex++;

        return (object) $row_values;
    }
    else {
      // Make sure we have a loaded file.
      if ($this->getNextFile()) {
        $this->parseFile();
        return $this->getNextRow();
      }
      else {
        $this->unloadSpreadsheet();
        return FALSE;
      }
    }
  }

  /**
   * Use this if we reached EOF on current file and we want to switch to the next file.
   *
   * @return bool
   *   Returns TRUE of we have switched to the next file and FALSE if we're out of files
   *   or if we have encountered some errors.
   */
  protected function getNextFile() {
    // Unload whatever we're having.
    $this->unloadSpreadsheet();

    // Get 1st path, if we're just starting,
    // otherwise get the next file.
    if (empty($this->currentFile)) {
      $paths = $this->filePaths;
      $path = array_shift($paths);
    }
    else {
      $current_index = array_search($this->currentFile, $this->filePaths);
      if ($current_index !== FALSE) {
        // There are two cases: we've processed all files or not.
        if (count($this->filePaths) == ($current_index + 1)) {
          return FALSE;
        }
        else {
          $path = $this->filePaths[$current_index + 1];
        }
      }
    }

    // Now that we know what file we need, load it.
    if ($this->loadSpreadsheet($path)) {
      $this->resetPosition();

      return TRUE;
    }
    return FALSE;
  }

  /**
   * We might want to use this elsewhere.
   * @param $type
   *   Source Type.
   * @return array
   *   Array of fields.
   */
  static public function generateFields($type) {
    $fields = array();
    $fields['unmapped'] = t('Missed unmapped data that we still extract.');
    $fields['file'] = t('File Path: Mainly for logging reasons.');
    $fields['summary_id'] = t('Unique ID of this Summary Data (hash: File Path)');

    switch ($type) {
      case EITI_SOURCE_SUMMARY_DATA:
        $fields['country_name'] = t('Country Name');
        $fields['start_date'] = t('Start Date');
        $fields['end_date'] = t('End Date');
        $fields['independent_administrator'] = t('Independent Administrator');
        $fields['publish_date'] = t('Date that the EITI Report was published (i.e., made publicly available)');
        $fields['sectors:oil'] = t('Sectors covered: Oil (bool)');
        $fields['sectors:gas'] = t('Sectors covered: Gas (bool)');
        $fields['sectors:mining'] = t('Sectors covered: Mining (bool)');
        $fields['sectors:other'] = t('Sectors covered: Other (array, label [text] => value [text])');
        $fields['web_links'] = t('All the web links to files (array, array of URLs)');
        $fields['number:reporting_gov'] = t('Number of reporting government entities (int)');
        $fields['number:reporting_comp'] = t('Number of reporting companies (int)');
        $fields['currency:iso'] = t('Reporting Currency: ISO');
        $fields['currency:conversion'] = t('Reporting Currency: Conversion rate utilised. (US $ 1 = ?)');
        $fields['dissaggregation:revenue_stream'] = t('Disaggregtion of Data: By Revenue Stream (bool)');
        $fields['dissaggregation:company'] = t('Disaggregtion of Data: By Company (bool)');
        $fields['dissaggregation:project'] = t('Disaggregtion of Data: By Project (bool)');
        $fields['contact:name'] = t('Contact details to person who has completed this template: Name (text)');
        $fields['contact:organization'] = t('Contact details to person who has completed this template: Organization (text)');
        $fields['contact:email'] = t('Contact details to person who has completed this template: Email (text)');
        break;

      case EITI_SOURCE_INDICATOR_VALUE:
        $fields['row_id'] = t('Unique ID of the Row.');
        $fields['group'] = t('The group column value.');
        $fields['subgroup'] = t('The subgroup column value.');
        $fields['entry'] = t('The entry / value of the indicator.');
        $fields['unit'] = t('Unites in which those are measured.');
        $fields['source'] = t('Direct URL to source, or to section in EITI Report.');
        $fields['comment'] = t('Comments.');
        break;

      case EITI_SOURCE_COMPANY:
        $fields['column_id'] = t('Column ID.');
        $fields['company_name'] = t('Company Name.');
        $fields['company_id'] = t('Company Identification Number.');
        $fields['commodity'] = t('Commodity the company works with.');
        break;

      case EITI_SOURCE_REVENUE_GOVERNMENT:
        $fields['row_id'] = t('Unique ID of the Row.');
        $fields['gfs_id'] = t('GFS ID of the GFS Code.');
        $fields['gfs_status'] = t('GFS Code Status - whether it is included or not in the report.');
        $fields['revenue_stream'] = t('Name of the Revenue Stream in the country.');
        $fields['organization'] = t('Name of Receiving Government organization.');
        $fields['revenue'] = t('Revenues disclosed by the Government.');
        break;

      case EITI_SOURCE_REVENUE_COMPANY:
        $fields['column_id'] = t('Column ID of the queries company.');
        $fields['position_id'] = t('Unique ID of the Row and Column (in form of row:column).');
        $fields['gfs_id'] = t('GFS ID of the GFS Code.');
        $fields['gfs_status'] = t('GFS Code Status - whether it is included or not in the report.');
        $fields['revenue_stream'] = t('Name of the Revenue Stream in the country.');
        $fields['company'] = t('Name of Receiving Government organization.');
        $fields['revenue'] = t('Revenues disclosed by the Government.');
        break;
    }
    return $fields;
  }

  /**
   * Use this function to fetch the report version.
   * Fetching rows later might depend on this one.
   */
  protected function updateReportVersion() {
    $version = '';

    if ($this->currentWorkbook) {
      // We won't update the currentPosition, we'll just jump directly to
      // identifying the report version.
      $sheetIntro = $this->currentWorkbook->getSheetByName('Introduction');
      if (empty($sheetIntro)) {
        $sheetIntro = $this->currentWorkbook->getSheet(0);
      }
      $highestRow = $sheetIntro->getHighestRow();
      $highestColumn = $sheetIntro->getHighestColumn();
      $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);

      // Iterate through and get the values, then preg_match'em.
      for ($row = 0; $row <= $highestRow; ++$row) {
        for ($col = 0; $col <= $highestColumnIndex; ++$col) {
          $cellValue = trim($sheetIntro->getCellByColumnAndRow($col, $row)->getValue());
          if (preg_match('/(v|Version|Version )([0-9]+(\.[0-9]+))+/', $cellValue, $matches)) {
            $version = (isset($matches[2])) ? $matches[2] : $matches[0];
            // If we found our version, break from 2 for loops.
            break 2;
          }
        }
      }
    }
    $this->currentReportVersion = $version;
  }

  /**
   * Small function that generates unique ID.
   * At this moment we take into account 3 things:
   *  - File Path.
   *  (- File Version.)
   *  (- Last Date it was Updated.)
   */
  protected function getUniqueId() {
    $uniqueId = '';
    if ($this->currentWorkbook) {
      $uniqueArray[] = $this->currentFile;
      // $uniqueArray[] = $this->currentReportVersion;
      // $uniqueArray[] = $this->currentWorkbook->getProperties()->getModified();
      if ($this->currentWorkbook) {
        return md5(implode(':', $uniqueArray));
      }
    }
    return FALSE;
  }

  /**
   * Helper function that identifies how many entities are in the file.
   */
  protected function getMigrationRowsCountInFile() {
    // If we have, just return the value.
    if (!empty($this->migrateRowsCountInFile)) {
      return $this->migrateRowsCountInFile;
    }
    // If we don't, return 0.
    return 0;
  }

  /**
   * Main parsing function, it passes through the worksheet and returns the
   * so-called "Migration Rows" (arrays of data), that later is used for
   * mapping.
   */
  protected function parseFile() {
    switch ($this->sourceType) {
      case EITI_SOURCE_SUMMARY_DATA:
        // Get the sheet.
        $aboutSheet = $this->getSheet(EITI_SHEET_TYPE_ABOUT);

        // If we have our sheet, by default set the count of Summary Data rows
        // to 1, as we have 1 summary data per file.
        if (!empty($aboutSheet)) {
          // Now let's parse the file.
          $highestRow = $aboutSheet->getHighestRow();
          $highestColumn = $aboutSheet->getHighestColumn();
          $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);

          // Defaults.
          $start_row = 4;
          $start_column = 1;

          // Find the "Entry" (Adjusting defaults).
          if ($position = $this->findPositionInSheet($aboutSheet, array('Entry'))) {
            $start_row = $position['row'] + 1;
            $start_column = $position['column'] - 2;
          }

          // Now let's walk through the right cells.
          $migrationRow = array();
          $lastRememberedGroup = '';
          for ($row = $start_row; $row < $highestRow; $row++) {
            $groupCellValue = trim($aboutSheet->getCellByColumnAndRow($start_column, $row)->getValue());
            $subgroupCellValue = trim($aboutSheet->getCellByColumnAndRow($start_column + 1, $row)->getValue());
            $valueCellValue = trim($aboutSheet->getCellByColumnAndRow($start_column + 2, $row)->getCalculatedValue());

            // Before we do the lookup, let's make sure that the group is correct.
            // If it's empty (or "add rows ..."), we use the previous group-value.
            if ($groupCellValue == '' || stripos($groupCellValue, 'add rows')) {
              $groupCellValue = $lastRememberedGroup;
            }
            else {
              $lastRememberedGroup = $groupCellValue;
            }

            // Now, finally, let's do the look-up and assign the value.
            $field = $this->lookupField($groupCellValue, $subgroupCellValue);
            if (!empty($valueCellValue)) {
              $migrationRow[$field][] = $valueCellValue;
            }
          }

          // Normalize date values.
          $dateFields = array('start_date', 'end_date', 'publish_date');
          foreach ($dateFields as $dateField) {
            // Screw it, it's just 1 value anyway for them.
            $excelDate = $migrationRow[$dateField][0];
            $phpDate = PHPExcel_Shared_Date::ExcelToPHP($excelDate);
            $migrationRow[$dateField] = $phpDate;
          }

          // Create unique id.
          $migrationRow['summary_id'] = $this->getUniqueId();
          $migrationRow['file'] = $this->currentFile;
          $this->migrateRows[] = $migrationRow;

          $this->migrateRowsCountInFile = 1;
          $this->migrateRowsInTotal++;
        }
        else {
          unset($this->migrateRowsCountInFile);
        }
        break;

      case EITI_SOURCE_INDICATOR_VALUE:
        // Get our sheet.
        $contextualSheet = $this->getSheet(EITI_SHEET_TYPE_CONTEXTUAL);
        if (!empty($contextualSheet)) {
          // Now let's parse the file.
          $highestRow = $contextualSheet->getHighestRow();
          $highestColumn = $contextualSheet->getHighestColumn();
          $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
          $this->migrateRowsCountInFile = 0;

          // Defaults.
          $start_row = 4;
          $start_column = 1;

          // Find the "Entry" and break out (Adjusting defaults).
          // Find the "Entry" (Adjusting defaults).
          if ($position = $this->findPositionInSheet($contextualSheet, array('Entry'))) {
            $start_row = $position['row'] + 1;
            $start_column = $position['column'] - 2;
          }

          // Also we have to make sure that there's a "Unit" column.
          $unitColumnFound = ($this->findPositionInSheet($contextualSheet, array('unit')) !== FALSE);
          if (!$unitColumnFound) {
            Migration::displayMessage(t('Indicator Values do not have the UNIT COLUMN.<br/>File: !file', array(
              '!file' => $this->currentFile,
            )));
            return FALSE;
          }

          // Now let's walk through the right cells.
          $lastRememberedGroup = '';
          for ($row = $start_row; $row < $highestRow; $row++) {
            $migrationRow = array();
            $groupCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column, $row)->getValue());
            $subgroupCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column + 1, $row)->getValue());
            $valueCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column + 2, $row)->getCalculatedValue());
            $unitCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column + 3, $row)->getValue());
            $sourceCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column + 4, $row)->getValue());
            $commentCellValue = trim($contextualSheet->getCellByColumnAndRow($start_column + 5, $row)->getValue());

            // Before we do the lookup, let's make sure that the group is correct.
            // If it's empty (or "add rows ..."), we use the previous group-value.
            if ($groupCellValue == '' || (stripos($groupCellValue, 'modify entry') !== FALSE)
              || (stripos($groupCellValue, 'add rows') !== FALSE)
              || (stripos($groupCellValue, 'add/remove') !== FALSE)) {
              $groupCellValue = $lastRememberedGroup;
            }
            else {
              $lastRememberedGroup = $groupCellValue;
            }

            // In this case, we don't do any lookups, we just pass the values.
            if (!empty($groupCellValue) && !empty($subgroupCellValue)) {
              $migrationRow['summary_id'] = $this->getUniqueId();
              $migrationRow['row_id'] = $this->getUniqueId() . ':' . $row;
              $migrationRow['group'] = $groupCellValue;
              $migrationRow['subgroup'] = $subgroupCellValue;
              $migrationRow['entry'] = $valueCellValue;
              $migrationRow['unit'] = $unitCellValue;
              $migrationRow['source'] = $sourceCellValue;
              $migrationRow['comment'] = $commentCellValue;
              $migrationRow['file'] = $this->currentFile;

              $this->migrateRows[] = $migrationRow;
              $this->migrateRowsCountInFile++;
            }
          }
          $this->migrateRowsInTotal += $this->migrateRowsCountInFile;
        }
        break;

      case EITI_SOURCE_COMPANY:
        // Get our sheet.
        $revenuesSheet = $this->getSheet(EITI_SHEET_TYPE_REVENUES);
        if (!empty($revenuesSheet)) {
          // Now let's parse the file.
          $highestRow = $revenuesSheet->getHighestRow();
          $highestColumn = $revenuesSheet->getHighestColumn();
          $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
          $this->migrateRowsCountInFile = 0;

          // Defaults.
          $start_row = 3;
          $start_column = 8;

          // Find the "Companies" (Adjusting defaults).
          if ($position = $this->findPositionInSheet($revenuesSheet, array('c. companies', 'companies'))) {
            $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 1)->getValue());
            if (strtolower($value) == 'legal name') {
              $start_row = $position['row'] + 1;
            }
            else {
              $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 2)->getValue());
              if (strtolower($value) == 'legal name') {
                $start_row = $position['row'] + 2;
              }
            }
            $start_column = $position['column'] + 1;
          }

          // Now let's walk through the right cells.
          for ($column = $start_column; $column < $highestColumnIndex; $column++) {
            $migrationRow = array();
            $nameCellValue = trim($revenuesSheet->getCellByColumnAndRow($column, $start_row)->getValue());
            $idCellValue = trim($revenuesSheet->getCellByColumnAndRow($column, $start_row + 1)->getCalculatedValue());
            $commoditiesCellValue = trim($revenuesSheet->getCellByColumnAndRow($column, $start_row + 2)->getCalculatedValue());

            // In this case, we don't do any lookups, we just pass the values.
            if (!empty($nameCellValue)) {
              $migrationRow['summary_id'] = $this->getUniqueId();
              $migrationRow['column_id'] = $this->getUniqueId() . ':' . $column;
              $migrationRow['company_name'] = $nameCellValue;
              $migrationRow['company_id'] = $idCellValue;
              $migrationRow['commodity'] = $commoditiesCellValue;
              $migrationRow['file'] = $this->currentFile;

              $this->migrateRows[] = $migrationRow;
              $this->migrateRowsCountInFile++;
            }
          }
          $this->migrateRowsInTotal += $this->migrateRowsCountInFile;
        }
        break;

      case EITI_SOURCE_REVENUE_GOVERNMENT:
        // Get our sheet.
        $revenuesSheet = $this->getSheet(EITI_SHEET_TYPE_REVENUES);
        if (!empty($revenuesSheet)) {
          // Now let's parse the file.
          $highestRow = $revenuesSheet->getHighestRow();
          $highestColumn = $revenuesSheet->getHighestColumn();
          $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
          $this->migrateRowsCountInFile = 0;

          // Defaults.
          $start_row = 9;
          $start_column = 1;
          $currency = '';

          // Find the currency, if it won't be found, we'll use the summary data one.
          if ($currency_position = $this->findPositionInSheet($revenuesSheet, array('currency unit'))) {
            $currency = trim($revenuesSheet->getCellByColumnAndRow($currency_position['column'], $currency_position['row'] + 1)->getValue());
          }

          // Now we're looking up columns and making adjustments.
          if ($position = $this->findPositionInSheet($revenuesSheet, array('a. gfs classification of revenue streams'), 'gfs classification')) {
            $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 1)->getValue());
            if (strtolower($value) == 'gfs codes of revenue streams from extractive companies') {
              $start_row = $position['row'] + 2;
            }
            else {
              $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 2)->getValue());
              if (strtolower($value) == 'gfs codes of revenue streams from extractive companies') {
                $start_row = $position['row'] + 3;
              }
            }
            $start_column = $position['column'];

            // Because some files are broken, we need to make sure we have the right revenue column.
            $revenue_column = $position['column'] + 3;
            if (strpos(strtolower(trim($revenuesSheet->getCellByColumnAndRow($position['column'] + 3, $position['row'])->getValue())), 'b. revenue streams') !== FALSE) {
              $revenue_column = $position['column'] + 3;
            }
            elseif (strpos(strtolower(trim($revenuesSheet->getCellByColumnAndRow($position['column'] + 4, $position['row'])->getValue())), 'b. revenue streams') !== FALSE) {
              $revenue_column = $position['column'] + 4;
            }
          }

          // Now let's walk through the right cells.
          for ($row = $start_row; $row < $highestRow; $row++) {
            $migrationRow = array();
            $GFSCodeCellValue = trim($revenuesSheet->getCellByColumnAndRow($start_column, $row)->getValue());
            $GFSCodeStatusCellValue = trim($revenuesSheet->getCellByColumnAndRow($start_column + 2, $row)->getValue());
            $revenueStreamCellValue = trim($revenuesSheet->getCellByColumnAndRow($revenue_column, $row)->getValue());
            $orgCellValue = trim($revenuesSheet->getCellByColumnAndRow($revenue_column + 1, $row)->getValue());
            $revenueCellValue = trim($revenuesSheet->getCellByColumnAndRow($revenue_column + 2, $row)->getCalculatedValue());

            // In this case, we don't do any lookups, we just pass the values.
            if (!empty($GFSCodeCellValue) && !empty($GFSCodeStatusCellValue)) {
              $migrationRow['row_id'] = $this->getUniqueId() . ':' . $row;
              $migrationRow['summary_id'] = $this->getUniqueId();
              $migrationRow['gfs_id'] = $GFSCodeCellValue;
              $migrationRow['gfs_status'] = $GFSCodeStatusCellValue;
              $migrationRow['revenue_stream'] = $revenueStreamCellValue;
              $migrationRow['organization'] = $orgCellValue;
              $migrationRow['revenue'] = $revenueCellValue ;
              $migrationRow['file'] = $this->currentFile;
              $migrationRow['currency'] = $currency;

              $this->migrateRows[] = $migrationRow;
              $this->migrateRowsCountInFile++;
            }
          }
          $this->migrateRowsInTotal += $this->migrateRowsCountInFile;
        }
        break;

      case EITI_SOURCE_REVENUE_COMPANY:
        // Get our sheet.
        $revenuesSheet = $this->getSheet(EITI_SHEET_TYPE_REVENUES);
        if (!empty($revenuesSheet)) {
          // Now let's parse the file.
          $highestRow = $revenuesSheet->getHighestRow();
          $highestColumn = $revenuesSheet->getHighestColumn();
          $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
          $this->migrateRowsCountInFile = 0;

          // Defaults.
          $start_row = 9;
          $start_column = 1;
          $currency = '';

          // Find the currency, if it won't be found, we'll use the summary data one.
          if ($currency_position = $this->findPositionInSheet($revenuesSheet, array('currency unit'))) {
            $currency = trim($revenuesSheet->getCellByColumnAndRow($currency_position['column'], $currency_position['row'] + 1)->getValue());
          }
          // Now we're looking up columns and making adjustments.
          if ($comp_position = $this->findPositionInSheet($revenuesSheet, array('c. companies', 'companies'))) {
            $companies_column = $comp_position['column'] + 1;
          }
          if ($position = $this->findPositionInSheet($revenuesSheet, array('a. gfs classification of revenue streams'), 'gfs classification')) {
            $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 1)->getValue());
            if (strtolower($value) == 'gfs codes of revenue streams from extractive companies') {
              $start_row = $position['row'] + 2;
            }
            else {
              $value = trim($revenuesSheet->getCellByColumnAndRow($position['column'], $position['row'] + 2)->getValue());
              if (strtolower($value) == 'gfs codes of revenue streams from extractive companies') {
                $start_row = $position['row'] + 3;
              }
            }
            $start_column = $position['column'];
            $revenue_column = $position['column'] + 3;

            // Because some files are broken, we need to make sure we have the right revenue column.
            if (strpos(strtolower(trim($revenuesSheet->getCellByColumnAndRow($position['column'] + 3, $position['row'])->getValue())), 'b. revenue streams') !== FALSE) {
              $revenue_column = $position['column'] + 3;
            }
            elseif (strpos(strtolower(trim($revenuesSheet->getCellByColumnAndRow($position['column'] + 4, $position['row'])->getValue())), 'b. revenue streams') !== FALSE) {
              $revenue_column = $position['column'] + 4;
            }
          }

          // Now let's walk through the right cells.
          for ($column = $companies_column; $column < $highestColumnIndex; $column++) {
            for ($row = $start_row; $row < $highestRow; $row++) {
              $migrationRow = array();
              $GFSCodeCellValue = trim($revenuesSheet->getCellByColumnAndRow($start_column, $row)->getValue());
              $GFSCodeStatusCellValue = trim($revenuesSheet->getCellByColumnAndRow($start_column + 2, $row)->getValue());
              $revenueStreamCellValue = trim($revenuesSheet->getCellByColumnAndRow($revenue_column, $row)->getValue());
              $revenueCellValue = trim($revenuesSheet->getCellByColumnAndRow($column, $row)->getCalculatedValue());

              // In this case, we don't do any lookups, we just pass the values.
              if (!empty($GFSCodeCellValue) && !empty($GFSCodeStatusCellValue) && !empty($revenueCellValue) && $revenueCellValue !== '-') {
                $migrationRow['position_id'] = $this->getUniqueId() . ':' . $row . ':' . $column;
                $migrationRow['column_id'] = $this->getUniqueId() . ':' . $column;
                $migrationRow['summary_id'] = $this->getUniqueId();
                $migrationRow['gfs_id'] = $GFSCodeCellValue;
                $migrationRow['gfs_status'] = $GFSCodeStatusCellValue;
                $migrationRow['revenue_stream'] = $revenueStreamCellValue;
                $migrationRow['revenue'] = $revenueCellValue ;
                $migrationRow['file'] = $this->currentFile;
                $migrationRow['currency'] = $currency;

                $this->migrateRows[] = $migrationRow;
                $this->migrateRowsCountInFile++;
              }
            }
          }
          $this->migrateRowsInTotal += $this->migrateRowsCountInFile;
        }
        break;
    }
  }

  /**
   * Small helper function that looks up a cell in a sheet, that matches at least
   * one of the given values in $values.\
   *
   * @param PHPExcel_Worksheet $sheet
   *  PHPExcel Worksheet object.
   *
   * @param array $values
   *  Values of possible matches.
   *
   * @param string $final
   *  If we're very desperate, we can use this variable to match strpos().
   *
   * @return FALSE|array
   *  Returns a position array which has both row and column values, or FALSE.
   */
  protected function findPositionInSheet($sheet, $values, $final = NULL) {
    if (!empty($sheet)) {
      $highestRow = $sheet->getHighestRow();
      $highestColumn = $sheet->getHighestColumn();
      $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
      for ($row = 0; $row < $highestRow; $row++) {
        for ($column = 0; $column < $highestColumnIndex; $column++) {
          $cellValue = trim($sheet->getCellByColumnAndRow($column, $row)->getValue());
          foreach ($values as $value) {
            if (strtolower($cellValue) == strtolower($value)) {
              $position['row'] = $row;
              $position['column'] = $column;
              return $position;
            }
            // Finally check the $final variable.
            if ($final && (strpos($cellValue, $final) !== FALSE)) {
              $position['row'] = $row;
              $position['column'] = $column;
              return $position;
            }
          }
        }
      }
    }
    return FALSE;
  }

  /**
   * Gets the specified row.
   */
  protected function getParsedRow($index) {
    if (!empty($this->migrateRows) && isset($this->migrateRows[$index])) {
      return $this->migrateRows[$index];
    }
  }

  /**
   * Small function that fetches specific sheet from the spreadsheet.
   *
   * @param string $sheet_type
   *  One of the types defined as constants.
   *
   * @return NULL|PHPExcel_Worksheet
   *  Loaded sheet if found, or NULL.
   */
  protected function getSheet($sheet_type) {
    $sheet = NULL;

    switch ($sheet_type) {
      case EITI_SHEET_TYPE_ABOUT:
        $sheet = $this->currentWorkbook->getSheetByName('1. About');
        if (empty($sheet)) {
          // Second try, already via index.
          $sheet = $this->currentWorkbook->getSheet(1);
        }
        break;

      case EITI_SHEET_TYPE_CONTEXTUAL:
        $sheet = $this->currentWorkbook->getSheetByName('2. Contextual');
        if (empty($sheet)) {
          // Second try, already via index.
          $sheet = $this->currentWorkbook->getSheet(2);
        }
        break;

      case EITI_SHEET_TYPE_REVENUES:
        $sheet = $this->currentWorkbook->getSheetByName('3. Revenues');
        if (empty($sheet)) {
          // Second try, already via index.
          $sheet = $this->currentWorkbook->getSheet(3);
        }
        break;
    }

    return $sheet;
  }

  /**
   * Helps us decide which field are we currently looking at.
   *
   * @return string
   *   Returns string representing the field.
   */
  protected function lookupField($group, $subgroup) {
    $mappings = $this->lookupMappings();
    $group_position = TRUE;
    $subgroup_position = TRUE;
    $match = 'unmapped';
    foreach ($mappings as $field => $mapping) {
      foreach ($mapping['group'] as $group_hints) {
        $group_position = stripos($group, $group_hints);
        if ($group_position !== NULL && $group_position !== FALSE) {
          break;
        }
      }
      foreach ($mapping['subgroup'] as $subgroup_hints) {
        $subgroup_position = stripos($subgroup, $subgroup_hints);
        if ($subgroup_position !== NULL && $subgroup_position !== FALSE) {
          break;
        }
      }

      // If at least one was found, use the $field, but don't break.
      if (($group_position !== NULL && $group_position !== FALSE) || ($subgroup_position !== NULL && $subgroup_position !== FALSE)) {
        $match = $field;

        // If both match, use the field and break.
        if (($group_position !== NULL && $group_position !== FALSE) && ($subgroup_position !== NULL && $subgroup_position !== FALSE)) {
          $match = $field;
          break;
        }
        else {
          // Reset these values for next iteration.
          $group_position = NULL;
          $subgroup_position = NULL;
        }
      }
    }
    return $match;
  }

  /**
   * This is one important function, it returns the sacred hinting mappings.
   *
   * In lookupField() - we'll make a search and see if the current row has
   * any matches on group, subgroup, or both. If it has, we can return the field.
   *
   * @return array
   *   Where [key] - is the field from the self::generateFields(),
   *   [value] - is an array made up of 2 arrays:
   *     - $mappings['field']['group'] - array of hinting strings in group.
   *     - $mappings['field']['subgroup'] - array of hinting strings in subgroup.
   */
  protected function lookupMappings() {
    $mappings = array();
    switch ($this->sourceType) {
      case EITI_SOURCE_SUMMARY_DATA:
        $mappings['country_name'] = array(
          'group' => array('country'),
          'subgroup' => array(),
        );
        $mappings['start_date'] = array(
          'group' => array('fiscal year'),
          'subgroup' => array('start'),
        );
        $mappings['end_date'] = array(
          'group' => array('fiscal year'),
          'subgroup' => array('end'),
        );
        $mappings['independent_administrator'] = array(
          'group' => array('independent administrator'),
          'subgroup' => array(),
        );
        $mappings['publish_date'] = array(
          'group' => array('date', 'publish'),
          'subgroup' => array(),
        );
        $mappings['sectors:oil'] = array(
          'group' => array('sectors covered'),
          'subgroup' => array('oil'),
        );
        $mappings['sectors:gas'] = array(
          'group' => array('sectors covered'),
          'subgroup' => array('gas'),
        );
        $mappings['sectors:mining'] = array(
          'group' => array('sectors covered'),
          'subgroup' => array('mining'),
        );
        $mappings['sectors:other'] = array(
          'group' => array('sectors covered'),
          'subgroup' => array('other'),
        );
        $mappings['web_links'] = array(
          'group' => array('web links'),
          'subgroup' => array(),
        );
        $mappings['number:reporting_gov'] = array(
          'group' => array('number of reporting government'),
          'subgroup' => array(),
        );
        $mappings['number:reporting_comp'] = array(
          'group' => array('number of reporting companies'),
          'subgroup' => array(),
        );
        $mappings['currency:iso'] = array(
          'group' => array('currency'),
          'subgroup' => array('iso'),
        );
        $mappings['currency:conversion'] = array(
          'group' => array('currency'),
          'subgroup' => array('conversion'),
        );
        $mappings['dissaggregation:revenue_stream'] = array(
          'group' => array('disaggregtion of data'),
          'subgroup' => array('revenue'),
        );
        $mappings['dissaggregation:company'] = array(
          'group' => array('disaggregtion of data'),
          'subgroup' => array('company'),
        );
        $mappings['dissaggregation:project'] = array(
          'group' => array('disaggregtion of data'),
          'subgroup' => array('project'),
        );
        $mappings['contact:name'] = array(
          'group' => array('contact details'),
          'subgroup' => array('name'),
        );
        $mappings['contact:organization'] = array(
          'group' => array('contact details'),
          'subgroup' => array('organisation'),
        );
        $mappings['contact:email'] = array(
          'group' => array('contact details'),
          'subgroup' => array('email'),
        );
        break;
    }
    return $mappings;
  }

  /**
   * Returns a string representing the source query.
   *
   * @return string
   */
  public function __toString() {
    return implode(PHP_EOL, $this->filePaths);
  }
}
