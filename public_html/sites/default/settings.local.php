<?php
/**
 * The current project environment.
 * NOTE: The variable can be used inside update scripts, use only the following
 *       values: local, staging, preprod, production, other.
 */
define('PROJECT_ENVIRONMENT', 'local');

if (PROJECT_ENVIRONMENT == 'local') {
  $databases['default']['default'] = [
    'database' => "db",
    'username' => "db",
    'password' => "db",
    'host' => "postgres",
    'driver' => "pgsql",
    'port' => '5432',
    'prefix' => "",
  ];

  // Allow developers to debug environments.
  $hide_errors = FALSE;
  if ($hide_errors && PROJECT_ENVIRONMENT == 'production') {
    ini_set('error_reporting', E_ALL & ~E_DEPRECATED & ~E_STRICT);
    ini_set('display_errors', 'Off');
  }
  else {
    ini_set('error_reporting', E_ALL);
    ini_set('display_errors', 'On');
  }

  $conf['theme_debug'] = TRUE;

  /**
   * "Stage File Proxy" is recommended for development environments to easily
   * retrieve files from the origin environment of the DB.
   */
  //$conf['stage_file_proxy_origin'] = "http://example.org"; // no trailing slash!
  //$conf['stage_file_proxy_origin_dir'] = 'sites/default/files';

  /**
   * Custom Memcache daemon configuration.
   */
  $use_memcache = TRUE;
  if ($use_memcache) {
    // Use the DB name for unique memcache key prefix.
//    $conf['memcache_key_prefix'] = $databases['default']['default']['database'];

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

    $conf['memcache_stampede_protection'] = TRUE;

    // Memcache servers and bins info.
    $conf['memcache_servers'] = [
      '127.0.0.1:11211' => 'default',
      //'unix:///path/to/socket' => 'default'
    ];
    $conf['memcache_bins'] = [
      'cache' => 'default',
    ];

  }
}

/**
 * Debugging helper.
 */
function pa($mixed, $stop = FALSE) {
  $ar = debug_backtrace();
  $key = pathinfo($ar[0]['file']);
  $key = $key['basename'] . ':' . $ar[0]['line'];
  $print = array($key => $mixed);
  echo '<pre>' . print_r($print, 1) . '</pre>';
  if ($stop == 1) {
    exit();
  }
}

