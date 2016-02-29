<?php
/**
 * @file
 * Define helper functions.
 */

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function helpertheme_features_component_export_alter(&$component_export, $component) {
  $entries_list = array();
  switch ($component) {
    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        'site_footer_contact',
        'site_footer_legal',
        'site_footer_slogan',
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
 * Implements hook_form_FORM_ID_alter() for menu_edit_item().
 */
function helpertheme_form_menu_edit_item_alter(&$form, &$form_state, $form_id) {
  $menus = array(
    'main-menu',
    'menu-footer-social',
  );
  if (!in_array($form['original_item']['#value']['menu_name'], $menus)) {
    return;
  }

  $mlid = $form['mlid']['#value'];

  $form['helpertheme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Icon Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['helpertheme']['#attached']['css'][] = array(
    'type' => 'inline',
    'data' => '.radioicon-label svg {height: 32px; width: 32px; vertical-align: middle !important; }',
  );

  $icons = helpertheme_get_svg_icons();
  $options = array('' => t('<none>'));
  $options += drupal_map_assoc(array_keys($icons));

  $selected_icon = variable_get(HELPERTHEME_SVG_ICON_NAME_PREFIX . $mlid, '');

  $form['helpertheme']['helpertheme_icon'] = array(
    '#type' => 'radioicons',
    '#title' => t('Icon'),
    '#options' => $options,
    '#icons' => $icons,
    '#default_value' => $selected_icon,
  );

  $form['#submit'][] = 'helpertheme_form_menu_edit_item_save_icon';
}

/**
 * Submit handler for menu_edit_item form. Save icon for menu link.
 *
 * @TODO: Remove variable after a memnu link is deleted.
 */
function helpertheme_form_menu_edit_item_save_icon($form, &$form_state) {
  $mlid = $form_state['values']['mlid'];

  if (!empty($form_state['values']['helpertheme_icon'])) {
    variable_set(HELPERTHEME_SVG_ICON_NAME_PREFIX . $mlid, $form_state['values']['helpertheme_icon']);
  }
  else {
    variable_del(HELPERTHEME_SVG_ICON_NAME_PREFIX . $mlid);
  }
}
