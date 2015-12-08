
# MCA Server Requirements


## Minimum Hardware Requirements
  * CPU: 2 cores, 64-bit

  * RAM: 8GB

  * HDD: 40GB - for storing user uploaded files, only 200MB are required for the project.


## Software Requirements
  * Operating System: any Enterprise Linux v7.x - see https://www.scientificlinux.org

  * Nginx v1.6 - see https://www.drupal.org/requirements/webserver

  * PostgreSQL v9.2 - see https://www.drupal.org/requirements/database

  * PHP v5.4 - see https://www.drupal.org/requirements/php
    
    And libraries:
    * cli
    * fpm - see http://wiki.nginx.org/Drupal
    * gd
    * intl
    * mbstring
    * pdo
    * pgsql
    * xml
    
    Settings: 
    ```
    max_execution_time = 60
    memory_limit = 512M
    post_max_size = 128M
    upload_max_filesize = 128M
    ```

  * Memcache v1.4

  * git


## Backups

A backup system should be put in place for both the DataBase and the user
uploaded files, located under `public_html/sites/default/files`.
