<?php

// Updated from 20161022.69.01 to update.0027.
// Provide a list of modules to be installed.
$modules = array(
  'eitientity_score_data',
);
_us_module__install($modules);

// Prepare a list of features to be installed.
$feature_names = array(
  'eitiet_score_data',
  'eitiet_score_requirement',
);
_us_features__install($feature_names);
