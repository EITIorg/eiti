<?php

/**
 * Implements hook_form_alter().
 */
function eitiwidgets_form_alter(&$form, &$form_state, $form_id) {
  // Yeah it's long.
  if ($form_id == 'fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form') {
    // Alter our form.
    eitiwidgets_fpp_form_alter($form, $form_state);

    // Append our custom validation.
    $form['#validate'][] = 'eitiwidgets_fpp_form_validation';
  }
}

/**
 * A place where we alter our FPP forms.
 */
function eitiwidgets_fpp_form_alter(&$form, &$form_state) {
  switch ($form_state['entity']->bundle) {
    case 'quote':
//      dsm($form);
      break;
  }
}

/**
 * Our custom form validations.
 */
function eitiwidgets_fpp_form_validation(&$form, &$form_state) {
  switch ($form_state['entity']->bundle) {
    // General entity form validation for the "Featured Bookmarks".
    case 'featured_bookmarks':
      $list_size = isset($form_state['values']['field_fpp_widget']['und'][0]['settings']['bookmarks']['widget_size']) ? $form_state['values']['field_fpp_widget']['und'][0]['settings']['bookmarks']['widget_size'] : 0;

      if (!empty($list_size)) {
        $ief = reset($form_state['inline_entity_form']);
        if (count($ief['entities']) < $list_size) {
          $msg = t('Please make sure you have specified at least @num bookmarks - because of the widget size you have specified.', array(
            '@num' => $list_size,
          ));
          form_set_error('field_fpp_bookmark_list][und', $msg);
        }
      }
      else {
        $msg = t('Please specify the widget size.');
        form_set_error('field_fpp_widget][und][0][settings][bookmarks][widget_size', $msg);
      }
      break;
  }
}
