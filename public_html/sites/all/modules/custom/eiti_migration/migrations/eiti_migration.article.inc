<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Class EITIGenericToArticleMigration
 *
 * The generic migration class to Article CT. News, Blog Posts & Events migrations
 * should implement this class.
 */
abstract class EITIGenericToArticleMigration extends EITINodeMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('This is a demo migration used to show how we can grab data from different sheets.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));

    // Now the mappings.
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');
    $this->addFieldMapping('body:language', 'language', FALSE);

    // Now let's handle the paths.
    $this->removeFieldMapping('path', 'path');
    $this->addFieldMapping('migrate_redirects', 'path');
    $this->addFieldMapping('pathauto', 'pathauto', FALSE)
      ->description('We want to enable pathauto generated paths. Old ones are just redirects.')
      ->defaultValue(TRUE);
  }
}

/**
 * Class EITINewsToArticleMigration
 *
 * The News to Article migration class.
 */
class EITINewsToArticleMigration extends EITIGenericToArticleMigration {
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['files_merged'] = t('Merged files.');
    $this->sourceFields['files_merged:description'] = t('Merged file description');

    // Default constructor.
    parent::__construct($arguments);

    // Now the mappings.
    $this->addFieldMapping('field_article_type')
      ->defaultValue('news');
    $this->addFieldMapping('field_featured_image', 'field_image')
      ->sourceMigration('EITINewsFeaturedImageMigration');
    $this->addFieldMapping('field_featured_image:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('body:summary', 'field_teaser', FALSE);

    $this->addFieldMapping('field_image_gallery', 'field_image_gallery')
      ->sourceMigration('EITINewsImageGalleryMigration');
    $this->addFieldMapping('field_image_gallery:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_attachments', 'files_merged')
     ->sourceMigration(array('EITINewsUploadFilesMigration', 'EITINewsAttachedFilesMigration'));
    $this->addFieldMapping('field_attachments:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_tags', 'field_taxonomy_tags_news')
      ->sourceMigration('EITITaxonomyTagsNewsMigration');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_related_country', 'field_taxonomy_countries');

    // Simple mappings
    // $this->addSimpleMappings(array('language, revision, log, body:language, body:format'));

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
      'field_support_company',
      'field_taxonomy_related_subsite',
    ));

    $this->addUnmigratedDestinations(array(
      'field_event_date',
      'field_event_location',
    ));

    // Note: This is migrated in a separate file migration.
    $this->addUnmigratedSources(array('field_image_caption'));
  }

  /**
   * Simple row preparation.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Now let's play with the country field.
    $exceptions = array(
      'Democratic Republic of Congo' => 'CD',
      "Côte d'Ivoire" => 'CI'
    );
    if (!empty($row->field_taxonomy_countries)) {
      $country_vocabulary_vid = 9;
      $terms = $this->fetchSourceTerm($country_vocabulary_vid, $row->field_taxonomy_countries);
      // Reset and repopulate.
      $row->field_taxonomy_countries = array();
      foreach ($terms as $term) {
        $country = countries_country_lookup($term->name, 'name');
        if (!empty($country)) {
          $row->field_taxonomy_countries[] = $country->iso2;
        }
        elseif (in_array($term->name, array_keys($exceptions))) {
          $row->field_taxonomy_countries[] = $exceptions[$term->name];
        }
      }
    }

    // Merge files together.
    $upload_files = (!empty($row->upload)) ? $row->upload : array();
    $field_news_files = (!empty($row->field_news_file)) ? $row->field_news_file : array();
    $merged_files = array_merge($upload_files, $field_news_files);
    $row->files_merged = $merged_files;

    return TRUE;
  }
}

/**
 * Class EITIBlogToArticleMigration
 *
 * The Blog to Article migration class.
 */
class EITIBlogToArticleMigration extends EITIGenericToArticleMigration {
  public function __construct($arguments) {
    // Default constructor.
    parent::__construct($arguments);

    // Now the mappings.
    $this->addFieldMapping('field_article_type')
      ->defaultValue('blog');
    $this->addFieldMapping('field_featured_image', 'field_image')
      ->sourceMigration('EITIBlogFeaturedImageMigration');
    $this->addFieldMapping('field_featured_image:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('body:summary', 'field_teaser', FALSE);

    $this->addFieldMapping('field_image_gallery', 'field_image_gallery')
      ->sourceMigration('EITIBlogImageGalleryMigration');
    $this->addFieldMapping('field_image_gallery:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_attachments', 'upload')
     ->sourceMigration('EITIBlogUploadFilesMigration');
    $this->addFieldMapping('field_attachments:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_tags', 'field_taxonomy_tags_blog')
      ->sourceMigration('EITITaxonomyTagsBlogMigration');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_related_country', 'field_taxonomy_countries');

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
      'field_support_company',
      'field_taxonomy_related_subsite',
    ));

