<?php

define('EITIWIDGETS_PANELS_TITLE_ENTITY', 99);

/**
 * Implements hook_form_alter().
 *
 * @inheritdoc
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
    // Add extra title display option.
    $form['display_title']['hide_title']['#options'][EITIWIDGETS_PANELS_TITLE_ENTITY] = t('Inherited from entity');

    // Hide the "Manually set" title type (visibility) option.
    unset($form['display_title']['hide_title']['#options'][PANELS_TITLE_FIXED]);

    // Hide the "From pane" title type (visibility) option.
    unset($form['display_title']['hide_title']['#options'][PANELS_TITLE_PANE]);

    // Hide the "Substitutions" fieldset.
    $form['display_title']['contexts']['#access'] = FALSE;

    // Hide preview button.
    $form['preview']['#access'] = FALSE;

    // Hide the "Create new revision" checkbox.
    $form['revision_information']['#access'] = FALSE;

    // Determine the entity_type. :(
    if (isset($form_state['entity']) && method_exists($form_state['entity'], 'entityType')) {
      $entity_type = call_user_func(array($form_state['entity'], 'entityType'));
    }
    else if (isset($form_state['entity']->panelizer['default']->entity_type)) {
      $entity_type = $form_state['entity']->panelizer['default']->entity_type;
    }

    // Replace the cancel submit button with a link to the entity page.
    if (isset($entity_type)) {
      $entity_uri = entity_uri($entity_type, $form_state['entity']);

      $options = array();
      $path = $entity_uri['path'];

      // A destination in $_GET always overrides the function arguments.
      // We do not allow absolute URLs to be passed via $_GET, as this can be an attack vector.
      if (isset($_GET['destination']) && !url_is_external($_GET['destination'])) {
        $destination = drupal_parse_url($_GET['destination']);
        $path = $destination['path'];
        $options['query'] = $destination['query'];
        $options['fragment'] = $destination['fragment'];
      }

      $form['buttons']['cancel'] = array(
        '#type' => 'link',
        '#title' => t('Cancel'),
        '#href' => $path,
        '#options' => $options,
        '#weight' => 20,
      );
    }
  }
}

/**
 * A place where we alter our FPP forms.
 *
 * @param array $form
 * @param array $form_state
 */
function eitiwidgets_fpp_form_alter(&$form, &$form_state) {
  $entity = $form_state['entity'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);

  // Do not make all FPPs reusable by default.
  // @see: fieldable_panels_panes_entities_add_page().
  if (!empty($entity->is_new) && isset($form['reusable']['reusable'])) {
    $entity->reusable = FALSE;
    $form['reusable']['reusable']['#default_value'] = FALSE;
  }

  // Hide the FPP view mode selector.
  if (isset($form['view_mode']['#default_value'])) {
    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => $form['view_mode']['#default_value'],
    );
  }

  // Add our checkbox (it will be serialized and stored as a Ctools Content-Type instance setting).
  $form['show_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Title'),
    '#description' => t("If you won't like to display the title on the page, but use it only for <strong>adminsitrative side</strong>, uncheck this box."),
    '#default_value' => (!isset($form_state['conf']['show_title'])) ? TRUE : $form_state['conf']['show_title'],
    '#weight' => 1,
  );
  // We need additional submit handler to save our custom properties into $conf.
  $form['#submit'][] = 'eitiwidgets_fpp_form_show_title_submit';

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
      $field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_widget', $entity_language);
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

  // Do not allow editing of FPP entities outside of the required context.
  if (isset($form_state['required_ctools_contexts_available']) && !$form_state['required_ctools_contexts_available']) {
    $form['actions']['submit']['#disabled'] = TRUE;
    form_set_error('field_fpp_widget', '<strong>' . t('Please configure this pane inside of the "Customize display > Content" page.') . '</strong>');
  }
}

/**
 * Submit handler that saves addition proprieties for FPP.
 *
 * @param array $form
 * @param array $form_state
 */
