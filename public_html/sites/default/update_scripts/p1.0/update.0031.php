<?php

// Adjust score requirements.
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'score_req');
$query->propertyCondition('code', '6.1.b');
$results = $query->execute();

if (!empty($results['score_req'])) {
  $found_item = reset($results['score_req']);
  entity_delete('score_req', $found_item->id);
}

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
