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
  'title' => 'Featured Bookmarks',
  'description' => 'Displays a list of featured bookmarks in a square-stylized fashion.',
  'render callback' => 'contentblock_featured_bookmarks_render',
  'settings form' => 'contentblock_featured_bookmarks_settings',
  'entity form alter' => 'contentwidget_featured_bookmarks_form_alter',
  'entity group alter' => 'contentwidget_featured_bookmarks_group_alter',
  'defaults' => array(),
);

/**
 * Render callback for the 'Featured Bookmarks' predefined widget.
 */
function contentblock_featured_bookmarks_render($plugin, $widget_settings, $entity, $langcode) {
  $size = $widget_settings['widget_size'];

  $referenced_ids = array();

  foreach ($entity->field_fpp_bookmark_list[$langcode] as $reference) {
    $referenced_ids[] = $reference['target_id'];
  }
  $referenced_entities = entity_load('node', $referenced_ids);
  $referenced_entities = array_values($referenced_entities);

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

  // Load entities with their different modes.
  $entities_renderable_arr = array();
  if (isset($large_tiles_ids)) {
    $large_tiles_ids = drupal_map_assoc($large_tiles_ids);
    $large_bookmarks = array_intersect_key($referenced_entities, $large_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $large_bookmarks, 'bm_large_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }
  if (isset($medium_tiles_ids)) {
    $medium_tiles_ids = drupal_map_assoc($medium_tiles_ids);
    $medium_bookmarks = array_intersect_key($referenced_entities, $medium_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $medium_bookmarks, 'bm_medium_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }
  if (isset($small_tiles_ids)) {
    $small_tiles_ids = drupal_map_assoc($small_tiles_ids);
    $small_bookmarks = array_intersect_key($referenced_entities, $small_tiles_ids);
    $bookmarks_renderable_arr = entity_view('node', $small_bookmarks, 'bm_small_tile');
    $entities_renderable_arr += $bookmarks_renderable_arr['node'];
  }

  // Now we follow the initial arrangement and put together the items array.
  $items = array();
  foreach ($referenced_entities as $key => $entity) {
    $items[$key] = render($entities_renderable_arr[$entity->nid]);
  }

  // Use a simple list for output.
  $output = theme('item_list', array(
    'items' => $items,
    'title' => '',
    'type' => 'ul',
    'attributes' => array(
      'class' => array('widget-list-size-' . $size, 'widget-wrapper')
    ),
  ));
  return array('#markup' => $output);
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentblock_featured_bookmarks_settings(&$element, &$form_state, $plugin, $widget_settings) {
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
    '#ajax' => array(
      'callback' => 'contentblock_featured_bookmarks_settings_ajax',
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
      '#markup' => t('Please select the size of the widget for prev12iew.'),
      '#prefix' => '<div id="widget-preview">',
      '#suffix' => '</div>',
    );
  }

  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function contentblock_featured_bookmarks_settings_ajax($form, $form_state) {
  // TODO: maybe we should check the language.
  return $form['field_fpp_widget'][LANGUAGE_NONE][0]['settings']['bookmarks']['widget_preview'];
}
