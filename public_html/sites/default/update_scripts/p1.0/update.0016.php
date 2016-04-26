<?php

// Provide a list of CORE modules to be disabled and uninstalled.
$modules = array(
  'leaflet',
);
_us_module__uninstall($modules);

// Provide a list of modules to be enabled and installed.
$modules = array(
  'content_access',
);
_us_module__install($modules);

// Prepare a list of features to be installed.
$feature_names = array(
  'eitict_stakeholder',
);
_us_features__install($feature_names);

// Use adminimal_helpertheme as the administration theme.
variable_set('admin_theme', 'adminimal_helpertheme');
_us_theme__enable('adminimal');
_us_theme__enable('adminimal_helpertheme');
