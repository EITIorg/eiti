<?php
/**
 * @file
 * This file contains changes related to the overall page.
 */

/**
 * Preprocess variables for html.tpl.php
 */
function eiti_preprocess_html(&$variables) {
  // TODO: Cleanup!
  if (variable_get('eiti_beta_warning', 1)) {
    $message = 'Welcome to our new website, highlighting the impact of the EITI’s work in our 51 member countries.';
    $message .= '<br>';
    $message .= 'Some features are still under construction. If needed, you can access our old site <a href="https://eiti.org/home">here</a>';
    $variables['eiti_beta_warning'] = t($message);
  }
}

/**
 * Preprocess variables for page.tpl.php
 */
function eiti_preprocess_page(&$variables) {
  // For now hide breadcrumb.
  $variables['display_breadcrumb'] = FALSE;

  // Hide tabs on various pages and for anonymous users.
  $variables['display_tabs'] = TRUE;
  if (user_is_anonymous()) {
    $variables['display_tabs'] = FALSE;
  }
  else if (drupal_is_front_page() && !user_access('create page content')) {
    $variables['display_tabs'] = FALSE;
  }

  // Always display tabs on admin pages.
  if (arg(0) == 'admin') {
    $variables['display_tabs'] = TRUE;
  }

  $variables['browser_warnings'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('browser-warnings-wrapper')),
  );

  // Inform users that they are using an outdated browser.
  $variables['browser_warnings']['oldbrowser'] = array();
  if (empty($_COOKIE['ignore_oldbrowser'])) {
    $variables['browser_warnings']['oldbrowser'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('oldbrowser-warning')),
      '#prefix' => "<!--[if lt IE 9]>\n",
      '#suffix' => "<![endif]-->\n",
    );

    $variables['browser_warnings']['oldbrowser']['message'] = array(
      '#type' => 'html_tag',
      '#tag' => 'p',
      '#value' => t('You are using an outdated browser. <a href="http://browsehappy.com">Upgrade your browser today</a> to better experience this site.'),
    );

    $variables['browser_warnings']['oldbrowser']['ignore'] = array(
      '#type' => 'html_tag',
      '#tag' => 'a',
      '#value' => 'x',
      '#attributes' => array(
        'class' => array(
          'ignore-link',
        ),
        'href' => '#',
        'title' => t('Hide this warning.'),
      ),
    );
  }

  // Inform users that they have JavaScript disabled.
  $variables['browser_warnings']['nojs'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('nojs-warning')),
    '#prefix' => '<noscript>',
    '#suffix' => '</noscript>',
  );
  $variables['browser_warnings']['nojs']['message'] = array(
    '#type' => 'html_tag',
    '#tag' => 'p',
    '#value' => t('Please enable JavaScript for full use of this site.'),
  );

  $style_main_content = FALSE;
  if (in_array(arg(0), array('admin', 'eform', 'user'))) {
    $style_main_content = TRUE;
  }
  else if (arg(2) != NULL && in_array(arg(0), array('node'))) {
    $style_main_content = TRUE;
  }

  $variables['main_content_classes'] = '';
  if ($style_main_content) {
    $variables['main_content_classes'] .= ' layout-block layout-separator';
  }

  if (!empty($_GET['page-template'])) {
    switch ($_GET['page-template']) {
      case 'simplepage':
        // Hide the admin menu and use a simple page template.
        admin_menu_suppress(TRUE);
        $variables['theme_hook_suggestions'][] = 'page__simplepage';
        break;
      default:
        // Do nothing!
        break;
    }
  }
}

/**
 * Implements hook_preprocess_html_tag().
 *
 * @see: http://wiki.whatwg.org/wiki/HTML_vs._XHTML#Element-specific_parsing
 */
function eiti_process_html_tag(&$vars) {
  $element = &$vars['element'];

  // Make Drupal 7 HTML5 compliant.
  if (in_array($element['#tag'], array('script', 'link', 'style'))) {
    // Remove the "type" attribute.
    unset($element['#attributes']['type']);

    // Remove CDATA comments.
    if (isset($element['#value_prefix']) && ($element['#value_prefix'] == "\n<!--//--><![CDATA[//><!--\n" || $element['#value_prefix'] == "\n<!--/*--><![CDATA[/*><!--*/\n")) {
      unset($element['#value_prefix']);
    }
    if (isset($element['#value_suffix']) && ($element['#value_suffix'] == "\n//--><!]]>\n" || $element['#value_suffix'] == "\n/*]]>*/-->\n")) {
      unset($element['#value_suffix']);
    }
  }
}

/**
 * Implements hook_css_alter().
 *
 * @TODO: Cleanup CSS!
 */
function eiti_css_alter(&$css) {
  $exclude_list = array(
    'modules',
    'sites/all/modules/contrib',
  );
  $exceptions_list = array(
    'sites/all/modules/contrib/admin_menu',
    'sites/all/modules/contrib/adminimal_admin_menu',
    'sites/all/modules/contrib/colorbox',
    'sites/all/modules/contrib/ctools',
    'sites/all/modules/contrib/date',
    'sites/all/modules/contrib/field_group',
    'sites/all/modules/contrib/hierarchical_select',
    'sites/all/modules/contrib/l10n_client',
    'sites/all/modules/contrib/media',
    'sites/all/modules/contrib/owlcarousel',
    'sites/all/modules/contrib/views',
  );

  // The CSS_SYSTEM aggregation group doesn't make any sense and most of the
  // provided files are useless. Therefore we override almost all CSS files.
  foreach ($css as $file_path => $item) {
    if ($item['type'] != 'file') {
      continue;
    }

    if ($item['group'] == CSS_SYSTEM) {
      $item['group'] = CSS_DEFAULT;
      $item['weight'] = $item['weight'] - 100;
    }

    // We remove most of the default CSS files.
    $remove_file = FALSE;
    foreach ($exclude_list as $exclude_item) {
      if (strpos($file_path, $exclude_item) === 0) {
        $remove_file = TRUE;
        break;
      }
    }
    foreach ($exceptions_list as $exclude_item) {
      if (strpos($file_path, $exclude_item) === 0) {
        $remove_file = FALSE;
        break;
      }
    }

    if ($remove_file) {
      // Remove current file.
      unset($css[$file_path]);
    }
  }
}

/**
 * Implements hook_js_alter().
 *
 * @TODO: Cleanup JS!
 */
function eiti_js_alter(&$js) {
  // The JS_LIBRARY aggregation group doesn't need to be in a separate file.
  foreach ($js as $file_path => $item) {
    if ($item['type'] != 'file') {
      continue;
    }

    if ($item['group'] == JS_LIBRARY) {
      $item['group'] = JS_DEFAULT;
      $item['weight'] = $item['weight'] - 100;
    }
  }
}

/**
 * Implements hook_form_alter().
 */
function eiti_form_alter(&$form, &$form_state, $form_id) {
  // Duplicate the form ID as a class so we can reduce specificity in our CSS.
  $identifier = drupal_clean_css_identifier($form['#id']);
  if (!isset($form['#attributes']['class'])) {
    $form['#attributes']['class'][] = $identifier;
  }
  else if (is_array($form['#attributes']['class'])) {
    if (!in_array($identifier, $form['#attributes']['class'])) {
      $form['#attributes']['class'][] = $identifier;
    }
  }
}
