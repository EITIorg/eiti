<?php

/**
 * @file
 * Board decision information.
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

  if (empty($entity) || !isset($entity->type) || $entity->type != 'board_decision') {
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
        'single-fluid-row-wrapper',
      ),
    ),
  );
  $block['top_info']['upper'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'upper',
      ),
    ),
  );
  $block['top_info']['upper']['left'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'left',
      ),
    ),
  );
  $block['top_info']['upper']['left']['created'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#value' => date('d.m.Y', $entity->created),
    '#attributes' => array('class' => array('created')),
  );
  $block['top_info']['upper']['left']['decision'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#value' => t('Decision') . ' ' . $entity_wrapper->field_bd_number->value() . '/' . $entity_wrapper->field_board_meeting_circular->value(),
    '#attributes' => array('class' => array('decision')),
  );

  // Previous and next links.
  $block['top_info']['upper']['right'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'right',
      ),
    ),
  );
  $prev_bd_nid = db_select('node', 'n')
    ->condition('n.status', 1)
    ->condition('n.type', 'board_decision')
    ->condition('n.created', $entity->created, '<')
    ->fields('n', array('nid'))
    ->orderBy('n.created', 'DESC')
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if ($prev_bd_nid) {
    $block['top_info']['upper']['right']['prev'] = array(
      '#type' => 'html_container',
      '#tag' => 'span',
      '#title' => '<',
      '#title_tag' => 'a',
      '#title_attributes' => array(
        'href' => url('node/' . $prev_bd_nid),
        'class' => array('link'),
      ),
      '#attributes' => array(
        'class' => array(
          'prev',
        ),
      ),
    );
  }
  $next_bd_nid = db_select('node', 'n')
    ->condition('n.status', 1)
    ->condition('n.type', 'board_decision')
    ->condition('n.created', $entity->created, '>')
    ->fields('n', array('nid'))
    ->orderBy('n.created', 'ASC')
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if ($next_bd_nid) {
    $block['top_info']['upper']['right']['next'] = array(
      '#type' => 'html_container',
      '#tag' => 'span',
      '#title' => '>',
      '#title_tag' => 'a',
      '#title_attributes' => array(
        'href' => url('node/' . $next_bd_nid),
        'class' => array('link'),
      ),
      '#attributes' => array(
        'class' => array(
          'next',
        ),
      ),
    );
  }

  // Basis.
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
      $block['top_info']['lower'] = array(
        '#type' => 'html_container',
        '#tag' => 'div',
        '#attributes' => array(
          'class' => array(
            'lower',
          ),
        ),
      );
      $block['top_info']['lower']['basis'] = array(
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#value' => t('Based on') . ' ' . $link,
        '#attributes' => array('class' => array('basis')),
      );
    }
  }

  // The Board's decision.
  $body = $entity_wrapper->language($language->language)->body->value();
  if ($body['safe_value']) {
    $block['body'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Board decision in full'),
      '#title_tag' => 'h2',
      '#title_attributes' => array('class' => array('title')),
      '#attributes' => array(
        'class' => array(
          'board-decision',
          'single-fluid-row-wrapper',
        ),
      ),
    );
    $block['body']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => $body['safe_value'],
      '#attributes' => array('class' => array('value')),
    );
  }

  // Bottom info.
  $block['bottom_info'] = array(
    '#type' => 'html_container',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array(
        'bottom-info',
        'single-fluid-row-wrapper',
      ),
    ),
  );

  // Keywords.
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

  // Country.
  $country = $entity_wrapper->field_country->value();
  if ($country) {
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
      '#value' => l($country->name, 'implementing_country/' . $country->id),
      '#attributes' => array('class' => array('value')),
    );
  }

  // Validation PDF.
  $validation = $entity_wrapper->field_validation->value();
  if ($validation) {
    $pdf_url = url(
      'scorecard-pdf',
      array(
        'query' => array(
          'filter[country]' => $validation->country_id,
          'filter[year]' => $validation->year,
        )
      )
    );
    $block['validation'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Save decision as PDF'),
      '#title_tag' => 'a',
      '#title_attributes' => array(
        'href' => $pdf_url,
        'target' => '_blank',
        'class' => array('link'),
      ),
      '#attributes' => array(
        'class' => array(
          'validation',
          'single-fluid-row-wrapper',
        ),
      ),
    );
  }

  // General data for links.
  $icon = helpertheme_get_svg_icon('arrow', array('height' => '1em', 'width' => '1em'));
  $link_options = array('html' => TRUE, 'attributes' => array('class' => array('link-title-with-icon')));

  // Related public content.
  $public_content = $entity_wrapper->field_public_content->value();
  if ($public_content) {
    $block['public_content'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Related public content'),
      '#title_tag' => 'div',
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'public-content',
          'link-items',
          'single-fluid-row-wrapper',
        ),
      ),
    );
    $links = '';
    foreach ($public_content as $node) {
      $links .= '<div class="field-item">';
      $links .= l($icon . $node->title, 'node/' . $node->nid, $link_options);
      $links .= '</div>';
    }
    $block['public_content']['links'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => $links,
      '#attributes' => array('class' => array('field-items')),
    );
  }

  // Related decisions.
  $related_decisions = $entity_wrapper->field_board_decisions->value();
  if ($related_decisions) {
    $block['related_decisions'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Related decisions'),
      '#title_tag' => 'div',
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'related-decisions',
          'link-items',
          'single-fluid-row-wrapper',
        ),
      ),
    );
    $links = '';
    foreach ($related_decisions as $node) {
      $links .= '<div class="field-item">';
      $links .= l($icon . $node->title, 'node/' . $node->nid, $link_options);
      $links .= '</div>';
    }
    $block['related_decisions']['links'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => $links,
      '#attributes' => array('class' => array('field-items')),
    );
  }

  // Related internal content.
  $internal_content = $entity_wrapper->field_internal_content->value();
  if ($internal_content) {
    $block['internal_content'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Related internal content'),
      '#title_tag' => 'div',
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'internal-content',
          'link-items',
          'single-fluid-row-wrapper',
        ),
      ),
    );
    $links = '';
    foreach ($internal_content as $node) {
      $links .= '<div class="field-item">';
      $links .= l($icon . $node->title, 'node/' . $node->nid, $link_options);
      $links .= '</div>';
    }
    $block['internal_content']['links'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => $links,
      '#attributes' => array('class' => array('field-items')),
    );
  }

  return (object) array(
    'content' => $block,
  );
}
