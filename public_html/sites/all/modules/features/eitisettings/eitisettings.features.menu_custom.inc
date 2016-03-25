<?php
/**
 * @file
 * eitisettings.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function eitisettings_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-footer-information.
  $menus['menu-footer-information'] = array(
    'menu_name' => 'menu-footer-information',
    'title' => 'Footer Information',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-footer-navigation.
  $menus['menu-footer-navigation'] = array(
    'menu_name' => 'menu-footer-navigation',
    'title' => 'Footer Navigation',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-footer-social.
  $menus['menu-footer-social'] = array(
    'menu_name' => 'menu-footer-social',
    'title' => 'Footer Social',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-site-navigation.
  $menus['menu-site-navigation'] = array(
    'menu_name' => 'menu-site-navigation',
    'title' => 'Site Navigation',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
    'language' => 'und',
    'i18n_mode' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer Information');
  t('Footer Navigation');
  t('Footer Social');
  t('Main menu');
  t('Site Navigation');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('User menu');

  return $menus;
}
