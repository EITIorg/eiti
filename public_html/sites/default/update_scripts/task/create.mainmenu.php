<?php

/**
 * @file: Create Main Menu Item Links.
 * @desc: This script can be used to (re)create the menu items.
 */

/**
 * Define main menu item links.
 */
function __us_main_menu_default_item_links() {
  $items = array();
  $items[] = array(
    'link_title' => 'Map',
    'link_path' => 'countries',
    'menu_name' => 'main-menu',
    'weight' => 0,
    'plid' => 0,
  );
  $items[] = array(
    'link_title' => 'Publications',
    'link_path' => 'resources',
    'menu_name' => 'main-menu',
    'weight' => 1,
    'plid' => 0,
  );
  $items[] = array(
    'link_title' => 'Analysis',
    'link_path' => 'news-events',
    'menu_name' => 'main-menu',
    'weight' => 2,
    'plid' => 0,
  );
  $items[] = array(
    'link_title' => 'About',
    'link_path' => '<front>',
    'menu_name' => 'main-menu',
    'weight' => 3,
    'plid' => 0,
  );
  $items[] = array(
    'link_title' => 'Connect',
    'link_path' => '<front>',
    'menu_name' => 'main-menu',
    'weight' => 4,
    'plid' => 0,
  );
  $items[] = array(
    'link_title' => 'Global Conference',
    'link_path' => 'http://www.lima2016.eiti.org',
    'menu_name' => 'main-menu',
    'weight' => 5,
    'plid' => 0,
  );

  return $items;
}

// Get the menu items and create those.
$main_menu_items = __us_main_menu_default_item_links();
foreach ($main_menu_items as $menu_item) {
  _us_menu__create_link($menu_item, 'main-menu');
}


