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
