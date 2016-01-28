<?php

$plugin = array(
  'label' => t('Indicator Values'),
  'resource' => 'indicator_value',
  'name' => 'indicator_value__1_00',
  'entity_type' => 'indicator_value',
  'description' => t('Fetch all indicator values entities.'),
  'class' => 'EITIApiIndicatorValue',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
