<?php

// Provide a list of modules to be installed.
$modules = array(
  'path',  // CORE module.
  'pathauto',
  'filefield_paths',
  'globalredirect',
  'redirect',
  'token',
  'transliteration',
);
_us_module__install($modules);

// Cleanup pathauto entity specific patterns.
db_delete('variable')
  ->condition('name', db_like("pathauto_") . '%' . db_like('pattern'), 'LIKE')
  ->execute();
variable_set('pathauto_node_pattern', '');
variable_set('pathauto_user_pattern', '');
if (module_exists('taxonomy')) {
  variable_set('pathauto_taxonomy_pattern', '');
}

// Cleanup pathauto punctuation rules.
db_delete('variable')
  ->condition('name', db_like("pathauto_punctuation_") . '%', 'LIKE')
  ->execute();

// Update pathauto settings.
variable_set('pathauto_verbose', 0);
variable_set('pathauto_separator', '-');
variable_set('pathauto_case', '1');
variable_set('pathauto_max_length', '100');
variable_set('pathauto_max_component_length', '100');
variable_set('pathauto_update_action', 2);
variable_set('pathauto_transliterate', 1);
variable_set('pathauto_reduce_ascii', 1);
variable_set('pathauto_ignore_words', '');

// Update redirect settings.
variable_set('redirect_auto_redirect', 1);
variable_set('redirect_passthrough_querystring', 1);
variable_set('redirect_warning', false);
variable_set('redirect_default_status_code', '301');
variable_set('redirect_page_cache', 0);
$period = 60 * 60 * 24 * 30 * 6;  // 180 days.
variable_set('redirect_purge_inactive', $period);

// Update globalredirect settings.
variable_set('redirect_global_home', 1);
variable_set('redirect_global_clean', 1);
variable_set('redirect_global_canonical', 1);
variable_set('redirect_global_deslash', 0);
variable_set('redirect_global_admin_paths', 0);
