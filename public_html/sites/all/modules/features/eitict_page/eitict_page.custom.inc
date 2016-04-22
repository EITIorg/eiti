<?php
/**
 * @file
 * eitict_page.custom.inc
 */

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function eitict_page_features_component_export_alter(&$component_export, $component) {
  $entries_list = array();
  switch ($component) {
    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // We use "the same allowed layouts as standard Panels pages".
        'panelizer_node:page_allowed_layouts',

        // We use "the same allowed content as standard Panels pages".
        'panelizer_node:page_allowed_types',
      );
  }

  $removed_entries_list = array();
  foreach ($entries_list as $name) {
    if (isset($component_export['options']['sources'][$name])) {
      unset($component_export['options']['sources'][$name]);
      $removed_entries_list[] = check_plain($name);
    }

    if ($component == 'dependencies') {
      if (isset($component_export['options']['detected'][$name])) {
        unset($component_export['options']['detected'][$name]);
      }
    }
  }
}


/**
 * Implements hook_form_content_access_page_alter().
 */
function eitict_page_form_content_access_page_alter(&$form, &$form_state, $form_id) {
  $form['per_role']['#description'] = t('Note that content which is not published is treated in a different way. Access can not be granted from this form.');

  foreach (element_children($form['per_role']) as $key) {
    if (empty($form['per_role'][$key]['#type']) || $form['per_role'][$key]['#type'] != 'checkboxes') {
      continue;
    }

    switch ($key) {
      case 'view':
        $form['per_role'][$key]['#title'] =  t('View page');
        break;
      default:
        if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
          $form['per_role'][$key]['#process'][] = 'eitict_page_content_access_hide_checkboxes';
        }
        break;
    }
  }
}

/**
 * Formapi #process callback, that disables checkboxes for roles without access to content
 */
function eitict_page_content_access_hide_checkboxes($element) {
  unset($element['#prefix']);
  unset($element['#suffix']);
  unset($element['#title']);

  foreach (element_children($element) as $key) {
    $element[$key]['#type'] = 'value';
    $element[$key]['#value'] = $element[$key]['#default_value'];
  }
  return $element;
}
