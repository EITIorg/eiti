<?php
/**
 * @file
 * Provide information for favicons, mstile and apple-touch-icons.
 *
 * A new set of "favicons" can be genarated using a rendered version of the
 * favicon.svg file from the favicons theme folder
 *
 * @see http://css-tricks.com/favicon-quiz
 * @see http://realfavicongenerator.net
 */

/**
 * Returns an array of favicon related tags.
 * @see helpertheme_html_head_alter().
 */
function _helpertheme_favicons($theme_path) {
  // Apple.
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '57x57',
      'href' => url($theme_path . '/favicons/apple-touch-icon-57x57.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '60x60',
      'href' => url($theme_path . '/favicons/apple-touch-icon-60x60.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '72x72',
      'href' => url($theme_path . '/favicons/apple-touch-icon-72x72.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '76x76',
      'href' => url($theme_path . '/favicons/apple-touch-icon-76x76.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '114x114',
      'href' => url($theme_path . '/favicons/apple-touch-icon-114x114.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '120x120',
      'href' => url($theme_path . '/favicons/apple-touch-icon-120x120.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '144x144',
      'href' => url($theme_path . '/favicons/apple-touch-icon-144x144.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '152x152',
      'href' => url($theme_path . '/favicons/apple-touch-icon-152x152.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'sizes' => '180x180',
      'href' => url($theme_path . '/favicons/apple-touch-icon-180x180.png'),
    ),
  );

  // Android.
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => url($theme_path . '/favicons/favicon-32x32.png'),
      'sizes' => '32x32',
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => url($theme_path . '/favicons/favicon-194x194.png'),
      'sizes' => '194x194',
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => url($theme_path . '/favicons/favicon-96x96.png'),
      'sizes' => '96x96',
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => url($theme_path . '/favicons/favicon-194x194.png'),
      'sizes' => '194x194',
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => url($theme_path . '/favicons/favicon-16x16.png'),
      'sizes' => '16x16',
    ),
  );

  // Other.
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'manifest',
      'href' => url($theme_path . '/favicons/manifest.json'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'mask-icon',
      'color' => '#5bbad5',
      'href' => url($theme_path . '/favicons/safari-pinned-tab.svg'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'shortcut icon',
      'href' => url($theme_path . '/favicons/favicon.ico'),
    ),
  );

  // Microsoft.
  $favicon_tags[] = array(
    '#tag' => 'meta',
    '#type' => 'html_tag',
    '#attributes' => array(
      'name' => 'msapplication-TileColor',
      'content' => '#da532c',
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'meta',
    '#type' => 'html_tag',
    '#attributes' => array(
      'name' => 'msapplication-TileImage',
      'content' => url($theme_path . '/favicons/mstile-144x144.png'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'meta',
    '#type' => 'html_tag',
    '#attributes' => array(
      'name' => 'msapplication-config',
      'content' => url($theme_path . '/favicons/browserconfig.xml'),
    ),
  );
  $favicon_tags[] = array(
    '#tag' => 'meta',
    '#type' => 'html_tag',
    '#attributes' => array(
      'name' => 'theme-color',
      'content' => '#ffffff',
    ),
  );

  return $favicon_tags;
}
