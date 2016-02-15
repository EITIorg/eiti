<?php
/**
 * @file
 * eitiet_implementing_country.custom.inc
 */

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function eitiet_implementing_country_features_component_export_alter(&$component_export, $component) {
  $entries_list = array();
  switch ($component) {
    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // We use "the same allowed layouts as standard Panels pages".
        'panelizer_implementing_country:normal_allowed_layouts',

        // We use "the same allowed content as standard Panels pages".
        'panelizer_implementing_country:normal_allowed_types',
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
