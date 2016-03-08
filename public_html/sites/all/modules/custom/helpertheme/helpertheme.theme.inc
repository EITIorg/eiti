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

    if (isset($element['#title_icon']['symbol'])) {
      $element['#title_icon']['options'] = isset($element['#title_icon']['options']) ? $element['#title_icon']['options'] : array();
      // Get the SVG icon markup.
      $svgicon = helpertheme_get_svg_icon($element['#title_icon']['symbol'], $element['#title_icon']['options']);
      $element['#title'] = $svgicon . ' <span class="text">' . $element['#title'] . '<span>';
    }

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
function theme_svg_icon(array $elements) {
  if (empty($elements['#info']['name'])) {
    return '';
  }

  // Provide a fallback sprite.
  if (empty($elements['#info']['group'])) {
    $elements['#info']['group'] = 'icons';
  }

  // Set a default attributes.
  foreach (array('class', 'height', 'width') as $key) {
    if (!empty($elements['#options'][$key])) {
      $elements['#attributes'][$key] = $elements['#options'][$key];
      continue;
    }

    // Provide defaults
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
  $elements['#attributes']['class'][] = drupal_html_class('symbol--' . $elements['#info']['name']);

  if (empty($elements['#info']['in_sprite'])) {
    // Prepare the sprite file path.
    $svg_file_name = $elements['#info']['group'] . '/' . $elements['#info']['name'] . '.svg';
    $svg_file_path = drupal_get_path('module', 'helpertheme') . '/images/' . $svg_file_name;

    $image_options = array(
      'path' => $svg_file_path,
    );
    foreach (array_keys($elements['#attributes']) as $key) {
      if ($key == 'width' || $key == 'height') {
        $font_base_size = 16;
        $image_options[$key] = preg_replace('/[^\d]+em/', '', $elements['#attributes'][$key]) * $font_base_size;
        continue;
      }

      $image_options[$key] = $elements['#attributes'][$key];
    }

    return theme('image', $image_options);
  }
  else {
    return theme('svg_sprite', $elements);
  }
}

/**
 * Returns HTML for the svg sprite icons.
 *
 * @param array $elements
 * @return null|string
 */
function theme_svg_sprite(array $elements) {
  // Prepare the sprite file path.
  $sprite_file_name = $elements['#info']['group'] . '.svg';
  $sprite_file_path = drupal_get_path('module', 'helpertheme') . '/sprites/' . $sprite_file_name;

  // A dummy query-string is added to filenames, to gain control over
  // browser-caching. The string changes on every update or full cache
  // flush, forcing browsers to load a new copy of the files, as the
  // URL changed.
  $query_string = variable_get('css_js_query_string', '0');
  $path_suffix = '?' . $query_string;

  // Specify the sprite element.
  $path_suffix .= '#' . $elements['#info']['name'];

  $elements['#use']['xlink:href'] = file_create_url($sprite_file_path) . $path_suffix;

  return '<svg' . drupal_attributes($elements['#attributes']) . '><use' . drupal_attributes($elements['#use']) . '/></svg>';
}

/**
 * Returns HTML for the header logo.
 */
function theme_header_identity() {
  // Always reference the EITI theme, and not the current active theme.
  $theme = 'eiti';
  $theme_path = drupal_get_path('theme', $theme);

  // Get the logo paths if it has been changed.
  $logo_path = theme_get_setting('logo_path', $theme);

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
      '#path' => file_create_url($theme_path . '/logo.svg'),
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
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'header-items',
      ),
    ),
  );

  // Get the menu links.
  $menu_name = 'user-menu';
  if (user_is_logged_in() && $links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $elements['user_navigation'] = array(
      '#type' => 'html_container',
      '#tag' => 'nav',
      '#title' => t('User Menu'),
      '#title_attributes' => array('class' => array('element-invisible')),
      '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
      '#attributes' => array(
        'role' => 'navigation',
        'class' => array(
          'user-navigation',
        ),
      ),
    );

    $elements['user_navigation']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'header-user-links',
          'links',
          'clearfix',
        )
      ),
    );
  }


  // Add the language switcher links.
  if (drupal_multilingual()) {
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
    $lang_links = language_negotiation_get_switch_links('language', $path);
    if (isset($lang_links->links)) {
      $elements['language_switcher'] = array(
        '#type' => 'html_container',
        '#tag' => 'nav',
        '#title' => t('Languages'),
        '#title_attributes' => array('class' => array('language-switcher-title')),
        '#title_icon' => array(
          'symbol' => 'message',
          'options' => array('width' => '1.5em', 'height' => '1.5em'),
        ),
        '#attributes' => array(
          'role' => 'navigation',
          'class' => array(
            'language-switcher',
          ),
        ),
      );

      $elements['language_switcher']['wrapper'] = array(
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

      $elements['language_switcher']['wrapper']['links'] = array(
        '#theme' => 'links__language_switcher',
        '#links' => $lang_links->links,
        '#attributes' => array(
          'class' => array(
            'language-switcher-' . $lang_links->provider,
            'locale-links',
          ),
        ),
      );
    }
  }

  // Get the menu links.
  $menu_name = 'main-menu';
  $elements['navigation'] = array(
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
    $elements['navigation']['links'] = array(
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
    $elements['navigation']['empty'] = array(
      '#markup' => t('Main Menu not configured!'),
    );
  }

  // Prepare the search-form.
  // @TODO: Use a search form.
  //$menu_elements['search']['#prefix'] = '<div class="search-form-wrapper">';
  //$menu_elements['search']['#suffix'] = '</div>';
  //$search_form = drupal_get_form('search_form');
  //unset($search_form['basic']['keys']['#title']);

  // Render the HTML.
  $output = drupal_render($elements);

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
  // Always reference the EITI theme, and not the current active theme.
  $theme_path = drupal_get_path('theme', 'eiti');

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

  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));
  $variables['identity']['logo_markup']['png'] = array(
    '#theme' => 'image',
    '#path' => file_create_url($theme_path . '/images/logo-white.png'),
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
