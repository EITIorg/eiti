<?php

$plugin = array(
  'label' => t('Summary Data'),
  'resource' => 'summary_data',
  'name' => 'summary_data__1_00',
  'entity_type' => 'summary_data',
  'bundle' => 'summary_data',
  'description' => t('Fetch all summary data entities.'),
  'class' => 'EITIApiSummaryData',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
