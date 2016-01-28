<?php

$plugin = array(
  'label' => t('GFS Codes'),
  'resource' => 'gfs_code',
  'name' => 'gfs_code__1_00',
  'entity_type' => 'gfs_code',
  'description' => t('Fetch all gfs code entities.'),
  'class' => 'EITIApiGFSCode',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
