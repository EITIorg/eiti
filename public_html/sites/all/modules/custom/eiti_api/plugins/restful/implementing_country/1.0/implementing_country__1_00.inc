<?php

$plugin = array(
  'label' => t('Implementing Country'),
  'resource' => 'implementing_country',
  'name' => 'implementing_country__1_00',
  'entity_type' => 'implementing_country',
  'bundle' => 'normal',
  'description' => t('Fetch all implementing countries entities.'),
  'class' => 'EITIApiImplementingCountry',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
