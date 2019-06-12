<?php

/**
 * @file
 * Related articles.
 */

$plugin = array(
  'title' => t('Related articles'),
  'description' => t('Related article list for article nodes.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__related_articles__render',
);

/**
 * Output function for related articles.
 */
function eiti_ctools_extra__related_articles__render($subtype, $conf, $panel_args, $context) {
  if (arg(0) == 'node') {
    $entity = menu_get_object();
  }

  if (empty($entity) || !isset($entity->type) || $entity->type != 'article') {
    return NULL;
  }

  global $language;
  $entity_wrapper = entity_metadata_wrapper('node', $entity);
  $tags = $entity_wrapper->language($language->language)->field_tags->raw();
  if (!$tags) {
    return NULL;
  }
  else {
    $tags = implode('+', $tags);
    $view = views_embed_view('articles', 'related', $tags);
    if (!trim(strip_tags($view))) {
      return NULL;
    }
  }

  $block['articles'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'related-articles',
        'single-narrow-row-wrapper',
      ),
    ),
  );
  $block['articles']['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h2',
    '#value' => t('Related articles'),
    '#attributes' => array('class' => array('title'), 'id' => drupal_html_id('Related articles')),
    '#prefix' => '<div class="pane-title-wrapper">',
    '#suffix' => '</div>',
  );
  $block['articles']['top'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => t('<a href="/articles">See all</a>'),
    '#attributes' => array('class' => array('top')),
  );
  $block['articles']['list'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => $view,
  );
  return (object) array(
    'content' => $block,
  );
}
