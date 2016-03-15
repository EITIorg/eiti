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

        $searcher = 'search_api@node_search';
        $realm_name = 'block';

        // Get the realm.
        $build = facetapi_build_realm($searcher, $realm_name);
        $facet_name = 'field_related_country';
        $elements[$facet_name] = array(
          '#type' => 'html_container',
          '#tag' => 'div',
          '#title' => t($build[$facet_name]['#title']),
          '#title_attributes' => array('class' => array('facet-title')),
          '#contextual_info' => array('admin/config/search/facetapi', array($searcher, $realm_name, $facet_name)),
          '#attributes' => array(
          ),
        );

        $elements[$facet_name]['filters'] = $build[$facet_name];

        $variables['attachment_before'] .= render($elements);
      }
  }
}
