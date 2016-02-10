<?php
/**
 * @file
 * Exposes custom theme functions.
 */

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

  $args = array();
  if (!is_null($elements['symbol'])) {
    $args['fragment'] = $elements['symbol'];
  }
  $elements['#use']['xlink:href'] = url($elements['path'], $args);

  return '<svg' . drupal_attributes($elements['#attributes']) . '><use'. drupal_attributes($elements['#use']) . '/></svg>';
}

/**
 * Returns HTML for the header logo.
 */
function theme_header_logo() {
  global $theme;

  // Text for homepage header logo link.
  $site_link_title = t(variable_get('site_link_title', 'Visit the main page'));
  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

  $items['#prefix'] = '<div class="site-name-wrapper contextual-links-region">';
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
      ),
    );
  }
  else {
    $logo_alt = $site_name;
    $items['header']['logo_markup']['svg'] = array(
      '#theme' => 'image',
      '#path' => url(drupal_get_path('theme', $theme) . '/logo.svg'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
      ),
      '#prefix' => "<!--[if (gte IE 9)|!(IE)]><!-->",
      '#suffix' => "<!--<![endif]-->",
    );
    $items['header']['logo_markup']['png'] = array(
      '#theme' => 'image',
      '#path' => url(drupal_get_path('theme', $theme) . '/logo.png'),
      '#alt' => $logo_alt,
      '#attributes' => array(
        'role' => 'presentation',
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
  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    // Mark this element as potentially having contextual links attached to it.
    $menu_elements['nav']['#prefix'] = '<nav role="navigation" class="main-navigation">';
    $menu_elements['nav']['#suffix'] = '</nav>';

    $menu_elements['nav']['subject'] = array(
      '#type' => 'html_tag',
      '#tag' => 'h2',
      '#value' => 'Main Menu',
      '#attributes' => array('class' => array('element-invisible')),
    );

    // Initialize the template variable as a renderable array.
    // $menu_elements['nav']['contextual_links'] = array(
    //   '#type' => 'contextual_links',
    //   '#contextual_links' => array(
    //     'menu' => array('admin/structure/menu/manage', array('user-menu')),
    //   ),
    // );

    $menu_elements['nav']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'header-links',
          'links',
          'clearfix',
        )
      ),
    );
  }

  // Prepare the search-form.
  $menu_elements['search']['#prefix'] = '<div class="search-form">';
  $menu_elements['search']['#suffix'] = '</div>';
  $search_form = drupal_get_form('search_form');
  unset($search_form['basic']['keys']['#title']);
  $menu_elements['search']['form'] = $search_form;

  // Add the language switcher links.
  if (drupal_multilingual()) {
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
            'language-switcher-' . $lang_links->provider,
            'header-links',
            'clearfix',
          )
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
  $footer_elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'footer-items',
      ),
    ),
  );

  // Render the HTML.
  $output = drupal_render($footer_elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>\s+\</', '><', $output);
}
