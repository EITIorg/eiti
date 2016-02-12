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
  $fieldable_panels_pane_type->name = 'featured_bookmarks';
  $fieldable_panels_pane_type->title = 'Featured Bookmarks';
  $fieldable_panels_pane_type->description = 'Featured bookmarks go here (also known as Media Section).';
  $export['featured_bookmarks'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'key_facts';
  $fieldable_panels_pane_type->title = 'Key Facts';
  $fieldable_panels_pane_type->description = 'Widget that contains a couple of key facts.';
  $export['key_facts'] = $fieldable_panels_pane_type;

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
  $fieldable_panels_pane_type->name = 'visualization';
  $fieldable_panels_pane_type->title = 'Visualization';
  $fieldable_panels_pane_type->description = '...';
  $export['visualization'] = $fieldable_panels_pane_type;

  $fieldable_panels_pane_type = new stdClass();
  $fieldable_panels_pane_type->disabled = FALSE; /* Edit this to true to make a default fieldable_panels_pane_type disabled initially */
  $fieldable_panels_pane_type->api_version = 1;
  $fieldable_panels_pane_type->name = 'wide_image';
  $fieldable_panels_pane_type->title = 'Wide Image';
  $fieldable_panels_pane_type->description = '';
  $export['wide_image'] = $fieldable_panels_pane_type;

  return $export;
}
