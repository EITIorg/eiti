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
  $elasticsearch_connector_cluster->url = 'https://vpc-preprod-search-4qw7x7nlftscry2ddr3crx45ta.eu-west-1.es.amazonaws.com';
  $elasticsearch_connector_cluster->status = 1;
  $elasticsearch_connector_cluster->options = array(
    'multiple_nodes_connection' => 0,
    'use_authentication' => 0,
    'authentication_type' => 'elasticsearch_aws_connector_aws_signed_requests',
    'username' => '',
    'password' => '',
    'timeout' => '3',
    'elasticsearch_connector_upgraded_types' => 0,
  );
  $export['main'] = $elasticsearch_connector_cluster;

  return $export;
}
