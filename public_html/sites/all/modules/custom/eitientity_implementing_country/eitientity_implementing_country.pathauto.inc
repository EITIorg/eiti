<?php

/**
 * Batch processing callback; Generate aliases for implementing countries.
 */
function eitientity_implementing_country_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('eiti_implementing_country', 'ic');
  $query->leftJoin('url_alias', 'ua', "CONCAT('implementing_country/', ic.id) = ua.source");
  $query->addField('ic', 'id');
  $query->isNull('ua.source');
  $query->condition('ic.id', $context['sandbox']['current'], '>');
  $query->orderBy('ic.id');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'implementing_country');

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

  eitientity_implementing_country_update_alias_multiple($ids, 'bulkupdate');
  $context['sandbox']['count'] += count($ids);
  $context['sandbox']['current'] = max($ids);
  $context['message'] = t('Updated alias for Implementing Country @id.', array('@id' => end($ids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}
