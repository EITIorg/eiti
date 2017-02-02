<?php

/**
 * @file
 * Provides a custom 'Header' widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Header'),
  'description' => t('Display a header with sub-header and some links, with an optional background.'),
  'render callback' => 'contentwidget__header__render',
  'settings form' => 'contentwidget__header__settings',
  'defaults' => array(),
);

/**
 * Render callback for the 'Header' predefined widget.
 */
function contentwidget__header__render($plugin, $widget_settings, $entity, $langcode) {
  $header_small = (!empty($widget_settings['header_small'])) ? $widget_settings['header_small'] : FALSE;
  $header_big = (!empty($widget_settings['header_big'])) ? $widget_settings['header_big'] : FALSE;

  // And now prepare the list of links.
  $link_items = array();
  for ($link_count = 0; $link_count < $widget_settings['links']['links_number']; $link_count++) {
    $item_title = $widget_settings['links']['link_' . $link_count]['title_' . $link_count];
    $item_link = $widget_settings['links']['link_' . $link_count]['link_' . $link_count];
    $item_icon = $widget_settings['links']['link_' . $link_count]['icon_' . $link_count];
    if (empty($item_title) || empty($item_link)) {
      continue;
    }

    // Get the SVG icon markup.
    $svgicon = helpertheme_get_svg_icon($item_icon, array('width' => '2em', 'height' => '2em'));

    $item_options = array(
      'attributes' => array(
        'class' => array(
          'link',
          'link-with-icon',
          drupal_html_class('icon--' . $item_icon),
        ),
      ),
      'html' => TRUE,
    );
    $link_items[] = l(t('!icon @title', array('!icon' => $svgicon, '@title' => $item_title)), $item_link, $item_options);
  }

  $block = array(
    '#type' => 'container',
    '#attributes' => array()
  );

  $block['overlay']['headers'] = array(
    '#type' => 'container',
  );

  $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $langcode);
  $video_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_video', $langcode);
  if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
    $featured_image_data = $entity->field_fpp_background_image[$image_field_language][0];

    // Use the featured image as background image.
    $selector_prefix = implode('-', array('fieldable_panels_pane', entity_id('fieldable_panels_pane', $entity)));
    helpertheme_get_background_image_with_overlay($block, $featured_image_data, $selector_prefix);
    $block['overlay']['#attributes']['class'][] = 'clearfix';
  }
  elseif (!empty($entity->field_fpp_background_video[$video_field_language])) {
    $featured_video_data = $entity->field_fpp_background_video[$video_field_language];

    // Use the featured video as background video.
    $selector_prefix = implode('-', array('fieldable_panels_pane', entity_id('fieldable_panels_pane', $entity)));
    $video_settings = $widget_settings['video_settings'];
    helpertheme_get_background_video_with_overlay($block, $featured_video_data, $video_settings);
    $block['overlay']['#attributes']['class'][] = 'clearfix';
  }
  else {
    $block['#attributes']['class'][] = 'no-background-image';
  }

  // Only if it's set, we want to show the tag.
  if ($header_big) {
    $block['overlay']['headers']['header_big'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h2',
      '#value' => $header_big,
      '#attributes' => array(
        'class' => array('title'),
      ),
    );
  }

  // Only if it's set, we want to show the tag.
  if ($header_small) {
    $block['overlay']['headers']['header_small'] = array(
      '#type' => 'html_tag',
      '#tag' => 'p',
      '#value' => $header_small,
      '#attributes' => array(
        'class' => array('subtitle'),
      ),
    );
  }

  if (!empty($link_items)) {
    $block['overlay']['links_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('links-wrapper'),
      ),
    );
    $block['overlay']['links_wrapper']['links'] = array(
      '#theme' => 'item_list',
      '#items' => $link_items,
      '#type' => 'ul',
      '#title' => '',
      '#attributes' => array(
        'class' => array('links'),
      ),
    );
  }

  if (empty($entity->field_fpp_background_image[$image_field_language][0]) && empty($entity->field_fpp_background_video[$video_field_language])) {
    $block['overlay']['headers']['#attributes']['class'][] = 'single-fluid-row-wrapper';
    $block['overlay']['links_wrapper']['links']['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }
  else {
    $block['overlay']['#attributes']['class'][] = 'single-fluid-row-wrapper';
  }

  return $block;
}

/**
 * Settings form for the 'Top Projects' predefined widget.
 */
function contentwidget__header__settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $entity = $form_state['entity'];
  $langcode = $entity->language;
  $field_header_type_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_header_type', $langcode);

  $header_small = isset($widget_settings['header_small']) ? $widget_settings['header_small'] : '';
  $header_big = isset($widget_settings['header_big']) ? $widget_settings['header_big'] : '';
  $links_max = isset($widget_settings['links']['links_number']) ? $widget_settings['links']['links_number'] : 4;
  $video_muted = isset($widget_settings['video_settings']['video_muted']) ? $widget_settings['video_settings']['video_muted'] : TRUE;
  $video_loop = isset($widget_settings['video_settings']['video_loop']) ? $widget_settings['video_settings']['video_loop'] : TRUE;
  $video_hide_controllers = isset($widget_settings['video_settings']['video_hide_controllers']) ? $widget_settings['video_settings']['video_hide_controllers'] : TRUE;
  $video_autoplay = isset($widget_settings['video_settings']['video_autoplay']) ? $widget_settings['video_settings']['video_autoplay'] : TRUE;
  $video_height = isset($widget_settings['video_settings']['video_height']) ? $widget_settings['video_settings']['video_height'] : 'video';
  $disable_overlay = isset($widget_settings['video_settings']['disable_overlay']) ? $widget_settings['video_settings']['disable_overlay'] : FALSE;

  // @TODO: Rename!
  $settings_form['header_big'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $header_big,
    '#size' => 100,
  );
  $settings_form['header_small'] = array(
    '#type' => 'textfield',
    '#title' => t('Subtitle (simple paragraph)'),
    '#default_value' => $header_small,
    '#size' => 100,
  );

  // Let's add video-related settings.
  $settings_form['video_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#id' => 'video-custom-settings',
    '#states' => array(
      'visible' => array(
        array(
          'input[name="field_fpp_header_type[' . $field_header_type_language . ']"]' => array('value' => 'video'),
        )
      )
    )
  );
  $settings_form['video_settings']['video_muted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mute the video'),
    '#description' => t('Checking this box mutes the video.'),
    '#default_value' => $video_muted,
  );
  $settings_form['video_settings']['video_autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto-play'),
    '#description' => t('This video will auto-play as soon as the page is loaded. Otherwise, there will be a play button.'),
    '#default_value' => $video_autoplay,
  );
  $settings_form['video_settings']['video_loop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop'),
    '#description' => t('Would you like this video to loop?'),
    '#default_value' => $video_loop,
  );
  $settings_form['video_settings']['video_hide_controllers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide Media Buttons'),
    '#description' => t('Would you like to hide the Media Controllers (play / mute buttons)?'),
    '#default_value' => $video_hide_controllers,
  );
  $settings_form['video_settings']['disable_overlay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the Overlay'),
    '#description' => t('Check this box to disable the overlay.'),
    '#default_value' => $disable_overlay,
  );
  $settings_form['video_settings']['video_height'] = array(
    '#type' => 'select',
    '#title' => t('Video height'),
    '#description' => t('How big the video should be?'),
    '#options' => array(
      'video' => t('Give priority to video (full height)'),
      'overlay' => t('Give priority to overlay content'),
      'overlay_padding_2' => t('Give priority to overlay content (+2 padding)'),
      'overlay_padding_4' => t('Give priority to overlay content (+4 padding)'),
      'overlay_padding_6' => t('Give priority to overlay content (+6 padding)'),
      'overlay_padding_8' => t('Give priority to overlay content (+8 padding)'),
      'overlay_padding_10' => t('Give priority to overlay content (+10 padding)'),
    ),
    '#default_value' => $video_height,
  );

  $settings_form['links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="links-wrapper">',
    '#suffix' => '</div>',
  );

  $settings_form['links']['links_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of Links'),
    '#options' => drupal_map_assoc(range(0, 4)),
    '#description' => t('Please specify the number of links you want to use.'),
    '#default_value' => $links_max,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_contentwidget__header__settings_ajax',
      'event' => 'change',
      'wrapper' => 'links-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Create links.
  for ($link_count = 0; $link_count < $links_max; $link_count++) {
    $link_url = isset($widget_settings['links']['link_' . $link_count]['link_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['link_' . $link_count] : '';
    $link_title = isset($widget_settings['links']['link_' . $link_count]['title_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['title_' . $link_count] : '';
    $link_icon = isset($widget_settings['links']['link_' . $link_count]['icon_' . $link_count]) ? $widget_settings['links']['link_' . $link_count]['icon_' . $link_count] : '';

    $fieldset_name = t('Link #!number:', array('!number' => ($link_count + 1)));
    if (isset($link_title)) {
      $fieldset_name .= ' ' . check_plain($link_title);
    }

    $settings_form['links']['link_' . $link_count] = array(
      '#type' => 'fieldset',
      '#title' => $fieldset_name,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $icons = helpertheme_get_svg_icons();
    $options = array('' => t('No Icon'));
    $options += drupal_map_assoc(array_keys($icons));
    $settings_form['links']['link_' . $link_count]['icon_' . $link_count] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $options,
      '#icons' => $icons,
      '#default_value' => $link_icon,
    );
    $settings_form['links']['link_' . $link_count]['title_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('Link Title'),
      '#size' => 30,
      '#prefix' => '<div class="container-inline">',
      '#default_value' => $link_title,
      '#required' => TRUE,
    );
    $settings_form['links']['link_' . $link_count]['link_' . $link_count] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#suffix' => '</div>',
      '#size' => 50,
      '#default_value' => $link_url,
      '#required' => TRUE,
    );
  }
  return $settings_form;
}

/**
 * Ajax callback for the settings form.
 */
function _contentwidget__header__settings_ajax($form, $form_state) {
  $entity = $form['#entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);
  $widget_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
  return $form['field_fpp_widget'][$widget_field_language][0]['settings']['header']['links'];
}
