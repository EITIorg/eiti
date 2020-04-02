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
    'title' => 'Link to persons board',
    'visibility' => 0,
  );

  $export['views-11095694fe68b9668dc8660623f88aac'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '11095694fe68b9668dc8660623f88aac',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'supporters/*
taxonomy/term/714
taxonomy/term/715
taxonomy/term/716
taxonomy/term/10386
taxonomy/term/10387
taxonomy/term/10388
taxonomy/term/10389
taxonomy/term/10390
taxonomy/term/10391',
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
