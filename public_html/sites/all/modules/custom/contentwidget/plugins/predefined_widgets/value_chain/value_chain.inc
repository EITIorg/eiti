<?php

/**
 * @file
 * Provides a custom Value Chain widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => 'Value Chain',
  'description' => 'Use this widget to create the value chain.',
  'render callback' => 'contentwidget_value_chain_render',
  'settings form' => 'contentwidget_value_chain_settings',
  'defaults' => array(
    'chains_count' => 4,
  ),
);

/**
 * Render callback for the 'Value Chain' predefined widget.
 */
function contentwidget_value_chain_render($plugin, $widget_settings, $entity, $langcode) {
  $chains_count = $widget_settings['chains_count'];

  // Iterate through the link icons (formatting already inspired from the prototype).
  $chains_list = array();
  $delta = NULL;
  for ($delta = 0; $delta < $chains_count; $delta++) {
    $value_chain = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'value-chain-wrapper',
          'value-chain-wrapper--' . $delta,
          'clearfix',
        ),
      ),
    );

    $link_markup = array();

    $options = array(
      'height' => '4em',
      'width' => '4em',
    );
    $link_markup['icon'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#attributes' => array(
        'class' => array('chain-icon'),
      ),
      '#value' => helpertheme_get_svg_icon($widget_settings['chains'][$delta]['icon'], $options),
    );

    $link_markup['title'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#attributes' => array(
        'class' => array('title')
      ),
      '#value' => check_plain($widget_settings['chains'][$delta]['title']),
    );

    $url = $widget_settings['chains'][$delta]['url'];
    $value_chain['link'] = array(
      '#theme' => 'link',
      '#text' => render($link_markup),
      '#path' => $url,
      '#options' => array(
        'attributes' => array(
          'class' => array(
            'chain-info',
          ),
        ),
        'html' => TRUE,
      ),
    );

    $add_arrow = TRUE;
    if ($delta == 0) {
      // Do not add arrow after the first item.
      $add_arrow = FALSE;
    }
    else if ($delta == $chains_count - 1) {
      // Do not add arrow after the last item.
      $add_arrow = FALSE;
    }
    else if ($delta == $chains_count - 2) {
      // Do not add arrow before the last item.
      $add_arrow = FALSE;
    }

    if ($add_arrow) {
      $options = array(
        'height' => '6em',
        'width' => '1em',
      );
      $value_chain['arrow'] = array(
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => array(
          'class' => array('arrow'),
        ),
        '#value' => helpertheme_get_svg_icon('narrow-arrow', $options),
        '#weight' => -1,
      );
    }

    $chains_list[$delta] = render($value_chain);
  }

  $block['value_chain'] = array(
    '#theme' => 'item_list',
    '#items' => $chains_list,
    '#title' => '',
    '#type' => 'ul',
    '#attributes' => array(
      'class' => array(
        'value-chain-list',
        'value-chain-list--count-' . $chains_count,
      ),
    ),
  );

  return $block;
}

/**
 * Settings form for the 'Value Chain' predefined widget.
 */
function contentwidget_value_chain_settings(&$element, &$form_state, $plugin, $widget_settings) {
  $settings_form = array();
  $blocks_count = isset($widget_settings['chains_count']) ? $widget_settings['chains_count'] : '';

  $available_sizes = array();
  $sizes = drupal_map_assoc(range(4, 9));
  foreach ($sizes as $size) {
    $available_sizes[$size] = format_plural($size, '1 Block', '@count Blocks');
  }

  $wrapper_id = 'chain-blocks-form-elements-wrapper';
  $settings_form['chains_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of Chain Blocks'),
    '#options' => $available_sizes,
    '#default_value' => $blocks_count,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'contentwidget_value_chain_settings_ajax',
      'wrapper' => $wrapper_id,
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  $settings_form['chains'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $wrapper_id,
    ),
  );


  $triggering_element = empty($form_state['triggering_element']) ? array() : $form_state['triggering_element'];
  $triggering_element_name = empty($triggering_element['#parents']) ? NULL : array_pop($triggering_element['#parents']);
  if ($triggering_element_name == 'chains_count') {
    $blocks_count = $triggering_element['#value'];
  }
  else {
    $blocks_count = $widget_settings['chains_count'];
  }

  // Create the forms for the icon links.
  for ($delta = 0; $delta < $blocks_count; $delta++) {
    $block_settings = empty($widget_settings['chains'][$delta]) ? array() : $widget_settings['chains'][$delta];
    $settings_form['chains'][$delta] = _contentwidget_get_chain_elements($form_state, $block_settings, $delta);
  }

  $settings_form['#attached']['css'] = array(
    drupal_get_path('module', 'helpergeneric') . '/helpergeneric.admin.css',
  );

  return $settings_form;
}

/**
 * Helper function creating the form elements for a value chain.
 *
 * @see: contentwidget_value_chain_settings()
 */
function _contentwidget_get_chain_elements(&$form_state, $block_settings, $delta) {
  // Fetch the re-usable icon options.
  $icons = helpertheme_get_svg_icons();
  $icon_options = array('' => t('No Icon'));
  $icon_options += drupal_map_assoc(array_keys($icons));

  $elements = array(
    '#type' => 'fieldset',
    '#title' => t('Block #@number:', array('@number' => ($delta + 1))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $elements['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => isset($block_settings['title']) ? $block_settings['title'] : '',
  );

  $elements['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#required' => TRUE,
    '#default_value' => isset($block_settings['url']) ? $block_settings['url'] : '',
  );

  $elements['icon'] = array(
    '#type' => 'radioicons',
    '#title' => t('Icon'),
    '#options' => $icon_options,
    '#icons' => $icons,
    '#required' => TRUE,
    '#default_value' => isset($block_settings['icon']) ? $block_settings['icon'] : '',
  );


  return $elements;
}

/**
 * Ajax callback for the settings form.
 */
function contentwidget_value_chain_settings_ajax($form, $form_state) {
  $triggering_element = $form_state['triggering_element'];

  // Go one level up in the form, to the container.
  $element = drupal_array_get_nested_value($form, array_slice($triggering_element['#array_parents'], 0, -1));

  return $element['chains'];
}
