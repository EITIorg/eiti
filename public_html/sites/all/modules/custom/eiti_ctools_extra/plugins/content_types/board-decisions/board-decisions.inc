<?php

/**
 * @file
 * Board decisions.
 */

$plugin = array(
  'title' => t('Board decisions'),
  'description' => t('Board decisions list.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__board_decisions__render',
);

/**
 * Output function for board decisions.
 */
function eiti_ctools_extra__board_decisions__render($subtype, $conf, $panel_args, $context) {
  $block['board_decisions'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'board-decisions',
        'single-fluid-row-wrapper',
      ),
    ),
  );
  $block['board_decisions']['title'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h2',
    '#value' => t('Board decisions'),
    '#attributes' => array('class' => array('title'), 'id' => drupal_html_id('Board decisions')),
    '#prefix' => '<div class="pane-title-wrapper">',
    '#suffix' => '</div>',
  );
  $block['board_decisions']['list'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => views_embed_view('board_decisions', 'default'),
    '#attributes' => array('class' => array('list')),
  );

  return (object) array(
    'content' => $block,
  );
}
