<?php


class EITIMigrateDestinationSummaryData extends MigrateDestinationEntity {
  /**
   * Static function that returns the schema field that identifies a destination
   * entity.
   */
  static public function getKeySchema() {
    return array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'description' => 'ID of destination entity',
      ),
    );
  }

  /**
   * Basic initialization
   *
   * @param string $bundle
   *  Bundle of the summary data.
   * @param array $options
   *  Options applied to entities.
   */
  public function __construct($bundle, array $options = array()) {
    parent::__construct('summary_data', $bundle, $options);
  }


  /**
   * Returns a list of fields available to be mapped for the node type (bundle)
   *
   * @param Migration $migration
   *  Optionally, the migration containing this destination.
   * @return array
   *  Keys: machine names of the fields (to be passed to addFieldMapping)
   *  Values: Human-friendly descriptions of the fields.
   */
  public function fields($migration = NULL) {
    $fields = array();

    $fields['country_id'] = t('Implementing country ID.');
    $fields['year_start'] = t('Starting year of the report.');
    $fields['year_end'] = t('Ending year of the report.');
    $fields['published'] = t('Report\'s publish date.');
    $fields['currency_code'] = t('Currency ID for the summary data (Default: USD).');
    $fields['currency_rate'] = t('Conversion rate (1 $ = ?) (Default: 1).');
    $fields['status'] = t('Is the report published or now (Default: Published).');
    $fields['created'] = t('Timestamp of summary data creation (Default: Now).');
    $fields['changed'] = t('Timestamp of the change of the summary data (Default: Now).');
    $fields['company_id_name'] = t('Company identifier name');
    $fields['company_id_register'] = t('Company identifier register');
    $fields['company_id_register_url'] = t('Company identifier register url');

    // Then add in anything provided by handlers
    $fields += migrate_handler_invoke_all('Entity', 'fields', $this->entityType, $this->bundle, $migration);

    return $fields;
  }

  /**
   * Delete a batch of nodes at once.
   *
   * @param $nids
   *  Array of node IDs to be deleted.
   */
  public function bulkRollback(array $ids) {
    migrate_instrument_start('entity_delete_multiple');
    $this->prepareRollback($ids);
    entity_delete_multiple('summary_data', $ids);
    $this->completeRollback($ids);
    migrate_instrument_stop('entity_delete_multiple');
  }

  /**
   * Import a single summary data entity.
   *
   * @param $entity
   *  Entity object to build. Prefilled with any fields mapped in the Migration.
   * @param $row
   *  Raw source data object - passed through to prepare/complete handlers.
   * @return array
   *  Array of key fields (id only in this case) of the summary data that was saved if
   *  successful. FALSE on failure.
   */
  public function import(stdClass $entity, stdClass $row) {
    if (!empty($row->migrate_map_destid1)) {
      $entity->id = $row->migrate_map_destid1;
    }

    // Set some default properties.
    $defaults = array(
      'type' => $this->bundle,
      'currency_code' => 'USD',
      'currency_rate' => '1',
      'status' => NODE_PUBLISHED,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
    );
    foreach ($defaults as $field => $value) {
      if (!isset($entity->$field)) {
        $entity->$field = $value;
      }
    }

    $this->prepare($entity, $row);

    // Know if we're updating or not.
    if (isset($entity->id) && $entity->id) {
      $updating = TRUE;
    }
    else {
      $updating = FALSE;
    }

    // Make sure our class is here.
    if (!$entity instanceof SummaryDataEntity) {
      $entity = new SummaryDataEntity((array) $entity, 'summary_data');
    }

    // Validate field data prior to saving.
    MigrateDestinationEntity::fieldAttachValidate('summary_data', $entity);

    migrate_instrument_start('entity_save');
    entity_save('summary_data', $entity);
    migrate_instrument_stop('entity_save');

    if (isset($entity->id) && $entity->id > 0) {
      $this->complete($entity, $row);
      $return = array($entity->id);

      if ($updating) {
        $this->numUpdated++;
      }
      else {
        $this->numCreated++;
      }
    }
    else {
      $return = FALSE;
    }
    return $return;
  }
}
