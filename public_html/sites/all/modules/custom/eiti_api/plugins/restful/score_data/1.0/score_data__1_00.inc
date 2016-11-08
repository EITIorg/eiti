<?php

$plugin = array(
  'label' => t('Score Data'),
  'resource' => 'score_data',
  'name' => 'score_data__1_00',
  'entity_type' => 'score_data',
  'description' => t('Fetch all the score data entities.'),
  'class' => 'EITIApiScoreData',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
