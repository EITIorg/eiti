<?php
/**
 * @file
 * Drupal site-specific configuration file for local development.
 *
 * Important! Rename base setting.php to setting_default.php and rename this file to settings.php.
 * And don't commit new settings.php file!
 */

$databases = array();
$update_free_access = FALSE;
$drupal_hash_salt = '1234';
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);

$conf['404_fast_paths_exclude'] = '/\/(?:styles)|(?:system\/files)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

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

  // Implements Memcache settings
  $conf['cache_backends'][] = 'sites/all/modules/contrib/memcache/memcache.inc';
  $conf['lock_inc'] = 'sites/all/modules/contrib/memcache/memcache-lock.inc';
  $conf['memcache_stampede_protection'] = TRUE;
  $conf['cache_default_class'] = 'MemCacheDrupal';
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
  $conf['page_cache_without_database'] = TRUE;
  $conf['page_cache_invoke_hooks'] = FALSE;
  $conf['memcache_servers'] = array('127.0.0.1:11211' => 'default');
  $conf['memcache_bins'] = array(
    'cache'                 =>  'default',
    'cache_block'           =>  'default',
    'cache_field'           =>  'default',
    'cache_filter'          =>  'default',
    'cache_image'           =>  'default',
    'cache_libraries'       =>  'default',
    'cache_menu'            =>  'default',
    'cache_page'            =>  'default',
    'cache_path'            =>  'default',
    'cache_rules'           =>  'default',
    'cache_token'           =>  'default',
    'cache_views'           =>  'default',
    'cache_views_data'      =>  'default',
  );

}

