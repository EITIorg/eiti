<?php

/**
 * @file
 * Articles.
 */

$plugin = array(
  'title' => t('Articles'),
  'description' => t('Article list.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__articles__render',
  'edit form' => 'eiti_ctools_extra__articles__settings_form',
  'defaults' => array(
    'display' => 'default',
  ),
);

/**
 * Output function for articles.
 */
function eiti_ctools_extra__articles__render($subtype, $conf, $panel_args, $context) {
  $block['articles'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'articles',
        'single-fluid-row-wrapper',
      ),
    ),
  );
  $block['articles']['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h2',
    '#value' => t('News and blog posts'),
    '#attributes' => array('class' => array('title'), 'id' => drupal_html_id('News and blog posts')),
    '#prefix' => '<div class="pane-title-wrapper">',
    '#suffix' => '</div>',
  );
  $display = isset($conf['display']) ? $conf['display'] : 'default';
  $view = '';
  if ($display === 'latest' && isset($conf['tags']) && $conf['tags']) {
    $tags = explode(',', $conf['tags']);
    $voc = taxonomy_vocabulary_machine_name_load('tags');
    foreach ($tags as $key => $tag) {
      $tags[$key] = trim($tag);
    }
    $tids = db_select('taxonomy_term_data')
      ->fields('taxonomy_term_data', array('tid'))
      ->condition('vid', $voc->vid)
      ->condition('name', $tags, 'IN')
      ->execute()->fetchCol();
    if ($tids) {
      $tids = implode('+', $tids);
      $view = views_embed_view('articles', $display, $tids);
    }
  }
  if (!$view) {
    $view = views_embed_view('articles', $display);
  }
  if ($display === 'latest') {
    $block['articles']['top'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => t('<a href="/latest">See all</a>'),
      '#attributes' => array('class' => array('top')),
    );
  }
  $block['articles']['list'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => $view,
  );
  if ($display === 'latest') {
    $block['articles']['bottom'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => t('<a href="/latest">See all</a>'),
      '#attributes' => array('class' => array('bottom')),
    );
  }
  return (object) array(
    'content' => $block,
  );
}

/**
 * Settings form for articles.
 */
function eiti_ctools_extra__articles__settings_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $cleanup_list = array(
    'override_title',
    'override_title_text',
    'override_title_heading',
    'override_title_markup',
  );
  foreach ($cleanup_list as $key) {
    if (isset($form[$key])) {
      $form[$key]['#access'] = FALSE;
    }
  }
  $form['display'] = array(
    '#title' => t('Display'),
    '#type' => 'select',
    '#options' => array(
      'default' => t('Full list with filters'),
      'latest' => t('Latest 5'),
    ),
    '#default_value' => $conf['display'],
  );
  $form['tags'] = array(
    '#title' => t('Tags'),
    '#type' => 'textfield',
    '#default_value' => $conf['tags'],
    '#autocomplete_path' => 'taxonomy/autocomplete/field_tags',
    '#description' => t('Limit the results to the entered tags. This only works with the latest 5 display (has no effect otherwise).'),
  );
  return $form;
}

/**
 * Submit handler for article settings form.
 */
function eiti_ctools_extra__articles__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
