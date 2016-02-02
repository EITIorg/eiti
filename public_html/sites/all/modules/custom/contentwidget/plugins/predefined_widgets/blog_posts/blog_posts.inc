<?php

/**
 * @file
 * Provides a custom blog_posts And Events widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Blog Posts Listing',
  'description' => 'Will display a list of recent blog posts.',
  'render callback' => 'contentblock_blog_posts_widget_render',
  'settings form' => 'contentblock_blog_posts_widget_settings',
  'defaults' => array(),
);

/**
 * Render callback for the 'Blog Posts Listing' predefined widget.
 */
function contentblock_blog_posts_widget_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];

  $view_name = 'article';
  $view_display_id = 'blog_posts_listing';

  $view = views_get_view($view_name);
  if (!$view || !$view->access($view_display_id)) {
    return;
  }
  $view->set_display($view_display_id);

  // Replaces the class for the view wrapper.
  $css_class = drupal_html_class('contentwidget--' . $view_display_id);
  $view->display_handler->set_option('css_class', $css_class);

  return array('#markup' => $view->preview());
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentblock_blog_posts_widget_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();

  return $settings_form;
}
