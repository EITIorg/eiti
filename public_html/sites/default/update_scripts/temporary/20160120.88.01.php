<?php


// Provide a list of modules to be installed.
$modules = array(
  'contentblock',
  'contentwidget',
  'eiti_api',
  'eiti_migration',
  'eitientity_gfs_code',
  'eitientity_implementing_country',
  'eitientity_indicator',
  'eitientity_indicator_value',
  'eitientity_organisation',
  'eitientity_revenue_stream',
  'eitientity_summary_data',
  'helperentity',
  'helpergeneric',
  'helpertheme',
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
  'eitiet_contentblock',
  'eitiet_organisation',
  'eitiet_summary_data',
  'eitii18n',
  'eitipermissions',
  'eititaxonomies',
);
_us_features__install($feature_names);


// Revert all features and clear system caches.
_us_features__revert_all();
drupal_flush_all_caches();
