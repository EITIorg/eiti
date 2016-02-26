<?php
/**
 * @file
 * eitipermissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eitipermissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media',
  );

  // Exported permission: 'access rules debug'.
  $permissions['access rules debug'] = array(
    'name' => 'access rules debug',
    'roles' => array(),
    'module' => 'rules',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'admin_display_suite'.
  $permissions['admin_display_suite'] = array(
    'name' => 'admin_display_suite',
    'roles' => array(),
    'module' => 'ds',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer advanced pane settings'.
  $permissions['administer advanced pane settings'] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer entity translation'.
  $permissions['administer entity translation'] = array(
    'name' => 'administer entity translation',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: 'administer entityqueue'.
  $permissions['administer entityqueue'] = array(
    'name' => 'administer entityqueue',
    'roles' => array(),
    'module' => 'entityqueue',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(),
    'module' => 'field_group',
  );

  // Exported permission: 'administer file types'.
  $permissions['administer file types'] = array(
    'name' => 'administer file types',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: 'administer files'.
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
    'module' => 'image',
  );

  // Exported permission: 'administer languages'.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: 'administer less'.
  $permissions['administer less'] = array(
    'name' => 'administer less',
    'roles' => array(),
    'module' => 'less',
  );

  // Exported permission: 'administer media browser'.
  $permissions['administer media browser'] = array(
    'name' => 'administer media browser',
    'roles' => array(),
    'module' => 'media',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer page manager'.
  $permissions['administer page manager'] = array(
    'name' => 'administer page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: 'administer pane access'.
  $permissions['administer pane access'] = array(
    'name' => 'administer pane access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer panelizer'.
  $permissions['administer panelizer'] = array(
    'name' => 'administer panelizer',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panels layouts'.
  $permissions['administer panels layouts'] = array(
    'name' => 'administer panels layouts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer panels styles'.
  $permissions['administer panels styles'] = array(
    'name' => 'administer panels styles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer phpexcel'.
  $permissions['administer phpexcel'] = array(
    'name' => 'administer phpexcel',
    'roles' => array(),
    'module' => 'phpexcel',
  );

  // Exported permission: 'administer redirects'.
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'redirect',
  );

  // Exported permission: 'administer restful'.
  $permissions['administer restful'] = array(
    'name' => 'administer restful',
    'roles' => array(),
    'module' => 'restful',
  );

  // Exported permission: 'administer rules'.
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(),
    'module' => 'rules',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(),
    'module' => 'search',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'advanced migration information'.
  $permissions['advanced migration information'] = array(
    'name' => 'advanced migration information',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
    ),
    'module' => 'migrate',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'bypass file access'.
  $permissions['bypass file access'] = array(
    'name' => 'bypass file access',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'bypass rules access'.
  $permissions['bypass rules access'] = array(
    'name' => 'bypass rules access',
    'roles' => array(),
    'module' => 'rules',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'change layouts in place editing'.
  $permissions['change layouts in place editing'] = array(
    'name' => 'change layouts in place editing',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'configure tablefield'.
  $permissions['configure tablefield'] = array(
    'name' => 'configure tablefield',
    'roles' => array(),
    'module' => 'tablefield',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create bookmark content'.
  $permissions['create bookmark content'] = array(
    'name' => 'create bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create document content'.
  $permissions['create document content'] = array(
    'name' => 'create document content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create files'.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'create mention content'.
  $permissions['create mention content'] = array(
    'name' => 'create mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create person content'.
  $permissions['create person content'] = array(
    'name' => 'create person content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'path',
  );

  // Exported permission: 'currency.currency.administer'.
  $permissions['currency.currency.administer'] = array(
    'name' => 'currency.currency.administer',
    'roles' => array(),
    'module' => 'currency',
  );

  // Exported permission: 'currency.currency_exchanger.administer'.
  $permissions['currency.currency_exchanger.administer'] = array(
    'name' => 'currency.currency_exchanger.administer',
    'roles' => array(),
    'module' => 'currency',
  );

  // Exported permission: 'currency.currency_locale_pattern.administer'.
  $permissions['currency.currency_locale_pattern.administer'] = array(
    'name' => 'currency.currency_locale_pattern.administer',
    'roles' => array(),
    'module' => 'currency',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any audio files'.
  $permissions['delete any audio files'] = array(
    'name' => 'delete any audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any bookmark content'.
  $permissions['delete any bookmark content'] = array(
    'name' => 'delete any bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any document content'.
  $permissions['delete any document content'] = array(
    'name' => 'delete any document content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any document files'.
  $permissions['delete any document files'] = array(
    'name' => 'delete any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any image files'.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any mention content'.
  $permissions['delete any mention content'] = array(
    'name' => 'delete any mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any person content'.
  $permissions['delete any person content'] = array(
    'name' => 'delete any person content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any report files'.
  $permissions['delete any report files'] = array(
    'name' => 'delete any report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any video files'.
  $permissions['delete any video files'] = array(
    'name' => 'delete any video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own audio files'.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own bookmark content'.
  $permissions['delete own bookmark content'] = array(
    'name' => 'delete own bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own document content'.
  $permissions['delete own document content'] = array(
    'name' => 'delete own document content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own document files'.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own mention content'.
  $permissions['delete own mention content'] = array(
    'name' => 'delete own mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own person content'.
  $permissions['delete own person content'] = array(
    'name' => 'delete own person content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own report files'.
  $permissions['delete own report files'] = array(
    'name' => 'delete own report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own video files'.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
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

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(),
    'module' => 'admin_menu',
  );

  // Exported permission: 'download any audio files'.
  $permissions['download any audio files'] = array(
    'name' => 'download any audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any document files'.
  $permissions['download any document files'] = array(
    'name' => 'download any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any image files'.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any report files'.
  $permissions['download any report files'] = array(
    'name' => 'download any report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any video files'.
  $permissions['download any video files'] = array(
    'name' => 'download any video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own audio files'.
  $permissions['download own audio files'] = array(
    'name' => 'download own audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own document files'.
  $permissions['download own document files'] = array(
    'name' => 'download own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own image files'.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own report files'.
  $permissions['download own report files'] = array(
    'name' => 'download own report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own video files'.
  $permissions['download own video files'] = array(
    'name' => 'download own video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any audio files'.
  $permissions['edit any audio files'] = array(
    'name' => 'edit any audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any bookmark content'.
  $permissions['edit any bookmark content'] = array(
    'name' => 'edit any bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any document content'.
  $permissions['edit any document content'] = array(
    'name' => 'edit any document content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any document files'.
  $permissions['edit any document files'] = array(
    'name' => 'edit any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any image files'.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any mention content'.
  $permissions['edit any mention content'] = array(
    'name' => 'edit any mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any person content'.
  $permissions['edit any person content'] = array(
    'name' => 'edit any person content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any report files'.
  $permissions['edit any report files'] = array(
    'name' => 'edit any report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any video files'.
  $permissions['edit any video files'] = array(
    'name' => 'edit any video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own audio files'.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own bookmark content'.
  $permissions['edit own bookmark content'] = array(
    'name' => 'edit own bookmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own document content'.
  $permissions['edit own document content'] = array(
    'name' => 'edit own document content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own document files'.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own mention content'.
  $permissions['edit own mention content'] = array(
    'name' => 'edit own mention content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own person content'.
  $permissions['edit own person content'] = array(
    'name' => 'edit own person content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own report files'.
  $permissions['edit own report files'] = array(
    'name' => 'edit own report files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own video files'.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
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

  // Exported permission: 'export tablefield'.
  $permissions['export tablefield'] = array(
    'name' => 'export tablefield',
    'roles' => array(),
    'module' => 'tablefield',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'gfs_code entity administer'.
  $permissions['gfs_code entity administer'] = array(
    'name' => 'gfs_code entity administer',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_gfs_code',
  );

  // Exported permission: 'gfs_code entity view'.
  $permissions['gfs_code entity view'] = array(
    'name' => 'gfs_code entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_gfs_code',
  );

  // Exported permission: 'helpergeneric access taxonomy'.
  $permissions['helpergeneric access taxonomy'] = array(
    'name' => 'helpergeneric access taxonomy',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'helpergeneric',
  );

  // Exported permission: 'helpergeneric administer menus'.
  $permissions['helpergeneric administer menus'] = array(
    'name' => 'helpergeneric administer menus',
    'roles' => array(),
    'module' => 'helpergeneric',
  );

  // Exported permission: 'helpergeneric administer settings'.
  $permissions['helpergeneric administer settings'] = array(
    'name' => 'helpergeneric administer settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'helpergeneric',
  );

  // Exported permission: 'helpergeneric administer urls'.
  $permissions['helpergeneric administer urls'] = array(
    'name' => 'helpergeneric administer urls',
    'roles' => array(),
    'module' => 'helpergeneric',
  );

  // Exported permission: 'helpergeneric administer users'.
  $permissions['helpergeneric administer users'] = array(
    'name' => 'helpergeneric administer users',
    'roles' => array(),
    'module' => 'helpergeneric',
  );

  // Exported permission: 'indicator entity administer'.
  $permissions['indicator entity administer'] = array(
    'name' => 'indicator entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_indicator',
  );

  // Exported permission: 'indicator entity view'.
  $permissions['indicator entity view'] = array(
    'name' => 'indicator entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_indicator',
  );

  // Exported permission: 'indicator_value entity administer'.
  $permissions['indicator_value entity administer'] = array(
    'name' => 'indicator_value entity administer',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_indicator_value',
  );

  // Exported permission: 'indicator_value entity view'.
  $permissions['indicator_value entity view'] = array(
    'name' => 'indicator_value entity view',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eitientity_indicator_value',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'manipulate all entityqueues'.
  $permissions['manipulate all entityqueues'] = array(
    'name' => 'manipulate all entityqueues',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'entityqueue',
  );

  // Exported permission: 'manipulate entityqueues'.
  $permissions['manipulate entityqueues'] = array(
    'name' => 'manipulate entityqueues',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'entityqueue',
  );

  // Exported permission: 'migration information'.
  $permissions['migration information'] = array(
    'name' => 'migration information',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
    ),
    'module' => 'migrate',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'rebuild tablefield'.
  $permissions['rebuild tablefield'] = array(
    'name' => 'rebuild tablefield',
    'roles' => array(),
    'module' => 'tablefield',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'revenue_stream entity administer'.
  $permissions['revenue_stream entity administer'] = array(
    'name' => 'revenue_stream entity administer',
    'roles' => array(
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity create'.
  $permissions['revenue_stream entity create'] = array(
    'name' => 'revenue_stream entity create',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity delete'.
  $permissions['revenue_stream entity delete'] = array(
    'name' => 'revenue_stream entity delete',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity edit'.
  $permissions['revenue_stream entity edit'] = array(
    'name' => 'revenue_stream entity edit',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revenue_stream entity view'.
  $permissions['revenue_stream entity view'] = array(
    'name' => 'revenue_stream entity view',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'eitientity_revenue_stream',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'toggle field translatability'.
  $permissions['toggle field translatability'] = array(
    'name' => 'toggle field translatability',
    'roles' => array(),
    'module' => 'entity_translation',
  );

  // Exported permission: 'translate any entity'.
  $permissions['translate any entity'] = array(
    'name' => 'translate any entity',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'entity_translation',
  );

  // Exported permission: 'translate file entities'.
  $permissions['translate file entities'] = array(
    'name' => 'translate file entities',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'entity_translation',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'locale',
  );

  // Exported permission: 'translate node entities'.
  $permissions['translate node entities'] = array(
    'name' => 'translate node entities',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'entity_translation',
  );

  // Exported permission: 'update scripts manage'.
  $permissions['update scripts manage'] = array(
    'name' => 'update scripts manage',
    'roles' => array(),
    'module' => 'update_scripts',
  );

  // Exported permission: 'update scripts run task scripts'.
  $permissions['update scripts run task scripts'] = array(
    'name' => 'update scripts run task scripts',
    'roles' => array(),
    'module' => 'update_scripts',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(),
    'module' => 'search',
  );

  // Exported permission: 'use ctools import'.
  $permissions['use ctools import'] = array(
    'name' => 'use ctools import',
    'roles' => array(),
    'module' => 'ctools',
  );

  // Exported permission: 'use ipe with page manager'.
  $permissions['use ipe with page manager'] = array(
    'name' => 'use ipe with page manager',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use media wysiwyg'.
  $permissions['use media wysiwyg'] = array(
    'name' => 'use media wysiwyg',
    'roles' => array(),
    'module' => 'media_wysiwyg',
  );

  // Exported permission: 'use page manager'.
  $permissions['use page manager'] = array(
    'name' => 'use page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: 'use panels caching features'.
  $permissions['use panels caching features'] = array(
    'name' => 'use panels caching features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels dashboard'.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'use panels in place editing'.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels locks'.
  $permissions['use panels locks'] = array(
    'name' => 'use panels locks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use text format clean_summary'.
  $permissions['use text format clean_summary'] = array(
    'name' => 'use text format clean_summary',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'view files'.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own files'.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own private files'.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view pane admin links'.
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'view private files'.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'internal editor' => 'internal editor',
      'translation editor' => 'translation editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  return $permissions;
}
