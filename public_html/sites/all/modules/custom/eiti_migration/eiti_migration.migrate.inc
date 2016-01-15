<?php
/**
 * @file
 * This is where we define / register all of the migrations.
 */

/**
 * Implements hook_migrate_api().
 */
function eiti_migration_migrate_api() {
  // Make a check if user has specified the legacy settings before registering
  // the migrations.
  $legacy_database = variable_get('eiti_migration_db_name', '');
  $legacy_username = variable_get('eiti_migration_db_user_name', '');
  $legacy_password = variable_get('eiti_migration_db_user_pass', '');
  $legacy_public = variable_get('eiti_migration_files_public', '');
  if ($legacy_database == '' || $legacy_username == '' || $legacy_password == '') {
    drupal_set_message('Please <a href="admin/content/migrate/configure-legacy">configure the Legacy System settings</a> on this machine before you run or register your migrations. Make sure you complete all the fields.');
    return array();
  }

  // The basics go here.
  $migrations = array(
    'api' => 2,
    'groups' => array(
      'core' => array(
        'title' => t('Core Migrations: Users, Taxonomies, others'),
      ),
      'articles' => array(
        'title' => t('Migration to the Article CT'),
      ),
      'documents' => array(
        'title' => t('Migration to the Document CT'),
      ),
      'persons' => array(
        'title' => t('Migration to the Person CT'),
      ),
      'mentions' => array(
        'title' => t('Migration to the Mention CT'),
      ),
      'spreadsheets' => array(
        'title' => t('Migration of spreadsheets (Reports) to custom entities.'),
      ),
    ),
  );

  // Migrations themselves go here.
  $migrations['migrations'] = array();

  // #################################
  // ######## CORE MIGRATIONS ########
  // #################################
  // Core Migrations include: users, taxonomies.
  $migrations['migrations']['EITIUserPictureMigration'] = array(
    'class_name' => 'DrupalPicture7Migration',
    'group_name' => 'core',
    'description' => t('Migrate user Pictures.'),
    'destination_dir' => 'public://pictures',
    'source_dir' => $legacy_public,
  );
  $migrations['migrations']['EITIUsersMigration'] = array(
    'class_name' => 'EITIUsersMigration',
    'group_name' => 'core',
    'description' => t('Migrate users.'),
    'picture_migration' => 'EITIUserPictureMigration',
    'dependencies' => array('EITIUserPictureMigration'),
  );
  $migrations['migrations']['EITITaxonomyTagsNewsMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_news',
    'destination_vocabulary' => 'tags',
    'description' => t('Migrate news tags (tags_news) to one common tags vocabulary.'),
  );
  $migrations['migrations']['EITITaxonomyTagsBlogMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_blog',
    'destination_vocabulary' => 'tags',
    'description' => t('Migrate news tags (tags_news) to one common tags vocabulary.'),
  );
  $migrations['migrations']['EITITaxonomyTagsEventsMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'tags_events',
    'destination_vocabulary' => 'tags',
    'description' => t('Migrate news tags (tags_news) to one common tags vocabulary.'),
  );
  $migrations['migrations']['EITITaxonomyResouceCategoryMigration'] = array(
    'class_name' => 'DrupalTerm7Migration',
    'group_name' => 'core',
    'soft_dependencies' => array('EITIUsersMigration'),
    'source_vocabulary' => 'resource_category',
    'destination_vocabulary' => 'document_category',
    'description' => t('Migrate the resource category tags to document category.'),
  );

  // ####################################
  // ######## ARTICLE MIGRATIONS ########
  // ####################################
  // Article Migrations goes here: News articles, Blog Posts and Events.

  // But first, files.
  $migrations['migrations']['EITINewsFeaturedImageMigration'] = array(
    'class_name' => 'EITINewsFeaturedImageMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://',
    'bundle' => 'image',
    'description' => t('Migrates the Featured Images from the Legacy System (2 fields to one).'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIBlogFeaturedImageMigration'] = array(
    'class_name' => 'EITIBlogFeaturedImageMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://',
    'bundle' => 'image',
    'description' => t('Migrates the Featured Images from the Legacy System (2 fields to one).'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIEventFeaturedImageMigration'] = array(
    'class_name' => 'EITIEventFeaturedImageMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://',
    'bundle' => 'image',
    'description' => t('Migrates the Featured Images from the Legacy System (2 fields to one).'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITINewsImageGalleryMigration'] = array(
    'class_name' => 'EITINewsImageGalleryMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://image_gallery',
    'bundle' => 'image',
    'description' => t('Migrates the Gallery-related Images from the Legacy System (2 fields to one).'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIBlogImageGalleryMigration'] = array(
    'class_name' => 'EITIBlogImageGalleryMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://image_gallery',
    'bundle' => 'image',
    'description' => t('Migrates the Gallery-related Images from the Legacy System (2 fields to one).'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITINewsAttachedFilesMigration'] = array(
    'class_name' => 'EITINewsAttachedFilesMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Attached Files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITINewsUploadFilesMigration'] = array(
    'class_name' => 'EITINewsUploadFilesMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Upload field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIBlogUploadFilesMigration'] = array(
    'class_name' => 'EITIBlogUploadFilesMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Upload field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIEventUploadFilesMigration'] = array(
    'class_name' => 'EITIEventUploadFilesMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Upload field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIIMCEFilesMigration'] = array(
    'class_name' => 'EITIIMCEFilesMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'description' => t('Migrates the IMCE files.'),
    'dependencies' => array('EITIUsersMigration'),
  );

  // Now, nodes themselves.
  $migrations['migrations']['EITINewsToArticleMigration'] = array(
    'class_name' => 'EITINewsToArticleMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'file_migration' => 'EITIIMCEFilesMigration',
    'source_type' => 'news',
    'destination_type' => 'article',
    'description' => t('Migration responsible for migrating news articles to the article content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
      'EITIIMCEFilesMigration',
      'EITINewsFeaturedImageMigration',
      'EITINewsImageGalleryMigration',
      'EITINewsUploadFilesMigration',
      'EITINewsAttachedFilesMigration',
      'EITITaxonomyTagsNewsMigration'
    ),
  );
  $migrations['migrations']['EITIBlogToArticleMigration'] = array(
    'class_name' => 'EITIBlogToArticleMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'file_migration' => 'EITIIMCEFilesMigration',
    'source_type' => 'blog',
    'destination_type' => 'article',
    'description' => t('Migration responsible for migrating blog posts to the article content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
      'EITIIMCEFilesMigration',
      'EITIBlogFeaturedImageMigration',
      'EITIBlogImageGalleryMigration',
      'EITIBlogUploadFilesMigration',
      'EITITaxonomyTagsBlogMigration'
    ),
  );
  $migrations['migrations']['EITIEventsToArticleMigration'] = array(
    'class_name' => 'EITIEventsToArticleMigration',
    'group_name' => 'articles',
    'user_migration' => 'EITIUsersMigration',
    'file_migration' => 'EITIIMCEFilesMigration',
    'source_type' => 'event',
    'destination_type' => 'article',
    'description' => t('Migration responsible for migrating event nodes to the article content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
      'EITIIMCEFilesMigration',
      'EITIEventFeaturedImageMigration',
      'EITIEventUploadFilesMigration',
      'EITITaxonomyTagsEventsMigration'
    ),
  );

  // #####################################
  // ######## DOCUMENT MIGRATIONS ########
  // #####################################
  // Document Migrations goes here.
  $migrations['migrations']['EITIDocumentUploadFilesMigration'] = array(
    'class_name' => 'EITIDocumentUploadFilesMigration',
    'group_name' => 'documents',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Upload field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIDocumentFilesPreviewMigration'] = array(
    'class_name' => 'EITIDocumentFilesPreviewMigration',
    'group_name' => 'documents',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://document_preview',
    'bundle' => 'document',
    'description' => t('Migrates the Image Previews field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIDocumentAttachmentsMigration'] = array(
    'class_name' => 'EITIDocumentAttachmentsMigration',
    'group_name' => 'documents',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://documents',
    'bundle' => 'document',
    'description' => t('Migrates the Document File field files.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIDocumentMigration'] = array(
    'class_name' => 'EITIDocumentMigration',
    'group_name' => 'documents',
    'user_migration' => 'EITIUsersMigration',
    'file_migration' => 'EITIIMCEFilesMigration',
    'source_type' => 'eiti_document',
    'destination_type' => 'document',
    'description' => t('Migration responsible for migrating eiti_document nodes to the document content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
      'EITIIMCEFilesMigration',
      'EITITaxonomyResouceCategoryMigration',
      'EITIDocumentUploadFilesMigration',
      'EITIDocumentAttachmentsMigration',
      'EITIDocumentFilesPreviewMigration',
    ),
  );

  // ###################################
  // ######## PERSON MIGRATIONS ########
  // ###################################
  $migrations['migrations']['EITIPersonPicturesMigration'] = array(
    'class_name' => 'EITIPersonPicturesMigration',
    'group_name' => 'persons',
    'user_migration' => 'EITIUsersMigration',
    'skip_pictures' => TRUE,
    'source_dir' => $legacy_public,
    'destination_dir' => 'public://person_picture',
    'bundle' => 'image',
    'description' => t('Migrates the images from the Contact legacy-ct to Person CT.'),
    'dependencies' => array('EITIUsersMigration'),
  );
  $migrations['migrations']['EITIPersonMigration'] = array(
    'class_name' => 'EITIPersonMigration',
    'group_name' => 'persons',
    'user_migration' => 'EITIUsersMigration',
    'file_migration' => 'EITIIMCEFilesMigration',
    'source_type' => 'contact',
    'destination_type' => 'person',
    'description' => t('Migration responsible for migrating contact nodes to the person content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
      'EITIIMCEFilesMigration',
      'EITIPersonPicturesMigration',
    ),
  );

  // #####################################
  // ######## MENTIONS MIGRATIONS ########
  // #####################################
  // Mentions Migrations goes here: In the News CT to Mentions.
  $migrations['migrations']['EITIMentionMigration'] = array(
    'class_name' => 'EITIMentionMigration',
    'group_name' => 'mentions',
    'user_migration' => 'EITIUsersMigration',
    'source_type' => 'in_the_news',
    'destination_type' => 'mention',
    'description' => t('Migration responsible for migrating In the News nodes to the mention content-type.'),
    'soft_dependencies' => array(
      'EITIUsersMigration',
    ),
  );

  // ###################################################
  // ######## SPREADSHEETS / REPORTS MIGRATIONS ########
  // ###################################################
  $migrations['migrations']['EITISummaryDataMigration'] = array(
    'class_name' => 'EITISummaryDataMigration',
    'group_name' => 'spreadsheets',
    'description' => t('Migrates the Summary Data from the specified spreadsheets.'),
  );

  // Add legacy database key.
  foreach($migrations['migrations'] as $key => $migration) {
    // Add the connection only to the groups we want to opt in.
    $opt_in_groups = array('core', 'articles', 'documents', 'persons', 'mentions');
    if (in_array($migration['group_name'], $opt_in_groups)) {
      $migrations['migrations'][$key]['source_database'] = array(
        'driver'   => 'mysql',
        'database' => $legacy_database,
        'username' => $legacy_username,
        'password' => $legacy_password,
        'host'     => 'localhost',
        'prefix'   => '',
      );
      $migrations['migrations'][$key]['source_version'] = '7';
      $migrations['migrations'][$key]['source_connection'] = 'legacy';
    }
  }

  // And some handlers.
  $migrations['destination handlers'] = array(
    'EITIMigrateRedirectEntityHandler',
  );

  return $migrations;
}
