<?php
/**
 * @file
 * Exposes custom theme functions.
 */

/**
 * An HTML5 alternative to theme_container().
 *
 * Returns HTML to wrap child elements in a container.
 *
 * Used for grouped form items. Can also be used as a #theme_wrapper for any
 * renderable element, to surround it with a <div> and add attributes such as
 * classes or an HTML id.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #id, #attributes, #children.
 *
 * @return string
 */
function theme_html_container($variables) {
  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  $prefix = array();

  if (isset($element['#contextual_info'])) {
    $element['#attributes']['class'][] = 'contextual-links-region';
    $prefix['contextual_links'] = array(
      '#type' => 'contextual_links',
      '#contextual_links' => array($element['#contextual_info']),
    );
  }

  if (isset($element['#title'])) {
    $title_tag = isset($element['#title_tag']) ? $element['#title_tag'] : 'h2';
    $title_attributes = isset($element['#title_attributes']) ? $element['#title_attributes'] : array();
    $prefix['title'] = array(
      '#type' => 'html_tag',
      '#tag' => $title_tag,
      '#value' => $element['#title'],
      '#attributes' => $title_attributes,
    );
  }

  $tag = isset($element['#tag'])? $element['#tag'] : 'div';
  return "<$tag" . drupal_attributes($element['#attributes']) . '>' . render($prefix) . $element['#children'] . "</$tag>";
}

/**
 * Returns HTML for the svg icons.
 *
 * @param array $elements
 * @return null|string
 */
function theme_svg_sprite(array $elements) {
  if (empty($elements['symbol'])) {
    return NULL;
  }

  // Provide a fallback sprite.
  if (empty($elements['sprite_name'])) {
    $elements['sprite_name'] = 'icons';
  }

  // Set the sprite path.
  $sprite_file_name = $elements['sprite_name'] . '.svg';
  $elements['path'] = drupal_get_path('module', 'helpertheme') . '/sprites/' . $sprite_file_name;

  // Set a default attributes.
  foreach (array('class', 'height', 'width', 'viewBox') as $key) {
    if (array_key_exists($key, $elements) && is_null($elements[$key])) {
      continue;
    }

    if (!empty($elements[$key])) {
      $elements['#attributes'][$key] = $elements[$key];
      continue;
    }

    switch ($key) {
      case 'width':
      case 'height':
        $elements['#attributes'][$key] = '2em';
        break;
    }
  }

  // @TODO: improve accessibility.
  $elements['#attributes']['role'] = 'presentation';
  $elements['#attributes']['class'][] = 'icon';
  $elements['#attributes']['class'][] = drupal_html_class('symbol--' . $elements['symbol']);

  $args = array();
  if (!is_null($elements['symbol'])) {
    $args['fragment'] = $elements['symbol'];
  }
  $elements['#use']['xlink:href'] = url($elements['path'], $args);

  return '<svg' . drupal_attributes($elements['#attributes']) . '><use' . drupal_attributes($elements['#use']) . '/></svg>';
}

/**
 * Returns HTML for the header logo.
 */
