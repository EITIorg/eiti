<?php
/**
 * @file
 * This file contains view preprocess functions.
 */

/**
 * Implements template_preprocess_views_view().
 */
function eiti_preprocess_views_view(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements template_preprocess_views_view_unformatted().
 */
function eiti_preprocess_views_view_unformatted(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements template_preprocess_views_view_fields().
 */
function eiti_preprocess_views_view_fields(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements template_preprocess_views_view_table().
 */
function eiti_preprocess_views_view_table(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/*******************************************************************************
 * Helper functions for template_preprocess_HOOK() implementations.
 */

/**
 * Implements template_preprocess_views_view() for the search view.
 */
function __eiti_preprocess_views_view__search(&$variables) {
  switch ($variables['view']->current_display) {
    case 'page':
      if (!empty($variables['view']->result)) {
        if (!isset($variables['attachment_before'])) {
          $variables['attachment_before'] = '';
        }

        $elements = array();

        // Get the realm info.
        // For a list of facet names see the features export page: admin/structure/features/eitisearch/recreate
        $searcher = 'search_api@node_search';
        $realm_name = 'block';
        $realm = facetapi_build_realm($searcher, $realm_name);

        // Add "Filter by Content type" facets block.
        $facet_name = 'type';
        if (isset($realm[$facet_name])) {
          $elements[$facet_name] = array(
            '#type' => 'html_container',
            '#tag' => 'div',
            '#title' => t('Filter by @title:', array('@title' => $realm[$facet_name]['#title'])),
            '#title_tag' => 'h3',
            '#title_attributes' => array('class' => array('facet-title')),
            '#contextual_info' => array('admin/config/search/facetapi', array($searcher, $realm_name, $facet_name)),
            '#attributes' => array(),
          );
          $elements[$facet_name]['filters'] = $realm[$facet_name];
        }

        // Add "Filter by Related Country" facets block.
        $facet_name = 'field_related_country:name';
        if (isset($realm[$facet_name])) {
          $elements[$facet_name] = array(
            '#type' => 'html_container',
            '#tag' => 'div',
            '#title' => t('Filter by @title:', array('@title' => t('Related Country'))),
            '#title_tag' => 'h3',
            '#title_attributes' => array('class' => array('facet-title')),
            '#contextual_info' => array('admin/config/search/facetapi', array($searcher, $realm_name, $facet_name)),
            '#attributes' => array(),
          );
          $elements[$facet_name]['filters'] = $realm[$facet_name];
        }

        $variables['attachment_before'] .= render($elements);
      }
  }
}

/**
 * Implements template_preprocess_views_view() for the blog view.
 */
function __eiti_preprocess_views_view__blog(&$variables) {
  switch ($variables['view']->current_display) {
    case 'page':
      if (empty($variables['view']->result)) {
        return;
      }
      // Force wide layout.
      $layout = 'widelayout';
      $class = drupal_html_class('page-layout--' . $layout);
      helpertheme_set_html_classes($class);
  }
}

/**
 * Implements template_preprocess_views_view() for the events view.
 */
function __eiti_preprocess_views_view__events(&$variables) {
  switch ($variables['view']->current_display) {
    case 'page':
      if (empty($variables['view']->result)) {
        return;
      }
      // Force wide layout.
      $layout = 'widelayout';
      $class = drupal_html_class('page-layout--' . $layout);
      helpertheme_set_html_classes($class);
  }
}

/**
 * Implements template_preprocess_views_view() for the news view.
 */
function __eiti_preprocess_views_view__news(&$variables) {
  switch ($variables['view']->current_display) {
    case 'page':
      if (empty($variables['view']->result)) {
        return;
      }
      // Force wide layout.
      $layout = 'widelayout';
      $class = drupal_html_class('page-layout--' . $layout);
      helpertheme_set_html_classes($class);
  }
}
