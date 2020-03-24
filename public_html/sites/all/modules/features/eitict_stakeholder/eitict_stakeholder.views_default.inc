<?php

/**
 * @file
 * eitict_stakeholder.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eitict_stakeholder_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'stakeholders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Stakeholders';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stakeholders';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<div class="stk-companies"><h2><span class="stk-total">@total <span>companies support the EITI<h2></div>';
  /* Header: Global: View area */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'supporters:companies_categories';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_stk_logo']['id'] = 'field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['table'] = 'field_data_field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['field'] = 'field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['label'] = '';
  $handler->display->display_options['fields']['field_stk_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_stk_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_stk_logo']['settings'] = array(
    'image_style' => 'logo-small',
    'image_link' => 'content',
  );
  /* Field: Entity translation: Title: translated */
  $handler->display->display_options['fields']['title_field_et']['id'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field_et']['field'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['label'] = '';
  $handler->display->display_options['fields']['title_field_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_field_et']['type'] = 'title_linked';
  $handler->display->display_options['fields']['title_field_et']['settings'] = array(
    'title_style' => '_none',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: Entity translation: Short intro: translated */
  $handler->display->display_options['fields']['field_short_intro_et']['id'] = 'field_short_intro_et';
  $handler->display->display_options['fields']['field_short_intro_et']['table'] = 'field_data_field_short_intro';
  $handler->display->display_options['fields']['field_short_intro_et']['field'] = 'field_short_intro_et';
  $handler->display->display_options['fields']['field_short_intro_et']['label'] = '';
  $handler->display->display_options['fields']['field_short_intro_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_short_intro_et']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['field_short_intro_et']['settings'] = array(
    'trim_length' => '300',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See more';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]';
  /* Contextual filter: Content: Type (field_stk_type) */
  $handler->display->display_options['arguments']['field_stk_type_tid']['id'] = 'field_stk_type_tid';
  $handler->display->display_options['arguments']['field_stk_type_tid']['table'] = 'field_data_field_stk_type';
  $handler->display->display_options['arguments']['field_stk_type_tid']['field'] = 'field_stk_type_tid';
  $handler->display->display_options['arguments']['field_stk_type_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_stk_type_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_stk_type_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_stk_type_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_stk_type_tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published status */
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
    'stakeholder' => 'stakeholder',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'stakeholders_companies');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Stakeholders companies';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_stk_type',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="stk-total">@total </span>';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h2>%1 support the EITI</h2>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Header: Global: View area */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'supporters:companies_categories';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_stk_type']['id'] = 'field_stk_type';
  $handler->display->display_options['fields']['field_stk_type']['table'] = 'field_data_field_stk_type';
  $handler->display->display_options['fields']['field_stk_type']['field'] = 'field_stk_type';
  $handler->display->display_options['fields']['field_stk_type']['label'] = '';
  $handler->display->display_options['fields']['field_stk_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_stk_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_stk_type']['type'] = 'hs_taxonomy_term_reference_last_text_only';
  $handler->display->display_options['fields']['field_stk_type']['delta_offset'] = '0';
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_stk_logo']['id'] = 'field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['table'] = 'field_data_field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['field'] = 'field_stk_logo';
  $handler->display->display_options['fields']['field_stk_logo']['label'] = '';
  $handler->display->display_options['fields']['field_stk_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_stk_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_stk_logo']['settings'] = array(
    'image_style' => 'logo-small',
    'image_link' => 'content',
  );
  /* Field: Entity translation: Title: translated */
  $handler->display->display_options['fields']['title_field_et']['id'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field_et']['field'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['label'] = '';
  $handler->display->display_options['fields']['title_field_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_field_et']['type'] = 'title_linked';
  $handler->display->display_options['fields']['title_field_et']['settings'] = array(
    'title_style' => '_none',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: Entity translation: Short intro: translated */
  $handler->display->display_options['fields']['field_short_intro_et']['id'] = 'field_short_intro_et';
  $handler->display->display_options['fields']['field_short_intro_et']['table'] = 'field_data_field_short_intro';
  $handler->display->display_options['fields']['field_short_intro_et']['field'] = 'field_short_intro_et';
  $handler->display->display_options['fields']['field_short_intro_et']['label'] = '';
  $handler->display->display_options['fields']['field_short_intro_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_short_intro_et']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['field_short_intro_et']['settings'] = array(
    'trim_length' => '300',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See more';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Type (field_stk_type) */
  $handler->display->display_options['sorts']['field_stk_type_tid']['id'] = 'field_stk_type_tid';
  $handler->display->display_options['sorts']['field_stk_type_tid']['table'] = 'field_data_field_stk_type';
  $handler->display->display_options['sorts']['field_stk_type_tid']['field'] = 'field_stk_type_tid';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_action'] = 'default';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '1';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'stakeholder' => 'stakeholder',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $translatables['stakeholders'] = array(
    t('Master'),
    t('Stakeholders'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<div class="stk-companies"><h2><span class="stk-total">@total <span>companies support the EITI<h2></div>'),
    t('See more'),
    t('All'),
    t('Block'),
    t('Stakeholders companies'),
    t('<span class="stk-total">@total </span>'),
    t('<h2>%1 support the EITI</h2>'),
  );
  $export['stakeholders'] = $view;

  return $export;
}
