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
  'settings alter' => 'contentwidget_featured_bookmarks_settings_alter',
  'entity form alter' => 'contentwidget_featured_bookmarks_form_alter',
  'entity group alter' => 'contentwidget_featured_bookmarks_group_alter',
  'defaults' => array(),
);

/**
 * Render callback for the 'Featured Bookmarks' predefined widget.
 */
function contentblock_featured_bookmarks_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];
  $size = $widget_settings['bookmarks']['widget_size'];

  $referenced_ids = array();
  foreach ($entity->field_bookmark_list[$langcode] as $reference) {
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
  $default_size = isset($widget_settings['bookmarks']['widget_size']) ? $widget_settings['bookmarks']['widget_size'] : '';

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
  if (!empty($widget_settings['bookmarks']['widget_size'])) {
    $settings_form['widget_preview'] = array(
      '#type' => 'container',
      '#prefix' => '<div id="widget-preview">',
      '#suffix' => '</div>',
    );
    $settings_form['widget_preview']['image'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#attributes' => array(
        'class' => 'widget-size-' . $widget_settings['bookmarks']['widget_size'],
        'src' => '/' . $plugin['path'] . '/layouts/layout-' . $widget_settings['bookmarks']['widget_size'] . '.png',
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
  return $form['field_cbwidget'][LANGUAGE_NONE][0]['settings']['bookmarks']['widget_preview'];
}

/**
 * Alters the predefined entity form.
 */
function contentwidget_featured_bookmarks_form_alter(&$form, &$form_state, $plugin) {
  // We need to make sure that this file is included anyway, because validation will trigger an error.
  form_load_include($form_state, 'inc', 'contentwidget', 'plugins/predefined_widgets/bookmarks/bookmarks');
  // Add our custom validation.
  $form['actions']['submit']['#validate'][] = 'contentwidget_featured_bookmarks_form_validate';
}

/**
 * Our custom validation callback for the general entity form.
 */
function contentwidget_featured_bookmarks_form_validate($form, $form_state) {
  if ($form_state['values']['field_cbwidget']['und'][0]['widget'] == 'bookmarks') {
    $widget_settings = !empty($form_state['values']['field_cbwidget']['und'][0]['settings']) ? unserialize($form_state['values']['field_cbwidget']['und'][0]['settings']) : array();
    $size = isset($widget_settings['bookmarks']['widget_size']) ? $widget_settings['bookmarks']['widget_size'] : 0;
    if (!empty($size)) {
      $ief = reset($form_state['inline_entity_form']);
      if (count($ief['entities']) < $size) {
        $msg = t('Please make sure you have specified at least @num bookmarks - because of the widget size you have specified.', array(
          '@num' => $size,
        ));
        form_set_error('field_bookmark_list][und', $msg);
      }
    }
    else {
      $msg = t('Please specify the widget size.');
      form_set_error('field_cbwidget][und][0][settings][bookmarks][widget_size', $msg);
    }
  }
}

/**
 * Callback for the groups pre-render, allows us to interact with entity groups.
 */
function contentwidget_featured_bookmarks_group_alter(&$element) {
  // Make sure the group is there.
  if (!empty($element['group_bookmark'])) {
    // Make sure that the group shows up only when the widget is "Featured Bookmarks".
    $element['group_bookmark']['#id'] = 'group-event-details';
    $element['group_bookmark']['#states'] = array(
      'visible' => array(
        'input[name="field_cbwidget[und][0][widget]"]' => array('value' => 'bookmarks'),
      ),
    );
  }
}
