<?php
/**
 * @file
 * This file contains theme functions overrides.
 */

/**
 * Implements theme_menu_tree() for the main_menu.
 */
function eiti_menu_tree__main_menu__toplevel(array $variables) {
  return '<ul class="navigation-list-toplevel clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree() for main_menu sublevel.
 */
function eiti_menu_tree__main_menu__sublevel(array $variables) {
  return '<ul class="navigation-list-sublevel clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link() for main_menu.
 */
function eiti_menu_link__styled_menu(array $variables) {
  // Remove the 'leaf' class.
  if (in_array('leaf', $variables['element']['#attributes']['class'])) {
    $variables['element']['#attributes']['class'] = array_diff($variables['element']['#attributes']['class'], array('leaf'));
  }

  // Remove the 'expanded' class.
  if (in_array('expanded', $variables['element']['#attributes']['class'])) {
    $variables['element']['#attributes']['class'] = array_diff($variables['element']['#attributes']['class'], array('expanded'));
  }

  // Remove the 'collapsed' class.
  if (in_array('collapsed', $variables['element']['#attributes']['class'])) {
    $variables['element']['#attributes']['class'] = array_diff($variables['element']['#attributes']['class'], array('collapsed'));
  }

  // Get the Parent Link ID.
  $plid = $variables['element']['#original_link']['plid'];

  if (empty($plid)) {
    // Style the menu toplevel.
    $top_level_nav[] = $variables['element']['#original_link']['mlid'];
    return __eiti_menu_link__level($variables, 'toplevel');
  }

  if (!empty($plid) && in_array($plid, $top_level_nav)) {
    // Style the menu sublevel.
    return __eiti_menu_link__level($variables, 'sublevel');
  }

  // Directly call the original theme function.
  return theme_menu_link($variables);
}

/**
 * Helper for theme_menu_tree().
 */
function __eiti_menu_link__level(array &$variables, $level = NULL) {
  $element = $variables['element'];

  switch ($level) {
    case 'toplevel':
      // Add list item class.
      $element['#attributes']['class'][] = 'top-listitem';

      // Add title as list item class.
      $extra_class = $element['#title'];
      if (function_exists('transliteration_get')) {
        $extra_class = transliteration_get($extra_class);
      }
      $extra_class = drupal_html_class('top-listitem-' . $extra_class);
      $element['#attributes']['class'][] = $extra_class;

      // Add link class.
      $element['#localized_options']['attributes']['class'][] = 'top-link';

      // Set the link title if not provided.
      if (empty($element['#localized_options']['attributes']['title'])) {
        $element['#localized_options']['attributes']['title'] = $element['#title'];
      }

      if ($element['#below']) {
        // Change the override the rendering of the subitems wrapper.
        $element['#below']['#theme_wrappers'] = array('menu_tree__main_menu__sublevel');

        // Add link class.
        $element['#localized_options']['attributes']['class'][] = 'with-sublevel';
      }

      break;

    case 'sublevel':
      // Add list item class.
      $element['#attributes']['class'][] = 'sublevel-wrapper';

      // Add link class.
      $element['#localized_options']['attributes']['class'][] = 'sublevel-title';

      if ($element['#below']) {
        // Add link class.
        $element['#localized_options']['attributes']['class'][] = 'with-sublevel';
      }
      break;
  }

  // Render the submenu items.
  $output = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $output .= '<div class="navigation-sublevel clearfix">' . $sub_menu . '</div>';
  }

  // Get the svg icon for this menu link.
  $svgicon = '';
  $mlid = $element['#original_link']['mlid'];
  $selected_icon = variable_get(HELPERTHEME_SVG_ICON_NAME_PREFIX . $mlid, '');
  if (!empty($selected_icon)) {
    $svgicon = helpertheme_get_svg_icon($selected_icon, array('width' => '1.5em', 'height' => '1.5em')) . ' ';
  }

  // Render the menu link.
  $link_title = $svgicon . '<span class="text">' . check_plain($element['#title']) . '</span>';
  $link = l($link_title, $element['#href'], array_merge_recursive($element['#localized_options'], array('html' => TRUE)));

  $tag = 'li';
  return "<$tag" . drupal_attributes($element['#attributes']) . '>' . $link . $output . "</$tag>\n";
}


/**
 * Returns HTML for a set of links.
 *
 * @see theme_links().
 */
function eiti_links__enhanced($variables) {
  return _helpertheme_links__enhanced($variables);
}

/**
 * Override the default select.
 */
function eiti_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  if (isset($element['#use_unsafe_labels']) && $element['#use_unsafe_labels'] == TRUE) {
    return '<select' . drupal_attributes($element['#attributes']) . '>' . _eiti_form_select_options($element) . '</select>';
  }
  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}

/**
 * Custom implementation of form_select_options.
 */
function _eiti_form_select_options($element) {
  if (!isset($choices)) {
    $choices = $element['#options'];
  }
  // array_key_exists() accommodates the rare event where $element['#value'] is NULL.
  // isset() fails in this situation.
  $value_valid = isset($element['#value']) || array_key_exists('#value', $element);
  $value_is_array = $value_valid && is_array($element['#value']);
  $options = '';
  foreach ($choices as $key => $choice) {
    if (is_array($choice)) {
      $options .= '<optgroup label="' . check_plain($key) . '">';
      $options .= form_select_options($element, $choice);
      $options .= '</optgroup>';
    }
    elseif (is_object($choice)) {
      $options .= form_select_options($element, $choice->option);
    }
    else {
      $key = (string) $key;
      if ($value_valid && (!$value_is_array && (string) $element['#value'] === $key || ($value_is_array && in_array($key, $element['#value'])))) {
        $selected = ' selected="selected"';
      }
      else {
        $selected = '';
      }
      $options .= '<option value="' . check_plain($key) . '"' . $selected . '>' . filter_xss_admin($choice) . '</option>';
    }
  }
  return $options;
}
