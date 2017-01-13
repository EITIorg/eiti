<?php
/**
 * @file
 * This file contains changes related to the panels.
 */

/**
 * Add some extra markup to the standard panel panes.
 */
function eiti_preprocess_panels_pane(&$vars) {
  // In this specific case, we want to add a class (with PID or pane id).
  if (!empty($vars['pane'])) {
    $pane = $vars['pane'];
    $vars['classes_array'][] = drupal_html_class('pane-pid-' . $pane->pid);
  }
}
