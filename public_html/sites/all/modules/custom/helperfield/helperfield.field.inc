<?php


/**
 *  Implements hook_field_info().
 */
function helperfield_field_info() {
  return array(
    'helperfield_icon' => array(
      'label' => t('HelperField: Icon'),
      'description' => t('Exposes an icon selector.'),
      'settings' => array(),
      'instance_settings' => array('available_icons' => array()),
      'default_widget' => 'icon_selector',
      'default_formatter' => 'icon_formatter',
    ),
  );
}

/**
 *  Implements hook_field_widget_info().
 */
function helperfield_field_widget_info() {
  return array(
    'helperfield_icon_selector' => array(
      'label' => t('Icon Selector'),
      'field types' => array('helperfield_icon'),
      'behaviors' => array(
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
    ),
  );
}

/**
 * Implements hook_field_instance_settings_form().
 */
function helperfield_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];
  $form = array();

  // Prepare the list of widget options.
  //$options = array();
  //foreach (contentwidget_get_predefined_widgets() as $key => $info) {
  //  $options[$key] = $info['title'];
  //}
  //
  //$form['available_widgets'] = array(
  //  '#title' => t('Available Widgets'),
  //  '#description' => t('Leave empty for all widgets.'),
  //  '#type' => 'select',
  //  '#multiple' => TRUE,
  //  '#default_value' => $settings['available_widgets'],
  //  '#options' => $options,
  //);

  return $form;
}
