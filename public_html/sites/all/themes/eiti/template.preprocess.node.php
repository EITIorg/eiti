<?php
/**
 * @file
 * This file contains changes related to the node(s).
 */

/**
 * Implements hook_preprocess_node().
 */
function eiti_preprocess_node(&$variables) {
  $new_suggestion = implode('__', ['node', $variables['type'], $variables['view_mode']]);
  array_unshift($variables['theme_hook_suggestions'], $new_suggestion);

  $elements = $variables['elements'];
  // Hide Board link if there is no Board member on Stakeholder page.
  if ($elements['#bundle'] == 'stakeholder') {
    if (!empty($variables['content']['board_link']) && empty($elements['field_fpp_person_list'])) {
      hide($variables['content']['board_link']);
    }
  }
}
