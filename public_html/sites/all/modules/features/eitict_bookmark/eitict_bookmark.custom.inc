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
  if (isset($form_state['entity']) && $form_state['entity']->bundle == 'featured_bookmarks' && !empty($entity_form['field_bm_reference_type'])) {
    $field_prefix = 'field_fpp_bookmark_list[und][form][field_bm_reference_type][und]';
    $entity_form['field_bm_link']['#states'] = array(
      'visible' => array(
        array('input[name="' . $field_prefix . '"]' => array('value' => 'external')),
      )
    );
    $entity_form['field_bm_reference']['#states'] = array(
      'visible' => array(
        array('input[name="' . $field_prefix . '"]' => array('value' => 'internal')),
      )
    );
    $entity_form['status'] = array('#type' => 'value', '#value' => 1);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function eitict_bookmark_preprocess_node(&$variables) {
  if ($variables['type'] == 'bookmark') {
    // Load the wrapper for convenience.
    $node_emw = entity_metadata_wrapper('node', $variables['node']);
    $reference_type = $node_emw->field_bm_reference_type->value();

    $variables['bookmark_url'] = '';
    // Create a unified URL for the bookmark, either internal or external.
    switch ($reference_type) {
      case 'external':
        if (!empty($node_emw->field_bm_reference)) {
          $link_value = $node_emw->field_bm_reference->value();
          $variables['bookmark_url'] = $link_value['url'];
        }
        break;
      case 'internal':
        if (!empty($node_emw->field_bm_reference)) {
          $reference = $node_emw->field_bm_reference->value();
          if (!empty($reference)) {
            $variables['bookmark_url'] = url('node/' . $reference->nid);
          }
        }
        break;
    }
    // Pass the hide-title value (which hides all the overlay content).
    if (!empty($node_emw->field_bm_hide_title)) {
      $variables['hide_title'] = $node_emw->field_bm_hide_title->value();
    }
    $variables['classes_array'][] = drupal_html_class($variables['view_mode']);
  }
}
