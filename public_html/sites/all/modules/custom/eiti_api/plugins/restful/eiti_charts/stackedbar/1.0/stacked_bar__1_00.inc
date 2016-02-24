<?php

$plugin = array(
  'label' => t('EITI Charts: StackedBar Charts'),
  'resource' => 'stacked_bar',
  'name' => 'stacked_bar__1_00',
  'description' => t('Fetch all stacked-bar formatted data endpoints.'),
  'class' => 'EITIApiStackedBar',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
