<?php

// Provide a list of modules to be enabled and installed.
$modules = array(
  'facetapi',
    //'current_search',

  'search_api',
    'search_api_facetapi',
    'search_api_views',
  'search_api_override',
  'search_api_solr',
);
_us_module__install($modules);

// Prepare a list of features to be installed.
$feature_names = array(
  'eitisearch',
);
_us_features__install($feature_names);
