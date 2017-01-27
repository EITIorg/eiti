<?php

/**
 * @file
 * Minimalistic header to replace the standard header.
 */

$plugin = array(
  'title' => t('Minimalistic Header'),
  'description' => t('A standard minimalistic header (to be used when the blocks are disabled, like in Progress Report pages).'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__minimalistic_header__render',
  'edit form' => 'eiti_ctools_extra__minimalistic_header__settings_form',
  'defaults' => array(
    'title' => '',
  ),
);

/**
 * Output function for the 'Minimalistic Header' content type.
 */
function eiti_ctools_extra__minimalistic_header__render($subtype, $conf, $panel_args, $context) {
  $theme = 'eiti';

  // We'll need the logo as a link, so let's craft it out.
  $theme_path = drupal_get_path('theme', $theme);
  $logo_path = theme_get_setting('logo_path', $theme);
  $file_path = drupal_realpath($logo_path);
  $site_name = filter_xss_admin(variable_get('site_name', 'EITI.org Homepage'));
  $site_link_title = t(variable_get('site_link_title', 'Visit the main page'));
  $logo_markup = array(
    '#type' => 'html_container',
    '#tag' => 'a',
    '#attributes' => array(
      'href' => url('<front>'),
      'title' => $site_link_title,
      'rel' => 'home',
      'class' => array(
        'link', 'minimalistic-logo-link'
      ),
    ),
  );
  if (file_exists($file_path)) {
    $logo_markup['png'] = array(
      '#theme' => 'image',
      '#path' => file_create_url($logo_path),
      '#alt' => '',
      '#attributes' => array(
        'role' => 'presentation',
        'class' => array('site-logo'),
      ),
    );
  }
  else {
    $logo_alt = $site_name;
    $logo_markup['svg'] = array(
      '#theme' => 'image',
      '#path' => file_create_url($theme_path . '/logo.svg'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
        'class' => array('site-logo'),
      ),
      '#prefix' => "<!--[if (gte IE 9)|!(IE)]><!-->",
      '#suffix' => "<!--<![endif]-->",
    );
    $logo_markup['png'] = array(
      '#theme' => 'image',
      '#path' => file_create_url($theme_path . '/logo.png'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
        'class' => array('site-logo'),
      ),
      '#prefix' => "<!--[if lt IE 9 ]>",
      '#suffix' => "<![endif]-->",
    );
  }
  $block['wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'minimalistic-wrapper',
      ),
    )
  );
  $block['wrapper']['logo'] = $logo_markup;

  // Add the optional title.
  if (!empty($conf['title'])) {
    $block['wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h1',
      '#value' => $conf['title'],
      '#attributes' => array(
        'class' => array(
          'minimalistic-page-title',
        ),
      ),
    );
  }

  return (object) array(
    'content' => $block,
  );
}

/**
 * Settings form for the Minimalistic Header.
 */
function eiti_ctools_extra__minimalistic_header__settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $cleanup_list = array(
    'context',
    'override_title',
    'override_title_text',
    'override_title_heading',
    'override_title_markup',
  );
  foreach ($cleanup_list as $key) {
    if (isset($form[$key])) {
      $form[$key]['#access'] = FALSE;
    }
  }

  $form['title'] = array(
    '#title' => t('Title after the logo.'),
    '#type' => 'textfield',
    '#description' => t('Leave <strong>empty</strong> if you wish no title / description of the page.<br />Note: Make sure to place this widget on the top of the page.'),
    '#default_value' => $conf['title'],
  );

  return $form;
}

function eiti_ctools_extra__minimalistic_header__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
