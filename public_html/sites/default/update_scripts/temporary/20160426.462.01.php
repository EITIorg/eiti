<?php

/* Let's create some new indicators, if those don't exist */
$new_indicators = array();
$new_indicators[] = array(
  'id' => 70,
  'name' => "Copper, volume",
  'parent' => 6,
  'type' => "numeric",
);
$new_indicators[] = array(
  'id' => 71,
  'name' => "Gold, volume",
  'parent' => 6,
  'type' => "numeric",
);
$new_indicators[] = array(
  'id' => 72,
  'name' => "Coal, volume",
  'parent' => 6,
  'type' => "numeric",
);
$new_indicators[] = array(
  'id' => 73,
  'name' => "Copper, volume",
  'parent' => 9,
  'type' => "numeric",
);
$new_indicators[] = array(
  'id' => 74,
  'name' => "Gold, volume",
  'parent' => 9,
  'type' => "numeric",
);
$new_indicators[] = array(
  'id' => 75,
  'name' => "Coal, volume",
  'parent' => 9,
  'type' => "numeric",
);

/* Loop and create the values */
foreach ($new_indicators as $new_indicator) {
  $new_indicator_values = array(
      'status' => NODE_PUBLISHED,
      'created' => REQUEST_TIME,
    ) + $new_indicator;

  /** @var IndicatorEntity $new_entity */
  $new_entity = entity_create('indicator', $new_indicator_values);
  $new_entity->save();
}
