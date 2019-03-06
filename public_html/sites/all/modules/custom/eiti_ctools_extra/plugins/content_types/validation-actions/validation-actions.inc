<?php

/**
 * @file
 * Validation corrective actions.
 */

$plugin = array(
  'title' => t('Validation actions'),
  'description' => t("Validation corrective actions."),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__validation_actions__render',
);

/**
 * Output function for validation actions.
 */
function eiti_ctools_extra__validation_actions__render($subtype, $conf, $panel_args, $context) {
  if (arg(0) == 'node') {
    $entity = menu_get_object();
  }

  if (empty($entity) || !isset($entity->type) || $entity->type != 'board_decision') {
    return NULL;
  }

  global $language;
  $block = array();
  $entity_type = 'node';
  $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);

  // The corrective actions from related validation.
  $validation = $entity_wrapper->field_validation->value();
  if ($validation) {
    $validation_emw = entity_metadata_wrapper('score_data', $validation);
    $text = $validation_emw->language($language->language)->field_scd_pdf_text2->value();
    if ($text['safe_value']) {
      $block['actions'] = array(
        '#type' => 'html_container',
        '#tag' => 'div',
        '#attributes' => array(
          'class' => array(
            'validation-actions',
            'single-fluid-row-wrapper',
          ),
        ),
      );
      $block['actions']['title'] = array(
        '#theme' => 'html_tag',
        '#tag' => 'h2',
        '#value' => t('Corrective actions'),
        '#attributes' => array('class' => array('title'), 'id' => drupal_html_id('Corrective actions')),
        '#prefix' => '<div class="pane-title-wrapper">',
        '#suffix' => '</div>',
      );
      $block['actions']['value'] = array(
        '#theme' => 'html_tag',
        '#tag' => 'div',
        '#value' => $text['safe_value'],
        '#attributes' => array('class' => array('value')),
      );
    }
  }

  return (object) array(
    'content' => $block,
  );
}
