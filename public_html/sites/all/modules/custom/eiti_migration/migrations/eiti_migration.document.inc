<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Class EITIDocumentMigration
 *
 * The News to Article migration class.
 */
class EITIDocumentMigration extends EITINodeMigration {
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['files_merged'] = t('Merged files.');
    $this->sourceFields['files_merged:description'] = t('Merged file description');

    // Default constructor.
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('Migration used to migrate EITI Documents to the Document CT.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));

    // Now the mappings.
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');
    $this->addFieldMapping('language', 'language', FALSE);
    $this->addFieldMapping('body', 'field_document_desc', FALSE);
    $this->addFieldMapping('body:format', 'field_document_desc:format', FALSE)
     ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('body:summary', 'field_teaser', FALSE);
    $this->addFieldMapping('body:language', 'language', FALSE);

    // Now let's handle the paths.
    $this->removeFieldMapping('path', 'path');
    $this->addFieldMapping('migrate_redirects', 'path');
    $this->addFieldMapping('pathauto', 'pathauto', FALSE)
    ->description('We want to enable pathauto generated paths. Old ones are just redirects.')
    ->defaultValue(TRUE);

    // Now the mappings.
    $this->addFieldMapping('field_doc_image_preview', 'field_document_img')
      ->sourceMigration('EITIDocumentFilesPreviewMigration');
    $this->addFieldMapping('field_doc_image_preview:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_doc_image_preview:language', 'language');
    $this->addFieldMapping('field_doc_image_preview:alt', 'field_document_img:alt');
    $this->addFieldMapping('field_doc_image_preview:title', 'field_document_img:title');

    $this->addFieldMapping('field_attachments', 'files_merged')
     ->sourceMigration(array('EITIDocumentUploadFilesMigration', 'EITIDocumentAttachmentsMigration'));
    $this->addFieldMapping('field_attachments:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_attachments:language', 'language');

    $this->addFieldMapping('field_document_category', 'field_taxonomy_resource_category')
      ->sourceMigration('EITITaxonomyResouceCategoryMigration');
    $this->addFieldMapping('field_document_category:description', 'field_document_file:description');
    $this->addFieldMapping('field_document_category:source_type')
      ->defaultValue('tid');

    // Simple mappings
    // $this->addSimpleMappings(array('language, revision, log, body:language, body:format'));

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
      'field_weight',
      'body',
      'body:summary',
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
    $field_document_files = (!empty($row->field_document_file)) ? $row->field_document_file : array();
    $merged_files = array_merge($upload_files, $field_document_files);
    $row->files_merged = $merged_files;

    // Default to English always.
    $row->language = ($row->language == LANGUAGE_NONE) ? 'en' : $row->language;

    return TRUE;
  }
}

/**
 * Class EITIDocumentFilesPreviewMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIDocumentFilesPreviewMigration extends DrupalFile7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_data_field_document_img" fids.
    $query->innerJoin('field_data_field_document_img', 'ff', 'ff.field_document_img_fid = f.fid');
    // Only the ones used in the "eiti_document" nodes.
    $query->innerJoin('node', 'n', "n.nid = ff.entity_id AND n.type = 'eiti_document'");

    return $query;
  }
}

/**
 * Class EITIDocumentAttachmentsMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIDocumentAttachmentsMigration extends DrupalFile7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_data_field_document_file" fids.
    $query->innerJoin('field_data_field_document_file', 'ff', 'ff.field_document_file_fid = f.fid');
    // Only the ones used in the "eiti_document" nodes.
    $query->innerJoin('node', 'n', "n.nid = ff.entity_id AND n.type = 'eiti_document'");

    return $query;
  }
}

/**
 * Class EITIDocumentUploadFilesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIDocumentUploadFilesMigration extends DrupalFile7Migration {
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
    // Only the ones used in the "eiti_document" nodes.
    $query->innerJoin('node', 'n', "n.nid = fu.entity_id AND n.type = 'eiti_document'");

    return $query;
  }
}
