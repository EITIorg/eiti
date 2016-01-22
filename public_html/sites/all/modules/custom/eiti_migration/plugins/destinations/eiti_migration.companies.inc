<?php


class EITIMigrateDestinationCompanies extends MigrateDestinationEntity {
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
  public function __construct(array $options = array()) {
    parent::__construct('company', 'company', $options);
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

    $fields['name'] = t('Company Name.');
    $fields['country_id'] = t('Country where the company is from.');
    $fields['status'] = t('Company Status.');
    $fields['created'] = t('Timestamp when the company was created.');
    $fields['changed'] = t('Timestamp when the company was changed.');

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
    entity_delete_multiple('company', $ids);
    $this->completeRollback($ids);
    migrate_instrument_stop('entity_delete_multiple');
  }

  /**
   * Import a single company entity.
   *
   * @param $entity
   *  Entity object to build. Prefilled with any fields mapped in the Migration.
   * @param $row
   *  Raw source data object - passed through to prepare/complete handlers.
   * @return array
   *  Array of key fields (id only in this case) of the company that was saved if
   *  successful. FALSE on failure.
   */
  public function import(stdClass $entity, stdClass $row) {
    // Set some default properties.
    $defaults = array(
      'type' => 'company',
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
    MigrateDestinationEntity::fieldAttachValidate('company', $entity);

    migrate_instrument_start('entity_save');
    entity_save('company', $entity);
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
