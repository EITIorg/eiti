<?php

$plugin = array(
  'label' => t('Country Status'),
  'resource' => 'country_status',
  'name' => 'country_status__2_00',
  'entity_type' => 'taxonomy_term',
  'bundle' => 'country_status',
  'description' => t('Export the "country_status" taxonomy term.'),
  'class' => 'EITIApiTermCountryStatus2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
