# some help tricks to start ddev of this project with postgres on Macbook.
# rename this file to config.custom.yaml and
# uncomment the next setting for avoid creating settings.ddev.php automatically during ddev start
#  disable_settings_management: true

# Also you need to disable including settings.ddev.php in settings.php and in settings.custom.php
# All settings should be here public_html/sites/default/settings.custom.php
# see:
#  // settings.custom.php example
#  $host = "postgres";
#  $port = 5432;
#  if (empty(getenv('DDEV_PHP_VERSION'))) {
#    $host = "127.0.0.1";
#    $port = 32946;
#  }
#  $databases['default']['default'] = array(
#    'database' => "db",
#    'username' => "db",
#    'password' => "db",
#    'host' => $host,
#    'driver' => "pgsql",
#    'port' => $port,
#    'prefix' => "",
#  );
#  ini_set('session.gc_probability', 1);
#  ini_set('session.gc_divisor', 100);
#  ini_set('session.gc_maxlifetime', 200000);
#  ini_set('session.cookie_lifetime', 2000000);
#  $drupal_hash_salt = 'hsjaxFtQadSsYEPajxTTabSzGQJaFmPxrQBgDMdfqbLXKmroWKzVQOmoqGJYIetW';

# Working with db
# import_DB:
# ../public_html$ zcat dump_local.sql.gz | drush sqlc
# export_DB:
# ../public_html$ drush sql-dump --result-file=./dump_local.sql

# Also you can try to use next command if you have appropriate scripts in .ddev/commands/postgres
#  ddev pgsql_export : Use pg_dump to export db to .ddev/import-db/postgresql.db.sql
#  ddev pgsql_import : Use pgsql to import .ddev/import-db/postgresql.db.sql into db - Note that this must be executed with an empty database.
