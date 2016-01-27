<?php


class EITIMigrateDestinationRevenues extends MigrateDestinationEntity {
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
   * @param array $options
   *  Options applied to entities.
   */
  public function __construct($bundle, array $options = array()) {
    parent::__construct('revenue_stream', $bundle, $options);
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

    $fields['gfs_code_id'] = t('GFS code ID.');
    $fields['report_status'] = t('Report status.');
    $fields['name'] = t('Name.');
    $fields['organisation_id'] = t('Organization ID.');

    $fields['revenue'] = t('Revenue in numbers.');
    $fields['currency'] = t('Currency used in the report.');
    $fields['original_revenue'] = t('Original Revenue in numbers.');
    $fields['original_currency'] = t('Original Currency used in the report.');

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
    entity_delete_multiple('revenue_stream', $ids);
    $this->completeRollback($ids);
    migrate_instrument_stop('entity_delete_multiple');
  }

  /**
   * Import a single indicator_value entity.
   *
   * @param $entity
   *  Entity object to build. Prefilled with any fields mapped in the Migration.
   * @param $row
   *  Raw source data object - passed through to prepare/complete handlers.
   * @return array
   *  Array of key fields (id only in this case) of the indicator_value that was saved if
   *  successful. FALSE on failure.
   */
  public function import(stdClass $entity, stdClass $row) {
    $defaults = array(
      'type' => $this->getBundle(),
      'status' => NODE_PUBLISHED,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
    );
    foreach ($defaults as $field => $value) {
      if (!isset($entity->$field)) {
        $entity->$field = $value;
      }
    }

    // Set some default properties.
    $this->prepare($entity, $row);

    // Know if we're updating or not.
    if (isset($entity->id) && $entity->id) {
      $updating = TRUE;
    }
    else {
      $updating = FALSE;
    }

    // Validate field data prior to saving.
    MigrateDestinationEntity::fieldAttachValidate('revenue_stream', $entity);

    migrate_instrument_start('entity_save');
    entity_save('revenue_stream', $entity);
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
