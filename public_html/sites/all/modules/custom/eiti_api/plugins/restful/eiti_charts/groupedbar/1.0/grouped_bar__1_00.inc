<?php

$plugin = array(
  'label' => t('EITI Charts: GroupedBar Charts'),
  'resource' => 'grouped_bar',
  'name' => 'grouped_bar__1_00',
  'description' => t('Fetch all grouped-bar formatted data endpoints.'),
  'class' => 'EITIApiGroupedBar',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