function eitiwidgets_fpp_form_show_title_submit($form, &$form_state) {
  // Specify which fields you will like to save to conf.
  $fields_to_save = array('show_title');
  foreach ($fields_to_save as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * A ctools content-type callback, which overrides the default FPP callback,
 * creating a wrapper callback that later makes additional checks and alters
 * the returned $content ($block).
 *
 * @see fieldable_panels_panes_fieldable_panels_pane_content_type_render
 *
 * @param string $subtype
 * @param array $conf
 * @param array $panel_args
 * @param array $context
 * @return \stdClass
 */
function eitiwidgets_fpp_render($subtype, $conf, $panel_args = array(), $context = array()) {
  $block = fieldable_panels_panes_fieldable_panels_pane_content_type_render($subtype, $conf, $panel_args = array(), $context = array());
  if (isset($conf['show_title']) && $conf['show_title'] == FALSE) {
    $block->title = '';
    unset($block->content['title_field']);
  }
  return $block;
}

/**
 * Validation handler for the FPP widget form.
 *
 * @see: eitiwidgets_form_alter()
 *
 * @param array $form
 * @param array $form_state
 */
function eitiwidgets_fpp_form_validation(&$form, &$form_state) {
  $function = '__' . __FUNCTION__ . '__' . $form_state['entity']->bundle;
  if (function_exists($function)) {
    $function($form, $form_state);
  }
}

/**
 * Validation handler for the featured_bookmarks widget form.
 *
 * @see: eitiwidgets_fpp_form_validation()
 *
 * @param array $form
 * @param array $form_state
 */
function __eitiwidgets_fpp_form_validation__featured_bookmarks(&$form, &$form_state) {
  // Get the number of featured bookmarks required for the entity.
  $field_language = $form['field_fpp_widget']['#language'];
  $widget_settings = $form_state['values']['field_fpp_widget'][$field_language][0]['settings'];
  $required_size = isset($widget_settings['bookmarks']['widget_size']) ? $widget_settings['bookmarks']['widget_size'] : 0;
  if (empty($required_size)) {
    return;
  }

  $path = array(
    'field_fpp_bookmark_list',
    $form['field_fpp_bookmark_list']['#language'],
  );
  $bookmark_list_values = drupal_array_get_nested_value($form_state['values'], $path);
  if ($bookmark_list_values) {
    $count = 0;
    foreach ($bookmark_list_values as $key => $value) {
      if ($key === 'add_more') {
        continue;
      }
      if (!empty($value['target_id'])) {
        $count++;
      }
    }

    if ($count < $required_size) {
      $msg = t('Please make sure you have specified at least @num bookmarks - because of the widget size you have specified.', array(
        '@num' => $required_size,
      ));
      form_set_error('field_fpp_bookmark_list', $msg);
    }
  }
}

/**
 * Implements hook_panels_pane_content_alter().
 *
 * @inheritdoc
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

  // Some widgets have a background image rendered inside.
  if (!empty($entity->field_fpp_background_image)) {
    $pane->css['css_class'] .= ' has-background-image';
  }
}

/**
 * Implements hook_entity_view().
 *
 * @inheritdoc
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

  if ($entity->bundle == 'quote') {
    $entity->content['quote_widget'] = eitiwidgets_get_quote_widget_markup($entity, $type, $view_mode, $langcode);

    // Move fields inside the new quote_widget element.
    if (isset($entity->content['field_fpp_quote'])) {
      $entity->content['quote_widget']['overlay']['blockquote']['field_fpp_quote'] = $entity->content['field_fpp_quote'];
      unset($entity->content['field_fpp_quote']);
    }
    if (isset($entity->content['field_fpp_source'])) {
      $entity->content['quote_widget']['overlay']['blockquote']['field_fpp_source'] = $entity->content['field_fpp_source'];
      unset($entity->content['field_fpp_source']);
    }
  }
}

/**
 * Prepares the content for the quote widget DS preprocessed field.
 */
function eitiwidgets_get_quote_widget_markup($entity, $type, $view_mode, $langcode) {
  $elements = array(
    '#type' => 'html_container',
  );

  $elements['overlay']['blockquote'] = array(
    '#type' => 'html_container',
    '#tag' => 'blockquote',
    '#attributes' => array(
      'class' => array(
        'single-fluid-row-wrapper',
      ),
    ),
  );

  $image_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_background_image', $langcode);
  if (!empty($entity->field_fpp_background_image[$image_field_language][0])) {
    $featured_image_data = $entity->field_fpp_background_image[$image_field_language][0];

    // Use the featured image as background image.
    $entity_id = entity_id('fieldable_panels_pane', $entity);
    $selector_prefix = implode('-', array('fieldable_panels_pane', $entity_id));
    helpertheme_get_background_image_with_overlay($elements, $featured_image_data, $selector_prefix);
  }

  $source_url_field_language = field_language('fieldable_panels_pane', $entity, 'field_fpp_source_url', $langcode);
  if (!empty($entity->field_fpp_source_url[$source_url_field_language][0])) {
    if (!empty($entity->field_fpp_source_url[$source_url_field_language][0]['url'])) {
      $url = $entity->field_fpp_source_url[$source_url_field_language][0]['url'];

      $elements['#tag'] = 'a';
      $elements['#attributes']['href'] = url($url);
      $elements['#attributes']['class'][] = 'linked-wrapper';
    }
  }

  return $elements;
}

/**
 * Implements hook_preprocess_fieldable_panels_pane().
 *
 * @inheritdoc
 */
function eitiwidgets_preprocess_fieldable_panels_pane(&$variables) {
  $entity = $variables['elements']['#fieldable_panels_pane'];
  $entity_language = entity_language('fieldable_panels_pane', $entity);

  // Constrain the pane content.
  $variables['classes_array'][] = 'clearfix';

  if (!isset($variables['main_classes'])) {
    $variables['main_classes'] = '';
  }
  if (empty($entity->field_fpp_background_image) && $entity->bundle != 'quote') {
    $variables['main_classes'] .= ' single-fluid-row-wrapper';
  }
}

/**
 * Implements hook_panelizer_overview_links_alter().
 *
 * @inheritdoc
 */
function eitiwidgets_panelizer_overview_links_alter(&$links_array, $entity_type, $entity, $view_mode) {
  // Do not show 'reset' link on panelizer overview pages for panelized entities..
  if (isset($links_array['reset'])) {
    unset($links_array['reset']);
  }
}


/**
 * Implements hook_preprocess_panelizer_view_mode().
 *
 * @inheritdoc
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
    else if (isset($element['#entity_type']) && $element['#entity_type'] == 'node') {
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

/**
 * Implements hook_menu_alter().
 *
 * @inheritdoc
 */
function eitiwidgets_menu_alter(&$items) {
  if (isset($items['admin/structure/fieldable-panels-panes/view/%fieldable_panels_panes/access'])) {
    $items['admin/structure/fieldable-panels-panes/view/%fieldable_panels_panes/access']['access callback'] = 'eitiwidgets_fieldable_panels_panes_access';
  }
  if (isset($items['admin/structure/fieldable-panels-panes/view/%fieldable_panels_panes/revision'])) {
    $items['admin/structure/fieldable-panels-panes/view/%fieldable_panels_panes/revision']['access callback'] = 'eitiwidgets_fieldable_panels_panes_access';
  }
}

/**
 * Alternative access callback for the FPP "Access Control" and "Revision" tabs.
 *
 * @param string $op
 * @param stdClass|null $entity
 * @param stdClass|null $account
 * @return bool
 */
function eitiwidgets_fieldable_panels_panes_access($op, $entity = NULL, $account = NULL) {
  if (function_exists('helpergeneric_cleanup_ui') && helpergeneric_cleanup_ui()) {
    return FALSE;
  }

  return entity_get_controller('fieldable_panels_pane')->access($op, $entity, $account);
}

/**
 * Implements hook_entity_info_alter().
 *
 * @inheritdoc
 */
function eitiwidgets_entity_info_alter(&$info) {
  if (!empty($info['fieldable_panels_pane']['bundles'])) {
    foreach ($info['fieldable_panels_pane']['bundles'] as $name => &$bundle) {
      $bundle['pane category'] = t('Widget Library');
      $bundle['pane icon'] = drupal_get_path('module', 'contentwidget') . '/icon-eiti-widget.png';
    }
  }
}

/**
 * Implements hook_ctools_plugin_pre_alter().
 *
 * @inheritdoc
 */
function eitiwidgets_ctools_plugin_pre_alter(&$plugin, &$info) {
  // Alter the fieldable panels pane plugin so that it supports one more configuration,
  // and change its render callback (which will act as a wrapper callback).
  if ($plugin['plugin type'] == 'content_types' && $plugin['name'] == 'fieldable_panels_pane') {
    $plugin['defaults']['show_title'] = TRUE;
    $plugin['render callback'] = 'eitiwidgets_fpp_render';
  }
}

/**
 * Implements hook_preprocess_panels_add_content_modal().
 *
 * @inheritdoc
 */
function eitiwidgets_preprocess_panels_add_content_modal(&$vars) {
  // Change the categories order.
  // @see: panels_renderer_editor::get_category()
  $category = 'Widget library';
  $library_key = preg_replace('/[^a-z0-9]/', '-', strtolower($category));
  $vars['categories'][$library_key]['weight'] = -99;
  uasort($vars['categories'], 'drupal_sort_weight');

  // Recreate the list of categories using the new order and add prefix reusable prefix to categories.
  $without_prefix = array(
    $library_key
  );
  $vars['categories_array'] = array();
  foreach ($vars['categories'] as $key => $category_info) {
    // 'root' category is actually displayed under the categories, so
    // skip it.
    if ($key == 'root') {
      continue;
    }

    $class = 'panels-modal-add-category';
    if ($key == $vars['category']) {
      $class .= ' active';
    }

    $url = $vars['renderer']->get_url('select-content', $vars['region'], $key);

    $title = $category_info['title'];
    if (!in_array($key, $without_prefix)) {
      $title = t('[reusable] !category', array('!category' => $category_info['title']));
    }
    $vars['categories_array'][] = ctools_ajax_text_button($title, $url, '', $class);
  }
}
