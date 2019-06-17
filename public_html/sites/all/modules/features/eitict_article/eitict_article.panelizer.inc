<?php

/**
 * @file
 * eitict_article.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function eitict_article_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'article';
  $panelizer->access = array();
  $panelizer->view_mode = 'default';
  $panelizer->name = 'node:article:default:default';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'h1';
  $panelizer->link_to_entity = FALSE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'widelayout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '30c2c4c4-ed27-43c4-898c-a33863c36ed2';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:article:default:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-2a140533-cfc0-4805-97c6-794f7e6fb825';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_featured_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_link' => 'content',
      'image_style' => 'ar-thumb',
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '2a140533-cfc0-4805-97c6-794f7e6fb825';
  $display->content['new-2a140533-cfc0-4805-97c6-794f7e6fb825'] = $pane;
  $display->panels['main'][0] = 'new-2a140533-cfc0-4805-97c6-794f7e6fb825';
  $pane = new stdClass();
  $pane->pid = 'new-919614ea-1ef3-41a1-a9bc-dd4e54501fa9';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:title_field';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'title_linked',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'title_class' => 'title',
      'title_link' => 'content',
      'title_style' => 'h3',
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '919614ea-1ef3-41a1-a9bc-dd4e54501fa9';
  $display->content['new-919614ea-1ef3-41a1-a9bc-dd4e54501fa9'] = $pane;
  $display->panels['main'][1] = 'new-919614ea-1ef3-41a1-a9bc-dd4e54501fa9';
  $pane = new stdClass();
  $pane->pid = 'new-e166f817-c618-463f-bb24-7ba2316c97e7';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'helpergeneric_clean_summary',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'trim_length' => 512,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'e166f817-c618-463f-bb24-7ba2316c97e7';
  $display->content['new-e166f817-c618-463f-bb24-7ba2316c97e7'] = $pane;
  $display->panels['main'][2] = 'new-e166f817-c618-463f-bb24-7ba2316c97e7';
  $pane = new stdClass();
  $pane->pid = 'new-377894e6-6f1c-4b05-a99c-3ad9a8cc72a2';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_event_date';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'date_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'format_type' => 'shortest',
      'fromto' => 'both',
      'multiple_from' => '',
      'multiple_number' => '',
      'multiple_to' => '',
      'show_remaining_days' => 0,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '377894e6-6f1c-4b05-a99c-3ad9a8cc72a2';
  $display->content['new-377894e6-6f1c-4b05-a99c-3ad9a8cc72a2'] = $pane;
  $display->panels['main'][3] = 'new-377894e6-6f1c-4b05-a99c-3ad9a8cc72a2';
  $pane = new stdClass();
  $pane->pid = 'new-5f3f5df8-b8ce-4921-b2b9-15512fc00f84';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_event_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '5f3f5df8-b8ce-4921-b2b9-15512fc00f84';
  $display->content['new-5f3f5df8-b8ce-4921-b2b9-15512fc00f84'] = $pane;
  $display->panels['main'][4] = 'new-5f3f5df8-b8ce-4921-b2b9-15512fc00f84';
  $pane = new stdClass();
  $pane->pid = 'new-9df8bf0a-8631-4612-ae92-280a97757bdf';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'ds_taxonomy_separator_localized',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'taxonomy_term_link' => 1,
      'taxonomy_term_separator' => ', ',
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '9df8bf0a-8631-4612-ae92-280a97757bdf';
  $display->content['new-9df8bf0a-8631-4612-ae92-280a97757bdf'] = $pane;
  $display->panels['main'][5] = 'new-9df8bf0a-8631-4612-ae92-280a97757bdf';
  $pane = new stdClass();
  $pane->pid = 'new-17060365-6b0e-4c9c-b57c-3458573596a8';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_related_country';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'hidden',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '17060365-6b0e-4c9c-b57c-3458573596a8';
  $display->content['new-17060365-6b0e-4c9c-b57c-3458573596a8'] = $pane;
  $display->panels['main'][6] = 'new-17060365-6b0e-4c9c-b57c-3458573596a8';
  $pane = new stdClass();
  $pane->pid = 'new-4667b98c-ebb2-458b-8f9a-313729f426f6';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_image_gallery';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'hidden',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '4667b98c-ebb2-458b-8f9a-313729f426f6';
  $display->content['new-4667b98c-ebb2-458b-8f9a-313729f426f6'] = $pane;
  $display->panels['main'][7] = 'new-4667b98c-ebb2-458b-8f9a-313729f426f6';
  $pane = new stdClass();
  $pane->pid = 'new-79d4b89e-9324-48ec-9a35-d03e693b2d4d';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_attachments';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'hidden',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 8;
  $pane->locks = array();
  $pane->uuid = '79d4b89e-9324-48ec-9a35-d03e693b2d4d';
  $display->content['new-79d4b89e-9324-48ec-9a35-d03e693b2d4d'] = $pane;
  $display->panels['main'][8] = 'new-79d4b89e-9324-48ec-9a35-d03e693b2d4d';
  $pane = new stdClass();
  $pane->pid = 'new-da84fe73-df95-4af0-821b-1ad505dc7269';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_article_type';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'hidden',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 9;
  $pane->locks = array();
  $pane->uuid = 'da84fe73-df95-4af0-821b-1ad505dc7269';
  $display->content['new-da84fe73-df95-4af0-821b-1ad505dc7269'] = $pane;
  $display->panels['main'][9] = 'new-da84fe73-df95-4af0-821b-1ad505dc7269';
  $pane = new stdClass();
  $pane->pid = 'new-2773906c-06bb-4cde-99d3-6ebcbcda7fe0';
  $pane->panel = 'main';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_mailchimp_signup_form';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
      'bypass_access' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 10;
  $pane->locks = array();
  $pane->uuid = '2773906c-06bb-4cde-99d3-6ebcbcda7fe0';
  $display->content['new-2773906c-06bb-4cde-99d3-6ebcbcda7fe0'] = $pane;
  $display->panels['main'][10] = 'new-2773906c-06bb-4cde-99d3-6ebcbcda7fe0';
  $pane = new stdClass();
  $pane->pid = 'new-e04064cb-693e-4e37-bf1d-e60b125480ca';
  $pane->panel = 'main';
  $pane->type = 'node_links';
  $pane->subtype = 'node_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => FALSE,
    'override_title_text' => '',
    'build_mode' => 'default',
    'identifier' => '',
    'link' => TRUE,
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_class' => 'link-wrapper',
  );
  $pane->extras = array();
  $pane->position = 11;
  $pane->locks = array();
  $pane->uuid = 'e04064cb-693e-4e37-bf1d-e60b125480ca';
  $display->content['new-e04064cb-693e-4e37-bf1d-e60b125480ca'] = $pane;
  $display->panels['main'][11] = 'new-e04064cb-693e-4e37-bf1d-e60b125480ca';
  $pane = new stdClass();
  $pane->pid = 'new-b10771a4-e9f0-400a-a7d1-919a8d295c2d';
  $pane->panel = 'main';
  $pane->type = 'fieldable_panels_pane';
  $pane->subtype = 'fpid:3110';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'full',
    'show_title' => 1,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 12;
  $pane->locks = array();
  $pane->uuid = 'b10771a4-e9f0-400a-a7d1-919a8d295c2d';
  $display->content['new-b10771a4-e9f0-400a-a7d1-919a8d295c2d'] = $pane;
  $display->panels['main'][12] = 'new-b10771a4-e9f0-400a-a7d1-919a8d295c2d';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-2a140533-cfc0-4805-97c6-794f7e6fb825';
  $panelizer->display = $display;
  $export['node:article:default:default'] = $panelizer;

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'article';
  $panelizer->access = array();
  $panelizer->view_mode = 'full';
  $panelizer->name = 'node:article:default:full';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'widelayout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '338b0663-dba3-4175-a1c3-daf9957ae6d8';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:article:default:full';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-ee30c107-23bc-4fd1-ad63-b1cb9c5b82c2';
  $pane->panel = 'main';
  $pane->type = 'entity_view';
  $pane->subtype = 'node';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'full',
    'context' => 'panelizer',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'ee30c107-23bc-4fd1-ad63-b1cb9c5b82c2';
  $display->content['new-ee30c107-23bc-4fd1-ad63-b1cb9c5b82c2'] = $pane;
  $display->panels['main'][0] = 'new-ee30c107-23bc-4fd1-ad63-b1cb9c5b82c2';
  $pane = new stdClass();
  $pane->pid = 'new-2fea3b61-0dc4-4f71-8bc0-1149217c9b5f';
  $pane->panel = 'main';
  $pane->type = 'related-articles';
  $pane->subtype = 'related-articles';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '2fea3b61-0dc4-4f71-8bc0-1149217c9b5f';
  $display->content['new-2fea3b61-0dc4-4f71-8bc0-1149217c9b5f'] = $pane;
  $display->panels['main'][1] = 'new-2fea3b61-0dc4-4f71-8bc0-1149217c9b5f';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:article:default:full'] = $panelizer;

  return $export;
}
