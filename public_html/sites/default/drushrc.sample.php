<?php

/**
 * @file
 * Drush environment specific configuration sample file.
 * Copy this file to drushrc.custom.php and update the information.
 *
 * NOTE: Do not commit 'drushrc.custom.php' to version control!
 */

/**
 * By default Drupal's $GLOBALS['base_url'] will be set to http://default. This
 * may cause some issues with URLs for the Apache Solr index, URLs for inline
 * images, etc.
 *
 * NOTE: It also helps with generating one time login links using `drush uli`.
 */
$options['uri'] = "http://eiti.local";  // Without a trailing slash.
