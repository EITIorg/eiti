<?php
/**
 * @file
 * Define helper functions.
 */

/**
 * Returns an array of links for a navigation menu.
 *
 * @see: menu_navigation_links();
 *
 * @param string $menu_name
 * @param int $levels
 * @return array
 */
function helpertheme_menu_navigation_links($menu_name, $levels = 0) {
  // For now only return one level.
  if ($levels > 1) {
    $levels = 1;
  }

  // Get the menu hierarchy for the current page.
  $tree = menu_tree_page_data($menu_name, $levels);

  // Create a single level of links.
  $links = array();
  foreach ($tree as $item) {
    if ($link_tree = _helpertheme_prepare_tree($item)) {
      $key = 'menu-' . $item['link']['mlid'];
      if (!empty($link_tree['below'])) {
        $key .= ' has-sublevel';
      }
      // Keyed with the unique mlid to generate classes in theme_links().
      $links[$key] = $link_tree;
    }
  }

  return $links;
}

/**
 * Helper for helpertheme_menu_navigation_links().
 *
 * @param $item
 * @param bool $is_sublevel
 */
function _helpertheme_prepare_tree($item, $is_sublevel = FALSE) {
  if ($item['link']['hidden']) {
    return FALSE;
  }

  $link = $item['link']['localized_options'];
  $link['href'] = $item['link']['href'];
  $link['title'] = $item['link']['title'];
  $link['mlid'] = $item['link']['mlid'];

  // Add classes in order to ease the styling of links.
  $link['attributes']['class'][] = 'link';
  $link['attributes']['class'][] = $is_sublevel ? 'link-sublevel' : 'link-toplevel';
  $link['attributes']['class'][] = 'link-' . drupal_html_class($link['title']);

  // Prepare child elements.
  if (!empty($item['below'])) {
    foreach ($item['below'] as $subitems) {
      if ($link_subitems = _helpertheme_prepare_tree($subitems, TRUE)) {
        $link['below']['menu-' . $subitems['link']['mlid']] = $link_subitems;
      }
    }

    // If any sub-menus are present add an extra class.
    if (!empty($link['below'])) {
      $link['attributes']['class'][] = 'with-sublevel';
    }
  }

  return $link;
}

/**
 * Get the page title visibility.
 */
function helpertheme_page_title_get_status() {
  if (drupal_is_front_page()) {
    return FALSE;
  }

  return (bool) helpertheme_page_title_set_status();
}

/**
 * Set the page title visibility.
 */
function helpertheme_page_title_set_status($value = NULL) {
  static $status;
  if (!isset($value) && isset($status)) {
    return $status;
  }

  if (isset($value)) {
    $status = $value;
    return $status;
  }

  return FALSE;
}

/**
 * Get the extra classes for the page HTML tag.
 */
function helpertheme_get_html_classes() {
  return helpertheme_set_html_classes();
}

/**
 * Set extra classes for the page HTML tag.
 */
function helpertheme_set_html_classes($new = NULL) {
  static $classes = array();
  if (!isset($new)) {
    return $classes;
  }

  if (is_string($new)) {
    $new = array($new);
  }

  $classes = array_merge($classes, $new);
  return $classes;
}
