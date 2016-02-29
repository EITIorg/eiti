<?php

/**
 * @file
 *
 * Holds classes related to the summary data import process.
 *
 */

class EITIIndicatorValuesMigration extends EITISpreadsheetMigration {

  /**
   * Overrides the default constructor.
   */
  public function __construct($arguments) {
    // We need to define some dummy sources that we'll populate later.
    $this->sourceFields['value_boolean'] = t('Value in: Boolean');
    $this->sourceFields['value_enum'] = t('Value in: Enum');
    $this->sourceFields['value_numeric'] = t('Value in: Numeric');
    $this->sourceFields['value_text'] = t('Value in: Text');
    $this->sourceFields['value_unit'] = t('Units');
    $this->sourceFields['original_value_numeric'] = t('Original Numeric Value.');
    $this->sourceFields['original_value_unit'] = t('Original Unit Value');

    parent::__construct($arguments);

    // Prepare the Source.
    if (isset($arguments['single_file'])) {
      $file = $arguments['single_file'];
      $real_path = drupal_realpath($file->uri);
      $real_paths = array($real_path);
    }
    else {
      $real_paths = $this->getSpreadsheetFiles();
    }

    // Check the validity.
    if (!$real_paths) {
      throw new MigrateException(t("No files in the system to import from."), Migration::MESSAGE_ERROR, MigrateMap::STATUS_FAILED);
    }
    $this->source = new EITIMigrateSourceSpreadsheet($real_paths, EITI_SOURCE_INDICATOR_VALUE);
    $this->destination = new EITIMigrateDestinationIndicatorValue();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'row_id' => array(
          'type' => 'varchar',
          'description' => t('Row ID'),
          'length' => 64,
          'not null' => TRUE,
          'default' => '',
         )
      ),
      EITIMigrateDestinationSummaryData::getKeySchema()
    );

    // Mappings go here.
    $this->addFieldMapping('indicator_id', 'subgroup');
    $this->addFieldMapping('value_boolean', 'value_boolean');
    $this->addFieldMapping('value_enum', 'value_enum');
    $this->addFieldMapping('value_numeric', 'value_numeric');
    $this->addFieldMapping('value_text', 'value_text');
    $this->addFieldMapping('value_unit', 'value_unit');
    $this->addFieldMapping('original_value_numeric', 'original_value_numeric');
    $this->addFieldMapping('original_value_unit', 'original_value_unit');
    $this->addFieldMapping('source', 'source');
    $this->addFieldMapping('comment', 'comment');

    // Now let's fetch the indicators and store those in our object.
    $groups = eitientity_indicator_get_by_bundle('group');
    $this->groupIndicators = $groups;

    $booleans = eitientity_indicator_get_by_bundle('boolean');
    $this->boolIndicators = $booleans;

    $numerics = eitientity_indicator_get_by_bundle('numeric');
    $this->numericIndicators = $numerics;

    $texts = eitientity_indicator_get_by_bundle('text');
    $this->textIndicators = $texts;

    $enums = eitientity_indicator_get_by_bundle('enum');
    $this->enumIndicators = $enums;

  }

  /**
   * Default prepare row function where we do some normalizations / data
   * massage.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // We'll need this a bit later for normalization.
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);
    $rate_to_usd = $summary_data_emw->currency_rate->value();

    // Let's try and find the group and subgroup (indicator).

    // If we need, we first find the group (but we don't really need that).
    $group_id = $this->findBestMatch($row->group, $this->groupIndicators);

    // Let's check for aliases..
    $row->subgroup = $this->normalizeIndicator($row->subgroup);

    // Now let's handle the subgroup (that's what we definitely need).
    $all_indicators = $this->boolIndicators + $this->numericIndicators + $this->textIndicators + $this->enumIndicators;
    $indicators_in_group = array();
    foreach ($all_indicators as $id => $indicator) {
      if ($indicator->parent == $group_id) {
        $indicators_in_group[$id] = $indicator;
      }
    }
    if ($indicator_id = $this->findBestMatch($row->subgroup, $indicators_in_group)) {
      $row->subgroup = $indicator_id;
      $indicator = $all_indicators[$indicator_id];

      $row->value_unit = $this->normalizeUnit($row->unit);
      $row->original_value_numeric = $row->entry;
      $row->original_value_unit = $this->normalizeUnit($row->unit);

      // Now let's handle the other values.
      switch ($indicator->type) {
        case 'numeric':
          $value = $row->entry;
          if (!is_numeric($value)) {
            if (!$this->checkEmptyValue($value)) {
              $msg = t('Indicator !name - Numeric expected, this value given instead: !value<br/>File: !file', array(
                '!value' => drupal_placeholder($row->entry),
                '!name' => '<strong>' . $indicator->name . '</strong>',
                '!file' => $row->file,
              ));
              $this->queueMessage($msg, MigrationBase::MESSAGE_NOTICE);
              return FALSE;
            }
            else {
              // $value = NULL;
              // $row->value_numeric = $value;
              $msg = t('Indicator !name - has an empty value. Skipping the item.<br/>File: !file', array(
                '!value' => drupal_placeholder($row->entry),
                '!name' => '<strong>' . $indicator->name . '</strong>',
                '!file' => $row->file,
              ));
              $this->queueMessage($msg, MigrationBase::MESSAGE_WARNING);
              return FALSE;
            }
          }
          else {
            // Transform the value and save it.
            $row->value_numeric = $this->normalizeValue($value, $row->value_unit, $rate_to_usd);
          }
          break;

        case 'boolean':
          $value = $this->getBooleanListValue($row->entry);
          if ($value == NULL) {
            $msg = t('Indicator !name - Boolean expected, this value given instead (treating as NULL): !value.<br />Skipping the item.<br/>File: !file', array(
              '!value' => drupal_placeholder($row->entry),
              '!name' => '<strong>' . $indicator->name . '</strong>',
              '!file' => $row->file,
            ));
            $this->queueMessage($msg, MigrationBase::MESSAGE_WARNING);
            return FALSE;
          }
          $row->value_boolean = $value;
          break;

        case 'text':
          $row->value_text = $row->entry;
          break;

        case 'enum':
          $value = $this->getBooleanListValue($row->entry);

          if ($value == NULL) {
            $msg = t('Indicator !name - Enum expected, this value given instead (treating as NULL): !value<br/>Skipping item.<br/>File: !file', array(
              '!value' => drupal_placeholder($row->entry),
              '!name' => '<strong>' . $indicator->name . '</strong>',
              '!file' => $row->file,
            ));
            $this->queueMessage($msg, MigrationBase::MESSAGE_WARNING);
            return FALSE;
          }
          $row->value_enum = $value;
          break;
      }
    }
    else {
      $msg = t('Indicator not found! Given indicator: !name<br/>File: !file', array(
        '!name' => '<strong>' . $row->subgroup . '</strong>',
        '!file' => $row->file,
      ));
      $this->queueMessage($msg, MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
  }

  /**
   * Pre-final callback which allows us both check and alter the entity
   * before it's actually saved in the database.
   */
  public function prepare($entity, $row) {
    // Extra data processing?
    // Not that we need to do anything here for now.
  }

  /**
   * Finally the entity is saved, we have the id and we can now do some
   * of the post-processing.
   */
  public function complete($entity, $row) {
    // One thing we need to do, is to look-up the summary_data id, load it and
    // save the indicator id in the field "field_sd_indicator_values".
    $summary_data_id = $this->handleSourceMigration('EITISummaryDataMigration', $row->summary_id);
    $summary_data = entity_load_single('summary_data', $summary_data_id);
    $summary_data_emw = entity_metadata_wrapper('summary_data', $summary_data);
    $summary_data_emw->field_sd_indicator_values[] = $entity->id;
    $summary_data_emw->save();
  }

}
