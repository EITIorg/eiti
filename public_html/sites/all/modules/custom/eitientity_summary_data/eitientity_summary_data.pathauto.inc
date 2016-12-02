<?php

/**
 * Batch processing callback; Generate aliases for summary data.
 */
function eitientity_summary_data_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('eiti_summary_data', 'sd');
  $query->leftJoin('url_alias', 'ua', "CONCAT('summary_data/', sd.id) = ua.source");
  $query->addField('sd', 'id');
  $query->isNull('ua.source');
  $query->condition('sd.id', $context['sandbox']['current'], '>');
  $query->orderBy('sd.id');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'summary_data');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $ids = $query->execute()->fetchCol();

  eitientity_summary_data_update_alias_multiple($ids, 'bulkupdate');
  $context['sandbox']['count'] += count($ids);
  $context['sandbox']['current'] = max($ids);
  $context['message'] = t('Updated alias for Summary Data @id.', array('@id' => end($ids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}
