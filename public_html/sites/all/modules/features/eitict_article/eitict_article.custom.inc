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

  // Modifications for teaser display.
  if ($view_mode === 'teaser') {
    if (isset($entity->content['field_featured_image'], $entity->content['body'])) {
      unset($entity->content['body']);
    }
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

  $article_type = helperfield_field_get_value('node', $entity, 'field_article_type', 0, 'value');

  // Add link to list display.
  if ($article_type != 'event') {
    $elements['overlay']['article_list_link'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('News and blog posts'),
      '#title_tag' => 'a',
      '#title_attributes' => array(
        'href' => url('latest'),
        'class' => array('link'),
      ),
      '#attributes' => array(
        'class' => array(
          'article-list-link',
          'single-narrow-row-wrapper',
        ),
      ),
    );
  }

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

  // Left side elements.
  $elements['left'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'left',
      ),
    ),
  );

  // Prepare the article information "field".
  switch ($article_type) {
    case 'event':
      if (isset($entity->content['field_event_date'])) {
        $elements['left']['field_event_date'] = $entity->content['field_event_date'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('date', $options);
        $elements['left']['field_event_date'][0]['#prefix'] = $svgicon;

        $entity->content['field_event_date']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_event_location'])) {
        $elements['left']['field_event_location'] = $entity->content['field_event_location'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('country', $options);
        $elements['left']['field_event_location'][0]['#prefix'] = $svgicon;

        $entity->content['field_event_location']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_tags'])) {
        $elements['left']['field_tags'] = $entity->content['field_tags'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('tag', $options);
        $elements['left']['field_tags'][0]['#prefix'] = $svgicon;

        $entity->content['field_tags']['#printed'] = TRUE;
      }
      break;

    default:
      if (isset($entity->content['author'])) {
        $elements['left']['author'] = $entity->content['author'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('author', $options);
        $elements['left']['author'][0]['#prefix'] = $svgicon;

        $entity->content['author']['#printed'] = TRUE;
      }

      if (isset($entity->content['post_date'])) {
        $elements['left']['post_date'] = $entity->content['post_date'];
        $entity->content['post_date']['#printed'] = TRUE;
      }

      if (isset($entity->content['field_tags'])) {
        $elements['left']['field_tags'] = $entity->content['field_tags'];

        $size = '1em';
        $options = array(
          'width' => $size,
          'height' => $size,
        );
        $svgicon = helpertheme_get_svg_icon('tag', $options);
        $elements['left']['field_tags'][0]['#prefix'] = $svgicon;

        $entity->content['field_tags']['#printed'] = TRUE;
      }
      break;
  }

  // Right side elements.
  $elements['right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'right',
      ),
    ),
  );
  $rss_url = FALSE;
  if ($article_type == 'news') {
    $rss_url = 'feed/news.xml';
  }
  elseif ($article_type == 'blog') {
    $rss_url = 'feed/blog.xml';
  }
  if ($rss_url) {
    $elements['right']['rss'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('RSS'),
      '#title_tag' => 'a',
      '#title_attributes' => array(
        'href' => url($rss_url),
        'class' => array('link'),
        'target' => '_blank',
      ),
      '#attributes' => array(
        'class' => array(
          'rss',
        ),
      ),
    );
  }
  $elements['right']['print'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('Print'),
    '#title_tag' => 'a',
    '#title_attributes' => array(
      'href' => 'javascript:window.print()',
      'class' => array('link'),
    ),
    '#attributes' => array(
      'class' => array(
        'print',
      ),
    ),
  );
  if (isset($entity->content['addtoany'])) {
    $elements['right']['addtoany'] = $entity->content['addtoany'];
    $entity->content['addtoany']['#printed'] = TRUE;
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
  $token_def['tokens']['node']['article-type-adjusted'] = array(
    'name' => t('Adjusted Article Type'),
    'description' => t('Contains the adjusted version of the Article Type.'),
  );

  return $token_def;
}

/**
 * Implements hook_tokens().
 */
function eitict_article_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $opted_types = array('node');
  $opted_tokens = array('title-field-english', 'article-type-adjusted');

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
      case 'article-type-adjusted':
        $node = $data['node'];
        $node_emw = entity_metadata_wrapper('node', $node);
        $field_article_type = $node_emw->field_article_type->value();
        $replacements[$original] = $field_article_type;
        break;
    }
  }

  return $replacements;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function eitict_article_preprocess_views_view(&$variables) {
  if ($variables['name'] === 'articles' && $variables['display_id'] === 'default') {
    // Attachment is not being attached automatically when using views_embed_view()
    // and no results behavior is not working properly.
    if (isset($variables['attachment_before']) && !trim(strip_tags($variables['attachment_before']))) {
      $attachment_html = views_embed_view('articles', 'sticky');
      if (!trim(strip_tags($attachment_html))) {
        $attachment_html = '<div class="view-empty">' . t('There are no items to display.') . '</div>';
      }
      // Display attachment on first page only.
      elseif (isset($variables['view']->query->pager->current_page) && is_numeric($variables['view']->query->pager->current_page)) {
        if ($variables['view']->query->pager->current_page > 0) {
          $attachment_html = '';
        }
      }
      $variables['attachment_before'] = $attachment_html;
    }
  }
}

/**
 * Implements hook_node_presave().
 */
function eitict_article_node_presave($node) {
  // There should only ever be one stickied article.
  if ($node->type === 'article' && $node->sticky) {
    $query = db_select('node')
      ->fields('node', array('nid'))
      ->condition('type', 'article')
      ->condition('sticky', 1);
    if ($node->nid) {
      $query->condition('nid', $node->nid, '!=');
    }
    $nids = $query->execute()->fetchCol();
    if ($nids) {
      foreach ($nids as $nid) {
        $article = node_load($nid);
        $article->sticky = 0;
        node_save($article);
      }
    }
  }
}

/**
 * Implements hook_views_query_alter().
 */
function eitict_article_views_query_alter(&$view, &$query) {
  if ($view->name == 'articles') {
    foreach ($query->where as $k1 => $v1) {
      if (isset($v1['type']) && $v1['type'] === 'AND') {
        foreach ($v1['conditions'] as $k2 => $v2) {
          if (is_string($v2['field'])) {
            // End date needs to be end of the given day.
            if (strpos($v2['field'], "node.created <= ") === 0) {
              $parts = explode(' ', $v2['field']);
              if (isset($parts[2]) && is_numeric($parts[2])) {
                $end_date = $parts[2] + ((24 * 60 * 60) - 1);
                $query->where[$k1]['conditions'][$k2]['field'] = str_replace($parts[2], $end_date, $v2['field']);
              }
            }
          }
          elseif (is_object($v2['field'])) {
            $conditions = &$query->where[$k1]['conditions'][$k2]['field']->conditions();
            // Turn search case insensitive.
            if (isset($conditions[0]['field']) && is_string($conditions[0]['field'])) {
              $conditions[0]['field'] = str_replace(' LIKE ', ' ILIKE ', $conditions[0]['field']);
            }
          }
        }
      }
    }
  }
}
