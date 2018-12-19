<?php

$plugin = array(
  'label' => t('Revenues'),
  'resource' => 'revenue',
  'name' => 'revenue__2_00',
  'entity_type' => 'revenue_stream',
  'description' => t('Fetch all revenue stream entities.'),
  'class' => 'EITIApiRevenueStreams2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
