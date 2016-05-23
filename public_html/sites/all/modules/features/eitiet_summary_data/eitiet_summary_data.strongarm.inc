<?php
/**
 * @file
 * eitiet_summary_data.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitiet_summary_data_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_summary_data__summary_data';
  $strongarm->value = array(
    'view_modes' => array(
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'redirect' => array(
          'weight' => '15',
        ),
        'country_id' => array(
          'weight' => '1',
        ),
        'year_start' => array(
          'weight' => '2',
        ),
        'year_end' => array(
          'weight' => '3',
        ),
        'published' => array(
          'weight' => '4',
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
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
        'year_start' => array(
          'default' => array(
            'weight' => '25',
            'visible' => FALSE,
          ),
        ),
        'year_end' => array(
          'default' => array(
            'weight' => '1',
            'visible' => TRUE,
          ),
        ),
        'published' => array(
          'default' => array(
            'weight' => '24',
            'visible' => FALSE,
          ),
        ),
        'currency_code' => array(
          'default' => array(
            'weight' => '23',
            'visible' => FALSE,
          ),
        ),
        'currency_rate' => array(
          'default' => array(
            'weight' => '22',
            'visible' => FALSE,
          ),
        ),
        'status' => array(
          'default' => array(
            'weight' => '26',
            'visible' => FALSE,
          ),
        ),
        'created' => array(
          'default' => array(
            'weight' => '20',
            'visible' => FALSE,
          ),
        ),
        'changed' => array(
          'default' => array(
            'weight' => '21',
            'visible' => FALSE,
          ),
        ),
        'url' => array(
          'default' => array(
            'weight' => '16',
            'visible' => FALSE,
          ),
        ),
        'sectors_covered' => array(
          'default' => array(
            'weight' => '3',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_summary_data__summary_data'] = $strongarm;

  return $export;
}
