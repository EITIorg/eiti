<?php

$plugin = array(
  'label' => t('Indicator'),
  'resource' => 'indicator',
  'name' => 'indicator__1_00',
  'entity_type' => 'indicator',
  'description' => t('Fetch all indicator entities.'),
  'class' => 'EITIApiIndicator',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
