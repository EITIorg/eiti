<?php

/**
 * @file
 * Provides a custom News And Events widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'News Listing',
  'description' => 'Will display a list of recent news.',
  'render callback' => 'contentblock_news_widget_render',
  'settings form' => 'contentblock_news_widget_settings',
  'defaults' => array(),
);

/**
 * Render callback for the 'News Listing' predefined widget.
 */
function contentblock_news_widget_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];

  $view_name = 'article';
  $view_display_id = 'news_listing';

  $view = views_get_view($view_name);
  if (!$view || !$view->access($view_display_id)) {
    return;
  }
  $view->set_display($view_display_id);

  // Replaces the class for the view wrapper.
  $css_class = 'news-widget two-columns-grid';
  $view->display_handler->set_option('css_class', $css_class);

  return array('#markup' => $view->preview());
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentblock_news_widget_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  return $settings_form;
}
