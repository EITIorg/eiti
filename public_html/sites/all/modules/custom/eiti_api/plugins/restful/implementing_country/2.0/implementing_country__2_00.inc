<?php

$plugin = array(
  'label' => t('Implementing Country'),
  'resource' => 'implementing_country',
  'name' => 'implementing_country__2_00',
  'entity_type' => 'implementing_country',
  'bundle' => 'normal',
  'description' => t('Fetch all implementing country entities.'),
  'class' => 'EITIApiImplementingCountry2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
