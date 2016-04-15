<?php
/**
 * @file
 * eitientities.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitientities_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'title_node';
  $strongarm->value = array(
    'auto_attach' => array(
      'title' => 'title',
    ),
    'hide_label' => array(
      'entity' => 'entity',
      'page' => 0,
    ),
  );
  $export['title_node'] = $strongarm;

  return $export;
}
