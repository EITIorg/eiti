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
 *
 * @inheritdoc
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
 *
 * @inheritdoc
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
    $article_info['#attributes']['class'][] = 'single-narrow-row-wrapper';
    $article_info['#prefix'] = '<div class="article-info-wrapper">';
    $article_info['#suffix'] = '</div>';
  }
  else {
    $article_info['#attributes']['class'][] = 'simple';
  }
  $entity->article_info = render($article_info);


  // If a custom summary was provided, display it on the article page.
  if (in_array($view_mode, array('full'))) {
    if (!empty($entity->content['body']['#items'][0]['summary'])) {
      $article_summary = $entity->content['body']['#items'][0]['summary'];

      $article_summary_format = NULL;
      if (isset($entity->content['body']['#items'][0]['format'])) {
        $article_summary_format = $entity->content['body']['#items'][0]['format'];
      }

      $entity->article_summary = check_markup($article_summary, $article_summary_format);
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function eitict_article_form_article_node_form_alter(&$form, &$form_state) {
  $form['add_bookmark'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create a bookmark'),
    '#description' => t('Check this box if you want a bookmark to be automatically created for this article.'),
    '#default_value' => FALSE,
    '#weight' => 10.5,
  );
  $form['add_bookmark_img'] = array(
    '#type' => 'checkbox',
    '#title' => t('Re-use article\'s image.'),
    '#description' => t('Check this box if you want your bookmark to re-use the image uploaded higher.'),
    '#default_value' => FALSE,
    '#weight' => 10.6,
    '#states' => array(
      'visible' => array(
        'input[name="add_bookmark"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['actions']['submit']['#submit'][] = 'eitict_article_form_node_form_add_bookmark_submit';
}

/**
 * Submit handler that checks if the add_bookmark checkbox was checked or not,
 * and then creates a bookmark node with reference towards the article.
 */
function eitict_article_form_node_form_add_bookmark_submit($form, $form_state) {
  $add_bookmark = $form_state['values']['add_bookmark'];
  $add_bookmark_img = $form_state['values']['add_bookmark_img'];
  if ($add_bookmark) {
    $target_node = $form_state['node'];
    $details = array(
      'node' => $target_node,
    );
    if ($add_bookmark_img) {
      $details['image_field'] = 'field_featured_image';
    }
    eitict_bookmark_autocreate($details);
  }
}

/**
 * Helper function for article entity header.
 *
 * @inheritdoc
 */
function _eitict_article_entity_view_get_article_header($entity, $type, $view_mode, $langcode) {
  // Prepare the article header "field".
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'article-header',
      ),
    ),
  );

  // Add title to the article_header.
  if (isset($entity->content['title_field'])) {
    $elements['overlay']['title_wrapper'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'title-field-wrapper',
          'single-narrow-row-wrapper',
        ),
      ),
    );
    $elements['overlay']['title_wrapper']['title_field'] = $entity->content['title_field'];
    $entity->content['title_field']['#printed'] = TRUE;
  }

  // Add background image to the article_header.
  if (isset($entity->content['field_featured_image'][0])) {
    $featured_image_data = &$entity->content['field_featured_image'][0]['#item'];

    // Use the featured image as background image.
    $selector_prefix = implode('-', array($type, $entity->nid, $view_mode));
    helpertheme_get_background_image_with_overlay($elements, $featured_image_data, $selector_prefix);
    $elements['overlay']['#attributes']['class'][] = 'clearfix';
  }
  else {
    $elements['#attributes']['class'][] = 'without-featured-image';
  }

  return $elements;
}


/**
 * Helper function for article entity info.
 *
 * @inheritdoc
 */
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


/**
 * Implements hook_tokens_info().
 */
function eitict_article_token_info() {
  $token_def = array();

  // Generic adopted title (User Picture, Source, etc.).
  $token_def['tokens']['node']['title-field-english'] = array(
    'name' => t('English Title'),
    'description' => t('Contains the english version of the title.'),
  );

  return $token_def;
}

/**
 * Implements hook_tokens().
 */
function eitict_article_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $opted_types = array('node');
  $opted_tokens = array('title-field-english');

  // Only handling summary_data tokens.
  if (!in_array($type, $opted_types)) {
    return;
  }

  foreach ($tokens as $name => $original) {
    if (!in_array($name, $opted_tokens)) {
      continue;
    }

    switch ($name) {
      case 'title-field-english':
        $node = $data['node'];
        $node_emw = entity_metadata_wrapper('node', $node);
        $title_english = $node_emw->language('en')->title_field->value();
        $title_english = (empty($title_english)) ? $node_emw->title_field->value() : $title_english;
        $replacements[$original] = $title_english;
        break;
    }
  }

  return $replacements;
}
