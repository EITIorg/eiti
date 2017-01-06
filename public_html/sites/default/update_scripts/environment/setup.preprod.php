<?php

/**
 * @file: SETUP ENVIRONMENT: preprod
 * @desc: This script can be used to setup preprod environments.
 *
 * This is an update script for setting up PREPROD environments. The script
 * should run automatically at the end of the build process.
 *
 * Pre-production environments should behave just like production environments
 * but all the warning and error messages should also be displayed to the user.
 */

// Skip if we build other environments based on preprod.
if (PROJECT_ENVIRONMENT == 'preprod') {
  // Save a watchdog entry for this build.
  watchdog('us-environment', 'Setup PREPROD Environment');

  // Set the xmlsitemap base URL.
  variable_set('xmlsitemap_base_url', 'https://preprod.eiti.org');
}

// Enable CSS and JavaScript aggregation.
variable_set('preprocess_css', 1);
variable_set('preprocess_js', 1);

// Disable LESS Developer mode.
variable_set('less_devel', 0);
variable_set('less_watch', 0);

// Error messages to display:
//   ERROR_REPORTING_HIDE => None
//   ERROR_REPORTING_DISPLAY_SOME => Errors and warnings
//   ERROR_REPORTING_DISPLAY_ALL => All messages
variable_set('error_level', ERROR_REPORTING_DISPLAY_ALL);

// Provide a list of modules to be disabled and uninstalled.
$modules = array(
  'googleanalytics',
);
// Uninstall modules
_us_module__uninstall($modules);


// Include the production setup script.
include $script_directory . '/setup.production.php';
