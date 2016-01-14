<?php
/**
 * @file
 * eitiet_summarydata.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitiet_summarydata_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_summarydata__summarydata';
  $strongarm->value = array(
    'view_modes' => array(
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'redirect' => array(
          'weight' => '12',
        ),
        'country_id' => array(
          'weight' => '0',
        ),
        'year_start' => array(
          'weight' => '2',
        ),
        'year_end' => array(
          'weight' => '3',
        ),
        'published' => array(
          'weight' => '3',
        ),
        'currency_code' => array(
          'weight' => '7',
        ),
        'currency_rate' => array(
          'weight' => '8',
        ),
        'status' => array(
          'weight' => '0',
        ),
        'created' => array(
          'weight' => '10',
        ),
        'changed' => array(
          'weight' => '11',
        ),
        'url' => array(
          'weight' => '1',
        ),
      ),
      'display' => array(
        'country_id' => array(
          'default' => array(
            'weight' => '5',
            'visible' => TRUE,
          ),
        ),
        'year_start' => array(
          'default' => array(
            'weight' => '6',
            'visible' => TRUE,
          ),
        ),
        'year_end' => array(
          'default' => array(
            'weight' => '7',
            'visible' => TRUE,
          ),
        ),
        'published' => array(
          'default' => array(
            'weight' => '4',
            'visible' => TRUE,
          ),
        ),
        'currency_code' => array(
          'default' => array(
            'weight' => '3',
            'visible' => TRUE,
          ),
        ),
        'currency_rate' => array(
          'default' => array(
            'weight' => '2',
            'visible' => TRUE,
          ),
        ),
        'status' => array(
          'default' => array(
            'weight' => '9',
            'visible' => TRUE,
          ),
        ),
        'created' => array(
          'default' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
        'changed' => array(
          'default' => array(
            'weight' => '1',
            'visible' => TRUE,
          ),
        ),
        'url' => array(
          'default' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_summarydata__summarydata'] = $strongarm;

  return $export;
}
