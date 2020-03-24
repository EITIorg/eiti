<?php

/**
 * @file
 * eititaxonomies.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function eititaxonomies_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-supporters-companies_categories'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'supporters-companies_categories',
    'module' => 'views',
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

  $export['views-supporters-s_types'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'supporters-s_types',
    'module' => 'views',
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
    'title' => 'Supporters categories',
    'visibility' => 0,
  );

  return $export;
}
