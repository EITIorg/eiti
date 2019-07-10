<?php

/**
 * Implements hook_drush_command().
 */
function helpergeneric_drush_command() {
  $items = array();
  $items['eiti-s3fs-copy-local'] = array(
    'description' => dt('Copy local files from your public file system into your S3 bucket.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('eiti-s3-cl'),
    'callback' => 'drush_eiti_s3fs_copy_local',
  );
  return $items;
}

/**
 * Copy all files from the local public filesystem folders into S3.
 *
 * Based on drush_s3fs_copy_local().
 */
function drush_eiti_s3fs_copy_local() {
  $config = _s3fs_get_config();
  if (!_s3fs_validate_config($config)) {
    drupal_set_message(
      dt('Unable to validate your s3fs configuration settings. Please configure S3 File System from the admin/config/media/s3fs page and try again.'),
      'error'
    );
    return;
  }
  _helpergeneric_s3fs_copy_file_system_to_s3();
}

/**
 * Copies all the local files from the public file system into S3.
 */
function _helpergeneric_s3fs_copy_file_system_to_s3() {
  $scheme = 'public';
  $source_folder = realpath(variable_get('file_public_path', conf_path() . '/files'));
  $config = _s3fs_get_config();
  $public_folder = !empty($config['public_folder']) ? $config['public_folder'] : 's3fs-public';
  $file_paths = _helpergeneric_s3fs_recursive_dir_scan($source_folder);

  $i = 0;
  $j = 0;
  $msg_count = 100;
  foreach ($file_paths as $path) {
    $relative_path = str_replace($source_folder . '/', '', $path);
    copy($path, "s3://$public_folder/$relative_path");
    $i++;
    $j++;
    if ($i == $msg_count) {
      print "$j. Copied $msg_count files.\n";
      $i = 0;
    }
  }

  drupal_set_message(t('Copied all local %scheme files to S3.', array('%scheme' => $scheme)), 'status');
}

/**
 * Returns file paths.
 *
 * Based on _s3fs_recursive_dir_scan().
 */
function _helpergeneric_s3fs_recursive_dir_scan($dir) {
  $source_folder = realpath(variable_get('file_public_path', conf_path() . '/files'));
  $skip_dirs = array('css', 'ctools', 'js', 'languages', 'less', 'styles', 'xmlsitemap');

  $output = array();
  $files = scandir($dir);
  foreach ($files as $file) {
    $path = "$dir/$file";

    if ($file != '.' && $file != '..') {
      // In case they put their private root folder inside their public one,
      // skip it. When listing the private file system contents, $path will
      // never trigger this.
      if ($path == realpath(variable_get('file_private_path'))) {
        continue;
      }

      if (is_dir($path)) {
        // Skip unnecessary directories in the source folder.
        if ($dir === $source_folder) {
          $dirs = explode('/', $path);
          $last_dir = end($dirs);
          if ($last_dir && !in_array($last_dir, $skip_dirs)) {
            $output = array_merge($output, _s3fs_recursive_dir_scan($path));
          }
        }
        else {
          $output = array_merge($output, _s3fs_recursive_dir_scan($path));
        }
      }
      else {
        $output[] = $path;
      }
    }
  }
  return $output;
}
