<?php

/**
 * Implements hook_field_group_build_pre_render_alter.
 *
 * We use this, because no one has solved the fieldgroup conditional fields support.
 * @see https://www.drupal.org/node/1161314
 */
function eitict_article_field_group_build_pre_render_alter(&$element) {
  // Apply only to our form.
  if (isset($element['#form_id']) && $element['#form_id'] == 'article_node_form') {
    // Make sure the group is there.
    if (!empty($element['group_event_details'])) {
      $element['group_event_details']['#id'] = 'group-event-details';
      $element['group_event_details']['#states'] = array(
        'visible' => array(
          'input[name="field_article_type[und]"]' => array('value' => 'event'),
        ),
      );
    }
  }
}

/**
 * Implements hook_form_views_exposed_form_alter().
 */
function eitict_article_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $view = $form_state['view'];

  if ($view->name == 'news') {
    // Improve the form layout.
    $form['#attributes']['class'][] = 'single-fluid-row-wrapper';
    $form['search']['#size'] = 30;
    $form['tags']['#size'] = 30;
  }
}

/**
 * Implements hook_entity_view().
 */
function eitict_article_entity_view($entity, $type, $view_mode, $langcode) {
  if ($type != 'node' || $entity->type != 'article') {
    return;
  }

  // Add the article header (title and featured image)
  if (in_array($view_mode, array('full', 'teaser_alternative'))) {
    $article_header = _eitict_article_entity_view_get_article_header($entity, $type, $view_mode, $langcode);
    $entity->article_header = render($article_header);
  }

  // Add the article info.
  $article_info = _eitict_article_entity_view_get_article_info($entity, $type, $view_mode, $langcode);
  if (in_array($view_mode, array('full', 'teaser_alternative'))) {
    $article_info['#attributes']['class'][] = 'single-fluid-row-wrapper';
    $article_info['#prefix'] = '<div class="article-info-wrapper">';
    $article_info['#suffix'] = '</div>';
  }
  else {
    $article_info['#attributes']['class'][] = 'simple';
  }
  $entity->article_info = render($article_info);
}

/**
 * Helper function for article entity header.
 */
function _eitict_article_entity_view_get_article_header($entity, $type, $view_mode, $langcode) {
  // Prepare the article header "field".
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'article-header',
        'clearfix',
      ),
    ),
  );

  // Add title to the article_header.
  if (isset($entity->content['title_field'])) {
    $elements['title_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'title-field-wrapper',
          'single-fluid-row-wrapper',
          'clearfix',
        ),
      ),
    );
    $elements['title_wrapper']['title_field'] = $entity->content['title_field'];
    $entity->content['title_field']['#printed'] = TRUE;
  }

  // Add background image to the article_header.
  if (isset($entity->content['field_featured_image'][0])) {
    $featured_image_data = &$entity->content['field_featured_image'][0];

    // Prepare Markup.
    $featured_image_fid = $featured_image_data['#item']['fid'];;
    $selector = drupal_html_id('article-' . $entity->nid . '-featured-image-' . $featured_image_fid);
    $elements['#attributes']['class'][] = $selector;
    $elements['#attributes']['class'][] = 'with-featured-image';

    // Define breakpoints. Increased by 1em to account for browsers that include borders in viewport size.
    global $theme_info;
    // @small: ((@gen_column_width + @gen_gutter_width) * 8) + 1em;
    // @medium: ((@gen_column_width + @gen_gutter_width) * 12) + 1em;
    // @large: ((@gen_column_width + @gen_gutter_width) * 16) + 1em;
    $col_unit = $theme_info->info['less']['vars']['@gen_column_width'] + $theme_info->info['less']['vars']['@gen_gutter_width'];
    // $breakpoint_small = $col_unit * 8 + 1 . 'em';
    $breakpoint_medium = $col_unit * 12 + 1 . 'em';
    // $breakpoint_large = $col_unit * 16 + 1 . 'em';

    // Prepare inline style for: 'Smartphone' and 'Tablet'
    // @see: .xMediumAndDown() in custom-responsive.less
    $style_name = 'bg-small';
    $featured_image_path = image_style_url($style_name, $featured_image_data['#item']['uri']);
    $background_image = 'background-image: url("' . $featured_image_path . '");';
    $inline_style_xMediumAndDown = "@media (max-width: $breakpoint_medium) { .${selector} { ${background_image} }}\n";

    // Prepare inline style for: 'Normal Desktop' and 'Large Desktop'.
    // @see: .xNormalAndUp() in custom-responsive.less
    $style_name = 'bg-large';
    $featured_image_path = image_style_url($style_name, $featured_image_data['#item']['uri']);
    $background_image = 'background-image: url("' . $featured_image_path . '");';
    $inline_style_xNormalAndUp = "@media (min-width: $breakpoint_medium) { .${selector} { ${background_image} }}\n";

    $elements['style'] = array(
      '#type' => 'html_tag',
      '#tag' => 'style',
      '#value' => $inline_style_xMediumAndDown . $inline_style_xNormalAndUp,
    );
  }
  else {
    $elements['#attributes']['class'][] = 'without-featured-image';
  }

  return $elements;
}


function _eitict_article_entity_view_get_article_info($entity, $type, $view_mode, $langcode) {
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'article-info',
        'clearfix',
      ),
    ),
  );

  // Get the type of article.
  $article_type = helperfield_field_get_value('node', $entity, 'field_article_type', 0, 'value');

  // Prepare the article information "field".
  switch ($article_type) {
    case 'event':
      if (isset($entity->content['field_event_date'])) {
        $elements['field_event_date'] = $entity->content['field_event_date'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('date', $options);
        $elements['field_event_date'][0]['#prefix'] = $svgicon;

        $entity->content['field_event_date']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_event_location'])) {
        $elements['field_event_location'] = $entity->content['field_event_location'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('country', $options);
        $elements['field_event_location'][0]['#prefix'] = $svgicon;

        $entity->content['field_event_location']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_tags'])) {
        $elements['field_tags'] = $entity->content['field_tags'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('tag', $options);
        $elements['field_tags'][0]['#prefix'] = $svgicon;

        $entity->content['field_tags']['#printed'] = TRUE;
      }
      break;

    default:
      if (isset($entity->content['author'])) {
        $elements['author'] = $entity->content['author'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('author', $options);
        $elements['author'][0]['#prefix'] = $svgicon;

        $entity->content['author']['#printed'] = TRUE;
      }

      if (isset($entity->content['post_date'])) {
        $elements['post_date'] = $entity->content['post_date'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('date', $options);
        $elements['post_date'][0]['#prefix'] = $svgicon;

        $entity->content['post_date']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_tags'])) {
        $elements['field_tags'] = $entity->content['field_tags'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('tag', $options);
        $elements['field_tags'][0]['#prefix'] = $svgicon;

        $entity->content['field_tags']['#printed'] = TRUE;
      }
      break;
  }

  return $elements;
}
