<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function eitict_document_form_document_node_form_alter(&$form, &$form_state) {
  $weight = $form['field_doc_type_public']['#weight'];
  $weight -= 0.5;
  $node = $form_state['node'];
  if (!empty($node->nid)) {
    $node_emw = entity_metadata_wrapper('node', $node);
    $internal_value = $node_emw->field_doc_type_internal->value();
  }

  $form['doc_type'] = array(
    '#type' => 'radios',
    '#title' => t('Publication Type'),
    '#options' => array(
      'public' => t('Public'),
      'private' => t('Private / Internal')
    ),
    '#weight' => $weight,
    '#default_value' => empty($internal_value) ? 'public' : 'private',
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
  $form['actions']['submit']['#submit'][] = 'eitict_document_form_document_node_form_set_access_submit';
}

/**
 * Custom submit function that sets the content-access the newly created node.
 */
function eitict_document_form_document_node_form_set_access_submit($form, $form_state) {
  $node = $form_state['node'];
  $node_emw = entity_metadata_wrapper('node', $node);

  $doc_type = $form_state['values']['doc_type'];
  $settings = content_access_get_per_node_settings($node);
  if ($doc_type == 'private') {
    // Set the proper permissions.
    if (!empty($settings)) {
      if (!in_array(DRUPAL_AUTHENTICATED_RID, $settings['view'])) {
        $settings['view'][] = DRUPAL_AUTHENTICATED_RID;
      }
      $id = array_search(DRUPAL_ANONYMOUS_RID, $settings['view']);
      if ($id !== FALSE) {
        unset($settings['view'][$id]);
      }
    }
    else {
      $settings['view'][] = DRUPAL_AUTHENTICATED_RID;
    }
    content_access_save_per_node_settings($node, $settings);

    // Also clean-up the tags behind us.
    $node_emw->field_doc_type_public->set(NULL);
    $node_emw->save();
  }
  else {
    // Set the proper permissions.
    if (empty($settings) || !in_array(DRUPAL_ANONYMOUS_RID, $settings['view'])) {
      $settings['view'][] = DRUPAL_ANONYMOUS_RID;
    }
    content_access_save_per_node_settings($node, $settings);

    // Also clean-up the tags behind us.
    $node_emw->field_doc_type_internal->set(NULL);
    $node_emw->save();
  }
}

/**
 * Implements hook_form_views_exposed_form_alter().
 */
function eitict_document_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $view = $form_state['view'];
  if ($view->name == 'documents_search') {
    $search_label = $form['#info']['filter-search_api_views_fulltext']['label'];
    unset($form['#info']['filter-search_api_views_fulltext']['label']);
    $form['search_api_views_fulltext']['#attributes']['placeholder'][] = $search_label;

    $form['field_doc_published_date']['#type'] = 'date_select';
    $form['field_doc_published_date']['#date_format'] = 'F Y';

    $form['field_doc_published_date_1']['#type'] = 'date_select';
    $form['field_doc_published_date_1']['#date_format'] = 'F Y';
  }
}

/**
 * Implements hook_date_select_process_alter().
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
function eitict_document_date_select_process_alter(&$element, &$form_state, $context) {
  if (isset($form_state['view']) && $form_state['view']->name == 'documents_search') {
    $element['month']['#options'][''] = t('- Month -');
    $element['year']['#options'][''] = t('----');
  }
}
