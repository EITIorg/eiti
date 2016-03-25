<?php

// Provide a list of modules to be disabled and uninstalled.
$modules = array(
  'admin_menu_toolbar',  // TODO: Optimize module. Do not load jQuery a 2nd time.
);
_us_module__uninstall($modules);

// Provide a list of modules to be installed.
$modules = array(
  'adminimal_admin_menu',
);
_us_module__install($modules);
