<?php

/**
 * @file
 * eitict_stakeholder.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function eitict_stakeholder_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-persons_board_link'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'persons_board_link',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'adminimal' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'adminimal',
        'weight' => 0,
      ),
      'adminimal_helpertheme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'adminimal_helpertheme',
        'weight' => 0,
      ),
      'eiti' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'eiti',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
