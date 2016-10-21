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

    $fields['score_req'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_score_req_value_get_score_req_label',
      'label' => t('Score Requirement'),
      'weight' => 20,
    );

    $fields['score_req_value'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_score_req_value_get_score_req_value_value',
      'label' => t('Value'),
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

    $entity_form['value_boolean'] = array(
      '#type' => 'select',
      '#title' => t('Value'),
      '#options' => array(
        EITIENTITY_INDICATOR_VALUE_VALUE_NO => t('No'),
        EITIENTITY_INDICATOR_VALUE_VALUE_YES => t('Yes'),
      ),
      '#default_value' => $entity->value_boolean,
    );
    $this->entityFormSetElementStates($entity_form['value_boolean'], 'boolean', $entity_form['#parents'], 'score_req_id');

    return $entity_form;
  }

  /**
   * Sets the form element #states array in order to control the bundle specific
   * elements.
   *
   * @param array $form_element
   * @param string $bundle
   * @param array $form_parents_list
   * @param string $controller
   */
  protected function entityFormSetElementStates(&$form_element, $bundle, $form_parents_list, $controller) {
    $states_group = 0;

    $target_parents = $form_parents_list;
    $field_name = array_shift($target_parents);
    $target_parents[] = $controller;
    $controller_form_element_name = $field_name . '[' . implode('][', $target_parents) . ']';
    $jquery_selector = ':input[name="' . $controller_form_element_name . '"]';

    // Get a list of score_reqs that use this form element.
    $score_reqs = eitientity_score_req_get_by_bundle($bundle);

    // Hide form element if no score_reqs use it.
    if (empty($score_reqs)) {
      $form_element['#access'] = FALSE;
    }

    /** @var ScoreReqEntity $score_req */
    foreach ($score_reqs as $score_req) {
      if (!empty($form_element['#states']['visible'][$states_group])) {
        $form_element['#states']['required'][$states_group][] = 'or';
        $form_element['#states']['visible'][$states_group][] = 'or';
      }
      $form_element['#states']['required'][$states_group][][$jquery_selector] = array('value' => $score_req->identifier());
      $form_element['#states']['visible'][$states_group][][$jquery_selector] = array('value' => $score_req->identifier());
    }
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
