<?php

// Here is where we just want to update the existing indicators.
$indicators_to_text = array(
  'Public registry of licences, oil',
  'Public registry of licences, mining',
);

$query = db_update('eiti_indicator');
$query->fields(array(
  'type' => 'text',
));
$query->condition('name', $indicators_to_text, 'IN');
$query->execute();