    $this->addUnmigratedDestinations(array(
      'field_event_date',
      'field_event_location',
    ));

    // Note: This is migrated in a separate file migration.
    $this->addUnmigratedSources(array('field_image_caption'));
  }

  /**
   * Simple row preparation.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Merge files together.
    $upload_files = (!empty($row->upload)) ? $row->upload : array();
    $field_news_files = (!empty($row->field_news_file)) ? $row->field_news_file : array();
    $merged_files = array_merge($upload_files, $field_news_files);
    $row->files_merged = $merged_files;

    // Now let's play with the country field.
    $exceptions = array(
      'Democratic Republic of Congo' => 'CD',
      "Côte d'Ivoire" => 'CI'
    );
    if (!empty($row->field_taxonomy_countries)) {
      $country_vocabulary_vid = 9;
      $terms = $this->fetchSourceTerm($country_vocabulary_vid, $row->field_taxonomy_countries);
      // Reset and repopulate.
      $row->field_taxonomy_countries = array();
      foreach ($terms as $term) {
        $country = countries_country_lookup($term->name, 'name');
        if (!empty($country)) {
          $row->field_taxonomy_countries[] = $country->iso2;
        }
        elseif (in_array($term->name, array_keys($exceptions))) {
          $row->field_taxonomy_countries[] = $exceptions[$term->name];
        }
      }
    }

    return TRUE;
  }

}

/**
 * Class EITIEventsToArticleMigration
 *
 * The Blog to Article migration class.
 */
class EITIEventsToArticleMigration extends EITIGenericToArticleMigration {
  public function __construct($arguments) {
    // Default constructor.
    parent::__construct($arguments);

    // Now the mappings.
    $this->addFieldMapping('field_article_type')
      ->defaultValue('event');
    $this->addFieldMapping('field_featured_image', 'field_image')
      ->sourceMigration('EITIEventFeaturedImageMigration');
    $this->addFieldMapping('field_featured_image:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('body:summary', 'body:summary', FALSE);

    $this->addFieldMapping('field_attachments', 'upload')
     ->sourceMigration('EITIEventUploadFilesMigration');
    $this->addFieldMapping('field_attachments:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_tags', 'field_taxonomy_tags_events')
      ->sourceMigration('EITITaxonomyTagsEventsMigration');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');

    // Event specific things go here.
    $this->addFieldMapping('field_event_date', 'field_event_start');
    $this->addFieldMapping('field_event_date:to', 'field_event_start:value2');
    $this->addFieldMapping('field_event_location', 'field_event_location');

    $this->addUnmigratedDestinations(array(
      'field_countries',
    ));
  }

  /**
   * Simple row preparation.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Merge files together.
    $upload_files = (!empty($row->upload)) ? $row->upload : array();
    $field_news_files = (!empty($row->field_news_file)) ? $row->field_news_file : array();
    $merged_files = array_merge($upload_files, $field_news_files);
    $row->files_merged = $merged_files;

    return TRUE;
  }
}

/**
 * Class EITINewsFeaturedImageMigration
 *
 * This class helps us migrate correctly the featured images (and adding the caption as title to them).
 */
class EITINewsFeaturedImageMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_file_image_title_text', 'field_image_caption_value')
         ->defaultValue('');
    $this->addFieldMapping('field_file_image_title_text:language', 'language')
         ->defaultValue('en');
    $this->addFieldMapping('field_file_image_alt_text', 'field_image_caption_value')
         ->defaultValue('');
    $this->addFieldMapping('field_file_image_alt_text:language', 'language')
         ->defaultValue('en');
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_image" fids.
    $query->innerJoin('field_data_field_image', 'fi', 'fi.field_image_fid = f.fid');

    // Only the ones used in the "news" nodes.
    $query->innerJoin('node', 'n', "n.nid = fi.entity_id AND n.type = 'news'");

    // And add the captions when available.
    $query->leftJoin('field_data_field_image_caption', 'fic', 'fic.entity_id = fi.entity_id AND fic.revision_id = fi.revision_id');
    $query->fields('fic', array('field_image_caption_value'));
    $query->fields('n', array('language'));
    $query->fields('f', array('fid', 'uid', 'filename', 'uri', 'filemime', 'filesize', 'status', 'timestamp'));

    return $query;
  }

  /**
   * Overriding the default.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // Remove the tags.
    $row->field_image_caption_value = drupal_html_to_text($row->field_image_caption_value);
  }
}

/**
 * Class EITIBlogFeaturedImageMigration
 *
 * This class helps us migrate correctly the featured images (and adding the caption as title to them).
 */
class EITIBlogFeaturedImageMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_file_image_title_text', 'field_image_caption_value')
         ->defaultValue('');
    $this->addFieldMapping('field_file_image_title_text:language', 'language')
         ->defaultValue('en');
    $this->addFieldMapping('field_file_image_alt_text', 'field_image_caption_value')
         ->defaultValue('');
    $this->addFieldMapping('field_file_image_alt_text:language', 'language')
         ->defaultValue('en');
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_image" fids.
    $query->innerJoin('field_data_field_image', 'fi', 'fi.field_image_fid = f.fid');

