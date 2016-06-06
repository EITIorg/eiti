<?php

// Install Google Analytics only on production.
if (PROJECT_ENVIRONMENT == 'production') {
  // Provide a list of modules to be installed.
  $modules = array(
    'googleanalytics',
  );
  _us_module__install($modules);
}
