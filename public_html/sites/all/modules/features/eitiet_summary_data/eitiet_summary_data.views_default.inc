<?php
/**
 * @file
 * eitiet_summary_data.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eitiet_summary_data_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'summary_data';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eiti_summary_data';
  $view->human_name = 'Summary data';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Summary data';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Summary Data: Implementing Country */
  $handler->display->display_options['relationships']['country_id']['id'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['table'] = 'eiti_summary_data';
  $handler->display->display_options['relationships']['country_id']['field'] = 'country_id';
  /* Field: Summary Data: Summary data ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eiti_summary_data';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Creator */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Creator';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Eiti';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Summary Data: Published Date */
  $handler->display->display_options['fields']['published']['id'] = 'published';
  $handler->display->display_options['fields']['published']['table'] = 'eiti_summary_data';
  $handler->display->display_options['fields']['published']['field'] = 'published';
  $handler->display->display_options['fields']['published']['label'] = '';
  $handler->display->display_options['fields']['published']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['published']['date_format'] = 'custom';
  $handler->display->display_options['fields']['published']['custom_date_format'] = 'r';
  $handler->display->display_options['fields']['published']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: Summary Data: Summary Data Report File */
  $handler->display->display_options['fields']['field_sd_report_file']['id'] = 'field_sd_report_file';
  $handler->display->display_options['fields']['field_sd_report_file']['table'] = 'field_data_field_sd_report_file';
  $handler->display->display_options['fields']['field_sd_report_file']['field'] = 'field_sd_report_file';
  $handler->display->display_options['fields']['field_sd_report_file']['label'] = '';
  $handler->display->display_options['fields']['field_sd_report_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sd_report_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sd_report_file']['type'] = 'file_url_plain';
  /* Field: Summary Data: Year End */
  $handler->display->display_options['fields']['year_end']['id'] = 'year_end';
  $handler->display->display_options['fields']['year_end']['table'] = 'eiti_summary_data';
  $handler->display->display_options['fields']['year_end']['field'] = 'year_end';
  $handler->display->display_options['fields']['year_end']['label'] = '';
  $handler->display->display_options['fields']['year_end']['exclude'] = TRUE;
  $handler->display->display_options['fields']['year_end']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['year_end']['date_format'] = 'custom';
  $handler->display->display_options['fields']['year_end']['custom_date_format'] = 'Y';
  $handler->display->display_options['fields']['year_end']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: Field: Name */
  $handler->display->display_options['fields']['name_field']['id'] = 'name_field';
  $handler->display->display_options['fields']['name_field']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field']['field'] = 'name_field';
  $handler->display->display_options['fields']['name_field']['relationship'] = 'country_id';
  $handler->display->display_options['fields']['name_field']['label'] = '';
  $handler->display->display_options['fields']['name_field']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name_field']['alter']['text'] = '[name_field]
<br>
[year_end]';
  $handler->display->display_options['fields']['name_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name_field']['type'] = 'text_plain';
  $handler->display->display_options['fields']['name_field']['link_to_entity'] = 0;
  /* Field: Summary Data: Id2 */
  $handler->display->display_options['fields']['id2']['id'] = 'id2';
  $handler->display->display_options['fields']['id2']['table'] = 'eiti_summary_data';
  $handler->display->display_options['fields']['id2']['field'] = 'id2';
  $handler->display->display_options['fields']['id2']['label'] = '';
  $handler->display->display_options['fields']['id2']['element_label_colon'] = FALSE;
  /* Sort criterion: Summary Data: Published Date */
  $handler->display->display_options['sorts']['published']['id'] = 'published';
  $handler->display->display_options['sorts']['published']['table'] = 'eiti_summary_data';
  $handler->display->display_options['sorts']['published']['field'] = 'published';
  $handler->display->display_options['sorts']['published']['order'] = 'DESC';
  /* Filter criterion: Summary Data: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'eiti_summary_data';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'id2';
  $handler->display->display_options['row_options']['link_field'] = 'field_sd_report_file';
  $handler->display->display_options['row_options']['description_field'] = 'name_field';
  $handler->display->display_options['row_options']['creator_field'] = 'nothing';
  $handler->display->display_options['row_options']['date_field'] = 'published';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'id',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['path'] = 'feed/summary-data.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
  );

  /* Display: Country feed */
  $handler = $view->new_display('feed', 'Country feed', 'feed_country');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'id2';
  $handler->display->display_options['row_options']['link_field'] = 'field_sd_report_file';
  $handler->display->display_options['row_options']['description_field'] = 'name_field';
  $handler->display->display_options['row_options']['creator_field'] = 'nothing';
  $handler->display->display_options['row_options']['date_field'] = 'published';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'id',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Summary Data: Implementing Country */
  $handler->display->display_options['relationships']['country_id']['id'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['table'] = 'eiti_summary_data';
  $handler->display->display_options['relationships']['country_id']['field'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Implementing Country: Iso */
  $handler->display->display_options['arguments']['iso']['id'] = 'iso';
  $handler->display->display_options['arguments']['iso']['table'] = 'eiti_implementing_country';
  $handler->display->display_options['arguments']['iso']['field'] = 'iso';
  $handler->display->display_options['arguments']['iso']['relationship'] = 'country_id';
  $handler->display->display_options['arguments']['iso']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['iso']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['iso']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['iso']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['iso']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['iso']['limit'] = '0';
  $handler->display->display_options['path'] = 'feed/%/summary-data.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
  );
  $translatables['summary_data'] = array(
    t('Master'),
    t('Summary data'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Implementing Country'),
    t('.'),
    t('Eiti'),
    t('[name_field]
<br>
[year_end]'),
    t('Feed'),
    t('Country feed'),
    t('All'),
  );
  $export['summary_data'] = $view;

  return $export;
}
