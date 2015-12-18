<?php

/**
 * Implements hook_field_group_build_pre_render_alter.
 *
 * We use this, because no one has solved the fieldgroup conditional fields support.
 * @see https://www.drupal.org/node/1161314
 */
function eitict_article_field_group_build_pre_render_alter(&$element) {
  // Apply only to our form.
  if (isset($element['#form_id']) && $element['#form_id'] == 'article_node_form') {
    // Make sure the group is there.
    if (!empty($element['group_event_details'])) {
      $element['group_event_details']['#id'] = 'group-event-details';
      $element['group_event_details']['#states'] = array(
        'visible' => array(
          'input[name="field_article_type[und]"]' => array('value' => 'event'),
        ),
      );
    }
  }
}
