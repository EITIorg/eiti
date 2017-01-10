<?php


class EITIMigrateDestinationIndicatorValue extends MigrateDestinationEntity {
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
    parent::__construct('indicator_value', 'ignore', $options);
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

    $fields['indicator_id'] = t('Indicator ID.');
    $fields['value_boolean'] = t('Boolean value..');
    $fields['value_enum'] = t('Enum value');
    $fields['value_numeric'] = t('Numeric value.');
    $fields['value_unit'] = t('Units in which the values were saved.');
    $fields['original_value_numeric'] = t('Original numeric value.');
    $fields['original_value_unit'] = t('Original value for units.');
    $fields['value_text'] = t('Text value.');
    $fields['source'] = t('Source for this value.');
    $fields['comment'] = t('Comment left for the value.');

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
    entity_delete_multiple('indicator_value', $ids);
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
    // Set some default properties.
    $this->prepare($entity, $row);

    // Know if we're updating or not.
    if (isset($entity->id) && $entity->id) {
      $updating = TRUE;
    }
    else {
      $updating = FALSE;
    }

    // Make sure our class is here.
    if (!$entity instanceof IndicatorValueEntity) {
      $entity = new IndicatorValueEntity((array) $entity, 'indicator_value');
    }

    // Validate field data prior to saving.
    MigrateDestinationEntity::fieldAttachValidate('indicator_value', $entity);

    migrate_instrument_start('entity_save');
    entity_save('indicator_value', $entity);
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
