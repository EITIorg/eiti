<?php

// Update the value for variable: link_extra_domains
// In this particular case, we want to add .scot domain.
$default_arr = explode('|', LINK_DOMAINS);
$value = variable_get('link_extra_domains', $default_arr);

// Add extra domain.
$value[] = 'scot';

// Save.
variable_set('link_extra_domains', $value);
