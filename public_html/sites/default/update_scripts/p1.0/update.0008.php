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


// Set the footer slogan.
variable_set('site_footer_slogan', 'See how natural resources are managed and used in your country');

// Set the footer contact information.
$footer_contact = <<<EOD
Ruseløkkveien 26, 0251<br>
Oslo, Norway<br>
+47 222 00 800<br>
<a href="mailto:secretariat@eiti.org">secretariat@eiti.org</a>
EOD;
variable_set('site_footer_contact', $footer_contact);

// Set the footer contact information.
$footer_legal = <<<EOD
Unless otherwise noted, you may republish our content for free. Please give credit to our source (for web, with direct link, for print with EITI International Secretariat, eiti.org).
EOD;
variable_set('site_footer_legal', $footer_legal);
