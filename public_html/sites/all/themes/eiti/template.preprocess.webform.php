<?php

/**
 * Implements theme_preprocess_webform_progressbar()
 */
function eiti_preprocess_webform_progressbar(&$variables) {

  if (isset($variables['page_labels'])) {
  	$page_labels = $variables['page_labels'];

    foreach ($page_labels as $delta => $label) {
      if (substr_count($label, t('Step ')) > 0) {
        $items = explode(':', $label);
        
        if (isset($items[0]) && !empty($items[0])) {
          $items[0] = '<span>' . $items[0] . '</span>';
          $label = implode('', $items);
          $page_labels[$delta] = $label;
        }
      }
    }

    $variables['page_labels'] = $page_labels;
  }
}