    // Only the ones used in the "blog" nodes.
    $query->innerJoin('node', 'n', "n.nid = fi.entity_id AND n.type = 'blog'");

    // And add the captions when available.
    $query->leftJoin('field_data_field_image_caption', 'fic', 'fic.entity_id = fi.entity_id AND fic.revision_id = fi.revision_id');
    $query->fields('fic', array('field_image_caption_value'));
    $query->fields('n', array('language'));
    $query->fields('f', array('fid', 'uid', 'filename', 'uri', 'filemime', 'filesize', 'status', 'timestamp'));

    return $query;
  }

  /**
   * Overriding the default.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // Remove the tags.
    $row->field_image_caption_value = drupal_html_to_text($row->field_image_caption_value);
  }
}
/**
 * Class EITIEventFeaturedImageMigration
 *
 * This class helps us migrate correctly the featured images (and adding the caption as title to them).
 */
class EITIEventFeaturedImageMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_image" fids.
    $query->innerJoin('field_data_field_image', 'fi', 'fi.field_image_fid = f.fid');

    // Only the ones used in the "event" nodes.
    $query->innerJoin('node', 'n', "n.nid = fi.entity_id AND n.type = 'event'");

    // And add the captions when available.
    $query->fields('n', array('language'));
    $query->fields('f', array('fid', 'uid', 'filename', 'uri', 'filemime', 'filesize', 'status', 'timestamp'));

    return $query;
  }
}

/**
 * Class EITINewsImageGalleryMigration
 *
 * This class helps us migrate image galleries from the legacy to the new system.
 */
class EITINewsImageGalleryMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_image_gallery" fids.
    $query->innerJoin('field_data_field_image_gallery', 'fg', 'fg.field_image_gallery_fid = f.fid');

    // Only the ones used in the "news" nodes.
    $query->innerJoin('node', 'n', "n.nid = fg.entity_id AND n.type = 'news'");

    return $query;
  }
}

/**
 * Class EITIBlogImageGalleryMigration
 *
 * This class helps us migrate image galleries from the legacy to the new system.
 */
class EITIBlogImageGalleryMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_image_gallery" fids.
    $query->innerJoin('field_data_field_image_gallery', 'fg', 'fg.field_image_gallery_fid = f.fid');

    // Only the ones used in the "blog" nodes.
    $query->innerJoin('node', 'n', "n.nid = fg.entity_id AND n.type = 'blog'");

    return $query;
  }
}


/**
 * Class EITINewsAttachedFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITINewsAttachedFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_data_field_news_file" fids.
    $query->innerJoin('field_data_field_news_file', 'ff', 'ff.field_news_file_fid = f.fid');
    // Only the ones used in the "news" nodes.
    $query->innerJoin('node', 'n', "n.nid = ff.entity_id AND n.type = 'news'");

    return $query;
  }

  public function complete($entity, $row) {
    if ($entity->type == 'report') {
      $entity->type = 'document';
      file_save($entity);
    }
  }
}

/**
 * Class EITIIMCEFilesMigration
 *
 * This class helps us IMCE files from the legacy to the new system.
 */
class EITIIMCEFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "IMCE" fids.
    $query->innerJoin('file_usage', 'fu', "f.fid = fu.fid AND fu.module = 'imce'");

    return $query;
  }

  /**
   * Complete function.
   */
  public function complete($entity, $row) {
    if ($entity->type == 'report') {
      $entity->type = 'document';
      file_save($entity);
    }
  }
}


/**
 * Class EITINewsUploadFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITINewsUploadFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "upload" fids.
    $query->innerJoin('field_data_upload', 'fu', 'fu.upload_fid = f.fid');
    // Only the ones used in the "news" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'news'");

    return $query;
  }

  public function complete($entity, $row) {
    if ($entity->type == 'report') {
      $entity->type = 'document';
      file_save($entity);
    }
  }
}

/**
 * Class EITIBlogUploadFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIBlogUploadFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "upload" fids.
    $query->innerJoin('field_data_upload', 'fu', 'fu.upload_fid = f.fid');
    // Only the ones used in the "blog" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'blog'");

    return $query;
  }

  public function complete($entity, $row) {
    if ($entity->type == 'report') {
      $entity->type = 'document';
      file_save($entity);
    }
  }
}

/**
 * Class EITIEventUploadFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIEventUploadFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "upload" fids.
    $query->innerJoin('field_data_upload', 'fu', 'fu.upload_fid = f.fid');
    // Only the ones used in the "event" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'event'");

    return $query;
  }

  public function complete($entity, $row) {
    if ($entity->type == 'report') {
      $entity->type = 'document';
      file_save($entity);
    }
  }
}


