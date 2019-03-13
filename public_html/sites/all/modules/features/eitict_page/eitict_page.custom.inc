<?php
/**
 * @file
 * eitict_page.custom.inc
 */

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function eitict_page_features_component_export_alter(&$component_export, $component) {
  $entries_list = array();
  switch ($component) {
    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // We use "the same allowed layouts as standard Panels pages".
        'panelizer_node:page_allowed_layouts',

        // We use "the same allowed content as standard Panels pages".
        'panelizer_node:page_allowed_types',
      );
  }

  $removed_entries_list = array();
  foreach ($entries_list as $name) {
    if (isset($component_export['options']['sources'][$name])) {
      unset($component_export['options']['sources'][$name]);
      $removed_entries_list[] = check_plain($name);
    }

    if ($component == 'dependencies') {
      if (isset($component_export['options']['detected'][$name])) {
        unset($component_export['options']['detected'][$name]);
      }
    }
  }
}


/**
 * Implements hook_form_content_access_page_alter().
 */
function eitict_page_form_content_access_page_alter(&$form, &$form_state, $form_id) {
  $form['per_role']['#description'] = t('Note that content which is not published is treated in a different way. Access can not be granted from this form.');

  foreach (element_children($form['per_role']) as $key) {
    if (empty($form['per_role'][$key]['#type']) || $form['per_role'][$key]['#type'] != 'checkboxes') {
      continue;
    }

    switch ($key) {
      case 'view':
        $form['per_role'][$key]['#title'] =  t('View page');
        break;
      default:
        if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
          $form['per_role'][$key]['#process'][] = 'eitict_page_content_access_hide_checkboxes';
        }
        break;
    }
  }
}

/**
 * Formapi #process callback, that disables checkboxes for roles without access to content
 */
function eitict_page_content_access_hide_checkboxes($element) {
  unset($element['#prefix']);
  unset($element['#suffix']);
  unset($element['#title']);

  foreach (element_children($element) as $key) {
    $element[$key]['#type'] = 'value';
    $element[$key]['#value'] = $element[$key]['#default_value'];
  }
  return $element;
}

/**
 * Implements hook_entity_view().
 *
 * @inheritdoc
 */
function eitict_page_entity_view($entity, $type, $view_mode, $langcode) {
  if ($type != 'node' || $entity->type != 'page') {
    return;
  }

  // Add the article header (title and featured image)
//  if (in_array($view_mode, array('teaser'))) {
//    $article_header = _eitict_article_entity_view_get_article_header($entity, $type, $view_mode, $langcode);
//    $entity->article_header = render($article_header);
//  }

  // Add the article info.
  $article_info = _eitict_page_entity_view_get_article_info($entity, $type, $view_mode, $langcode);
  if (in_array($view_mode, array('teaser'))) {
    $article_info['#attributes']['class'][] = 'single-narrow-row-wrapper';
    $article_info['#prefix'] = '<div class="article-info-wrapper">';
    $article_info['#suffix'] = '</div>';
  }
  else {
    $article_info['#attributes']['class'][] = 'simple';
  }
  $entity->article_info = render($article_info);
}

/**
 * Helper function for article entity info.
 *
 * @inheritdoc
 */
function _eitict_page_entity_view_get_article_info($entity, $type, $view_mode, $langcode) {
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'article-info',
        'clearfix',
      ),
    ),
  );
}

/**
 * Implements hook_panels_post_render().
 */
function eitict_page_panels_post_render($panels_display, $renderer) {
  // Add feedback form to page node panels display if it's enabled.
  if (isset($panels_display->context['panelizer']->data)) {
    $data = $panels_display->context['panelizer']->data;
    if (isset($data->type) && $data->type === 'page') {
      if (isset($data->field_feedback_form['und'][0]['value']) && $data->field_feedback_form['und'][0]['value']) {
        $webform_nid = FALSE;
        if (function_exists('eitict_webform_get_feedback_nid')) {
          $webform_nid = eitict_webform_get_feedback_nid();
        }
        if ($webform_nid) {
          $webform_node = node_load($webform_nid);
          $webform_view = node_view($webform_node, 'full');
          $webform_display = '<div class="feedback-form single-fluid-row-wrapper">';
          $webform_display .= drupal_render($webform_view);
          $webform_display .= '</div>';
          return $webform_display;
        }
      }
    }
  }
}
