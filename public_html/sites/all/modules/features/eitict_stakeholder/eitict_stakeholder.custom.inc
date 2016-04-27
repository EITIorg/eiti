<?php

/**
 * Implements hook_entity_view_alter().
 */
function eitict_stakeholder_entity_view_alter(&$build, $type) {
  if ($type != 'taxonomy_term') {
    return;
  }

  $page_term = $build['#term'];
  if ($page_term->vocabulary_machine_name != 'stakeholder_types') {
    return;
  }

  // Get an ordered list of terms.
  $terms_list = taxonomy_get_tree($page_term->vid, 0, 1, TRUE);
  $links = array();
  foreach ($terms_list as $weight => $term_object) {
    $entity_uri = entity_uri($type, $term_object);
    $links[] = array(
      'title' => entity_label($type, $term_object),
      'href' => $entity_uri['path'],
    );
  }

  $build['stakeholder_links'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#attributes' => array(
      'class' => array(
        'stakeholder-links',
      ),
    ),
    '#weight' => -99,
  );
}
