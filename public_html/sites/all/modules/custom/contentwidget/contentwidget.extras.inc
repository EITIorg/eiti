<?php
/**
 * Helper hooks for predefined_widgets plugins.
 */


/**
 * Implements hook_fieldable_panels_pane_view().
 */
function contentwidget_fieldable_panels_pane_view($panels_pane, $view_mode, $langcode) {
  // Hide original title when title_field is used (not displayed) on the entity.
  if (isset($panels_pane->title_field) && isset($panels_pane->content['title'])) {
    unset($panels_pane->content['title']);
  }
}

/**
 * Implements hook_entity_view().
 */
function contentwidget_entity_view($entity, $type, $view_mode, $langcode) {
  $predefined_widget_context = NULL;

  // Call widget specific hook_entity_view method.
  if ($type == 'fieldable_panels_pane') {
    $widget_field_language = field_language($type, $entity, 'field_fpp_widget', $langcode);
    if (!empty($entity->field_fpp_widget[$widget_field_language][0]['widget'])) {
      $predefined_widget_context = contentwidget_get_predefined_widget_context($type, $entity, $langcode, 'field_fpp_widget');
    }
  }
  else if (!empty($entity->predefined_widget_context)) {
    $predefined_widget_context = $entity->predefined_widget_context;
    $predefined_widget_context['referenced_entity'] = $entity;
  }

  if (empty($predefined_widget_context)) {
    return;
  }

  if ($function = ctools_plugin_get_function($predefined_widget_context['plugin'], 'hook_entity_view')) {
    $result[] = call_user_func_array($function, array($predefined_widget_context));
  }
}
