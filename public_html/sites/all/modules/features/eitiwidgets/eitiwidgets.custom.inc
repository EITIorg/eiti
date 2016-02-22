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

  // Define to which FPP we want to allow Icon Selection.
  $fpp_bundles_with_icons = array('text');

  // Now add the icon selector.
  if (in_array($form['#entity']->bundle, $fpp_bundles_with_icons)) {
    $form['title_icon'] = array(
      '#type' => 'container',
    );
    $form['title_icon']['title_icon_checkbox'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use an Icon'),
      '#description' => t('Do you want to use an icon in the title?'),
      '#default_value' => isset($form_state['conf']['use_icon']) ? $form_state['conf']['use_icon'] : FALSE,
    );
    $icons = helpertheme_get_svg_icons();
    $icon_options = drupal_map_assoc(array_keys($icons));
    $field_name = 'title_icon_checkbox';
    $form['title_icon']['title_icon_selector'] = array(
      '#type' => 'radioicons',
      '#title' => t('Icon'),
      '#options' => $icon_options,
      '#icons' => $icons,
      '#default_value' => isset($form_state['conf']['icon']) ? $form_state['conf']['icon'] : '',
      '#states' => array(
        'visible' => array(
          array('input[name="' . $field_name . '"]' => array('checked' => TRUE)),
        ),
      )
    );
    $form['#submit'][] = 'eitiwidgets_fpp_form_icon_submit';
  }
}

/**
 * Submit callback for the icon option.
 */
function eitiwidgets_fpp_form_icon_submit(&$form, &$form_state) {
  // We just push the icon option into $form_state['conf'], which is serialized
  // and stored per ctools content_types instance.
  if (isset($form_state['values']['title_icon_checkbox']) && $form_state['values']['title_icon_checkbox']) {
    $form_state['conf']['icon'] = $form_state['values']['title_icon_selector'];
    $form_state['conf']['use_icon'] = $form_state['values']['title_icon_checkbox'];
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

/**
 * Implements hook_panels_pane_content_alter().
 */
function eitiwidgets_panels_pane_content_alter($content, $pane, $args, $contexts) {
  if (!isset($content->content['#fieldable_panels_pane'])) {
    return;
  }
  $entity = $content->content['#fieldable_panels_pane'];

  if (!isset($pane->css['css_class'])) {
    $pane->css['css_class'] = '';
  }

  // Get the field language.
  $langcode = $content->content['#language'];
  $field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $langcode);
  if (isset($entity->field_fpp_widget[$field_language][0])) {
    $field_values = reset($entity->field_fpp_widget[$field_language]);
    $pane->css['css_class'] .= ' ' . drupal_html_class('predefined-widget--' . $field_values['widget']);
  }
  else {
    $pane->css['css_class'] .= ' ' . drupal_html_class('predefined-widget--' . $entity->bundle);
  }
}
