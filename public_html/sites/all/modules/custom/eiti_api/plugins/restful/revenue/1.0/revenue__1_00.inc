<?php

$plugin = array(
  'label' => t('Revenues'),
  'resource' => 'revenue',
  'name' => 'revenue__1_00',
  'entity_type' => 'revenue_stream',
  'description' => t('Fetch all revenue stream entities.'),
  'class' => 'EITIApiRevenueStreams',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
