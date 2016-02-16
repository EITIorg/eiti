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
    case 'tabs_with_widgets':
      $tabs_number = isset($form_state['values']['field_fpp_widget']['und'][0]['settings']['tabs']['tabs_number']) ? $form_state['values']['field_fpp_widget']['und'][0]['settings']['tabs']['tabs_number'] : 4;

      $ief_id = key($form_state['inline_entity_form']);
      $entity_count = count($form_state['inline_entity_form'][$ief_id]['entities']);

      // Add a visual cue of cardinality count.
      $message = t('You have added @entities_count out of @cardinality_count allowed @label.', array(
        '@entities_count' => $entity_count,
        '@cardinality_count' => $tabs_number,
        '@label' => t('Widgets'),
      ));
      $form['field_fpp_content_widgets'][LANGUAGE_NONE]['cardinality_count'] = array(
        '#markup' => '<div class="ief-cardinality-count" id="ief-cardinality">' . $message . '</div>',
      );
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

/**
 * Implements hook_fieldable_panels_pane_view().
 */
function eitiwidgets_fieldable_panels_pane_view($panels_pane, $view_mode, $langcode) {
  // Hide original title when title_field is used (not displayed) on the entity.
  if (isset($panels_pane->title_field) && isset($panels_pane->content['title'])) {
    unset($panels_pane->content['title']);
  }
}
