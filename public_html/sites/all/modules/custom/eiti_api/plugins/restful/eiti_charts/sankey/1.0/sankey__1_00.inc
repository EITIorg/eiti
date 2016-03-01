<?php

$plugin = array(
  'label' => t('EITI Charts: Sankey Charts'),
  'resource' => 'sankey',
  'name' => 'sankey__1_00',
  'description' => t('Fetch all sankey chart formatted data endpoints.'),
  'class' => 'EITIApiSankey',
  'authentication_types' => TRUE,
  'authentication_optional' => TRUE,
);
