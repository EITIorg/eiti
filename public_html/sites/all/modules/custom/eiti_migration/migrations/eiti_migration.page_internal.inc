<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Class EITIInternalPageMigration
 *
 * The specific Pages to Internal Pages migration class.
 */
class EITIInternalPageMigration extends EITINodeMigration {
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['files_merged'] = t('Merged files.');
    $this->sourceFields['files_merged:description'] = t('Merged file description');

    // Default constructor.
    parent::__construct($arguments);

    // Now the mappings.
    $this->addFieldMapping('title_field', 'title', FALSE);
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('body', 'body', FALSE);
    $this->addFieldMapping('body:summary', 'body:summary', FALSE);
    $this->addFieldMapping('body:language', 'language', FALSE);

    $this->addFieldMapping('field_attachments', 'files_merged')
     ->sourceMigration(array('EITIIMCEFilesMigration', 'EITIPagesAttachedFilesMigration', 'EITIPagesUploadedFilesMigration'));
    $this->addFieldMapping('field_attachments:file_class')->defaultValue('MigrateFileFid');

    // Simple mappings
    // $this->addSimpleMappings(array('language, revision, log, body:language, body:format'));

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
      'field_image',
      'field_image_gallery',
      'field_image_caption',
      'field_attached_view',
      'field_taxonomy_related_subsite',
      'taxonomyextra',
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


  /**
   * Query for basic node fields from Drupal 7.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = parent::query();

    // Join with the "node access" table.
    $query->innerJoin('node_access', 'na', "na.nid = n.nid AND na.realm = 'content_access_rid'");

    return $query;
  }
}


/**
 * Class EITIPagesUploadedFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIPagesUploadedFilesMigration extends EITIDrupalFileMigration {
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
    // Only the ones used in the "page" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'page'");

    return $query;
  }
}



/**
 * Class EITIPagesFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIPagesAttachedFilesMigration extends EITIDrupalFileMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_page_files" fids.
    $query->innerJoin('field_data_field_page_files', 'fu', 'fu.field_page_files_fid = f.fid');
    // Only the ones used in the "page" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'page'");

    return $query;
  }
}


