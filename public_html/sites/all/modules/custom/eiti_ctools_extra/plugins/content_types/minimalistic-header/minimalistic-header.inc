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
    'hex_background' => 'f0f0f0',
    'close' => FALSE,
    'close_time' => '200',
    'include_language_switcher' => TRUE,
  ),
);

/**
 * Output function for the 'Minimalistic Header' content type.
 */
function eiti_ctools_extra__minimalistic_header__render($subtype, $conf, $panel_args, $context) {
  global $language;
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

  // Insert inline background color.
  if (!empty($conf['hex_background'])) {
    $inline_style = 'background-color: #' . $conf['hex_background'];
    $block['wrapper']['#attributes']['style'] = $inline_style;
  }

  $block['wrapper']['logo'] = $logo_markup;

  // Add the optional title.
  if (!empty($conf['title'])) {
    $block['wrapper']['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h1',
      '#value' => t($conf['title']),
      '#attributes' => array(
        'class' => array(
          'minimalistic-page-title',
        ),
      ),
    );
  }

  $menu_items = array(
    '#type' => 'container',
    '#weight' => '1',
    '#attributes' => array(
      'class' => array(
        'header-items',
        'clearfix',
      ),
    ),
  );
  $block['wrapper']['menu_items'] = $menu_items;
  if (!empty($conf['include_language_switcher']) && $conf['include_language_switcher'] == TRUE && drupal_multilingual()) {
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
    $lang_links = language_negotiation_get_switch_links('language', $path);

    if (isset($lang_links->links)) {
      $active_language = check_plain($language->native);
      $title_attributes = array(
        'class' => array('language-switcher-title'),
        'xml:lang' => $language->language,
      );

      $block['wrapper']['menu_items']['language_switcher'] = array(
        '#type' => 'html_container',
        '#tag' => 'nav',
        '#title' => $active_language,
        '#title_attributes' => $title_attributes,
        '#attributes' => array(
          'role' => 'navigation',
          'class' => array(
            'language-switcher',
            'container-inline',
          ),
        ),
      );

      $block['wrapper']['menu_items']['language_switcher']['wrapper'] = array(
        '#type' => 'html_container',
        '#attributes' => array(
          'class' => array(
            'locale-links-wrapper',
          ),
        ),
      );

      // Add language info to all links.
      $languages = language_list();
      foreach ($lang_links->links as &$link) {
        if (isset($link['attributes']['lang']) && isset($languages[$link['attributes']['lang']])) {
          $link['language'] = $languages[$link['attributes']['lang']];
        }
      }

      $block['wrapper']['menu_items']['language_switcher']['wrapper']['links'] = array(
        '#theme' => 'links__language_switcher',
        '#links' => $lang_links->links,
        '#attributes' => array(
          'class' => array(
            'language-switcher-' . $lang_links->provider,
            'locale-links',
          ),
        ),
      );

      // Make the button optional.
      if (!empty($conf['close']) && $conf['close'] == TRUE) {
        $block['wrapper']['menu_items']['toggle_btn']['#markup'] = l('Close', '', array(
          'fragment' => 'close',
          'attributes' => array(
            'class' => array('header-close-action'),
            'data-animation-time' => !empty($conf['close_time']) ? $conf['close_time'] : '200',
          ),
          'external' => TRUE,
        ));
        $block['wrapper']['menu_items']['toggle_btn']['#weight'] = '2';
      }
    }
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

  $form['hex_background'] = array(
    '#title' => t('Background Color'),
    '#type' => 'textfield',
    '#description' => t('Please specify the background color.'),
    '#field_prefix' => '#',
    '#size' => 6,
    '#default_value' => $conf['hex_background'],
  );

  $form['close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the "Close" button'),
    '#description' => t('If you want to enable the close button, please check this box.'),
    '#default_value' => $conf['close'],
  );

  $form['close_time'] = array(
    '#title' => t('Closing Milliseconds'),
    '#type' => 'textfield',
    '#description' => t('Please specify how many milliseconds should the close action take place? Note: "0" indicates that it should be instant.'),
    '#field_suffix' => t(' Milliseconds'),
    '#size' => 6,
    '#default_value' => $conf['close_time'],
    '#states' => array(
      'visible' => array(
        'input[name="close"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['include_language_switcher'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Language Switcher'),
    '#description' => t('Check this box if you want to include the language switcher.'),
    '#default_value' => $conf['include_language_switcher'],
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
