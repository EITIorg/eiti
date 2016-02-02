<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Class EITIPersonMigration
 *
 * The News to Article migration class.
 */
class EITIPersonMigration extends EITINodeMigration {
  public function __construct($arguments) {
    // Default constructor.
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('Migration used to migrate EITI Documents to the Document CT.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));

    // Now the mappings.
    $this->addFieldMapping('title_field', 'name');
    $this->addFieldMapping('title_field:language', 'language');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('body', 'field_contact_desc');
    $this->addFieldMapping('body:format', 'field_contact_desc:format')
      ->callbacks(array($this, 'mapFormat'));
    $this->addFieldMapping('body:language', 'language');

    // Now let's handle the paths.
    $this->removeFieldMapping('path', 'path');
    $this->addFieldMapping('migrate_redirects', 'path');
    $this->addFieldMapping('pathauto')
      ->description('We want to enable pathauto generated paths. Old ones are just redirects.')
      ->defaultValue(TRUE);

    // Now the mappings.
    $this->addFieldMapping('field_person_picture', 'field_contact_img')
      ->sourceMigration('EITIPersonPicturesMigration');
    $this->addFieldMapping('field_person_picture:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_person_picture:language', 'language');
    $this->addFieldMapping('field_person_picture:alt', 'field_contact_img:alt');
    $this->addFieldMapping('field_person_picture:title', 'field_contact_img:title');

    $this->addFieldMapping('field_board_member_type', 'field_board_member_type');
    $this->addFieldMapping('field_position', 'field_contact_role');
    $this->addFieldMapping('field_position:language', 'language');
    $this->addFieldMapping('field_position:create_term')
      ->defaultValue(TRUE);
    $this->addFieldMapping('field_position:ignore_case')
      ->defaultValue(TRUE);

     // Contacts.
    $this->addFieldMapping('field_email', 'field_contact_email');
    $this->addFieldMapping('field_phone_number', 'field_contact_phone');
    $this->addFieldMapping('field_fax_number', 'field_contact_fax');
    $this->addFieldMapping('field_website', 'field_contact_site');
    $this->addFieldMapping('field_website:title', 'field_contact_site:title');
    $this->addFieldMapping('field_website:attributes', 'field_contact_site:attributes');
    $this->addFieldMapping('field_related_country', 'field_ref_country_name_2');

    $this->addSimpleMappings(array('field_board_membership'));

    // Unmigrated sources.
    $this->addUnmigratedSources(array(
      'field_contact_type',
      'field_contact_file',
      'field_contact_org',
      'field_weight',
      'upload',
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
    // Make sure both values are used if one's missing: body vs field_contact_desc.
    if (empty($row->field_contact_desc)) {
      $row->field_contact_desc = $row->body;
    }

    // Do the same with the name vs title.
    if (empty($row->name)) {
      $row->name = $row->title;
    }

    // Populate the board membership.
    if (empty($row->field_board_member_type)) {
      $row->field_board_membership = 0;
    }
    else if (empty($row->field_alternates) || $row->field_alternates[0] == 0) {
      $row->field_board_membership = 1;
    }
    else {
      $row->field_board_membership = 2;
    }

    // Default to English always.
    $row->language = ($row->language == LANGUAGE_NONE) ? 'en' : $row->language;

    // Let's take care of the countries.
    if (!empty($row->field_ref_country_name_2)) {
      $row->field_ref_country_name_2 = $this->fetchSourceReferencedNodesCountry($row->field_ref_country_name_2);
    }
    return TRUE;
  }

  /**
   * Helper function that returns array of country-iso2s.
   */
  protected function fetchSourceReferencedNodesCountry($nids) {
    $countries = array();
    $exceptions = array(
      'Democratic Republic of Congo' => 'CD',
      "Côte d'Ivoire" => 'CI'
    );
    $query = Database::getConnection('default', $this->arguments['source_connection'])->select('node', 'n');
    $query->fields('n');
    $query->condition('nid', $nids, 'IN');
    $query->condition('status', 1);
    $query->leftJoin('field_data_field_country_info', 'fc', 'fc.entity_id = n.nid');
    $query->fields('fc');
    $query->leftJoin('field_data_field_taxonomy_countries', 'fx', 'fx.entity_id = n.nid');
    $query->fields('fx');
    $results = $query->execute();
    foreach ($results as $result) {
      $continue = FALSE;
      // In case that the country ISO2 is NO, it probably was left as default value, let's
      // try and check out the taxonomy reference value instead.
      if (empty($result->field_country_info_iso2) || $result->field_country_info_iso2 == 'NO') {
        $country_vocabulary_vid = 9;
        $terms = $this->fetchSourceTerm($country_vocabulary_vid, array($result->field_taxonomy_countries_tid));
        if (!empty($terms)) {
          $term = array_pop($terms);
          $country = countries_country_lookup($term->name, 'name');
          if (!empty($country)) {
            $countries[] = $country->iso2;
          }
          elseif (in_array($term->name, array_keys($exceptions))) {
            $countries[] = $exceptions[$term->name];
          }
        }
        else {
          $continue = TRUE;
        }
      }

      // Now the 2nd part.
      if (!empty($result->field_country_info_iso2) || $continue) {
        $countries[] = $result->field_country_info_iso2;
      }
    }
    $countries = array_unique($countries);
    return $countries;
  }
}

/**
 * Class EITIPersonPicturesMigration
 *
 * This class helps us migrate attached files from the legacy to the new system.
 */
class EITIPersonPicturesMigration extends DrupalFile7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }

  /**
   * Overriding the default query.
   */
  protected function query() {
    $query = parent::query();

    // Get only the "field_data_field_contact_img" fids.
    $query->innerJoin('field_data_field_contact_img', 'ff', 'ff.field_contact_img_fid = f.fid');
    // Only the ones used in the "eiti_document" nodes.
    $query->innerJoin('node', 'n', "n.nid = ff.entity_id AND n.type = 'contact'");

    return $query;
  }
}
