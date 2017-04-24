<?php

/**
 * @file
 * Ctools Plugin (content-type aka ctools panel pane).
 *
 * What is the difference between these ctools content_types vs contentwidget (with predefined_widgets):
 *  - You don't need to re-use instances of these widgets, but you can re-use the widget itself.
 *  - You don't need to create instances (and bundles, and fields, and.. etc).
 *  - The clearer UI of the Ctools Dialog Form (we can put them in a separate bucket).
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Embedded Widget'),
  'description' => t('Insert the embedded widget, such as: Storify, Infogr.am, etc..'),
  'category' => t('Widget Library'),
  'edit form' => 'eiti_ctools_extra__embedded_widget__edit_form',
  'icon' => drupal_get_path('module', 'contentwidget') . '/icon-eiti-base.png',
  'render callback' => 'eiti_ctools_extra__embedded_widget__render',
  'admin info' => 'eiti_ctools_extra__embedded_widget__admin_info',
  'single' => TRUE,
  'defaults' => array(
    'embedded_code' => '',
    'widget_type' => '',
    'storify' => array(
      'url' => '',
      'title' => '',
    ),
    'infogram' => array(
      'id' => '',
      'title' => '',
      'info_type' => '',
    ),
  ),
);


/**
 * Output function for the 'Embedded Widget' content type.
 */
function eiti_ctools_extra__embedded_widget__render($subtype, $conf, $panel_args, $context) {
  global $language;
  $block = new stdClass();

  // Now build the content.
  $content = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'embedded-widget-wrapper',
        'single-fluid-row-wrapper'
      ),
    )
  );

  switch ($conf['type']) {
    case 'storify':
      $content['widget']['#markup'] = theme('eiti_ctools_extra_storify', array(
        'url' => $conf['storify']['url'],
        'title' => $conf['storify']['title'],
      ));
      break;
    case 'infogram':
      $content['widget']['#markup'] = theme('eiti_ctools_extra_infogram', array(
        'info_id' => $conf['infogram']['id'],
        'info_type' => $conf['infogram']['info_type'],
        'title' => $conf['infogram']['title'],
      ));
      break;
  }

  $block->content = $content;
  return $block;
}

/**
 * A settings form for this widget.
 */
function eiti_ctools_extra__embedded_widget__edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['type'] = array(
    '#title' => t('Widget Type'),
    '#type' => 'select',
    '#description' => t('Please specify which widget / service type you want to embed. Can\'t find the type you need? We can define new types later.'),
    '#default_value' => $conf['type'],
    '#required' => TRUE,
    '#options' => array_merge(array('' => t('- Select - ')), _eiti_ctools_extra__embedded_widget__get_types()),
  );
  $form['embedded_code'] = array(
    '#title' => t('Embedded Code'),
    '#type' => 'textarea',
    '#description' => t('Please paste in the code.<br/><em>Note: We will do custom processing and not paste as-is because of the security.</em>'),
    '#default_value' => $conf['embedded_code'],
  );

  // Make a preview of parsed data.
  switch ($conf['type']) {
    case 'storify':
      $form['embedded_identified_url'] = array(
        '#markup' => '<div>' . t('<strong>Verified Storify URL</strong>: @url', array(
            '@url' => !empty($conf['storify']['url']) ? $conf['storify']['url'] : t('N/A'),
          )) . '</div>',
      );
      $form['embedded_identified_title'] = array(
        '#markup' => '<div>' . t('<strong>Verified Storify Title</strong>: @title', array(
            '@title' => !empty($conf['storify']['title']) ? $conf['storify']['title'] : t('N/A'),
          )) . '</div>',
      );
      break;

    case 'infogram':
      $form['embedded_identified_id'] = array(
        '#markup' => '<div>' . t('<strong>Verified Infogr.am ID</strong>: @url', array(
            '@url' => !empty($conf['infogram']['id']) ? $conf['infogram']['id'] : t('N/A'),
          )) . '</div>',
      );
      $form['embedded_identified_title'] = array(
        '#markup' => '<div>' . t('<strong>Verified Infogr.am Title</strong>: @title', array(
            '@title' => !empty($conf['infogram']['title']) ? $conf['infogram']['title'] : t('N/A'),
          )) . '</div>',
      );
      $form['embedded_identified_inf_type'] = array(
        '#markup' => '<div>' . t('<strong>Verified Infogr.am Type</strong>: @title', array(
            '@title' => !empty($conf['infogram']['info_type']) ? $conf['infogram']['info_type'] : t('N/A'),
          )) . '</div>',
      );
      break;
  }

  return $form;
}

/**
 * Standard form validation (this is also where we do the processing).
 */
function eiti_ctools_extra__embedded_widget__edit_form_validate($form, &$form_state) {
  // Check types and post-processing.
  $type = $form_state['values']['type'];
  $code = $form_state['values']['embedded_code'];
  $types = _eiti_ctools_extra__embedded_widget__get_types();
  if ($output = _eiti_ctools_extra__embedded_widget__process($type, $code)) {
    $form_state['conf'][$type] = $output;
  }
  else {
    form_set_error('embedded_code', t('Make sure you have pasted correct <strong>@type</strong> code.', array(
      '@type' => $types[$type]
    )));
  }
}

/**
 * Submit form callback.
 */
function eiti_ctools_extra__embedded_widget__edit_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Small helper function that returns all of the enabled services / widget types.
 */
function _eiti_ctools_extra__embedded_widget__get_types() {
  return array(
    'storify' => t('Storify'),
    'infogram' => t('Infogr.am')
  );
}

/**
 * Function that processes the embedded widget and fetches only needed content and
 * returns it as an array, to be stored in $conf.
 */
function _eiti_ctools_extra__embedded_widget__process($type, $code) {
  switch ($type) {
    case 'storify':
      // We don't bother to use DOMDocument because usually it's a valid XML.
      try {
        $xml_code = new SimpleXMLElement($code);
      }
      catch (Exception $e) {
        return FALSE;
      }
      $xml_code = new SimpleXMLElement($code);
      $src = (string) $xml_code->iframe['src'];
      $title = (string) $xml_code->noscript->a;

      $src_parsed = parse_url($src);
      if ($src_parsed['host'] == 'storify.com') {
        // So, -6 = getting rid of "/embed".
        return array(
          'url' => '//' . $src_parsed['host'] . substr($src_parsed['path'], 0, -6),
          'title' => $title,
        );
      }
      break;

    case 'infogram':
      // But here it's different, because of the <script> tag it's not a valid XML.
      // So we fallback to DOMDocument.
      $html_code = DOMDocument::loadHTML($code);
      $div_element = $html_code->getElementsByTagName('div')[0];

      if (!empty($div_element)) {
        $id = (string) $div_element->getAttribute('data-id');
        $title = (string) $div_element->getAttribute('data-title');
        $info_data = (string) $div_element->getAttribute('data-type');

        if (!empty($id) && !empty($info_data)) {
          return array(
            'id' => $id,
            'title' => $title,
            'info_type' => $info_data,
          );
        }
      }
      break;
  }
  return FALSE;
}


/**
 * Admin info callback function.
 */
function eiti_ctools_extra__embedded_widget__admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $types = _eiti_ctools_extra__embedded_widget__get_types();
    $block->title = t('Configured @type Widget', array(
      '@type' => $types[$conf['type']]
    ));
    $block->content = t('Embedded Widget (Configured).');
    return $block;
  }
}

