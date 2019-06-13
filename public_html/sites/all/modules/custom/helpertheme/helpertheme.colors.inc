<?php
/**
 * @file
 * Define helper functions.
 */

/**
 * Returns an array of colors for a navigation menu.
 *
 * Variables are lazy-loaded so we can reference them when creating variants.
 * @TODO: cleanup variables.
 */
function helpertheme_color_palette() {
  $colors = array();

  // Primary colors.
  $colors['primary'] = array(
    '#title' => 'Primary colors',
    '#weight' => 10,
  );

  $colors['primary']['clmain'] = array(
    '#value' => '#ffffff',
    '#desc' => 'page content background color',
    '#variants' => array(
      'clmain__header' => array(
        '#value' => '#FFFFFF',
        '#desc' => 'alternative content background color',
      ),
      'clmain__separator' => array(
        '#value' => '#DDDDDD',
        '#desc' => 'border header and content',
      ),
    ),
  );

  $colors['primary']['clnormal'] = array(
    '#value' => '#132856',
    '#desc' => 'default text color',
    '#variants' => array(
      'clnormal__dark' => array(
        '#value' => 'darken(@clnormal, 30%)',
        '#desc' => 'important text',
      ),
      'clnormal__alt' => array(
        '#value' => '#2b8636',
        '#desc' => 'alternative color for footer text',
      ),
      'clnormal__black' => array(
        '#value' => '#000000',
        '#desc' => 'alternative color for text',
      ),
    ),
  );

  $colors['primary']['cldetail'] = array(
    '#value' => '#165b89',
    '#desc' => 'links, highlighted items, page border',
    '#variants' => array(
      'cldetail__highlight' => array(
        '#value' => '#f6a70a',
        '#desc' => 'alternative highlight detail',
      ),
      'cldetail__alt' => array(
        '#value' => '#188fbb',
        '#desc' => 'alternative detail',
      ),
      'cldetail__separator' => array(
        '#value' => 'lighten(@cldetail, 35%)',
        '#desc' => 'menu border?!?',
      ),
    ),
  );


  // Secondary colors.
  $colors['secondary'] = array(
    '#title' => 'Secondary colors',
    '#weight' => 20,
  );

  $colors['secondary']['claltmain'] = array(
    '#value' => '#132856',
    '#desc' => 'alternative content background',
    '#variants' => array(
    ),
  );

  $colors['secondary']['claltnormal'] = array(
    '#value' => '#1bc2ee',
    '#desc' => 'alternative text color',
    '#variants' => array(
      'claltnormal__light' => array(
        '#value' => '#ffffff',
        '#desc' => 'alternative important text text',
      ),
      'claltnormal__alt' => array(
        '#value' => 'lighten(@claltnormal, 18%)',
        '#desc' => 'alternative color for footer text',
      ),
    ),
  );

  $colors['secondary']['clactive'] = array(
    '#value' => '#d24228',
    '#desc' => 'highlighted items',
    '#variants' => array(
      'clactive__alt' => array(
        '#value' => '#f6a70a',
        '#desc' => 'alternative color for highlighted items',
      ),
    ),
  );

  $colors['secondary']['claltdetail'] = array(
    '#value' => '#7F7F7F',
    '#desc' => 'forms input text',
    '#variants' => array(
    ),
  );

  $colors['secondary']['claltdetail__light'] = array(
    '#value' => '#BBBBBB',
    '#desc' => 'forms input text',
    '#variants' => array(
    ),
  );

  // HTML tag specific colors.
  $colors['htmltag'] = array(
    '#title' => 'HTML tag specific colors',
    '#weight' => 40,
  );

  $colors['htmltag']['clanchor'] = array(
    '#value' => '#188fbb',
    '#desc' => 'color for anchor tags',
    '#variants' => array(
      'clanchor__hover' => array(
        '#value' => '@clactive__alt',
        '#desc' => 'focused anchor tags',
      ),
      'clanchor__visited' => array(
        '#value' => 'darken(@clanchor, 15%)',
        '#desc' => 'visited anchor tags',
      ),
      'clanchor__active' => array(
        '#value' => 'darken(@clanchor, 25%)',
        '#desc' => 'active anchor tags',
      ),
    ),
  );


  // Notification colors.
  $colors['notification'] = array(
    '#title' => 'Notification message colors',
    '#weight' => 50,
  );

  $colors['notification']['clstatus'] = array(
    '#value' => '#6bc93f',
    '#desc' => 'success message base color',
    '#variants' => array(
      'clstatus__faded' => array(
        '#value' => 'lighten(@clstatus__alt, 18%)',
        '#desc' => 'box border',
      ),
      'clstatus__light' => array(
        '#value' => 'lighten(@clstatus, 40%)',
        '#desc' => 'box background',
      ),
      'clstatus__dark' => array(
        '#value' => 'darken(@clstatus, 40%)',
        '#desc' => 'text',
      ),
      'clstatus__alt' => array(
        '#value' => 'desaturate(@clstatus, 18)', // #73b355
        '#desc' => 'icons and box shadow',
      ),
    ),
  );

  $colors['notification']['clwarning'] = array(
    '#value' => '#d8a80e',
    '#desc' => 'warning message base color',
    '#variants' => array(
      'clwarning__faded' => array(
        '#value' => 'lighten(@clwarning__alt, 36%)',
        '#desc' => 'box border',
      ),
      'clwarning__light' => array(
        '#value' => 'lighten(@clwarning, 52%)',
        '#desc' => 'box background',
      ),
      'clwarning__dark' => array(
        '#value' => 'darken(@clwarning, 24%)',
        '#desc' => 'text color',
      ),
      'clwarning__alt' => array(
        '#value' => 'saturate(@clwarning, 18)', // #e29700
        '#desc' => 'icons and box shadow',
      ),
    ),
  );

  $colors['notification']['clerror'] = array(
    '#value' => '#d53615',
    '#desc' => 'error message base color',
    '#variants' => array(
      'clerror__faded' => array(
        '#value' => 'lighten(@clerror__alt, 36%)',
        '#desc' => 'box border',
      ),
      'clerror__light' => array(
        '#value' => 'lighten(@clerror, 50%)',
        '#desc' => 'box background',
      ),
      'clerror__dark' => array(
        '#value' => 'darken(@clerror, 24%)',
        '#desc' => 'text color',
      ),
      'clerror__alt' => array(
        '#value' => 'saturate(@clerror, 18)', // #ea2800
        '#desc' => 'icons and box shadow',
      ),
    ),
  );

  return $colors;
}