function theme_header_identity() {
  global $theme;

  // Text for homepage header logo link.
  $site_link_title = t(variable_get('site_link_title', 'Visit the main page'));
  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

  $items['#prefix'] = '<div class="site-identity-wrapper contextual-links-region">';
  $items['#suffix'] = '</div>';

  // Initialize the template variable as a renderable array.
  $items['contextual_links'] = array(
    '#type' => 'contextual_links',
    '#contextual_links' => array(
      'menu' => array('admin/settings/generic', array('edit')),
    ),
  );

  $items['header']['#prefix'] = '<h1 class="site-name">';
  $items['header']['#suffix'] = '</h1>';

  $items['header']['logo_markup'] = array(
    '#prefix' => '<a href="' . url('<front>') . '" title="' . $site_link_title . '" class="link" rel="home">',
    '#suffix' => "</a>",
  );

  // Get the logo paths if it has been changed.
  $logo_path = theme_get_setting('logo_path', $theme);

  $file_path = drupal_realpath($logo_path);
  if (file_exists($file_path)) {
    $items['header']['logo_markup']['png'] = array(
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
    $items['header']['logo_markup']['svg'] = array(
      '#theme' => 'image',
      '#path' => file_create_url(drupal_get_path('theme', $theme) . '/logo.svg'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
        'class' => array('site-logo'),
      ),
      '#prefix' => "<!--[if (gte IE 9)|!(IE)]><!-->",
      '#suffix' => "<!--<![endif]-->",
    );
    $items['header']['logo_markup']['png'] = array(
      '#theme' => 'image',
      '#path' => file_create_url(drupal_get_path('theme', $theme) . '/logo.png'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
        'class' => array('site-logo'),
      ),
      '#prefix' => "<!--[if lt IE 9 ]>",
      '#suffix' => "<![endif]-->",
    );
  }

  //$items['header']['logo_markup']['site_name'] = array(
  //  '#markup' => $site_name,
  //  '#prefix' => '<span class="text">',
  //  '#suffix' => "</span>",
  //);

  // Render the HTML.
  return drupal_render($items);
}

/**
 * Returns HTML for the header items.
 */
function theme_header_items() {
  $menu_elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'header-items',
      ),
    ),
  );

  // Get the menu links.
  $menu_name = 'main-menu';
  $menu_elements['navigation'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Main Menu'),
    '#title_attributes' => array('class' => array('section-title', 'element-invisible')),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      'role' => 'navigation',
      'class' => array(
        'main-navigation',
      ),
    ),
  );
  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $links['#extras']['svgicon_size'] = '1.5em';  // @TODO: Remove this hack!
    $menu_elements['navigation']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'header-links',
        ),
      ),
    );
  }
  else {
    $menu_elements['navigation']['empty'] = array(
      '#markup' => t('Main Menu not configured!'),
    );
  }

  // Prepare the search-form.
  // @TODO: Use a search form.
  //$menu_elements['search']['#prefix'] = '<div class="search-form-wrapper">';
  //$menu_elements['search']['#suffix'] = '</div>';
  //$search_form = drupal_get_form('search_form');
  //unset($search_form['basic']['keys']['#title']);

  // Add the language switcher links.
  if (FALSE && drupal_multilingual()) {
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
    $lang_links = language_negotiation_get_switch_links('language', $path);
    if (isset($lang_links->links)) {
      $menu_elements['lang']['#prefix'] = '<nav role="navigation" id="language-switcher" class="language-switcher">';
      $menu_elements['lang']['#suffix'] = '</nav>';

      $menu_elements['lang']['subject'] = array(
        '#type' => 'html_tag',
        '#tag' => 'h2',
        '#value' => 'Languages',
        '#attributes' => array('class' => array('element-invisible')),
      );

      // Add language info to all links.
      $languages = language_list();
      foreach ($lang_links->links as &$link) {
        if (isset($link['attributes']['lang']) && isset($languages[$link['attributes']['lang']])) {
          $link['language'] = $languages[$link['attributes']['lang']];
        }
      }

      $menu_elements['lang']['links'] = array(
        '#theme' => 'links__language_switcher',
        '#links' => $lang_links->links,
        '#attributes' => array(
          'class' => array(
            'language-switcher' . $lang_links->provider,
            'header-links',
            'locale-links',
          ),
        ),
      );
    }
  }

  // Render the HTML.
  $output = drupal_render($menu_elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>\s+\</', '><', $output);
}

/**
 * Returns HTML for main navigation menu.
 */
function theme_main_navigation() {
  $menu_elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'navigation-toplevel',
      ),
    ),
  );

  // Initialize the template variable as a renderable array.
  $menu_elements['contextual_links'] = array(
    '#type' => 'contextual_links',
    '#contextual_links' => array(
      'menu' => array('admin/structure/menu/manage', array('main-menu')),
    ),
  );
  // Mark this element as potentially having contextual links attached to it.
  $menu_elements['#attributes']['class'][] = 'contextual-links-region';

  $menu_elements['header'] = array(
    '#type' => 'html_tag',
    '#tag' => 'h2',
    '#value' => 'Main Menu',
    '#attributes' => array('class' => array('element-invisible')),
  );

  $menu_tree_callback = (function_exists('i18n_menu_translated_tree')) ? 'i18n_menu_translated_tree' : 'menu_tree';
  $menu_elements['navigation'] = $menu_tree_callback('main-menu');

  // Change the wrapper class.
  $menu_elements['navigation']['#theme_wrappers'] = array('menu_tree__main_menu__toplevel');

  // Render the menu.
  $output = drupal_render($menu_elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>[\n\ ]+\</', '><', $output);
}

