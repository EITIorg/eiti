<?php

/**
 * Batch processing callback; Generate aliases for organisation.
 */
function eitientity_organisation_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('eiti_organisation', 'org');
  $query->leftJoin('url_alias', 'ua', "CONCAT('organization/', org.id) = ua.source");
  $query->addField('org', 'id');
  $query->isNull('ua.source');
  $query->condition('org.id', $context['sandbox']['current'], '>');
  $query->orderBy('org.id');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'organisation');

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

  eitientity_organisation_update_alias_multiple($ids, 'bulkupdate');
  $context['sandbox']['count'] += count($ids);
  $context['sandbox']['current'] = max($ids);
  $context['message'] = t('Updated alias for Organisation @id.', array('@id' => end($ids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}
