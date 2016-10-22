<?php
/**
 * @file
 * eitiet_score_data.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function eitiet_score_data_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_scd_score_req_values'.
  $field_bases['field_scd_score_req_values'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_scd_score_req_values',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'entityqueue' => array(
            'status' => 0,
          ),
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(),
      ),
      'target_type' => 'score_req_value',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
