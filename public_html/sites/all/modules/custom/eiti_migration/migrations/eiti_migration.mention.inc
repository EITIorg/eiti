<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Class EITIMentionMigration
 *
 * The News to Article migration class.
 */
class EITIMentionMigration extends EITINodeMigration {
  public function __construct($arguments) {
    // Default constructor.
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('Migration used to migrate EITI In the News to the Mention CT.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));

    // Now the mappings.
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');
    $this->addFieldMapping('language', 'language', FALSE);
    $this->addFieldMapping('body', 'field_news_description', FALSE);
    $this->addFieldMapping('body:language', 'language', FALSE);

    // Now let's handle the paths.
    $this->removeFieldMapping('path', 'path');
    $this->addFieldMapping('migrate_redirects', 'path');
    $this->addFieldMapping('pathauto', 'pathauto', FALSE)
    ->description('We want to enable pathauto generated paths. Old ones are just redirects.')
    ->defaultValue(TRUE);

    // Now the mappings.
    $this->addFieldMapping('field_source_link:title', 'field_news_source:title');
    $this->addFieldMapping('field_source_link', 'field_news_link');
    $this->addFieldMapping('field_published_date', 'field_news_date');

    // Simple mappings
    // $this->addSimpleMappings(array('language, revision, log, body:language, body:format'));

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
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

    // Default to English always.
    $row->language = ($row->language == LANGUAGE_NONE) ? 'en' : $row->language;

    return TRUE;
  }
}
