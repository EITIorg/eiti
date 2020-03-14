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

        // Add "Filter by Tags" facets block.
        $facet_name = 'field_article_type';
        if (isset($realm[$facet_name])) {
          $elements[$facet_name] = array(
            '#type' => 'html_container',
            '#tag' => 'div',
            '#title' => t('Filter by @title:', array('@title' => t('Article Type'))),
            '#title_tag' => 'h3',
            '#title_attributes' => array('class' => array('facet-title')),
            '#contextual_info' => array('admin/config/search/facetapi', array($searcher, $realm_name, $facet_name)),
            '#attributes' => array(),
          );
          $elements[$facet_name]['filters'] = $realm[$facet_name];
        }

        // Add "Filter by Related Country » Label" facets block.
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

        // Add "Filter by Tags" facets block.
        $facet_name = 'field_tags';
        if (isset($realm[$facet_name])) {
          $elements[$facet_name] = array(
            '#type' => 'html_container',
            '#tag' => 'div',
            '#title' => t('Filter by @title:', array('@title' => t('Tags'))),
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

/**
 * Implements template_preprocess_views_view_unformatted() for the news view.
 */
function __eiti_preprocess_views_view_unformatted__stakeholders(&$variables) {
  switch ($variables['view']->current_display) {
    case 'stakeholders_companies':
      if (empty($variables['view']->result) || empty($variables["view"]->args[0])) {
        return;
      }
      // Hide group title if it is the single one.
      // And show only Become supporter link.
      $tid = $variables["view"]->args[0];
      $current_row = array_keys($variables["rows"]);
      if (!empty($variables["view"]->result[$current_row[0]]->field_field_stk_type[0]["raw"]["hs_lineages"])) {
        $lineage = $variables["view"]->result[$current_row[0]]->field_field_stk_type[0]["raw"]["hs_lineages"];
      }
      $lineage_tid = end($lineage)['tid'];
      if (!empty($lineage) && $lineage_tid == $tid) {
        $link = __eiti_get_becoming_supporter_link($tid);
        $variables["title"] = $link;
      }
      elseif (!empty($variables["view"]->result[$current_row[0]]->field_data_field_stk_type_field_stk_type_tid)) {
        // Show only Become supporter link.
        $tid = $variables["view"]->result[$current_row[0]]->field_data_field_stk_type_field_stk_type_tid;
        $link = __eiti_get_becoming_supporter_link($tid);
        $variables["title"] .= $link;
      }
  }
}

/**
 * Helper to get becoming_supporter link.
 */
function __eiti_get_becoming_supporter_link ($tid) {
  $term = taxonomy_term_load($tid);
  $link_markup = '';
  if (!empty($term->field_bs_link[$term->language][0])) {
    $bm_link = $term->field_bs_link[$term->language][0];
    $link = l(t('@link', ['@link' => $bm_link['title']]), $bm_link['url']);
    $link_markup = '<span class="bm-link">' . $link . '</span>';
  }
  return $link_markup;
}
