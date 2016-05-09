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
   * We just want to initialize some common things here.
   *
   * Default constructor.
   */
  function __construct(array $arguments) {
    parent::__construct($arguments);

    // Load the currencies.
    $this->allCurrencies = currency_load_all();
  }

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
    // Simple empty check.
    if (empty($value)) {
      return TRUE;
    }

    $is_empty = FALSE;
    switch (strtolower($value)) {
      case 'not applicable':
      case 'not available':
      case 'n/a':
      case '<text>':
      case '<url>':
      case '...':
      case '…':
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
    if ($matchRating[$bestMatchingID] > 95) {
      return $bestMatchingID;
    }
    return FALSE;
  }

  /**
   * Small helper function that is used to normalize certain values.
   */
  protected function normalizeValue($value, &$unit, $rate_to_usd = FALSE) {
    $normalizedValue = $value;
    $normalized = FALSE;

    $million = 1000000;
    $sm3_to_barrels = 6.29; // They always change their mind.
    $barrels_per_day_to_year = 365.242199;
    $barrels_to_sm3 = 0.15898757;
    $gj_to_sm3 = 35.5;
    switch ($unit) {
      case 'USD':
        $normalizedValue = $value;
        $normalized = TRUE;
        break;

      case 'M USD':
        $normalizedValue = $value * $million;
        $normalized = TRUE;
        $unit = 'USD';
        break;

      case 'Barrels per Day':
        // Fluids per day => per year.
        $normalizedValue = $value * $barrels_per_day_to_year * $barrels_to_sm3;
        $normalized = TRUE;
        $unit = 'Sm3';
        break;

      case 'Barrels':
        $normalizedValue = $value * $barrels_to_sm3;
        $normalized = TRUE;
        $unit = 'Sm3';
        break;

      case 'M Sm3':
        // M Sm3 => Barrels
        $normalizedValue = $value * $million;
        $unit = 'Sm3';
        $normalized = TRUE;
        break;

      case 'Sm3':
        // Sm3 => Barrels
        $normalizedValue = $value ;
        $unit = 'Sm3';
        $normalized = TRUE;
        break;

      case 'Gj':
        $normalizedValue = $value / $gj_to_sm3;
        $unit = 'Sm3';
        $normalized = TRUE;
    }

    // Last try, let's try and see if it's a currency.
    $found_currency = FALSE;
    if ($rate_to_usd !== FALSE && !$normalized) {
      foreach ($this->allCurrencies as $code => $currency) {
        if ($code == strtoupper($unit)) {
          $found_currency = TRUE;
          break;
        }
      }
      if ($found_currency) {
        $normalizedValue = round($value / $rate_to_usd);
        $unit = 'USD';
      }
    }
    return $normalizedValue;
  }

  /**
   * Small helper function that is used to normalize the unit.
   */
  protected function normalizeUnit($unit) {
    $normalizedUnit = $unit;
    switch (strtolower($unit)) {
      case 'us$':
      case 'us $':
      case 'usd':
        $normalizedUnit = 'USD';
        break;
      case 'million us $':
      case 'million $':
        $normalizedUnit = 'M USD';
        break;
      case 'million sm3 o.e':
      case 'million sm3':
        $normalizedUnit = 'M Sm3';
        break;
      case 'sm3 o.e.':
      case 'sm3 o.e':
      case 'sm3 oe':
      case 'sm3':
        $normalizedUnit = 'Sm3';
        break;
      case 'bbl':
      case 'barrel':
      case 'barrels':
        $normalizedUnit = 'Barrels';
        break;
      case 'barrels o.e. per day':
        $normalizedUnit = 'Barrels per Day';
        break;
      case 'gj':
        $normalizedUnit = 'Gj';
    }

    return $normalizedUnit;
  }

  /**
   * Small function that normalizes the indicator (basically looks up aliases).
   */
  protected function normalizeIndicator($indicator) {
    $adjusted_indicator = $indicator;
    switch (strtolower($indicator)) {
      case 'natural gas, value':
        $adjusted_indicator = 'Gas, value';
        break;
      case 'natural gas, volume':
        $adjusted_indicator = 'Gas, volume';
        break;
      case 'crude oil, volume':
        $adjusted_indicator = 'Oil, volume';
        break;
      case 'crude oil, value':
        $adjusted_indicator = 'Oil, value';
        break;

    }
    return $adjusted_indicator;
  }

  protected function getCurrencyMultiplier(&$currency_str) {
    $multiplier = 1;

    if (strlen($currency_str) !== 3) {
      // I.e. million usd, Millions US$, etc.
      if (strpos(strtolower($currency_str), 'million') !== FALSE) {
        $multiplier = 1000000;
      }

      // I.e. 1000 MNT, 1000000 USD etc.
      if (preg_match('/([0-9])\w+/', $currency_str, $match)) {
        $multiplier = $match[0];
      }

      // Now we want to find the currency in the string.
      $arr = explode(' ', $currency_str);
      foreach ($arr as $chunk) {
        if (strlen($chunk) == 3) {
          $currency_str = (strtolower($chunk) == 'us$') ? 'USD' : $chunk;
        }
      }
      // Finally we want to try some things.
      if (strpos($currency_str, '$')) {
        $currency_str = 'USD';
      }
      if (strpos($currency_str, '€')) {
        $currency_str = 'EUR';
      }
    }
    return $multiplier;
  }

  /**
   * Fetches all of the defined (and published) reports, that are ready for
   * parsing.
   */
  protected function getSpreadsheetFiles() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'file')
      ->propertyCondition('status', FILE_STATUS_PERMANENT)
      ->propertyCondition('type', 'report');

    $results = $query->execute();
    if (!empty($results['file'])) {
      $fids = array_keys($results['file']);
      $files = entity_load('file', $fids);

      $real_paths = array();
      foreach ($files as $fid => $file) {
        $real_paths[$fid] = drupal_realpath($file->uri);
      }

      return $real_paths;
    }
    return FALSE;
  }
}
