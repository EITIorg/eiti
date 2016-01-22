<?php


// Provide a list of modules to be installed.
$modules = array(
  'eitientity_company',
  'eitientity_gfs_code',
  'eitientity_implementing_country',
  'eitientity_indicator',
  'eitientity_indicator_value',
  'eitientity_summary_data',
  'helpergeneric',
);
_us_module__install($modules);

// Clear system caches.
drupal_flush_all_caches();


// Prepare a list of features to be installed.
$feature_names = array(
  'eitict_article',
  'eitict_document',
  'eitict_mention',
  'eitict_person',
  'eitientities',
  'eitiet_company',
  'eitiet_summary_data',
  'eitii18n',
  'eitipermissions',
  'eititaxonomies',
);
_us_features__install($feature_names);


// Revert all features and clear system caches.
_us_features__revert_all();
drupal_flush_all_caches();
