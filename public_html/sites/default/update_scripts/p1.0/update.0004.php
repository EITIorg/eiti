<?php

// Provide a list of modules to be installed.
$modules = array(
  'date',
    'date_api',
    //'date_migrate',
    //'date_migrate_example',
    'date_popup',
    //'date_repeat',
    //'date_tools',
    //'date_views',
);
_us_module__install($modules);

// Update site date settings.
variable_set('date_first_day', 1);
variable_set('date_format_long', 'l, F j, Y - H:i');
variable_set('date_format_medium', 'D, Y-m-d H:i');
variable_set('date_format_short', 'm/d/Y - H:i');
