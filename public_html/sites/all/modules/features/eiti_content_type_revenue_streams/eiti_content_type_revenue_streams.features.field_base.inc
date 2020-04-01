<?php

/**
 * @file
 * eiti_content_type_revenue_streams.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function eiti_content_type_revenue_streams_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_comments'.
  $field_bases['field_comments'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_comments',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'field_currency'.
  $field_bases['field_currency'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_currency',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'AED' => 'AED',
        'AFN' => 'AFN',
        'ALL' => 'ALL',
        'AMD' => 'AMD',
        'ANG' => 'ANG',
        'AOA' => 'AOA',
        'ARS' => 'ARS',
        'AUD' => 'AUD',
        'AWG' => 'AWG',
        'AZN' => 'AZN',
        'BAM' => 'BAM',
        'BBD' => 'BBD',
        'BDT' => 'BDT',
        'BGN' => 'BGN',
        'BHD' => 'BHD',
        'BIF' => 'BIF',
        'BMD' => 'BMD',
        'BND' => 'BND',
        'BOB' => 'BOB',
        'BRL' => 'BRL',
        'BSD' => 'BSD',
        'BTN' => 'BTN',
        'BWP' => 'BWP',
        'BYR' => 'BYR',
        'BZD' => 'BZD',
        'CAD' => 'CAD',
        'CDF' => 'CDF',
        'CHF' => 'CHF',
        'CLF' => 'CLF',
        'CNH' => 'CNH',
        'COP' => 'COP',
        'CRC' => 'CRC',
        'CUC' => 'CUC',
        'CVE' => 'CVE',
        'CZK' => 'CZK',
        'DJF' => 'DJF',
        'DKK' => 'DKK',
        'DOP' => 'DOP',
        'DZD' => 'DZD',
        'EGP' => 'EGP',
        'ERN' => 'ERN',
        'ETB' => 'ETB',
        'EUR' => 'EUR',
        'FJD' => 'FJD',
        'FKP' => 'FKP',
        'GBP' => 'GBP',
        'GEL' => 'GEL',
        'GGP' => 'GGP',
        'GHS' => 'GHS',
        'GIP' => 'GIP',
        'GMD' => 'GMD',
        'GNF' => 'GNF',
        'GTQ' => 'GTQ',
        'GYD' => 'GYD',
        'HKD' => 'HKD',
        'HNL' => 'HNL',
        'HRK' => 'HRK',
        'HTG' => 'HTG',
        'HUF' => 'HUF',
        'IDR' => 'IDR',
        'ILS' => 'ILS',
        'IMP' => 'IMP',
        'INR' => 'INR',
        'IQD' => 'IQD',
        'IRR' => 'IRR',
        'ISK' => 'ISK',
        'JEP' => 'JEP',
        'JMD' => 'JMD',
        'JOD' => 'JOD',
        'JPY' => 'JPY',
        'KES' => 'KES',
        'KGS' => 'KGS',
        'KHR' => 'KHR',
        'KMF' => 'KMF',
        'KPW' => 'KPW',
        'KRW' => 'KRW',
        'KWD' => 'KWD',
        'KYD' => 'KYD',
        'KZT' => 'KZT',
        'LAK' => 'LAK',
        'LBP' => 'LBP',
        'LKR' => 'LKR',
        'LRD' => 'LRD',
        'LSL' => 'LSL',
        'LYD' => 'LYD',
        'MAD' => 'MAD',
        'MDL' => 'MDL',
        'MGA' => 'MGA',
        'MKD' => 'MKD',
        'MMK' => 'MMK',
        'MNT' => 'MNT',
        'MOP' => 'MOP',
        'MRO' => 'MRO',
        'MUR' => 'MUR',
        'MVR' => 'MVR',
        'MWK' => 'MWK',
        'MXN' => 'MXN',
        'MYR' => 'MYR',
        'MZN' => 'MZN',
        'NAD' => 'NAD',
        'NGN' => 'NGN',
        'NIO' => 'NIO',
        'NOK' => 'NOK',
        'NPR' => 'NPR',
        'NZD' => 'NZD',
        'OMR' => 'OMR',
        'PAB' => 'PAB',
        'PEN' => 'PEN',
        'PGK' => 'PGK',
        'PHP' => 'PHP',
        'PKR' => 'PKR',
        'PLN' => 'PLN',
        'PYG' => 'PYG',
        'QAR' => 'QAR',
        'RON' => 'RON',
        'RSD' => 'RSD',
        'RUB' => 'RUB',
        'RWF' => 'RWF',
        'SAR' => 'SAR',
        'SBD' => 'SBD',
        'SCR' => 'SCR',
        'SDG' => 'SDG',
        'SEK' => 'SEK',
        'SGD' => 'SGD',
        'SHP' => 'SHP',
        'SLL' => 'SLL',
        'SOS' => 'SOS',
        'SRD' => 'SRD',
        'SSP' => 'SSP',
        'STD' => 'STD',
        'SYP' => 'SYP',
        'SZL' => 'SZL',
        'THB' => 'THB',
        'TJS' => 'TJS',
        'TMT' => 'TMT',
        'TND' => 'TND',
        'TOP' => 'TOP',
        'TRY' => 'TRY',
        'TTD' => 'TTD',
        'TVD' => 'TVD',
        'TWD' => 'TWD',
        'TZS' => 'TZS',
        'UAH' => 'UAH',
        'UGX' => 'UGX',
        'USD' => 'USD',
        'UYU' => 'UYU',
        'UZS' => 'UZS',
        'VEF' => 'VEF',
        'VND' => 'VND',
        'VUV' => 'VUV',
        'WST' => 'WST',
        'XAF' => 'XAF',
        'XCD' => 'XCD',
        'XOF' => 'XOF',
        'YER' => 'YER',
        'ZAR' => 'ZAR',
        'ZMW' => 'ZMW',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_in_kind_volume'.
  $field_bases['field_in_kind_volume'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_in_kind_volume',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'entity_translation_sync' => FALSE,
      'precision' => 10,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  // Exported field_base: 'field_levied_on_project'.
  $field_bases['field_levied_on_project'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_levied_on_project',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Yes' => 'Yes',
        'No' => 'No',
        'Partially' => 'Partially',
        'Not applicable' => 'Not applicable',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_payment_made_in_kind'.
  $field_bases['field_payment_made_in_kind'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_payment_made_in_kind',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Yes' => 'Yes',
        'No' => 'No',
        'Partially' => 'Partially',
        'Not applicable' => 'Not applicable',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_project_name'.
  $field_bases['field_project_name'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_project_name',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_reported_by_project'.
  $field_bases['field_reported_by_project'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_reported_by_project',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Yes' => 'Yes',
        'No' => 'No',
        'Partially' => 'Partially',
        'Not applicable' => 'Not applicable',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_revenue_value'.
  $field_bases['field_revenue_value'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_revenue_value',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_sector'.
  $field_bases['field_sector'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sector',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Oil' => 'Oil',
        'Gas' => 'Gas',
        'Mining' => 'Mining',
        'Not applicable' => 'Not applicable',
        'Oil & Gas' => 'Oil & Gas',
        'Other' => 'Other',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_unit'.
  $field_bases['field_unit'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_unit',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Barrels' => 'Barrels',
        'Sm3' => 'Sm3',
        'Tonnes' => 'Tonnes',
        'ouncez (oz)' => 'ouncez (oz)',
        'carats' => 'carats',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
