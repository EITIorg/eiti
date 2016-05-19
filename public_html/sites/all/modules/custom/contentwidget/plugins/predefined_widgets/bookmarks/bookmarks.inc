<?php

/**
 * @file
 * Provides a custom Featured Bookmarks widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Featured Bookmarks'),
  'description' => t('Displays a list of featured bookmarks in a square-stylized fashion.'),
  'hook_entity_view' => 'contentwidget__featured_bookmarks__hook_entity_view',
  'render callback' => 'contentwidget__featured_bookmarks__render',
  'settings form' => 'contentwidget__featured_bookmarks__settings',
  'defaults' => array(),
);

/**
 * Render callback for the 'Featured Bookmarks' predefined widget.
 */
function contentwidget__featured_bookmarks__render($plugin, $widget_settings, $entity, $langcode) {
  $size = $widget_settings['widget_size'];

  $referenced_ids = array();

  $entity_type = 'fieldable_panels_pane';
  $bookmark_list_field_language = field_language($entity_type, $entity, 'field_fpp_bookmark_list', $langcode);
  foreach ($entity->field_fpp_bookmark_list[$bookmark_list_field_language] as $reference) {
    $referenced_ids[] = $reference['target_id'];
  }
  $referenced_entities = entity_load('node', $referenced_ids);
  $referenced_entities = array_values($referenced_entities);

  // @TODO: Pass context variable to the render callback.
  $context = contentwidget_get_predefined_widget_context($entity_type, $entity, $langcode, 'field_fpp_widget');
  foreach ($referenced_entities as $referenced_entity) {
    $referenced_entity->predefined_widget_context = $context;
  }

  // Get the dimensions of each bookmark.
  list($large_tiles_ids, $medium_tiles_ids, $small_tiles_ids) = _contentwidget__featured_bookmarks__get_dimensions($size);

  // Load entities with their different modes.
  $entities_renderable_arr = array();
  if (!empty($large_tiles_ids)) {
    $large_tiles_ids = drupal_map_assoc($large_tiles_ids);
    $large_bookmarks = array_intersect_key($referenced_entities, $large_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $large_bookmarks, 'bm_large_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }

  if (!empty($medium_tiles_ids)) {
    $medium_tiles_ids = drupal_map_assoc($medium_tiles_ids);
    $medium_bookmarks = array_intersect_key($referenced_entities, $medium_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $medium_bookmarks, 'bm_medium_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }

  if (!empty($small_tiles_ids)) {
    $small_tiles_ids = drupal_map_assoc($small_tiles_ids);
    $small_bookmarks = array_intersect_key($referenced_entities, $small_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $small_bookmarks, 'bm_small_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }

  // Now we follow the initial arrangement and put together the items array.
  $items = array();
  foreach ($referenced_entities as $key => $entity) {
    $markup = render($entities_renderable_arr[$entity->nid]);

    // Remove whitespace between tags.
    $items[$key] = preg_replace('@>[\s\W]+<@', '><', $markup);
  }

  $block = array();

  $block['bookmarks'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#title' => '',
    '#type' => 'ul',
    '#attributes' => array(
      'class' => array(
        'bookmark-items-wrapper',
        'bookmark-items-count-' . $size,
        'clearfix',
      ),
    ),
  );

  return $block;
}

/**
 * @param $size
 * @return array
 */
function _contentwidget__featured_bookmarks__get_dimensions($size) {
  $small_tiles_ids = $medium_tiles_ids = $large_tiles_ids = array();

  switch ($size) {
    case 2:
      $large_tiles_ids = array(0, 1);
      break;
    case 3:
      $large_tiles_ids = array(0);
      $medium_tiles_ids = array(1, 2);
      break;
    case 4:
      $large_tiles_ids = array(0);
      $medium_tiles_ids = array(1);
      $small_tiles_ids = array(2, 3);
      break;
    case 6:
      $large_tiles_ids = array(0);
      $medium_tiles_ids = array(1, 4, 5);
      $small_tiles_ids = array(2, 3);
      break;
    case 7:
      $large_tiles_ids = array(0);
      $medium_tiles_ids = array(1, 6);
      $small_tiles_ids = array(2, 3, 4, 5);
      break;
  }

  return array($large_tiles_ids, $medium_tiles_ids, $small_tiles_ids);
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentwidget__featured_bookmarks__settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $default_size = isset($widget_settings['widget_size']) ? $widget_settings['widget_size'] : '';

  $available_sizes = array(
    '' => t('- Select -'),
    '2' => t('2 blocks'),
    '3' => t('3 blocks'),
    '4' => t('4 blocks'),
    '6' => t('6 blocks'),
    '7' => t('7 blocks'),
  );
  $settings_form['widget_size'] = array(
    '#type' => 'select',
    '#title' => t('Widget Size'),
    '#options' => $available_sizes,
    '#default_value' => $default_size,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__featured_bookmarks__settings_ajax',
      'wrapper' => 'widget-preview',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  // Show previews if user has selected a size.
  if (!empty($widget_settings['widget_size'])) {
    $settings_form['widget_preview'] = array(
      '#type' => 'container',
      '#prefix' => '<div id="widget-preview">',
      '#suffix' => '</div>',
    );
    $settings_form['widget_preview']['image'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#attributes' => array(
        'class' => 'widget-size-' . $widget_settings['widget_size'],
        'src' => '/' . $plugin['path'] . '/layouts/layout-' . $widget_settings['widget_size'] . '.png',
      ),
    );
  }
  else {
    $settings_form['widget_preview'] = array(
      '#type' => 'markup',
      '#markup' => t('Select the size of the widget, and a preview of the layout will be displayed.'),
      '#prefix' => '<div id="widget-preview">',
      '#suffix' => '</div>',
    );
  }

  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function _contentwidget__featured_bookmarks__settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['bookmarks']['widget_preview'];
}

/**
 * Helper for hook_fieldable_panels_pane_view().
 *
 * Please note that this helper is called multiple times if references exist.
 */
function contentwidget__featured_bookmarks__hook_entity_view($context) {
  // We need to prepare the referenced bookmarks.
  if (isset($context['referenced_entity'])) {
    $bookmark_entity = $context['referenced_entity'];
    $bookmark_language = entity_language('node', $bookmark_entity);
    $field_language = field_language('node', $bookmark_entity, 'field_bm_hide_title', $bookmark_language);

    // Hide the entity overlay.
    if (!empty($bookmark_entity->field_bm_hide_title[$field_language][0]['value'])) {
      unset($bookmark_entity->content['field_bm_bookmark_type']);
      unset($bookmark_entity->content['title_field']);
      unset($bookmark_entity->content['#groups']['group_overlay']);
    }
  }
}
