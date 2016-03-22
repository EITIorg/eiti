<?php
//49,"External indicators","null","group"
//50,"Extractives",49,"text"
//51,"GDP",49,"text"
//52,"Aid",49,"text"
//53,"FDI",49,"text"
//54,"Remittances",49,"text"
//55,"Total Gov Revenue",49,"text"

$external_indicator_group = "External indicators";
$external_indicators = array(
  "Extractives",
  "GDP",
  "Aid",
  "FDI",
  "Remittances",
  "Total Gov Revenue"
);

// Create the indicator group.
$indicator = array(
  'status' => NODE_PUBLISHED,
  'created' => REQUEST_TIME,
  'type' => 'group',
  'name' => $external_indicator_group,
);
$indicator = entity_create('indicator', $indicator);
$indicator->save();
$group_id = $indicator->id;

// Create all other indicators.
foreach ($external_indicators as $external_indicator) {
  $indicator = array(
    'status' => NODE_PUBLISHED,
    'created' => REQUEST_TIME,
    'type' => 'numeric',
    'name' => $external_indicator,
    'parent' => $group_id,
  );
  $indicator = entity_create('indicator', $indicator);
  $indicator->save();
}
