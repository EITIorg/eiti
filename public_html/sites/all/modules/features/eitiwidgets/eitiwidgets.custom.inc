<?php

define('EITIWIDGETS_PANELS_TITLE_ENTITY', 99);

/**
 * Implements hook_form_alter().
 */
function eitiwidgets_form_alter(&$form, &$form_state, $form_id) {
  $fpp_forms = array(
    'fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form',
    'fieldable_panels_panes_entity_edit_form'
  );
  if (in_array($form_id, $fpp_forms)) {
    // Alter our form.
    eitiwidgets_fpp_form_alter($form, $form_state);

    // Append our custom validation.
    $form['#validate'][] = 'eitiwidgets_fpp_form_validation';
  }

  if ($form_id == 'panelizer_edit_content_form') {
    $form['display_title']['hide_title']['#options'][EITIWIDGETS_PANELS_TITLE_ENTITY] = t('Inherited from entity');
  }
}

/**
 * A place where we alter our FPP forms.
 */
function eitiwidgets_fpp_form_alter(&$form, &$form_state) {
  $entity = $form_state['entity'];

  // Hide the FPP view mode selector.
  if (isset($form['view_mode']['#default_value'])) {
    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => $form['view_mode']['#default_value'],
    );
  }

  // Hide unused FPP specific form elements.
  // @see: fieldable_panels_panes_entity_edit_form_submit()
  $form['link'] = array(
    '#type' => 'value',
    '#value' => '',
  );
  $form['path'] = array(
    '#type' => 'value',
    '#value' => '',
  );

  switch ($entity->bundle) {
    case 'tabs_with_widgets':
      $field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity->language);
      $tabs_number = isset($form_state['values']['field_fpp_widget'][$field_language][0]['settings']['tabs']['tabs_number']) ? $form_state['values']['field_fpp_widget'][$field_language][0]['settings']['tabs']['tabs_number'] : 4;

      $ief_id = key($form_state['inline_entity_form']);
      $entity_count = count($form_state['inline_entity_form'][$ief_id]['entities']);

      // Add a visual cue of cardinality count.
      $message = t('You have added @entities_count out of @cardinality_count allowed @label.', array(
        '@entities_count' => $entity_count,
        '@cardinality_count' => $tabs_number,
        '@label' => t('Widgets'),
      ));
      $form['field_fpp_content_widgets'][$field_language]['cardinality_count'] = array(
        '#markup' => '<div class="ief-cardinality-count" id="ief-cardinality">' . $message . '</div>',
      );
      break;
  }
}

/**
 * Our custom form validations.
 */
function eitiwidgets_fpp_form_validation(&$form, &$form_state) {
  $entity = $form_state['entity'];

  switch ($entity->bundle) {
    // General entity form validation for the "Featured Bookmarks".
    case 'featured_bookmarks':
      $field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity->language);
      $list_size = isset($form_state['values']['field_fpp_widget'][$field_language][0]['settings']['bookmarks']['widget_size']) ? $form_state['values']['field_fpp_widget'][$field_language][0]['settings']['bookmarks']['widget_size'] : 0;

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
        form_set_error('field_fpp_widget][' . $field_language . '][0][settings][bookmarks][widget_size', $msg);
      }
      break;
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

  // Add Widget type as a CSS class onto the FPP pane wrapper.
  $langcode = $content->content['#language'];
  $field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $langcode);
  if (isset($entity->field_fpp_widget[$field_language][0])) {
    $field_values = reset($entity->field_fpp_widget[$field_language]);
    $pane->css['css_class'] .= ' ' . drupal_html_class('predefined-widget--' . $field_values['widget']);
  }
  else {
    $pane->css['css_class'] .= ' ' . drupal_html_class('predefined-widget--' . $entity->bundle);
  }
  $pane->css['css_class'] .= ' predefined-widget';
}

/**
 * Implements hook_entity_view().
 */
function eitiwidgets_entity_view($entity, $type, $view_mode, $langcode) {
  if ($type != 'fieldable_panels_pane') {
    return;
  }

  // Remove empty title tags!
  // @TODO: Fix for title.module integration.
  if (isset($entity->content['title']['#value']) && $entity->content['title']['#value'] == '') {
    unset($entity->content['title']);
  }
}

/**
 * Implements hook_preprocess_fieldable_panels_pane().
 */
function eitiwidgets_preprocess_fieldable_panels_pane(&$variables) {
  $entity = $variables['elements']['#fieldable_panels_pane'];

  // Constrain the pane content.
  $variables['classes_array'][] = 'clearfix';
  $variables['main_classes'] = 'single-fluid-row-wrapper';

  // @TODO: Use on all bundles.
  if (!empty($entity->field_fpp_background_image) && $entity->bundle == 'quote') {
    $image_url = NULL;

    // Get the background image URL.
    $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $entity->language);
    if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
      $image_file = (object) $entity->field_fpp_background_image[$image_field_language][0];
      // @TODO: Make sure the image is decently sized, we don't want 10MB background images.
      $image_url = file_create_url($image_file->uri);
    }

    if ($image_url) {
      $variables['attributes_array']['style'] = 'background-image: url("' . $image_url . '");';
    }
  }

  // @TODO: Only link the blockquote!
  if (!empty($entity->field_fpp_source_url)) {
    $source_url_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_source_url', $entity->language);
    if (!empty($entity->field_fpp_source_url[$source_url_field_language][0]['url'])) {
      $url = $entity->field_fpp_source_url[$source_url_field_language][0]['url'];
      $variables['main_wrapper'] = 'a';
      $variables['main_attributes'] = array(
        'href' => url($url),
      );
      $variables['main_classes'] .= ' linked-wrapper';
    }
  }
}

/**
 * Implements hook_panelizer_overview_links_alter().
 */
function eitiwidgets_panelizer_overview_links_alter(&$links_array, $entity_type, $entity, $view_mode) {
  // Do not show 'reset' link on panelizer overview pages for panelized entities..
  if (isset($links_array['reset'])) {
    unset($links_array['reset']);
  }
}


/**
 * Implements hook_preprocess_panelizer_view_mode().
 */
function eitiwidgets_preprocess_panelizer_view_mode(&$variables) {
  $element = $variables['element'];
  $entity = $element['#panelizer_entity'];
  $panelizer = $element['#panelizer'];

  if (isset($panelizer->display->hide_title) && $panelizer->display->hide_title == EITIWIDGETS_PANELS_TITLE_ENTITY) {
    $entity_label = NULL;
    if (method_exists($entity, 'label')) {
      $entity_label = $entity->label();
    }
    else if ($panelizer->entity_type == 'node') {
      $entity_label = entity_label('node', $entity);
    }

    if ($entity_label) {
      $variables['title'] = $entity_label;
    }
  }

  // Add classes to the page title.
  if (!empty($variables['title'])) {
    if (isset($variables['title_element']) && $variables['title_element'] == 'h1') {
      $variables['title_attributes_array']['class'][] = 'page-title';
      $variables['title_wrapper_attributes']['class'][] = 'single-fluid-row-wrapper';
    }
  }
}
