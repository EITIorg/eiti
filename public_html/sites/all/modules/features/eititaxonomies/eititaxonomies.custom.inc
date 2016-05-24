<?php

/**
 * Implements hook_menu_alter().
 */
function eititaxonomies_menu_alter(&$items) {
  // Use custom callback for taxonomy term pages.
  $items['taxonomy/term/%taxonomy_term']['page callback'] = 'eititaxonomies_taxonomy_term_page';

  // Disable feed page.
  $items['taxonomy/term/%taxonomy_term/feed']['access callback'] = FALSE;
}

/**
 * Menu callback; displays all nodes associated with a term.
 *
 * @see: taxonomy_term_page().
 * @see: i18n_taxonomy_menu_alter().
 * @see: i18n_taxonomy_term_page().
 *
 * @param $term
 *   The taxonomy term.
 * @return
 *   The page content.
 */
function eititaxonomies_taxonomy_term_page($term) {
  if ($term->vocabulary_machine_name != 'stakeholder_types') {
    return i18n_taxonomy_term_page($term);
  }
  $term = i18n_taxonomy_localize_terms($term);

  $langcode = $GLOBALS['language_content']->language;

  // Assign the term name as the page title.
  drupal_set_title(t('Stakeholder @type', array('@type' => $term->name)));

  // Build breadcrumb based on the hierarchy of the term.
  $current = (object) array(
    'tid' => $term->tid,
  );
  // @todo This overrides any other possible breadcrumb and is a pure hard-coded
  //   presumption. Make this behavior configurable per vocabulary or term.
  $breadcrumb = array();
  while ($parents = taxonomy_get_parents($current->tid)) {
    $parents = i18n_taxonomy_localize_terms($parents);
    $current = array_shift($parents);
    $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
  }
  $breadcrumb[] = l(t('Home'), NULL);
  $breadcrumb = array_reverse($breadcrumb);
  drupal_set_breadcrumb($breadcrumb);
  // drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);

  // Get an ordered list of terms.
  $terms_list = taxonomy_get_tree($term->vid, 0, 1, TRUE);
  $links = array();
  foreach ($terms_list as $weight => $term_object) {
    $entity_uri = entity_uri('taxonomy_term', $term_object);
    $links[] = array(
      'title' => entity_label('taxonomy_term', $term_object),
      'href' => $entity_uri['path'],
    );
  }

  $term->stakehoder_listing = '';
  $term->stakehoder_listing .= theme('links', array(
    'links' => $links,
    'attributes' => array(
      'class' => array(
        'term-stakeholder-types',
      ),
    ),
  ));

  // Add the taxonomy nodes listing.
  // We need this inside the taxonomy display settings page.
  $term->stakehoder_listing .= views_embed_view('taxonomy_nodes', 'block', $term->tid);

  $build = array();

  $build['term_display'] = array(
    '#prefix' => '<div class="term-display">',
    '#suffix' => '</div>',
    'term' => taxonomy_term_view($term, 'full', $langcode),
  );

  return $build;
}
