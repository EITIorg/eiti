<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function webform_steps_w3_form_webform_admin_settings_alter(&$form, &$form_state) {
  $form['progressbar_migrate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Progressbar migration'),
    '#description' => t('Import progressbar settings stored by the webform3 compatibility module (webform_steps_w3) into webform. Note that configurations made with webform4 might be overriden.'),
    '#weight' => -100,
  );
  $form['progressbar_migrate']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Start migration'),
    '#submit' => array('webform_steps_w3_migrate'),
  );
}

/**
 * Copy setting from webform_steps_w3_progressbar to webform.
 */
function webform_steps_w3_migrate() {
  $sql = <<<SQL
UPDATE {webform} w INNER JOIN {webform_steps_w3_progressbar} w3 USING(nid)
SET
  w.progressbar_bar = w3.progressbar_bar,
  w.progressbar_page_number = w3.progressbar_page_number,
  w.progressbar_percent = w3.progressbar_percent,
  w.progressbar_pagebreak_labels = w3.progressbar_pagebreak_labels,
  w.progressbar_label_first = w3.progressbar_label_first
SQL;
  db_query($sql);
  drupal_set_message(t('All configurations have now been migrated to webform4. You can now safely disable and uninstall webform_steps_w3.'));
}

/**
 * Implements hook_node_load().
 */
function webform_steps_w3_node_load($nodes, $types) {
  // Quick check to see if we need to do anything at all for these nodes.
  $webform_types = webform_variable_get('webform_node_types');
  if (count(array_intersect($types, $webform_types)) == 0) {
    return;
  }
  $defaults = webform_steps_w3_node_defaults();

  // Select all webforms that match these node IDs.
  $q = db_select('webform', 'w');
  $q->leftJoin('webform_steps_w3_progressbar', 'settings', 'w.nid=settings.nid');
  $q->addfield('settings', 'nid', 'has_settings');
  $result = $q->fields('w', array('nid'))
    ->fields('settings', array_keys($defaults))
    ->condition('w.nid', array_keys($nodes), 'IN')
    ->execute()
    ->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

  foreach ($result as $nid => $settings) {
    // Add progressbar settings to each node.
    if ($settings['has_settings']) {
      unset($settings['has_settings']);
      $nodes[$nid]->webform = $settings + $nodes[$nid]->webform;
    }
  }
}
