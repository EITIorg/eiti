<?php

/**
 * @file
 *
 * Holds generic / abstract classes for further report import process.
 * All other classes extend these classes or implement these interfaces.
 */

/**
 * Common class that all spreadsheet migrations extend.
 *
 * Holds useful functions.
 */
class EITISpreadsheetMigration extends Migration {

  /**
   * Helper function that transforms existing value to boolean-list.
   */
  protected function getBooleanListValue($value) {
    $correct_value = FALSE;
    switch (strtolower($value)) {
      case 'yes':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_YES;
        break;
      case 'no':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_NO;
        break;
      case 'partially':
        $correct_value = EITIENTITY_INDICATOR_VALUE_VALUE_PARTIALLY;
        break;
      default:
        $correct_value = NULL;
        break;
    }
    return $correct_value;
  }

  /**
   * Small helper function that checks if the value is empty or not.
   */
  protected function checkEmptyValue($value) {
    $is_empty = FALSE;
    switch (strtolower($value)) {
      case 'not applicable':
      case 'not available':
      case 'n/a':
      case '<text>':
      case '<url>':
      case '-':
      case '':
        $is_empty = TRUE;
        break;

      default:
        $is_empty = FALSE;
        break;
    }

    // More checking <tag>.
    if ($is_empty === FALSE) {
      if (preg_match('/<.+?>/', $value)) {
        $is_empty = TRUE;
      }
    }
    return $is_empty;
  }

  /**
   * Very useful function, helps us find the right indicators and not only.
   */
  protected function findBestMatch($needle, $haystack) {
    $matchRating = array();
    foreach ($haystack as $id => $obj) {
      $match_percent = 0;
      similar_text($needle, $obj->name, $match_percent);
      $matchRating[$id] = $match_percent;
    }
    asort($matchRating);
    end($matchRating);
    $bestMatchingID = key($matchRating);
    if ($matchRating[$bestMatchingID] > 80) {
      return $bestMatchingID;
    }
    return FALSE;
  }

  /**
   * Small helper function that is used to normalize certain values.
   */
  protected function normalizeValue($value) {
    $normalizedValue = $value;
    switch (strtolower($value)) {
      case 'us$':
      case 'us $':
        $normalizedValue = 'USD';
        break;
    }
    return $normalizedValue;
  }
}
