<?php

/**
 * @TODO: REMOVE!!!
 */
$plugin = array(
  'title' => t('DEPRECATED: Semi-Interactive Map'),
  'single' => TRUE,
  'description' => t('DO NOT USE THIS WIDGET!'),
  'category' => t('DEPRECATED'),
  'render callback' => '_DEPRECATED__eiti_ctools_extra_map_semi_interactive_render',
  'edit form' => '_DEPRECATED__eiti_ctools_extra_map_semi_interactive_edit_form',
);

function _DEPRECATED__eiti_ctools_extra_map_semi_interactive_render($subtype, $conf, $panel_args, $context) {}
function _DEPRECATED__eiti_ctools_extra_map_semi_interactive_edit_form($form, &$form_state) {}
