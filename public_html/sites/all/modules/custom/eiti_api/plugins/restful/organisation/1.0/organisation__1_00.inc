<?php

$plugin = array(
  'label' => t('Organisations'),
  'resource' => 'organisation',
  'name' => 'organisation__1_00',
  'entity_type' => 'organisation',
  'description' => t('Fetch all organisation entities.'),
  'class' => 'EITIApiOrganisation',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
