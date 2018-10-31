<?php

$plugin = array(
  'label' => t('Organisations'),
  'resource' => 'organisation',
  'name' => 'organisation__2_00',
  'entity_type' => 'organisation',
  'description' => t('Fetch all organisation entities.'),
  'class' => 'EITIApiOrganisation2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
  'formatter' => 'eiti_json',
);
