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

/**
 * Custom function that creates a bookmark with specified details.
 *
 * @param $details
 *  An array of details, such as target content, etc.
 *  Keys:
 *   - node - target node.
 *   - uid - that creates the bookmark, defaults to targets uid.
 */
function eitict_bookmark_autocreate($details) {
  $target = $details['node'];

  $values = array(
    'type' => 'bookmark',
    'uid' => isset($details['uid']) ? $details['uid'] : $target->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );

  // Set the basics.
  $node = entity_create('node', $values);
  $emw = entity_metadata_wrapper('node', $node);
  $temw = entity_metadata_wrapper('node', $target);
  $emw->title->set($target->title);

  // Set the type.
  if ($target->type == 'article') {
    $term_name = ucfirst($temw->field_article_type->value());
    $bookmark_terms = taxonomy_get_term_by_name($term_name, 'bookmark_type');
    $bookmark_term = reset($bookmark_terms);
    $emw->field_bm_bookmark_type->set($bookmark_term->tid);
  }

  $emw->field_bm_reference_type->set('internal');
  $emw->field_bm_reference->set(intval($target->nid));

  // And now let's check whether we want to re-use an image of the target node.
  if (isset($details['image_field'])) {
    $field_name = $details['image_field'];

    $image = $temw->{$field_name}->value();
    if (!empty($image)) {
      $emw->field_bm_image->set($image);
    }
  }
  $emw->save();

  drupal_set_message(t('A bookmark was created automatically.<br />!action', array(
    '!action' => l(t('Click here to adjust.'), 'node/' . $emw->raw()->nid . '/edit')
  )));
}
