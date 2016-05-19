<?php
/**
 * @file
 * eitiwidgets.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eitiwidgets_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'quick_summary_table';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eiti_summary_data';
  $view->human_name = 'Quick Summary Table';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'There is no data to display!';
  /* Relationship: Summary Data: Implementing Country */
  $handler->display->display_options['relationships']['country_id']['id'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['table'] = 'eiti_summary_data';
  $handler->display->display_options['relationships']['country_id']['field'] = 'country_id';
  $handler->display->display_options['relationships']['country_id']['label'] = 'IC';
  $handler->display->display_options['relationships']['country_id']['required'] = TRUE;
  /* Field: Entity translation: Name: translated */
  $handler->display->display_options['fields']['name_field_et']['id'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field_et']['field'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['relationship'] = 'country_id';
  $handler->display->display_options['fields']['name_field_et']['label'] = 'Implementing Country';
  /* Field: Summary Data: Year End */
  $handler->display->display_options['fields']['year_end']['id'] = 'year_end';
  $handler->display->display_options['fields']['year_end']['table'] = 'eiti_summary_data';
  $handler->display->display_options['fields']['year_end']['field'] = 'year_end';
  $handler->display->display_options['fields']['year_end']['separator'] = '';
  /* Field: Summary Data: Number of reporting companies */
  $handler->display->display_options['fields']['field_sd_no_reporting_com']['id'] = 'field_sd_no_reporting_com';
  $handler->display->display_options['fields']['field_sd_no_reporting_com']['table'] = 'field_data_field_sd_no_reporting_com';
  $handler->display->display_options['fields']['field_sd_no_reporting_com']['field'] = 'field_sd_no_reporting_com';
  $handler->display->display_options['fields']['field_sd_no_reporting_com']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Summary Data: Number of reporting government entities */
  $handler->display->display_options['fields']['field_sd_no_reporting_gov']['id'] = 'field_sd_no_reporting_gov';
  $handler->display->display_options['fields']['field_sd_no_reporting_gov']['table'] = 'field_data_field_sd_no_reporting_gov';
  $handler->display->display_options['fields']['field_sd_no_reporting_gov']['field'] = 'field_sd_no_reporting_gov';
  $handler->display->display_options['fields']['field_sd_no_reporting_gov']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Summary Data: Other data files */
  $handler->display->display_options['fields']['field_sd_file_links']['id'] = 'field_sd_file_links';
  $handler->display->display_options['fields']['field_sd_file_links']['table'] = 'field_data_field_sd_file_links';
  $handler->display->display_options['fields']['field_sd_file_links']['field'] = 'field_sd_file_links';
  /* Sort criterion: Summary Data: Year End */
  $handler->display->display_options['sorts']['year_end']['id'] = 'year_end';
  $handler->display->display_options['sorts']['year_end']['table'] = 'eiti_summary_data';
  $handler->display->display_options['sorts']['year_end']['field'] = 'year_end';
  $handler->display->display_options['sorts']['year_end']['order'] = 'DESC';
  /* Contextual filter: Summary Data: Summary data ID */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eiti_summary_data';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['id']['break_phrase'] = TRUE;
  $translatables['quick_summary_table'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('There is no data to display!'),
    t('IC'),
    t('Implementing Country'),
    t('Year End'),
    t('.'),
    t('Number of reporting companies'),
    t('Number of reporting government entities'),
    t('Other data files'),
    t('All'),
  );
  $export['quick_summary_table'] = $view;

  return $export;
}
