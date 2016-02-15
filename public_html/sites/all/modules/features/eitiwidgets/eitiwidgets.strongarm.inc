<?php
/**
 * @file
 * eitiwidgets.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitiwidgets_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_key_facts';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_key_facts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_quote';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_quote'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_visualization';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_visualization'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_wide_image';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_wide_image'] = $strongarm;

  return $export;
}
