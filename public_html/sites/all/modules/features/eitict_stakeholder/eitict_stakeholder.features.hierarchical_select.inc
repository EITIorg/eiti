<?php

/**
 * @file
 * eitict_stakeholder.features.hierarchical_select.inc
 */

/**
 * Implements hook_hierarchical_select_default_configs().
 */
function eitict_stakeholder_hierarchical_select_default_configs() {
$configs = array();
$config = array(
  'save_lineage' => '0',
  'enforce_deepest' => '0',
  'resizable' => '0',
  'level_labels' => array(
    'status' => 0,
    'labels' => array(
      '0' => '',
      '1' => '',
    ),
  ),
  'dropbox' => array(
    'status' => 0,
    'title' => 'All selections',
    'limit' => '0',
    'reset_hs' => '1',
    'sort' => 1,
  ),
  'editability' => array(
    'status' => 0,
    'item_types' => array(
      '0' => '',
      '1' => '',
    ),
    'allowed_levels' => array(
      '0' => 1,
      '1' => 1,
    ),
    'allow_new_levels' => 0,
    'max_levels' => '1',
  ),
  'entity_count' => array(
    'enabled' => array(
      'enabled' => 0,
      'require_entity' => 0,
      'settings' => array(
        'count_children' => 0,
        'entity_types' => array(),
      ),
    ),
    'require_entity' => NULL,
    'settings' => array(
      'count_children' => 0,
      'entity_types' => array(
        'node' => array(
          'count_node' => array(
            'article' => 'article',
            'board_decision' => 'board_decision',
            'bookmark' => 'bookmark',
            'document' => 'document',
            'internal' => 'internal',
            'mention' => 'mention',
            'page' => 'page',
            'person' => 'person',
            'progress_report' => 'progress_report',
            'stakeholder' => 'stakeholder',
          ),
        ),
        'taxonomy_term' => array(
          'count_taxonomy_term' => array(
            'board_decision_bases' => 0,
            'board_decision_keywords' => 0,
            'bookmark_type' => 0,
            'company_commodities' => 0,
            'company_sectors' => 0,
            'document_category' => 0,
            'person_positions' => 0,
            'publication_types_internal' => 0,
            'publication_types_public' => 0,
            'publishers' => 0,
            'tags' => 0,
            'country_status' => 0,
            'score_requirement_category' => 0,
            'stakeholder_types' => 0,
          ),
        ),
        'country' => array(
          'count_country' => array(
            'country' => 0,
          ),
        ),
        'implementing_country' => array(
          'count_implementing_country' => array(
            'normal' => 0,
          ),
        ),
        'organisation' => array(
          'count_organisation' => array(
            'agency' => 0,
            'company' => 0,
          ),
        ),
        'revenue_stream' => array(
          'count_revenue_stream' => array(
            'company' => 0,
            'agency' => 0,
          ),
        ),
        'score_data' => array(
          'count_score_data' => array(
            'standard' => 0,
          ),
        ),
        'score_req' => array(
          'count_score_req' => array(
            'standard' => 0,
          ),
        ),
        'summary_data' => array(
          'count_summary_data' => array(
            'summary_data' => 0,
          ),
        ),
        'fieldable_panels_pane' => array(
          'count_fieldable_panels_pane' => array(
            'countdown' => 0,
            'fact_blocks' => 0,
            'featured_articles' => 0,
            'featured_bookmarks' => 0,
            'featured_persons' => 0,
            'featured_publications' => 0,
            'header' => 0,
            'icon_blocks' => 0,
            'persons_grid' => 0,
            'quote' => 0,
            'table' => 0,
            'tabs_with_widgets' => 0,
            'teaser' => 0,
            'text' => 0,
            'value_chain' => 0,
            'visualization' => 0,
          ),
        ),
        'file' => array(
          'count_file' => array(
            'document' => 0,
            'report' => 0,
            'image' => 0,
            'video' => 0,
            'audio' => 0,
          ),
        ),
        'user' => array(
          'count_user' => array(
            'user' => 0,
          ),
        ),
      ),
    ),
  ),
  'animation_delay' => 400,
  'special_items' => array(),
  'render_flat_select' => 0,
  'config_id' => 'taxonomy-field_stk_type',
);

$configs['taxonomy-field_stk_type'] = $config;
return $configs;
}
