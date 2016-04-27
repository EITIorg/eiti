<?php


/**
 * Implements hook_form_views_exposed_form_alter().
 */
function eitict_document_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $view = $form_state['view'];

  if ($view->name == 'publications') {
    // Remove description for the "Document Category" exposed filter.
    if (isset($form['category']['#description'])) {
      unset($form['category']['#description']);
    }
  }
}
