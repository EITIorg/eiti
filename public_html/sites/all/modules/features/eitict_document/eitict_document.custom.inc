<?php

function eitict_document_form_document_node_form_alter(&$form, &$form_state) {
  $weight = $form['field_doc_type_public']['#weight'];
  $weight -= 0.5;
  $form['doc_type'] = array(
    '#type' => 'radios',
    '#title' => t('Publication Type'),
    '#options' => array(
      'public' => t('Public'),
      'private' => t('Private / Internal')
    ),
    '#weight' => $weight,
    '#default_value' => 'public',
    '#description' => t('Please specify whether this is a Public or Internal Publication'),
  );
  $form['field_doc_type_internal']['#states'] = array(
    'visible' => array(
      array(
        'input[name="doc_type"]' => array('value' => 'private'),
      )
    )
  );
  $form['field_doc_type_public']['#states'] = array(
    'visible' => array(
      array(
        'input[name="doc_type"]' => array('value' => 'public'),
      )
    )
  );
}

/**
 * Implements hook_form_views_exposed_form_alter().
 */
function eitict_document_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $view = $form_state['view'];
  if ($view->name == 'publications_search') {
    $search_label = $form['#info']['filter-search_api_views_fulltext']['label'];
    unset($form['#info']['filter-search_api_views_fulltext']['label']);
    $form['search_api_views_fulltext']['#attributes']['placeholder'][] = $search_label;
  }
}

/**
 * Implements hook_date_popup_process_alter().
 *
 * @param $element
 *  Date form element.
 *
 * @param $form_state
 *  Form state.
 *
 * @param $context
 *  Element's context.
 */
function eitict_document_date_popup_process_alter(&$element, &$form_state, $context) {
  if (isset($form_state['view']) && $form_state['view']->name == 'publications_search') {
    $description = $element['date']['#description'];
    unset($element['date']['#description']);
    unset($element['date']['#title']);
    $element['date']['#attributes']['placeholder'][] = $description;
  }
}
