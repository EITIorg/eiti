<?php

$plugin = array(
  'label' => t('Indicator'),
  'resource' => 'indicator',
  'name' => 'indicator__2_00',
  'entity_type' => 'indicator',
  'description' => t('Fetch all indicator entities.'),
  'class' => 'EITIApiIndicator2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
