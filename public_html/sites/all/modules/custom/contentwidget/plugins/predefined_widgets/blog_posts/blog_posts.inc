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
  'hidden' => TRUE,
  'render callback' => 'contentblock_blog_posts_widget_render',
  'defaults' => array(),
);

/**
 * Render callback for the 'Blog Posts Listing' predefined widget.
 */
function contentblock_blog_posts_widget_render($plugin, $widget_settings, $entity, $langcode) {
  $view_name = 'article';
  $view_display_id = 'blog_posts_listing';

  $view = views_get_view($view_name);
  if (!$view || !$view->access($view_display_id)) {
    return array();
  }
  $view->set_display($view_display_id);

  // Replaces the class for the view wrapper.
  $css_class = drupal_html_class('contentwidget--' . $view_display_id);
  $view->display_handler->set_option('css_class', $css_class);

  return array('#markup' => $view->preview());
}
