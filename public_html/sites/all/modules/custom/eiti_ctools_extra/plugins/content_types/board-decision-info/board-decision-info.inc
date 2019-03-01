<?php

/**
 * @file
 * Board decision main information.
 */

$plugin = array(
  'title' => t('Board decision info'),
  'description' => t('Board decision main information.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__board_decision_info__render',
);

/**
 * Output function for board decision info.
 */
function eiti_ctools_extra__board_decision_info__render($subtype, $conf, $panel_args, $context) {
  if (arg(0) == 'node') {
    $entity = menu_get_object();
  }

  if (empty($entity)) {
    return NULL;
  }

  global $language;
  $entity_type = 'node';
  $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);

  // Top info.
  $block['top_info'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'top-info',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );
  $block['top_info']['created'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#value' => date('d.m.Y', $entity->created),
    '#attributes' => array('class' => array('created')),
  );
  $block['top_info']['decision'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#value' => t('Decision') . ' ' . $entity_wrapper->field_bd_number->value() . '/' . $entity_wrapper->field_board_meeting_circular->value(),
    '#attributes' => array('class' => array('decision')),
  );

  $basis = $entity_wrapper->field_bd_basis->value();
  if ($basis) {
    $basis_emw = entity_metadata_wrapper('taxonomy_term', $basis);
    $link_field = $basis_emw->language($language->language)->field_link->value();
    if (isset($link_field['url'], $link_field['title'])) {
      $options = array();
      if (isset($link_field['attributes']['target']) && $link_field['attributes']['target']) {
        $options['attributes']['target'] = $link_field['attributes']['target'];
      }
      $link = l($link_field['title'], $link_field['url'], $options);
      $block['top_info']['basis'] = array(
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#value' => t('Based on') . ' ' . $link,
        '#attributes' => array('class' => array('basis')),
      );
    }
  }

  // Bottom info.
  $block['bottom_info'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'bottom-info',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );

  $keywords = $entity_wrapper->field_bd_keywords->value();
  if ($keywords) {
    $keyword_list = array();
    foreach ($keywords as $keyword) {
      $keyword_emw = entity_metadata_wrapper('taxonomy_term', $keyword);
      $keyword_list[] = $keyword_emw->name->value();
    }
    if (!empty($keyword_list)) {
      $block['bottom_info']['keywords'] = array(
        '#type' => 'html_container',
        '#tag' => 'div',
        '#title' => t('Keywords:'),
        '#title_tag' => 'span',
        '#title_attributes' => array('class' => array('label')),
        '#attributes' => array(
          'class' => array(
            'keywords',
          ),
        ),
      );
      $block['bottom_info']['keywords']['value'] = array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#value' => implode(', ', $keyword_list),
        '#attributes' => array('class' => array('value')),
      );
    }
  }

  $country = $entity_wrapper->field_country->value();
  if ($country) {
    // Looks like the ID value is not available.
    $c_id = db_select('eiti_implementing_country', 'ic')
      ->fields('ic', array('id'))
      ->condition('iso', $country->iso2)
      ->execute()
      ->fetchField();
    $country = entity_object_load($c_id, 'implementing_country');
    $country_emw = entity_metadata_wrapper('implementing_country', $country);
    $block['bottom_info']['country'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Country:'),
      '#title_tag' => 'span',
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'country',
        ),
      ),
    );
    $block['bottom_info']['country']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => l($country_emw->name->value(), 'implementing_country/' . $country_emw->id->value()),
      '#attributes' => array('class' => array('value')),
    );
  }

  return (object) array(
    'content' => $block,
  );
}
