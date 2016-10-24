<?php

$plugin = array(
  'label' => t('Country Status'),
  'resource' => 'country_status',
  'name' => 'country_status__1_00',
  'entity_type' => 'taxonomy_term',
  'bundle' => 'country_status',
  'description' => t('Export the "country_status" taxonomy term.'),
  'class' => 'EITIApiTermCountryStatus',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
