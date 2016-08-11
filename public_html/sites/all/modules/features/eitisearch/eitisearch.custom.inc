<?php

/**
 * @file
 * Contains all the custom code related to the search functionality.
 */

/**
 * Implements hook_search_api_solr_documents_alter().
 *
 * Alter Solr documents before they are sent to Solr for indexing.
 *
 * @param array $documents
 *   An array of SearchApiSolrDocument objects ready to be indexed, generated
 *   from $items array.
 * @param SearchApiIndex $index
 *   The search index for which items are being indexed.
 * @param array $items
 *   An array of items being indexed.
 */
function eitisearch_search_api_solr_documents_alter(array &$documents, SearchApiIndex $index, array $items) {
  if ($index->machine_name == 'document_search') {
    $document_relevance_field_key ='is_field_relevance';

    foreach ($documents as $document) {
      $relevance_field = $document->getField($document_relevance_field_key);
      if (!empty($relevance_field)) {
        $relevance_value = $relevance_field['value'];
        $document->setBoost($relevance_value);
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function eitisearch_form_views_exposed_form_alter(&$form, &$form_state) {
  $fields_to_adjust = array(
    'field_doc_type_internal',
    'field_doc_type_public',
  );

  foreach ($fields_to_adjust as $field_key) {
    $field = field_info_field($field_key);
    $options = eitisearch_adjusted_voc_options($field);
    $form[$field_key]['#options'] = array(t('- Any -')) + $options;
    $form[$field_key]['#use_unsafe_labels'] = TRUE;
  }
}

/**
 * Returns the set of valid terms for a taxonomy field.
 *
 * @param $field
 *   The field definition.
 * @return
 *   The array of valid terms for this field, keyed by term id.
 */
function eitisearch_adjusted_voc_options($field) {
  $options = array();
  foreach ($field['settings']['allowed_values'] as $tree) {
    if ($vocabulary = taxonomy_vocabulary_machine_name_load($tree['vocabulary'])) {
      if ($terms = taxonomy_get_tree($vocabulary->vid, $tree['parent'])) {
        foreach ($terms as $term) {
          if ($term->depth == 0) {
            $options[$term->tid] = i18n_taxonomy_term_name($term);
          }
          else {
            $options[$term->tid] = str_repeat('&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;', $term->depth) . i18n_taxonomy_term_name($term);
          }
        }
      }
    }
  }
  return $options;
}
