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
      $element['#title'] = $svgicon . ' <span class="text">' . $element['#title'] . '</span>';
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

  $cache_key = implode(':', array(
    'svg',
    $elements['#info']['group'],
    $elements['#info']['name'],
    md5(serialize($elements)),
  ));
  if ($cache = cache_get($cache_key)) {
    return $cache->data;
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
    $markup = theme('svg_inline', $elements);
  }
  else {
    $markup = theme('svg_sprite', $elements);
  }

  if (!empty($markup)) {
    cache_set($cache_key, $markup);
  }

  return $markup;
}

/**
 * Returns HTML for the svg sprite icons.
 *
 * @param array $elements
 * @return string
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
 * Returns markup for an inline svg icon.
 *
 * @param array $elements
 * @return string
 */
function theme_svg_inline(array $elements) {
  $sprite_file_path = $elements['#info']['path'];

  if ($svg_contents = @file_get_contents($sprite_file_path)) {
    $xml = new SimpleXMLElement($svg_contents);

    foreach ($elements['#attributes'] as $name => $value) {
      $value = implode(' ', (array) $value);
      $xml->addAttribute($name, $value);
    }

    $update_xml_string = $xml->asXML();
    $update_xml_string = str_replace('<?xml version="1.0"?>', '', $update_xml_string);
    return $update_xml_string;
  }

  return '';
}

/**
 * Returns HTML for the header items.
 */
function theme_header_items() {
  $elements['identity'] = _theme_header_items__identity();
  $elements['items'] = _theme_header_items__navigation();
  $elements['secondary_navigation_toggle'] = _theme_header_items__secondary_navigation_toggle();
  $elements['language_switcher'] = _theme_header_items__language_switcher();
  $elements['search'] = _theme_header_items__search();

  // Render the HTML.
  $output = drupal_render($elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>\s+\</', '><', $output);
}

/**
 * Returns HTML for the header menu.
 */
function _theme_header_items__secondary_navigation_toggle() {
  $elements = array();

  $elements['site_navigation'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('More'),
    '#title_tag' => 'a',
    '#title_attributes' => array(
      'href' => '#site-navigation',
      'class' => array('link'),
    ),
    '#attributes' => array(
      'class' => array(
        'site-navigation-toggle-wrapper',
      ),
    ),
  );

  // Render the HTML.
  return $elements;
}

/**
 * xxx
 *
 * @return array
 */
function _theme_header_items__identity() {
  // Always reference the EITI theme, and not the current active theme.
  $theme = 'eiti';
  $theme_path = drupal_get_path('theme', $theme);

  // Get the logo paths if it has been changed.
  $logo_path = theme_get_setting('logo_path', $theme);

  // Text for homepage header logo link.
  $site_link_title = t(variable_get('site_link_title', 'Visit the main page'));
  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

  $elements = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#contextual_info' => array('admin/settings/generic', array('edit')),
    '#attributes' => array(
      'class' => array(
        'site-identity-wrapper',
      ),
    ),
  );

  $elements['logo_markup'] = array(
    '#type' => 'html_container',
    '#tag' => 'a',
    '#attributes' => array(
      'href' => url('<front>'),
      'title' => $site_link_title,
      'rel' => 'home',
      'class' => array(
        'link',
      ),
    ),
    '#prefix' => '<h1 class="site-name">',
    '#suffix' => '</h1>',
  );


  $file_path = drupal_realpath($logo_path);
  if (file_exists($file_path)) {
    $elements['logo_markup']['png'] = array(
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
    $elements['logo_markup']['svg'] = array(
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
    $elements['logo_markup']['png'] = array(
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

  return $elements;
}

function _theme_header_items__navigation() {
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'header-items',
        'clearfix',
      ),
    ),
  );

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

  return $elements;
}

function _theme_header_items__search() {
  $elements['search'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'header-site-search',
      ),
    ),
  );

  $elements['search']['open'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => '',
    '#title_tag' => 'a',
    '#title_attributes' => array(
      'href' => '#',
      'class' => array('link'),
    ),
    '#title_icon' => array(
      'symbol' => 'search',
      'options' => array('width' => '1.125em', 'height' => '1.125em'),
    ),
    '#attributes' => array(
      'class' => array(
        'search-open',
      ),
    ),
  );

  $elements['search']['form'] = array(
    '#type' => 'html_container',
    '#tag' => 'form',
    '#attributes' => array(
      'action' => url('search'),
      'method' => 'get',
      'accept-charset' => 'UTF-8',
      'class' => array(
        'form',
        'element-hidden',
        'header-search-form',
      ),
    ),
  );

  $elements['search']['form']['textfield'] = array(
    '#type' => 'textfield',
    '#title' => t('Search Content'),
    '#title_tag' => 'h3',
    '#title_display' => 'invisible',
    '#name' => 'query',
    '#required' => TRUE,
    '#size' => 20,
    '#attributes' => array(
      'placeholder' => t('Enter search terms'),
    ),
  );

  $elements['search']['form']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#name' => '',
  );

  $elements['search']['form']['close'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('Close'),
    '#title_tag' => 'a',
    '#title_attributes' => array(
      'href' => '#',
      'class' => array('link'),
    ),
    '#attributes' => array(
      'class' => array(
        'search-close',
      ),
    ),
  );

  return $elements;
}

