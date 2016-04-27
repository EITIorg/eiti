<?php

// Provide a list of modules to be disabled and uninstalled.
$modules = array(
  'admin_menu_toolbar',
);
_us_module__uninstall($modules);

// Provide a list of modules to be installed.
$modules = array(
  'adminimal_admin_menu',
  'admin_views',
  'shortcut',

  'views_bulk_operations',
    'actions_permissions',

  'entitycache',
  'memcache',
    'memcache_admin',
);
_us_module__install($modules);

// Use adminimal as the administration theme.
variable_set('admin_theme', 'adminimal');
_us_theme__enable('adminimal');
