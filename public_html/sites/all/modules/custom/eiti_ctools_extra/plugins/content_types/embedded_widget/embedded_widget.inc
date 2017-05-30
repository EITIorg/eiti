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
      // Let's check if we have the 'default' key set. If we don't, we mock it.
      if (empty($conf['storify']['default'])) {
        $conf['storify']['default'] = $conf['storify'];
      }
      $content['widget']['#markup'] = theme('eiti_ctools_extra_storify', array(
        'url' => isset($conf['storify'][$language->language]['url']) ? $conf['storify'][$language->language]['url'] : $conf['storify']['default']['url'],
        'title' => isset($conf['storify'][$language->language]['title']) ? $conf['storify'][$language->language]['title'] : $conf['storify']['default']['title'],
      ));
      break;
    case 'infogram':
      // Let's check if we have the 'default' key set. If we don't, we mock it.
      if (empty($conf['infogram']['default'])) {
        $conf['infogram']['default'] = $conf['infogram'];
      }
      $content['widget']['#markup'] = theme('eiti_ctools_extra_infogram', array(
        'info_id' => isset($conf['infogram'][$language->language]['id']) ? $conf['infogram'][$language->language]['id'] : $conf['infogram']['default']['id'],
        'info_type' => isset($conf['infogram'][$language->language]['info_type']) ? $conf['infogram'][$language->language]['info_type'] : $conf['infogram']['default']['info_type'],
        'title' => isset($conf['infogram'][$language->language]['title']) ? $conf['infogram'][$language->language]['title'] : $conf['infogram']['default']['title'],
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

  $form['i18n'] = array(
    '#title' => t('Multilingual'),
    '#type' => 'checkbox',
    '#description' => t('If you want to specify a different Widget for a different language, please check this box.'),
    '#default_value' => $conf['i18n'],
  );

  $languages = language_list();
  foreach ($languages as $language) {
    $form['embedded_code_' . $language->language] = array(
      '#title' => t('Embedded Code (!language)', array('!language' => $language->name)),
      '#type' => 'textarea',
      '#description' => t('Specify the code for !language. If it\'s blank, we will use the default value.', array(
        '!language' => $language->name,
      )),
      '#default_value' => $conf['embedded_code_' . $language->language],
      '#states' => array(
        'visible' => array(
          'input[name="i18n"]' => array('checked' => TRUE),
        ),
      )
    );
  }

  $form['embedded_code'] = array(
    '#title' => t('Embedded Code (Default)'),
    '#type' => 'textarea',
    '#description' => t('Please paste in the code.<br/><em>Note: We will do custom processing and not paste as-is because of the security.</em>'),
    '#default_value' => $conf['embedded_code'],
  );

  // Make a preview of parsed data.
  switch ($conf['type']) {
    case 'storify':
      if ($conf['i18n'] == TRUE) {
        foreach ($conf['storify'] as $language_code => $storify_localized) {
          $form['embedded_identified_url_' . $language_code] = array(
            '#markup' => '<hr/><div>' . t('<strong>Verified Storify URL</strong> (@lang): @url', array(
                '@url' => !empty($conf['storify'][$language_code]['url']) ? $conf['storify'][$language_code]['url'] : t('N/A'),
                '@lang' => strtoupper($language_code)
              )) . '</div>',
          );
          $form['embedded_identified_title_' . $language_code] = array(
            '#markup' => '<div>' . t('<strong>Verified Storify Title</strong> (@lang): @title', array(
                '@title' => !empty($conf['storify'][$language_code]['title']) ? $conf['storify'][$language_code]['title'] : t('N/A'),
                '@lang' => strtoupper($language_code)
              )) . '</div>',
          );
        }
      }
      break;

    case 'infogram':
      if ($conf['i18n'] == TRUE) {
        foreach ($conf['infogram'] as $language_code => $storify_localized) {
          $form['embedded_identified_id_' . $language_code] = array(
            '#markup' => '<hr/><div>' . t('<strong>Verified Infogr.am ID</strong> (@lang): @url', array(
                '@url' => !empty($conf['infogram'][$language_code]['id']) ? $conf['infogram'][$language_code]['id'] : t('N/A'),
                '@lang' => strtoupper($language_code),
              )) . '</div>',
          );
          $form['embedded_identified_title_' . $language_code] = array(
            '#markup' => '<div>' . t('<strong>Verified Infogr.am Title</strong> (@lang): @title', array(
                '@title' => !empty($conf['infogram'][$language_code]['title']) ? $conf['infogram'][$language_code]['title'] : t('N/A'),
                '@lang' => strtoupper($language_code),
              )) . '</div>',
          );
          $form['embedded_identified_inf_type_' . $language_code] = array(
            '#markup' => '<div>' . t('<strong>Verified Infogr.am Type</strong> (@lang): @title', array(
                '@title' => !empty($conf['infogram'][$language_code]['info_type']) ? $conf['infogram'][$language_code]['info_type'] : t('N/A'),
                '@lang' => strtoupper($language_code),
              )) . '</div>',
          );
        }
      }
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
  $i18n = $form_state['values']['i18n'];
  $types = _eiti_ctools_extra__embedded_widget__get_types();
  $form_state['conf'][$type] = array();

  // Internationalization case!
  if ($i18n) {
    $languages = language_list();
    foreach ($languages as $language) {
      if (($form_state['values']['embedded_code_' . $language->language])) {
        // First, make sure it's off.
        unset($form_state['conf'][$type][$language->language]);
        if ($output = _eiti_ctools_extra__embedded_widget__process($type, $form_state['values']['embedded_code_' . $language->language])) {
          $form_state['conf'][$type][$language->language] = $output;
        }
        else {
          form_set_error('embedded_code_' . $language->language, t('Make sure you have pasted correct <strong>@type</strong> code.', array(
            '@type' => $types[$type]
          )));
        }
      }
    }
  }

  // Defaults still work as they used to (w/ or w/o i18n).
  if ($output = _eiti_ctools_extra__embedded_widget__process($type, $code)) {
    $form_state['conf'][$type]['default'] = $output;
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
    if ($conf['i18n']) {
      $block->title .= t(' (with internationalization)');
    }
    $block->content = t('Embedded Widget (Configured).');
    return $block;
  }
}

