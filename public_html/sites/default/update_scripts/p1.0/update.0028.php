<?php

// Provide a list of modules to be installed.
$modules = array(
  'xmlsitemap',
    // 'xmlsitemap_custom',
    // 'xmlsitemap_engines_test',
    'xmlsitemap_entity',
    'xmlsitemap_i18n',
    // 'xmlsitemap_menu',
    // 'xmlsitemap_modal',
    'xmlsitemap_node',
    // 'xmlsitemap_taxonomy',
    // 'xmlsitemap_user',
    'xmlsitemap_engines',
);
_us_module__install($modules);

// Prepare a list of features to be installed.
$feature_names = array(
  'eitict_progress_report',
);
_us_features__install($feature_names);
