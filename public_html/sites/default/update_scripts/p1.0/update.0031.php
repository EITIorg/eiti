<?php

// Adjust the 6.1.a to 6.1.
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'score_req');
$query->propertyCondition('code', '6.1.a');
$results = $query->execute();

if (!empty($results['score_req'])) {
  $found_item = reset($results['score_req']);
  $found_entity = entity_load_single('score_req', $found_item->id);
  $found_entity->code = '6.1';
  entity_save('score_req', $found_entity);
}

// Adjust score requirements.
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'score_req');
$query->propertyCondition('code', '6.1.b');
$results = $query->execute();

if (!empty($results['score_req'])) {
  $found_item = reset($results['score_req']);
  $req_id = $found_item->id;

  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'score_req_value');
  $efq->propertyCondition('score_req_id', $found_item->id);
  $results = $efq->execute();

  if (!empty($results['score_req_value'])) {
    $entities = entity_load('score_req_value', array_keys($results['score_req_value']));
    foreach ($entities as $entity) {
      entity_delete('score_req_value', $entity->id);
    }
  }

  entity_delete('score_req', $found_item->id);
}
