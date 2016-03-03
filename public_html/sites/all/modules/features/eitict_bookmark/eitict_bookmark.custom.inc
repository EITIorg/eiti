<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * For inline entity form:
 * @see: eitict_bookmark_inline_entity_form_entity_form_alter()
 */
function eitict_bookmark_form_bookmark_node_form_alter(&$form, &$form_state) {
  if (isset($form['field_bm_reference_type'])) {
    $entity = $form['#entity'];
    $entity_language = entity_language('node', $entity);

    $reference_field_language = field_language('node', $entity, 'field_bm_reference_type', $entity_language);
    if (isset($form['field_bm_link'])) {
      $form['field_bm_link']['#states'] = array(
        'visible' => array(
          array('input[name="field_bm_reference_type[' . $reference_field_language . ']"]' => array('value' => 'external')),
        )
      );
    }
    if (isset($form['field_bm_reference'])) {
      $form['field_bm_reference']['#states'] = array(
        'visible' => array(
          array('input[name="field_bm_reference_type[' . $reference_field_language . ']"]' => array('value' => 'internal')),
        )
      );
    }
  }
}

/**
 * Implements hook_inline_entity_form_entity_form_alter()
 *
 * For node entity form:
 * @see: eitict_bookmark_form_bookmark_node_form_alter()
 */
function eitict_bookmark_inline_entity_form_entity_form_alter(&$entity_form, &$form_state) {
  if (!isset($form_state['fieldable_panels_pane'])) {
    return;
  }

  $entity = $entity_form['#entity'];
  $entity_type = $entity_form['#entity_type'];
  $entity_language = entity_language($entity_type, $entity);

  if ($form_state['fieldable_panels_pane']->bundle == 'featured_bookmarks' && !empty($entity_form['field_bm_reference_type'])) {
    $ref_type_field_language = field_language($entity_type, $entity, 'field_bm_reference_type', $entity_language);
    $element_parents = array_merge($entity_form['#parents'], array(
      'field_bm_reference_type',
      $ref_type_field_language
    ));
    $field_prefix = helpergeneric_parents_array_to_string($element_parents);

    if (isset($entity_form['field_bm_link'])) {
      $entity_form['field_bm_link']['#states'] = array(
        'visible' => array(
          array('input[name="' . $field_prefix . '"]' => array('value' => 'external')),
        )
      );
    }

    if (isset($entity_form['field_bm_reference'])) {
      $entity_form['field_bm_reference']['#states'] = array(
        'visible' => array(
          array('input[name="' . $field_prefix . '"]' => array('value' => 'internal')),
        )
      );
    }

    // Hide the status field.
    $entity_form['status'] = array('#type' => 'value', '#value' => 1);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function eitict_bookmark_preprocess_node(&$variables) {
  if ($variables['type'] != 'bookmark') {
    return;
  }

  // Load the wrapper for convenience.
  $node_emw = entity_metadata_wrapper('node', $variables['node']);
  $reference_type = $node_emw->field_bm_reference_type->value();

  // Pass the hide-title value (which hides all the overlay content).
  if (!empty($node_emw->field_bm_hide_title)) {
    $variables['hide_title'] = $node_emw->field_bm_hide_title->value();
  }

  if (!isset($variables['main_classes'])) {
    $variables['main_classes'] = '';
  }

  // Get the bookmark URL.
  $variables['bookmark_url'] = '';
  // Create a unified URL for the bookmark, either internal or external.
  switch ($reference_type) {
    case 'external':
      if (!empty($node_emw->field_bm_link)) {
        $link_value = $node_emw->field_bm_link->value();
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

  // Convert the DS layout to an anchor tag.
  if ($variables['bookmark_url']) {
    $variables['main_wrapper'] = 'a';
    $variables['main_attributes'] = array(
      'href' => $variables['bookmark_url'],
    );
    $variables['main_classes'] .= ' linked-wrapper';
  }
}
