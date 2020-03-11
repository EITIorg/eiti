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

  $export['views-stakeholders-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'stakeholders-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'supporters/companies
supporters/civil-society
supporters/countries',
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
        'region' => 'content',
        'status' => 1,
        'theme' => 'eiti',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  return $export;
}
