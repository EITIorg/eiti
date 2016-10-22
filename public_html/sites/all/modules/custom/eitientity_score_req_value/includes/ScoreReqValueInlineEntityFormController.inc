<?php
/**
 * @file
 * Controllers extending the Entity API providing custom administrative pages.
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class ScoreReqValueInlineEntityFormController extends EntityInlineEntityFormController {

  /**
  * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('Score Requirement Value'),
      'plural' => t('Score Requirement Values'),
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

    $fields['field_score_req_category'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_score_req_value_get_score_req_category',
      'label' => t('Requirement Category'),
      'weight' => 10,
    );

    $fields['score_req'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_score_req_value_get_score_req_label',
      'label' => t('Score Requirement'),
      'weight' => 20,
    );

    $fields['score_req_value'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_score_req_value_get_score_req_value_value',
      'label' => t('Progress Value'),
      'weight' => 30,
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
    /** @var ScoreReqValueEntity $entity */
    $entity = $entity_form['#entity'];

    $score_req_information = eitientity_score_req_value_get_score_req_information();
    $entity_form['score_req_id'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Score Requirement'),
      '#default_value' => $entity->score_req_id,
      '#options' => $score_req_information['options'],
      '#options_attributes' => $score_req_information['attributes'],
      '#description' => t('The Score Requirement.'),
      '#theme' => 'select_score_reqs',
    );

    $entity_form['value'] = array(
      '#type' => 'select',
      '#title' => t('Level of Progress (Value)'),
      '#required' => TRUE,
      '#options' => array('' => t('- Select -')) + _eitientity_score_req_value_get_value_options(),
      '#default_value' => $entity->value,
    );

    $entity_form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $entity->description,
    );

    $entity_form['dir_of_progress'] = array(
      '#type' => 'select',
      '#title' => t('Direction of Progress'),
      '#options' => _eitientity_score_req_value_get_dir_of_progress_options(),
      '#default_value' => $entity->progress_value,
    );
    $entity_form['is_applicable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Is Applicable'),
      '#default_value' => $entity->is_applicable,
    );
    $entity_form['is_required'] = array(
      '#type' => 'radios',
      '#title' => t('Required or Encouraged?'),
      '#options' => array(
        EITIENTITY_SCORE_REQ_REQUIRED => t('Is Required'),
        EITIENTITY_SCORE_REQ_ENCOURAGED => t('Is Encouraged')
      ),
      '#default_value' => $entity->is_applicable,
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

    $score_req_entity = entity_load_single('score_req', $entity_form_values['score_req_id']);
    if (empty($score_req_entity)) {
      form_set_error($parents_path . 'score_req_id', t('Please select a valid score_req.'));
      return;
    }
    $entity_form['#score_req_entity'] = $score_req_entity;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);
  }
}