function _theme_header_items__language_switcher() {
  global $language;
  $elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'header-language',
      ),
    ),
  );

  // Add the language switcher links.
  if (drupal_multilingual()) {
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
    $lang_links = language_negotiation_get_switch_links('language', $path);

    if (isset($lang_links->links)) {
      $language_mappings = array(
        'en' => 'ENG',
        'fr' => 'FRA',
        'ru' => 'RUS',
        'es' => 'SPA',
      );
      if (isset($language_mappings[$language->language])) {
        $active_language = $language_mappings[$language->language];
      }
      else {
        $active_language = check_plain($language->native);
      }
      $title_attributes = array(
        'class' => array('language-switcher-title'),
        'xml:lang' => $language->language,
      );

      $elements['language_switcher'] = array(
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

  return $elements;
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
    '#path' => file_create_url($theme_path . '/images/logo-with-slogan.svg'),
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
  $variables['legal_navigation'] = array(
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
    $variables['legal_navigation']['links'] = array(
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
    $variables['legal_navigation']['empty'] = array(
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

  $variables['site_navigation'] = _theme_main_footer__site_navigation();
}

/**
 * Returns HTML for main navigation menu.
 */
function _theme_main_footer__site_navigation() {
  $menu_name = 'menu-site-navigation';

  $elements['close'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#title' => t('Close'),
    '#title_tag' => 'a',
    '#title_attributes' => array(
      'href' => '#',
      'class' => array('link'),
    ),
    '#attributes' => array(
      'class' => array(
        'nav-close',
      ),
    ),
  );

  $elements['search'] = array(
    '#type' => 'html_container',
    '#tag' => 'form',
    '#attributes' => array(
      'action' => url('search'),
      'method' => 'get',
      'accept-charset' => 'UTF-8',
      'class' => array(
        'footer-site-search',
      ),
    ),
  );

  $elements['search']['textfield'] = array(
    '#type' => 'textfield',
    '#title' => t('Search Content'),
    '#title_tag' => 'h3',
    '#title_display' => 'invisible',
    '#name' => 'query',
    '#required' => TRUE,
    '#size' => 20,
    '#attributes' => array(
      'placeholder' => t('Enter search terms'),
    ),
  );

  $elements['site_navigation'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Site Navigation'),
    '#title_tag' => 'h3',
    '#title_attributes' => array(
      'class' => array('section-title', 'element-invisible'),
    ),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      'role' => 'navigation',
      'class' => array(
        'site-navigation-wrapper',
      ),
    ),
  );

  // Get the main menu links for small displays.
  if ($links = helpertheme_menu_navigation_links('main-menu', 1)) {
    $links['#extras']['svgicon_size'] = '1.25em';
    $elements['site_navigation']['main_links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'navigation-links',
          'small-display',
        ),
      ),
    );
  }

  if ($links = helpertheme_menu_navigation_links($menu_name, 2)) {
    $links['#extras']['svgicon_size'] = '1.25em';
    $links['#extras']['menu_name'] = $menu_name;
    $elements['site_navigation']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'navigation-links',
        ),
      ),
    );

    $elements['site_navigation']['see_all'] = array(
      '#theme' => 'link',
      '#path' => 'site-map',
      '#text' => t('see all'),
      '#options' => array(
        'attributes' => array(
          'class' => array(
            'see-all-link-wrapper'
          ),
        ),
        'html' => FALSE,
      ),
    );
  }
  else {
    $elements['site_navigation']['empty'] = array(
      '#markup' => t('!menu_name not configured!', array('!menu_name' => t('Site Navigation'))),
    );
  }

  $menu_name = 'menu-footer-social';
  $elements['social'] = array(
    '#type' => 'html_container',
    '#tag' => 'nav',
    '#title' => t('Stay connected'),
    '#title_tag' => 'h3',
    '#title_attributes' => array(
      'class' => array('section-title', 'element-invisible'),
    ),
    '#contextual_info' => array('admin/structure/menu/manage', array($menu_name)),
    '#attributes' => array(
      //'role' => 'navigation',
      'class' => array(
        'footer-social',
      ),
    ),
    '#prefix' => '<div class="footer-social-wrapper">',
    '#suffix' => '</div>',
  );

  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $elements['social']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'social-link',
      '#attributes' => array(
        'class' => array(
          'footer-social-links',
        ),
      ),
    );
  }
  else {
    $elements['social']['empty'] = array(
      '#markup' => t('Menu not configured!'),
    );
  }

  return $elements;
}
