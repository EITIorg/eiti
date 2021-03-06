<?php

/**
 * @file
 * eitiwidgets.fieldable_panels_pane_type.inc
 */

/**
 * Implements hook_default_fieldable_panels_pane_type().
 */
function eitiwidgets_default_fieldable_panels_pane_type() {
  $export = array();

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'countdown';
  $fieldable_panels_pane_type->title = 'Countdown';
  $fieldable_panels_pane_type->description = 'Event information display with a countdown';
  $export['countdown'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'fact_blocks';
  $fieldable_panels_pane_type->title = 'Fact Blocks';
  $fieldable_panels_pane_type->description = 'Widget that contains a couple of key facts.';
  $export['fact_blocks'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'featured_articles';
  $fieldable_panels_pane_type->title = 'Featured Articles';
  $fieldable_panels_pane_type->description = 'Use this widget to create a list of selected articles of various types (blog, event, news).';
  $export['featured_articles'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'featured_bookmarks';
  $fieldable_panels_pane_type->title = 'Featured Bookmarks';
  $fieldable_panels_pane_type->description = 'Featured bookmarks go here (also known as Media Section).';
  $export['featured_bookmarks'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'featured_persons';
  $fieldable_panels_pane_type->title = 'Featured Persons';
  $fieldable_panels_pane_type->description = 'Featured persons go here (useful for the about pages).';
  $export['featured_persons'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'featured_publications';
  $fieldable_panels_pane_type->title = 'Featured Publications';
  $fieldable_panels_pane_type->description = '';
  $export['featured_publications'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'header';
  $fieldable_panels_pane_type->title = 'Header';
  $fieldable_panels_pane_type->description = '';
  $export['header'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'icon_blocks';
  $fieldable_panels_pane_type->title = 'Icon Blocks';
  $fieldable_panels_pane_type->description = 'If you want to create a list of icon, use this widget.';
  $export['icon_blocks'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'persons_grid';
  $fieldable_panels_pane_type->title = 'Persons grid';
  $fieldable_panels_pane_type->description = 'Grid display of persons (to display departments for example).';
  $export['persons_grid'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'quote';
  $fieldable_panels_pane_type->title = 'Quote';
  $fieldable_panels_pane_type->description = 'A wide image with an overlaid quote.';
  $export['quote'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'table';
  $fieldable_panels_pane_type->title = 'Table';
  $fieldable_panels_pane_type->description = 'Use this pane as a table.';
  $export['table'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'tabs_with_widgets';
  $fieldable_panels_pane_type->title = 'Tabs with Widgets';
  $fieldable_panels_pane_type->description = 'Basically allows you to create multiple tabs with different widgets inside.';
  $export['tabs_with_widgets'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'teaser';
  $fieldable_panels_pane_type->title = 'Teaser';
  $fieldable_panels_pane_type->description = 'Use teaser widget when you want to tease a iece of content with a title, description and a link (background images allowed).';
  $export['teaser'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'text';
  $fieldable_panels_pane_type->title = 'Text';
  $fieldable_panels_pane_type->description = 'A simple text widget.';
  $export['text'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'value_chain';
  $fieldable_panels_pane_type->title = 'Value Chain';
  $fieldable_panels_pane_type->description = 'If you want to create a value chain, use this widget.';
  $export['value_chain'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'visualization';
  $fieldable_panels_pane_type->title = 'Visualization';
  $fieldable_panels_pane_type->description = 'Use this content to create any type of charts, graphs, basically any visual component.';
  $export['visualization'] = $fieldable_panels_pane_type;

  return $export;
}
