<?php

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
