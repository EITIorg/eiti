<?php

/**
 * @file
 * eitict_stakeholder.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function eitict_stakeholder_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Link to persons board';
  $fe_block_boxes->format = 'filtered_html';
  $fe_block_boxes->machine_name = 'persons_board_link';
  $fe_block_boxes->body = '<p><a class="board-link" href="/about/board ">See the board</a></p>';

  $export['persons_board_link'] = $fe_block_boxes;

  return $export;
}
