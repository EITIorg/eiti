<?php


// Provide a list of modules to be installed.
$modules = array(
  'less',
  'html5_tools',
);
_us_module__install($modules);

// Set the default "LESS engine".
variable_set('less_engine', 'less.php');

// Enable theme and set it as default.
_us_theme__enable('eiti', TRUE);

// Disable default Drupal theme.
_us_theme__disable('bartik');
