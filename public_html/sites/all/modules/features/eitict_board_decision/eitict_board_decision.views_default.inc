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
  $view->name = 'board_decisions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Board decisions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Board decisions';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '25, 50, 100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'field_board_meeting_circular' => 'field_board_meeting_circular',
    'field_bd_number' => 'field_bd_number',
    'title_field' => 'title_field',
    'field_bd_keywords' => 'field_bd_keywords',
    'name_field' => 'name_field',
    'body' => 'body',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_board_meeting_circular' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bd_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_field' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bd_keywords' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name_field' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_country_target_id']['id'] = 'field_country_target_id';
  $handler->display->display_options['relationships']['field_country_target_id']['table'] = 'field_data_field_country';
  $handler->display->display_options['relationships']['field_country_target_id']['field'] = 'field_country_target_id';
  $handler->display->display_options['relationships']['field_country_target_id']['label'] = 'Country';
  /* Relationship: Content: Keywords (field_bd_keywords) */
  $handler->display->display_options['relationships']['field_bd_keywords_tid']['id'] = 'field_bd_keywords_tid';
  $handler->display->display_options['relationships']['field_bd_keywords_tid']['table'] = 'field_data_field_bd_keywords';
  $handler->display->display_options['relationships']['field_bd_keywords_tid']['field'] = 'field_bd_keywords_tid';
  $handler->display->display_options['relationships']['field_bd_keywords_tid']['label'] = 'Keywords';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'd.m.Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: Content: Related board meeting or circular */
  $handler->display->display_options['fields']['field_board_meeting_circular']['id'] = 'field_board_meeting_circular';
  $handler->display->display_options['fields']['field_board_meeting_circular']['table'] = 'field_data_field_board_meeting_circular';
  $handler->display->display_options['fields']['field_board_meeting_circular']['field'] = 'field_board_meeting_circular';
  $handler->display->display_options['fields']['field_board_meeting_circular']['label'] = '';
  $handler->display->display_options['fields']['field_board_meeting_circular']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_board_meeting_circular']['element_label_colon'] = FALSE;
  /* Field: Content: Decision number */
  $handler->display->display_options['fields']['field_bd_number']['id'] = 'field_bd_number';
  $handler->display->display_options['fields']['field_bd_number']['table'] = 'field_data_field_bd_number';
  $handler->display->display_options['fields']['field_bd_number']['field'] = 'field_bd_number';
  $handler->display->display_options['fields']['field_bd_number']['label'] = 'Decision #';
  $handler->display->display_options['fields']['field_bd_number']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bd_number']['alter']['text'] = '[field_bd_number]/[field_board_meeting_circular]';
  $handler->display->display_options['fields']['field_bd_number']['element_label_colon'] = FALSE;
  /* Field: Field: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['label'] = 'Decision';
  $handler->display->display_options['fields']['title_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 1;
  /* Field: Content: Keywords */
  $handler->display->display_options['fields']['field_bd_keywords']['id'] = 'field_bd_keywords';
  $handler->display->display_options['fields']['field_bd_keywords']['table'] = 'field_data_field_bd_keywords';
  $handler->display->display_options['fields']['field_bd_keywords']['field'] = 'field_bd_keywords';
  $handler->display->display_options['fields']['field_bd_keywords']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bd_keywords']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_bd_keywords']['delta_offset'] = '0';
  /* Field: Field: Name */
  $handler->display->display_options['fields']['name_field']['id'] = 'name_field';
  $handler->display->display_options['fields']['name_field']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field']['field'] = 'name_field';
  $handler->display->display_options['fields']['name_field']['relationship'] = 'field_country_target_id';
  $handler->display->display_options['fields']['name_field']['label'] = 'Country';
  $handler->display->display_options['fields']['name_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name_field']['link_to_entity'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'board_decision' => 'board_decision',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'allwords';
  $handler->display->display_options['filters']['combine']['group'] = 2;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'search';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    9 => 0,
    7 => 0,
    8 => 0,
    6 => 0,
    5 => 0,
    10 => 0,
    4 => 0,
    11 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'title_field' => 'title_field',
    'name_field' => 'name_field',
    'body' => 'body',
  );
  $translatables['board_decisions'] = array(
    t('Master'),
    t('Board decisions'),
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
    t('No results.'),
    t('Country'),
    t('Keywords'),
    t('Date'),
    t('Decision #'),
    t('[field_bd_number]/[field_board_meeting_circular]'),
    t('Decision'),
    t('Search'),
  );
  $export['board_decisions'] = $view;

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
