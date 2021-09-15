<?php

/**
 * @file
 * eitisearch.elasticsearch_connector_defaults.inc
 */

/**
 * Implements hook_default_elasticsearch_connector_cluster().
 */
function eitisearch_default_elasticsearch_connector_cluster() {
  $export = array();

  $elasticsearch_connector_cluster = new stdClass();
  $elasticsearch_connector_cluster->disabled = FALSE; /* Edit this to true to make a default elasticsearch_connector_cluster disabled initially */
  $elasticsearch_connector_cluster->api_version = 1;
  $elasticsearch_connector_cluster->cluster_id = 'main';
  $elasticsearch_connector_cluster->name = 'Main';
  $elasticsearch_connector_cluster->url = 'https://localhost';
  $elasticsearch_connector_cluster->status = 1;
  $elasticsearch_connector_cluster->options = 'a:7:{s:25:"multiple_nodes_connection";i:0;s:18:"use_authentication";i:0;s:19:"authentication_type";s:47:"elasticsearch_aws_connector_aws_signed_requests";s:8:"username";s:0:"";s:8:"password";s:0:"";s:7:"timeout";s:1:"3";s:38:"elasticsearch_connector_upgraded_types";i:0;}';
  $export['main'] = $elasticsearch_connector_cluster;

  return $export;
}
