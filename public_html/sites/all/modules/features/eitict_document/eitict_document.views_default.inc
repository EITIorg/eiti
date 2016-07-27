<?php
/**
 * @file
 * eitict_document.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eitict_document_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'publications';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Publications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Publications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content matches the search criteria.';
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
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Entity translation: Language */
  $handler->display->display_options['filters']['language_1']['id'] = 'language_1';
  $handler->display->display_options['filters']['language_1']['table'] = 'entity_translation';
  $handler->display->display_options['filters']['language_1']['field'] = 'language';
  $handler->display->display_options['filters']['language_1']['relationship'] = 'entity_translations';
  $handler->display->display_options['filters']['language_1']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );
  $handler->display->display_options['filters']['language_1']['group'] = 1;
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
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Field: Title (title_field) */
  $handler->display->display_options['filters']['title_field_value']['id'] = 'title_field_value';
  $handler->display->display_options['filters']['title_field_value']['table'] = 'field_data_title_field';
  $handler->display->display_options['filters']['title_field_value']['field'] = 'title_field_value';
  $handler->display->display_options['filters']['title_field_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['title_field_value']['group'] = 1;
  $handler->display->display_options['filters']['title_field_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title_field_value']['expose']['operator_id'] = 'title_field_value_op';
  $handler->display->display_options['filters']['title_field_value']['expose']['label'] = 'Filter by title';
  $handler->display->display_options['filters']['title_field_value']['expose']['operator'] = 'title_field_value_op';
  $handler->display->display_options['filters']['title_field_value']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title_field_value']['expose']['remember_roles'] = array(
    2 => '2',
  );
  /* Filter criterion: Content: Document Category (field_document_category) */
  $handler->display->display_options['filters']['field_document_category_tid']['id'] = 'field_document_category_tid';
  $handler->display->display_options['filters']['field_document_category_tid']['table'] = 'field_data_field_document_category';
  $handler->display->display_options['filters']['field_document_category_tid']['field'] = 'field_document_category_tid';
  $handler->display->display_options['filters']['field_document_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_document_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_document_category_tid']['expose']['operator_id'] = 'field_document_category_tid_op';
  $handler->display->display_options['filters']['field_document_category_tid']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_document_category_tid']['expose']['operator'] = 'field_document_category_tid_op';
  $handler->display->display_options['filters']['field_document_category_tid']['expose']['identifier'] = 'category';
  $handler->display->display_options['filters']['field_document_category_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_document_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_document_category_tid']['vocabulary'] = 'document_category';
  $handler->display->display_options['filters']['field_document_category_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Published Date (field_doc_published_date) */
  $handler->display->display_options['filters']['field_doc_published_date_value']['id'] = 'field_doc_published_date_value';
  $handler->display->display_options['filters']['field_doc_published_date_value']['table'] = 'field_data_field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date_value']['field'] = 'field_doc_published_date_value';
  $handler->display->display_options['filters']['field_doc_published_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_published_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_published_date_value']['expose']['operator_id'] = 'field_doc_published_date_value_op';
  $handler->display->display_options['filters']['field_doc_published_date_value']['expose']['label'] = 'Published Date';
  $handler->display->display_options['filters']['field_doc_published_date_value']['expose']['operator'] = 'field_doc_published_date_value_op';
  $handler->display->display_options['filters']['field_doc_published_date_value']['expose']['identifier'] = 'date';
  $handler->display->display_options['filters']['field_doc_published_date_value']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['field_doc_published_date_value']['granularity'] = 'month';
  $handler->display->display_options['filters']['field_doc_published_date_value']['year_range'] = '-30:+1';
  /* Filter criterion: Content: Document Category (field_document_category:language) */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'field_data_field_document_category';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );

  /* Display: Listing */
  $handler = $view->new_display('panel_pane', 'Listing', 'listing');
  $handler->display->display_options['pane_title'] = 'Listing: Publications';
  $handler->display->display_options['pane_category']['name'] = 'Widget Library';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'publications';
  $translatables['publications'] = array(
    t('Master'),
    t('Publications'),
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
    t('No content matches the search criteria.'),
    t('Translations'),
    t('Filter by title'),
    t('Category'),
    t('Published Date'),
    t('Listing'),
    t('Listing: Publications'),
    t('Widget Library'),
    t('Page'),
  );
  $export['publications'] = $view;

  return $export;
}
