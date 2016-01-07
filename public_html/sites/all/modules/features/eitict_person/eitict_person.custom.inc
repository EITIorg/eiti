<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function eitict_person_form_person_node_form_alter(&$form, &$form_state) {
  // Show the board member type only if the user IS a board member.
  $form['field_board_member_type']['#states'] = array(
    'visible' => array(
      array(
        array('input[name="field_board_membership[und]"]' => array('value' => 1)),
        'or',
        array('input[name="field_board_membership[und]"]' => array('value' => 2)),
      )
    )
  );
}
