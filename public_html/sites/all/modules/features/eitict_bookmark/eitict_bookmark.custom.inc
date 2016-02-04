<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function eitict_bookmark_form_bookmark_node_form_alter(&$form, &$form_state) {
  $form['field_bm_link']['#states'] = array(
    'visible' => array(
      array('input[name="field_bm_reference_type[und]"]' => array('value' => 'external')),
    )
  );
  $form['field_bm_reference']['#states'] = array(
    'visible' => array(
      array('input[name="field_bm_reference_type[und]"]' => array('value' => 'internal')),
    )
  );
}

/**
 * Implements hook_inline_entity_form_entity_form_alter()
 */
function eitict_bookmark_inline_entity_form_entity_form_alter(&$entity_form, &$form_state) {
  if ($form_state['entity_type'] == 'contentblock' && !empty($entity_form['field_bm_reference_type'])) {
    $entity_form['field_bm_link']['#states'] = array(
      'visible' => array(
        array('input[name="field_bookmark_list[und][form][field_bm_reference_type][und]"]' => array('value' => 'external')),
      )
    );
    $entity_form['field_bm_reference']['#states'] = array(
      'visible' => array(
        array('input[name="field_bookmark_list[und][form][field_bm_reference_type][und]"]' => array('value' => 'internal')),
      )
    );
    $entity_form['status'] = array('#type' => 'value', '#value' => 1);
  }
}
