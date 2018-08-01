<?php

$plugin = array(
  'label' => t('Summary Data'),
  'resource' => 'summary_data',
  'name' => 'summary_data__2_00',
  'entity_type' => 'summary_data',
  'bundle' => 'summary_data',
  'description' => t('Fetch all summary data entities.'),
  'class' => 'EITIApiSummaryData2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
