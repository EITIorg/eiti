<?php

/**
 * @file
 * Validation board's decision.
 */

$plugin = array(
  'title' => t('Validation decision'),
  'description' => t("Validation board's decision."),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__validation_decision__render',
);

/**
 * Output function for validation decision.
 */
function eiti_ctools_extra__validation_decision__render($subtype, $conf, $panel_args, $context) {
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

  // The Board's decision from related validation.
  $validation = $entity_wrapper->field_validation->value();
  if ($validation) {
    $validation_emw = entity_metadata_wrapper('score_data', $validation);
    $text = $validation_emw->language($language->language)->field_scd_pdf_text1->value();
    if ($text['safe_value']) {
      $block['decision'] = array(
        '#type' => 'html_container',
        '#tag' => 'div',
        '#attributes' => array(
          'class' => array(
            'validation-decision',
            'single-fluid-row-wrapper',
          ),
        ),
      );
      $block['decision']['title'] = array(
        '#theme' => 'html_tag',
        '#tag' => 'h2',
        '#value' => t("The Board's decision"),
        '#attributes' => array('class' => array('title'), 'id' => drupal_html_id("The Board's decision")),
        '#prefix' => '<div class="pane-title-wrapper">',
        '#suffix' => '</div>',
      );
      $block['decision']['value'] = array(
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