/**
 * Returns HTML for the footer items.
 */
function theme_footer_items() {
  $items = array();

  // Render the HTML.
  $output = drupal_render($items);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>\s+\</', '><', $output);
}

/**
 * @param $variables
 */
function helpertheme_preprocess_main_footer(&$variables) {

  $variables['identity'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#contextual_info' => array('admin/settings/generic', array('edit')),
    '#attributes' => array(
      'class' => array(
        'footer-identity',
      ),
    ),
  );

  // Always reference the EITI theme, and not the current active theme.
  $theme = 'eiti';
  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));
  $variables['identity']['logo_markup']['png'] = array(
    '#theme' => 'image',
    '#path' => url(drupal_get_path('theme', $theme) . '/images/logo-white.png'),
    '#alt' => $site_name,
    '#attributes' => array(
      'role' => 'presentation',
      'class' => array('footer-logo'),
    ),
  );

  $site_footer_slogan = filter_xss_admin(variable_get('site_footer_slogan', ''));
  $variables['identity']['site_slogan'] = array(
    '#markup' => $site_footer_slogan,
    '#prefix' => '<div class="footer-slogan">',
    '#suffix' => '</div>',
  );

  $variables['contact'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('EITI International Secretariat'),
    '#title_attributes' => array('class' => array('section-title')),
    '#contextual_info' => array('admin/settings/generic', array('edit')),
    '#attributes' => array(
      'class' => array(
        'footer-contact',
      ),
    ),
  );

  $site_footer_contact = filter_xss_admin(variable_get('site_footer_contact', ''));
  $variables['contact']['info'] = array(
    '#markup' => $site_footer_contact,
    '#prefix' => '<div class="footer-contact-info">',
    '#suffix' => '</div>',
  );

  $menu_name = 'menu-footer-information';
  $variables['information'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Footer Information Menu'),
    '#title_attributes' => array('class' => array('section-title', 'element-invisible')),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      'role' => 'navigation',
      'class' => array(
        'footer-information',
      ),
    ),
  );

  // Get the menu links.
  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $variables['information']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'footer-links',
          'footer-information-links',
        ),
      ),
    );
  }
  else {
    $variables['information']['empty'] = array(
      '#markup' => t('Menu not configured!'),
    );
  }

  $menu_name = 'menu-footer-social';
  $variables['social'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Stay connected'),
    '#title_attributes' => array('class' => array('section-title')),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      //'role' => 'navigation',
      'class' => array(
        'footer-social',
      ),
    ),
  );

  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $variables['social']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'social-link',
      '#attributes' => array(
        'class' => array(
          'footer-links',
          'footer-social-links',
        ),
      ),
    );
  }
  else {
    $variables['social']['empty'] = array(
      '#markup' => t('Menu not configured!'),
    );
  }

  // Get the menu links.
  $menu_name = 'menu-footer-navigation';
  $variables['navigation'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Footer Navigation Menu'),
    '#title_attributes' => array('class' => array('section-title', 'element-invisible')),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      'role' => 'navigation',
      'class' => array(
        'footer-navigation',
      ),
    ),
  );

  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $variables['navigation']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'footer-links',
          'footer-navigation-links',
        ),
      ),
    );
  }
  else {
    $variables['navigation']['empty'] = array(
      '#markup' => t('Menu not configured!'),
    );
  }

  $variables['legal'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('Content Use Policy'),
    '#title_attributes' => array('class' => array('section-title')),
    '#contextual_info' => array('admin/settings/generic', array('edit')),
    '#attributes' => array(
      'class' => array(
        'footer-legal',
      ),
    ),
  );

  $site_footer_legal = filter_xss_admin(variable_get('site_footer_legal', ''));
  $variables['legal']['info'] = array(
    '#markup' => $site_footer_legal,
    '#prefix' => '<div class="footer-legal-info">',
    '#suffix' => '</div>'
  );
}
