<?php

// Delete all links from menu.
_us_menu__delete_links('user-menu');

$link = array(
  'link_path' => 'admin/content',
  'link_title' => 'Content',
  'weight' => -45,
);
_us_menu__create_link($link, 'user-menu');

$link = array(
  'link_path' => 'admin/people',
  'link_title' => 'People',
  'weight' => -44,
);
_us_menu__create_link($link, 'user-menu');

$link = array(
  'link_path' => 'admin/settings',
  'link_title' => 'Settings',
  'weight' => -43,
);
_us_menu__create_link($link, 'user-menu');
