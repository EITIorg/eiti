<?php

$plugin = array(
  'label' => t('GFS Codes'),
  'resource' => 'gfs_code',
  'name' => 'gfs_code__2_00',
  'entity_type' => 'gfs_code',
  'description' => t('Fetch all gfs code entities.'),
  'class' => 'EITIApiGFSCode2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
