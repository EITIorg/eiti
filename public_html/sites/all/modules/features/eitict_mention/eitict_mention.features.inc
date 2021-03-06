<?php
/**
 * @file
 * eitict_mention.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eitict_mention_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function eitict_mention_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function eitict_mention_node_info() {
  $items = array(
    'mention' => array(
      'name' => t('Mention'),
      'base' => 'node_content',
      'description' => t('If EITI was mentioned anywhere on the web, in a blog post, or any news article that you want to share, create a mention by using this content-type (previously known as: In the News).'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
