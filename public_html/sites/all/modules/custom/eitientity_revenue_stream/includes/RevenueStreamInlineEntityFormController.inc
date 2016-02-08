<?php
/**
 * @file
 * Controllers extending the Entity API providing custom administrative pages.
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class RevenueStreamInlineEntityFormController extends EntityInlineEntityFormController {

  /**
  * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('revenue stream'),
      'plural' => t('revenue streams'),
    );
    return $labels;
  }

  /**
   * Returns an array of default settings in the form of key => value.
   */
  public function defaultSettings() {
    $defaults = parent::defaultSettings();
    return $defaults;
  }

  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function tableFields($bundles) {
    $fields = array();

    $fields['gfs_code'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_revenue_stream_get_gfs_code_label',
      'label' => t('GFS Code'),
      'weight' => 20,
    );

    $fields['organisation'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_revenue_stream_get_organisation_label',
      'label' => t('Organisation'),
      'weight' => 30,
    );

    $fields['currency'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_revenue_stream_get_currency_value',
      'label' => t('Currency'),
      'weight' => 35,
    );

    $fields['revenue'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_revenue_stream_get_revenue_value',
      'label' => t('Revenue'),
      'weight' => 35,
    );

    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   *
   * @param $entity_form
   * @param $form_state
   * @return array
   */
  public function entityForm($entity_form, &$form_state) {
    /** @var RevenueStreamEntity $entity */
    $entity = $entity_form['#entity'];

    $gfs_code_information = eitientity_gfs_code_get_gfs_code_information();
    $entity_form['gfs_code_id'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('GFS Code'),
      '#default_value' => $entity->gfs_code_id,
      '#options' => $gfs_code_information['options'],
    );

    // NOTE: The Revenue stream bundle name matches the organisation name.
    $entity_form['organisation_id'] = array(
      '#type' => 'ereference',
      '#title' => t('Organisation'),
      '#default_value' => $entity->organisation_id,
      '#required' => TRUE,
      '#referenced_type' => 'organisation',
      '#referenced_bundle' => $entity->type,
    );
    $entity_form['organisation_id']['#autocomplete_path'] = 'helpergeneric/ereference/organisation/' . $entity->type;

    $entity_form['currency'] = array(
      '#type' => 'select',
      '#title' => t('Currency'),
      '#required' => TRUE,
      '#options' => currency_options(),
      '#default_value' => $entity->currency,
    );

    $entity_form['revenue'] = array(
      '#type' => 'textfield',
      '#title' => t('Revenue'),
      '#required' => TRUE,
      '#default_value' => $entity->revenue,
    );

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   *
   * @param array $entity_form
   * @param array $form_state
   */
  public function entityFormValidate($entity_form, &$form_state) {
    $parents_path = implode('][', $entity_form['#parents']) . '][';

    // Get the submitted values.
    form_state_values_clean($form_state);
    $entity_form_values = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);

    $gfs_code_entity = entity_load_single('gfs_code', $entity_form_values['gfs_code_id']);
    if (empty($gfs_code_entity)) {
      form_set_error($parents_path . 'gfs_code_id', t('Please select a GFS Code.'));
      return;
    }
    $entity_form['#gfs_code_entity'] = $gfs_code_entity;

    $organisation_entity = entity_load_single('organisation', $entity_form_values['organisation_id']);
    if (empty($organisation_entity)) {
      form_set_error($parents_path . 'organisation_id', t('Please select a GFS Code.'));
      return;
    }
    $entity_form['#organisation_entity'] = $organisation_entity;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    dpm($form_state, '$form_state');
    parent::entityFormSubmit($entity_form, $form_state);
  }
}
