<?php
/**
 * @file
 * This file contains changes related to the node(s).
 */

/**
 * Implements hook_preprocess_node().
 */
function eiti_preprocess_node(&$variables) {
  $new_suggestion = implode('__', array('node', $variables['type'], $variables['view_mode']));
  array_unshift($variables['theme_hook_suggestions'], $new_suggestion);
}
