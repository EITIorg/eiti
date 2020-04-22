<?php

/**
 * @file
 * eitipanels.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eitipanels_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:11:"panels_page";s:23:"allowed_layout_settings";a:13:{s:8:"flexible";b:0;s:6:"onecol";b:0;s:6:"twocol";b:0;s:13:"twocol_bricks";b:0;s:25:"threecol_25_50_25_stacked";b:0;s:25:"threecol_33_34_33_stacked";b:0;s:14:"twocol_stacked";b:0;s:17:"threecol_25_50_25";b:0;s:17:"threecol_33_34_33";b:0;s:12:"doublelayout";b:0;s:12:"simplelayout";b:0;s:11:"bricklayout";b:0;s:10:"widelayout";b:1;}s:10:"form_state";N;}';
  $export['panels_page_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_types';
  $strongarm->value = array(
    'navigation_floating-navigation_floating' => TRUE,
    'timeline-timeline' => TRUE,
    'minimalistic-footer-minimalistic-footer' => TRUE,
    'embedded_widget-embedded_widget' => TRUE,
    'map_simple-map_simple' => TRUE,
    'mailchimp_archive-mailchimp_archive' => TRUE,
    'country-header-country-header' => TRUE,
    'quick-summary-tool-quick-summary-tool' => TRUE,
    'minimalistic-header-minimalistic-header' => TRUE,
    'toc-toc' => TRUE,
    'map_full-map_full' => TRUE,
    'eiti_mailchimp.generic_signup-eiti_mailchimp.generic_signup' => TRUE,
    'fieldable_panels_pane-countdown' => TRUE,
    'fieldable_panels_pane-fact_blocks' => TRUE,
    'fieldable_panels_pane-featured_articles' => TRUE,
    'fieldable_panels_pane-featured_bookmarks' => TRUE,
    'fieldable_panels_pane-featured_persons' => TRUE,
    'fieldable_panels_pane-featured_publications' => TRUE,
    'fieldable_panels_pane-header' => TRUE,
    'fieldable_panels_pane-icon_blocks' => TRUE,
    'fieldable_panels_pane-persons_grid' => TRUE,
    'fieldable_panels_pane-quote' => TRUE,
    'fieldable_panels_pane-table' => TRUE,
    'fieldable_panels_pane-tabs_with_widgets' => TRUE,
    'fieldable_panels_pane-teaser' => TRUE,
    'fieldable_panels_pane-text' => TRUE,
    'fieldable_panels_pane-value_chain' => TRUE,
    'fieldable_panels_pane-visualization' => TRUE,
    'fieldable_panels_pane-fpid:1257' => TRUE,
    'fieldable_panels_pane-fpid:1394' => TRUE,
    'fieldable_panels_pane-fpid:162' => TRUE,
    'fieldable_panels_pane-fpid:789' => TRUE,
    'fieldable_panels_pane-fpid:786' => TRUE,
    'fieldable_panels_pane-fpid:785' => TRUE,
    'fieldable_panels_pane-fpid:790' => TRUE,
    'fieldable_panels_pane-fpid:793' => TRUE,
  );
  $export['panels_page_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_default';
  $strongarm->value = array(
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'block' => 0,
    'custom' => 0,
    'entity_field' => 0,
    'entity_field_extra' => 0,
    'entity_form_field' => 0,
    'token' => 0,
    'entity_view' => 0,
    'views_panes' => 0,
    'views' => 0,
    'other' => 0,
  );
  $export['panels_page_default'] = $strongarm;

  return $export;
}
