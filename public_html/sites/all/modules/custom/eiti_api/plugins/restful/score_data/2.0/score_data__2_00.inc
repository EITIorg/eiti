<?php

$plugin = array(
  'label' => t('Validation Data'),
  'resource' => 'validation_data',
  'name' => 'score_data__2_00',
  'entity_type' => 'score_data',
  'description' => t('Fetch all the validation data entities.'),
  'class' => 'EITIApiScoreData2',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
  'major_version' => 2,
);
