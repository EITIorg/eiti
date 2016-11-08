<?php
/**
 * @file
 * eitiet_score_data.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function eitiet_score_data_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'score_data-standard-field_scd_score_req_values'.
  $field_instances['score_data-standard-field_scd_score_req_values'] = array(
    'bundle' => 'standard',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'score_data',
    'field_name' => 'field_scd_score_req_values',
    'label' => 'Score Requirements Values',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_clone' => 0,
          'allow_existing' => 0,
          'allow_new' => 1,
          'delete_references' => 1,
          'label_plural' => 'Score Requirement Values',
          'label_singular' => 'Score Requirement Value',
          'match_operator' => 'CONTAINS',
          'override_labels' => 0,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Score Requirements Values');

  return $field_instances;
}
