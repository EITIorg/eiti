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

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'body';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'field_doc_published_date';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'nid',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Entity translation: translations */
  $handler->display->display_options['relationships']['entity_translations']['id'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['table'] = 'node';
  $handler->display->display_options['relationships']['entity_translations']['field'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Public Sub-Type */
  $handler->display->display_options['fields']['field_doc_type_public']['id'] = 'field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['table'] = 'field_data_field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['field'] = 'field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['label'] = '';
  $handler->display->display_options['fields']['field_doc_type_public']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_doc_type_public']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_doc_type_public']['type'] = 'i18n_taxonomy_term_reference_plain';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = 'Publication type: [field_doc_type_public]
<br>
[body]';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Published Date */
  $handler->display->display_options['fields']['field_doc_published_date']['id'] = 'field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['table'] = 'field_data_field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['field'] = 'field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['label'] = '';
  $handler->display->display_options['fields']['field_doc_published_date']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_doc_published_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_doc_published_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => 'r',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  /* Filter criterion: Content: Internal Sub-Type (field_doc_type_internal) */
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['id'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['table'] = 'field_data_field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['field'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['vocabulary'] = 'publication_types_internal';
  /* Filter criterion: Content: Public Sub-Type (field_doc_type_public) */
  $handler->display->display_options['filters']['field_doc_type_public_tid']['id'] = 'field_doc_type_public_tid';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['table'] = 'field_data_field_doc_type_public';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['field'] = 'field_doc_type_public_tid';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['operator'] = 'not';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['value'] = array(
    4861 => '4861',
  );
  $handler->display->display_options['filters']['field_doc_type_public_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['vocabulary'] = 'publication_types_public';
  $handler->display->display_options['path'] = 'feed/publications.xml';

  /* Display: Country feed */
  $handler = $view->new_display('feed', 'Country feed', 'feed_country');
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'body';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'field_doc_published_date';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'nid',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Entity translation: translations */
  $handler->display->display_options['relationships']['entity_translations']['id'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['table'] = 'node';
  $handler->display->display_options['relationships']['entity_translations']['field'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Content: Country (field_doc_country) */
  $handler->display->display_options['relationships']['field_doc_country_iso2']['id'] = 'field_doc_country_iso2';
  $handler->display->display_options['relationships']['field_doc_country_iso2']['table'] = 'field_data_field_doc_country';
  $handler->display->display_options['relationships']['field_doc_country_iso2']['field'] = 'field_doc_country_iso2';
  $handler->display->display_options['relationships']['field_doc_country_iso2']['label'] = 'country';
  $handler->display->display_options['relationships']['field_doc_country_iso2']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Public Sub-Type */
  $handler->display->display_options['fields']['field_doc_type_public']['id'] = 'field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['table'] = 'field_data_field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['field'] = 'field_doc_type_public';
  $handler->display->display_options['fields']['field_doc_type_public']['label'] = '';
  $handler->display->display_options['fields']['field_doc_type_public']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_doc_type_public']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_doc_type_public']['type'] = 'i18n_taxonomy_term_reference_plain';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = 'Publication type: [field_doc_type_public]
<br>
[body]';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Published Date */
  $handler->display->display_options['fields']['field_doc_published_date']['id'] = 'field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['table'] = 'field_data_field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['field'] = 'field_doc_published_date';
  $handler->display->display_options['fields']['field_doc_published_date']['label'] = '';
  $handler->display->display_options['fields']['field_doc_published_date']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_doc_published_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_doc_published_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => 'r',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Countries: ISO2 */
  $handler->display->display_options['arguments']['iso2']['id'] = 'iso2';
  $handler->display->display_options['arguments']['iso2']['table'] = 'countries_country';
  $handler->display->display_options['arguments']['iso2']['field'] = 'iso2';
  $handler->display->display_options['arguments']['iso2']['relationship'] = 'field_doc_country_iso2';
  $handler->display->display_options['arguments']['iso2']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['iso2']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['iso2']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['iso2']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['iso2']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['iso2']['limit'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  /* Filter criterion: Content: Internal Sub-Type (field_doc_type_internal) */
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['id'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['table'] = 'field_data_field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['field'] = 'field_doc_type_internal_tid';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_internal_tid']['vocabulary'] = 'publication_types_internal';
  /* Filter criterion: Content: Public Sub-Type (field_doc_type_public) */
  $handler->display->display_options['filters']['field_doc_type_public_tid']['id'] = 'field_doc_type_public_tid';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['table'] = 'field_data_field_doc_type_public';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['field'] = 'field_doc_type_public_tid';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['operator'] = 'not';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['value'] = array(
    4861 => '4861',
  );
  $handler->display->display_options['filters']['field_doc_type_public_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_type_public_tid']['vocabulary'] = 'publication_types_public';
  $handler->display->display_options['path'] = 'feed/%/publications.xml';
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
    t('Feed'),
    t('author'),
    t('Publication type: [field_doc_type_public]
<br>
[body]'),
    t('Country feed'),
    t('country'),
    t('All'),
  );
  $export['publications'] = $view;

  $view = new view();
  $view->name = 'publications_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_document_search';
  $view->human_name = 'Publications Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Publications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'teaser';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['label'] = 'No results';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content matches the search criteria.';
  /* Field: Indexed Content: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  /* Sort criterion: Search: Relevance */
  $handler->display->display_options['sorts']['search_api_relevance']['id'] = 'search_api_relevance';
  $handler->display->display_options['sorts']['search_api_relevance']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['sorts']['search_api_relevance']['field'] = 'search_api_relevance';
  $handler->display->display_options['sorts']['search_api_relevance']['order'] = 'DESC';
  /* Sort criterion: Indexed Content: Published Date */
  $handler->display->display_options['sorts']['field_doc_published_date']['id'] = 'field_doc_published_date';
  $handler->display->display_options['sorts']['field_doc_published_date']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['sorts']['field_doc_published_date']['field'] = 'field_doc_published_date';
  $handler->display->display_options['sorts']['field_doc_published_date']['order'] = 'DESC';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Keyword search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'body:summary' => 'body:summary',
    'body:value' => 'body:value',
    'title' => 'title',
    'title_field' => 'title_field',
  );
  /* Filter criterion: Indexed Content: Internal Sub-Type */
  $handler->display->display_options['filters']['field_doc_type_internal']['id'] = 'field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_type_internal']['field'] = 'field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal']['value'] = array();
  $handler->display->display_options['filters']['field_doc_type_internal']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_type_internal']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['operator_id'] = 'field_doc_type_internal_op';
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['label'] = 'Publication Type';
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['operator'] = 'field_doc_type_internal_op';
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['identifier'] = 'field_doc_type_internal';
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_type_internal']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Content: Country */
  $handler->display->display_options['filters']['field_doc_country']['id'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_country']['field'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['value'] = array();
  $handler->display->display_options['filters']['field_doc_country']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_country']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_country']['expose']['operator_id'] = 'field_doc_country_op';
  $handler->display->display_options['filters']['field_doc_country']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['field_doc_country']['expose']['operator'] = 'field_doc_country_op';
  $handler->display->display_options['filters']['field_doc_country']['expose']['identifier'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_doc_country']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_country']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Content: Publisher */
  $handler->display->display_options['filters']['field_doc_publisher']['id'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_publisher']['field'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['operator_id'] = 'field_doc_publisher_op';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['operator'] = 'field_doc_publisher_op';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['identifier'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['remember_roles'] = array(
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
  /* Filter criterion: Indexed Content: Published Date */
  $handler->display->display_options['filters']['field_doc_published_date']['id'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_published_date']['field'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['operator'] = '>=';
  $handler->display->display_options['filters']['field_doc_published_date']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_published_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator_id'] = 'field_doc_published_date_op';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['label'] = 'Published After';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator_label'] = 'adsf';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator'] = 'field_doc_published_date_op';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['identifier'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['label'] = 'Published Date';
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['identifier'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_doc_published_date']['widget_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_doc_published_date']['year_range'] = '-4:+1';
  /* Filter criterion: Indexed Content: Published Date */
  $handler->display->display_options['filters']['field_doc_published_date_1']['id'] = 'field_doc_published_date_1';
  $handler->display->display_options['filters']['field_doc_published_date_1']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_published_date_1']['field'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_doc_published_date_1']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_published_date_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['operator_id'] = 'field_doc_published_date_1_op';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['label'] = 'Published Before';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['operator'] = 'field_doc_published_date_1_op';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['identifier'] = 'field_doc_published_date_1';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_published_date_1']['widget_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_doc_published_date_1']['year_range'] = '-4:+1';
  /* Filter criterion: Indexed Content: Relevance */
  $handler->display->display_options['filters']['field_relevance']['id'] = 'field_relevance';
  $handler->display->display_options['filters']['field_relevance']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_relevance']['field'] = 'field_relevance';
  $handler->display->display_options['filters']['field_relevance']['operator'] = '<>';
  $handler->display->display_options['filters']['field_relevance']['value'] = array(
    0 => '0',
  );

  /* Display: Public Page */
  $handler = $view->new_display('page', 'Public Page', 'page');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Keyword search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'body:summary' => 'body:summary',
    'body:value' => 'body:value',
    'title' => 'title',
    'title_field' => 'title_field',
  );
  /* Filter criterion: Indexed Content: Public Sub-Type */
  $handler->display->display_options['filters']['field_doc_type_public']['id'] = 'field_doc_type_public';
  $handler->display->display_options['filters']['field_doc_type_public']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_type_public']['field'] = 'field_doc_type_public';
  $handler->display->display_options['filters']['field_doc_type_public']['value'] = array();
  $handler->display->display_options['filters']['field_doc_type_public']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_type_public']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['operator_id'] = 'field_doc_type_public_op';
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['label'] = 'Publication Type';
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['operator'] = 'field_doc_type_public_op';
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['identifier'] = 'field_doc_type_public';
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_type_public']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Content: Country */
  $handler->display->display_options['filters']['field_doc_country']['id'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_country']['field'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['value'] = array();
  $handler->display->display_options['filters']['field_doc_country']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_country']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_country']['expose']['operator_id'] = 'field_doc_country_op';
  $handler->display->display_options['filters']['field_doc_country']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['field_doc_country']['expose']['operator'] = 'field_doc_country_op';
  $handler->display->display_options['filters']['field_doc_country']['expose']['identifier'] = 'field_doc_country';
  $handler->display->display_options['filters']['field_doc_country']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_doc_country']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_country']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Content: Publisher */
  $handler->display->display_options['filters']['field_doc_publisher']['id'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_publisher']['field'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['operator_id'] = 'field_doc_publisher_op';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['operator'] = 'field_doc_publisher_op';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['identifier'] = 'field_doc_publisher';
  $handler->display->display_options['filters']['field_doc_publisher']['expose']['remember_roles'] = array(
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
  /* Filter criterion: Indexed Content: Published Date */
  $handler->display->display_options['filters']['field_doc_published_date']['id'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_published_date']['field'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['operator'] = '>=';
  $handler->display->display_options['filters']['field_doc_published_date']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_published_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator_id'] = 'field_doc_published_date_op';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['label'] = 'Published After';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator_label'] = 'adsf';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['operator'] = 'field_doc_published_date_op';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['identifier'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['label'] = 'Published Date';
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['identifier'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_doc_published_date']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_doc_published_date']['widget_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_doc_published_date']['year_range'] = '-4:+1';
  /* Filter criterion: Indexed Content: Published Date */
  $handler->display->display_options['filters']['field_doc_published_date_1']['id'] = 'field_doc_published_date_1';
  $handler->display->display_options['filters']['field_doc_published_date_1']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_doc_published_date_1']['field'] = 'field_doc_published_date';
  $handler->display->display_options['filters']['field_doc_published_date_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_doc_published_date_1']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_published_date_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['operator_id'] = 'field_doc_published_date_1_op';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['label'] = 'Published Before';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['operator'] = 'field_doc_published_date_1_op';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['identifier'] = 'field_doc_published_date_1';
  $handler->display->display_options['filters']['field_doc_published_date_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_doc_published_date_1']['widget_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_doc_published_date_1']['year_range'] = '-4:+1';
  /* Filter criterion: Indexed Content: Relevance */
  $handler->display->display_options['filters']['field_relevance']['id'] = 'field_relevance';
  $handler->display->display_options['filters']['field_relevance']['table'] = 'search_api_index_document_search';
  $handler->display->display_options['filters']['field_relevance']['field'] = 'field_relevance';
  $handler->display->display_options['filters']['field_relevance']['operator'] = '<>';
  $handler->display->display_options['filters']['field_relevance']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['path'] = 'publications';

  /* Display: Private Page */
  $handler = $view->new_display('page', 'Private Page', 'page_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['path'] = 'publications-restricted';
  $translatables['publications_search'] = array(
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
    t('No results'),
    t('No content matches the search criteria.'),
    t('Title'),
    t('Keyword search'),
    t('Publication Type'),
    t('Country'),
    t('Publisher'),
    t('Published After'),
    t('adsf'),
    t('Published Date'),
    t('Published Before'),
    t('Public Page'),
    t('Private Page'),
  );
  $export['publications_search'] = $view;

  return $export;
}
