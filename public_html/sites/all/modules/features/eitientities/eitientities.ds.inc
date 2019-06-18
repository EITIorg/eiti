<?php

/**
 * @file
 * eitientities.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function eitientities_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'bm_large_tile';
  $ds_view_mode->label = 'Large Tile';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['bm_large_tile'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'bm_medium_tile';
  $ds_view_mode->label = 'Medium Tile';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['bm_medium_tile'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'bm_small_tile';
  $ds_view_mode->label = 'Small Tile';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['bm_small_tile'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'summary';
  $ds_view_mode->label = 'Summary';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['summary'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'teaser_alternative';
  $ds_view_mode->label = 'Teaser Alternative';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['teaser_alternative'] = $ds_view_mode;

  return $export;
}
