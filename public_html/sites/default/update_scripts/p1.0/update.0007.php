<?php

// Provide a list of modules to be installed.
$modules = array(
  'contentwidget',
  'eiti_api',
  'eiti_ctools_extra',
  'eiti_migration',
  'eitientity_gfs_code',
  'eitientity_implementing_country',
  'eitientity_indicator',
  'eitientity_indicator_value',
  'eitientity_organisation',
  'eitientity_revenue_stream',
  'eitientity_summary_data',
  'helperentity',
  'helperfield',
  'helpergeneric',
  'helpertheme',
);
_us_module__install($modules);

// Clear system caches.
drupal_flush_all_caches();


// Prepare a list of features to be installed.
$feature_names = array(
  'eitict_article',
  'eitict_bookmark',
  'eitict_document',
  'eitict_mention',
  'eitict_page',
  'eitict_person',
  'eitientities',
  'eitiet_file',
  'eitiet_implementing_country',
  'eitiet_organisation',
  'eitiet_summary_data',
  'eitii18n',
  'eitipanels',
  'eitipermissions',
  'eitisettings',
  'eititaxonomies',
  'eitiwidgets',
);
_us_features__install($feature_names);


// Revert all features and clear system caches.
_us_features__revert_all();
drupal_flush_all_caches();
