<?php
/**
 * @file
 * eitict_board_decision.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eitict_board_decision_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'content_reference';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Content reference';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any board_decision content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Entity translation: translations */
  $handler->display->display_options['relationships']['entity_translations']['id'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['table'] = 'node';
  $handler->display->display_options['relationships']['entity_translations']['field'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
    'document' => 'document',
    'page' => 'page',
  );
  /* Filter criterion: Content: Internal Sub-Type (field_doc_type_internal) */
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['id'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['table'] = 'field_data_field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['field'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['vocabulary'] = 'publication_types_internal';
  /* Filter criterion: Entity translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'entity_translation';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['relationship'] = 'entity_translations';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );

  /* Display: Public content */
  $handler = $view->new_display('entityreference', 'Public content', 'public_content');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Private documents */
  $handler = $view->new_display('entityreference', 'Private documents', 'private_documents');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any document content';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'document' => 'document',
  );
  /* Filter criterion: Content: Internal Sub-Type (field_doc_type_internal) */
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['id'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['table'] = 'field_data_field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['field'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['vocabulary'] = 'publication_types_internal';
  /* Filter criterion: Entity translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'entity_translation';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['relationship'] = 'entity_translations';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );
  $translatables['content_reference'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Translations'),
    t('Public content'),
    t('Private documents'),
  );
  $export['content_reference'] = $view;

  $view = new view();
  $view->name = 'validation_data';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eiti_score_data';
  $view->human_name = 'Validation data';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'score_data entity edit';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Validation Data: Implementing Country */
  $handler->display->display_options['relationships']['country_id']['id'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['table'] = 'eiti_score_data';
  $handler->display->display_options['relationships']['country_id']['field'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['required'] = TRUE;
  /* Field: Implementing Country: Implementing Country Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'eiti_implementing_country';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'country_id';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Validation Data: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'eiti_score_data';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['label'] = '';
  $handler->display->display_options['fields']['year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['year']['separator'] = '';
  /* Sort criterion: Validation Data: Year */
  $handler->display->display_options['sorts']['year']['id'] = 'year';
  $handler->display->display_options['sorts']['year']['table'] = 'eiti_score_data';
  $handler->display->display_options['sorts']['year']['field'] = 'year';
  $handler->display->display_options['sorts']['year']['order'] = 'DESC';

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entity_reference');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
    'year' => 'year',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['validation_data'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Implementing Country'),
    t('.'),
    t('Entity Reference'),
  );
  $export['validation_data'] = $view;

  return $export;
}
