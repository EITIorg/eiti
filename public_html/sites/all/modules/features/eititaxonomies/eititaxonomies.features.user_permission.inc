<?php

/**
 * @file
 * eititaxonomies.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eititaxonomies_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in board_decision_bases'.
  $permissions['delete terms in board_decision_bases'] = array(
    'name' => 'delete terms in board_decision_bases',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in board_decision_keywords'.
  $permissions['delete terms in board_decision_keywords'] = array(
    'name' => 'delete terms in board_decision_keywords',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in bookmark_type'.
  $permissions['delete terms in bookmark_type'] = array(
    'name' => 'delete terms in bookmark_type',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in company_commodities'.
  $permissions['delete terms in company_commodities'] = array(
    'name' => 'delete terms in company_commodities',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in company_sectors'.
  $permissions['delete terms in company_sectors'] = array(
    'name' => 'delete terms in company_sectors',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in document_category'.
  $permissions['delete terms in document_category'] = array(
    'name' => 'delete terms in document_category',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in person_positions'.
  $permissions['delete terms in person_positions'] = array(
    'name' => 'delete terms in person_positions',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in board_decision_bases'.
  $permissions['edit terms in board_decision_bases'] = array(
    'name' => 'edit terms in board_decision_bases',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in board_decision_keywords'.
  $permissions['edit terms in board_decision_keywords'] = array(
    'name' => 'edit terms in board_decision_keywords',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in bookmark_type'.
  $permissions['edit terms in bookmark_type'] = array(
    'name' => 'edit terms in bookmark_type',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in company_commodities'.
  $permissions['edit terms in company_commodities'] = array(
    'name' => 'edit terms in company_commodities',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in company_sectors'.
  $permissions['edit terms in company_sectors'] = array(
    'name' => 'edit terms in company_sectors',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in document_category'.
  $permissions['edit terms in document_category'] = array(
    'name' => 'edit terms in document_category',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in person_positions'.
  $permissions['edit terms in person_positions'] = array(
    'name' => 'edit terms in person_positions',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'translate taxonomy_term entities'.
  $permissions['translate taxonomy_term entities'] = array(
    'name' => 'translate taxonomy_term entities',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'entity_translation',
  );

  // Exported permission: 'view unpublished taxonomy terms'.
  $permissions['view unpublished taxonomy terms'] = array(
    'name' => 'view unpublished taxonomy terms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'termstatus',
  );

  return $permissions;
}
