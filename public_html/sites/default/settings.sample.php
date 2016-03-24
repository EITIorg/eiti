<?php

/**
 * @file
 * Environment specific configuration overrides sample file.
 * Copy this file to settings.custom.php and update the information.
 *
 * Add the following lines to the settings file:
 *  - comment: Allow environment specific configuration overrides.
 *  - phpcode: include_once('settings.custom.php');
 *
 * NOTE: Do not commit 'settings.custom.php' to version control!
 */

/**
 * The current project environment.
 * NOTE: The variable can be used inside update scripts, use only the following
 *       values: local, staging, preprod, production, other.
 */
define('PROJECT_ENVIRONMENT', 'local');

// Allow developers to debug production environments.
$hide_errors = TRUE;
if ($hide_errors && PROJECT_ENVIRONMENT == 'production') {
  ini_set('error_reporting', E_ALL & ~E_DEPRECATED);
  ini_set('display_errors', FALSE);
  ini_set('display_startup_errors', FALSE);
}

// Reset the database configuration.
$databases = array();

// Main database settings.
$databases['default']['default'] = array(
  'driver'   => 'pgsql',
  'database' => 'eiti_local',
  'username' => 'eiti_user',
  'password' => 'demo1',
  'host'     => '127.0.0.1',
  'prefix'   => '',
);

/**
 * Salt for one-time login links and cancel links, form tokens, etc. It should
 * be unique to each environment because of security concerns.
 *
 * NOTE: If this variable is empty, a hash of the serialized database
 * credentials will be used as a fallback salt.
 */
$drupal_hash_salt = '';

/**
 * Environments should have different settings, override the Search API settings.
 */
//$conf['search_api_override_mode'] = 'load';
//$conf['search_api_override_servers']['solr_server'] = array(
//  'name' => '(overridden) Solr Server for production',
//  'description' => '(overridden) The Solr search server configured for the production environment.',
//  'options' => array(
//    'path' => '/solr/eiti_production',
//  ),
//);

/**
 * Memcache daemon configuration.
 */
$use_memcache = FALSE;
if ($use_memcache) {
  // Use the DB name for unique memcache key prefix.
  $conf['memcache_key_prefix'] = $databases['default']['default']['database'];

  // Make memcache the default cache class.
  $conf['cache_backends'][] = 'sites/all/modules/contrib/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';

  // Use non-volatile storage for form cache.
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';

  // Do not bootstrap the DB when serving cached pages to anonymous visitors.
  $conf['page_cache_without_database'] = TRUE;
  $conf['page_cache_invoke_hooks'] = FALSE;

  // Use memcache for the locking mechanism (the semaphore table).
  $conf['lock_inc'] = 'sites/all/modules/contrib/memcache/memcache-lock.inc';

  // Memcache servers and bins info.
  $conf['memcache_servers'] = array(
    '127.0.0.1:11211' => 'default',
    //'unix:///path/to/socket' => 'default'
  );
  $conf['memcache_bins'] = array(
    'cache' => 'default',
  );
}

/**
 * "Stage File Proxy" is recommended for development environments to easily
 * retrieve files from the origin environment of the DB.
 */
//$conf['stage_file_proxy_origin'] = "http://example.org"; // no trailing slash!
//$conf['stage_file_proxy_origin_dir'] = 'sites/default/files';

/**
 * Deny access to unwanted visitors.
 */
$deny_access = FALSE;
if ($deny_access && php_sapi_name() != 'cli') {
  if (empty($_COOKIE['KnockKnock']) || $_COOKIE['KnockKnock'] != 'Nobel') {
    // - Knock, Knock. - Who’s there? - Nobel. - Nobel who? - No bell, that’s why I knocked!
    print 'You are not welcome here!';
    exit();
  }
}
