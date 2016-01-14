<?php
/**
 * @file
 * Controllers extending the Entity API providing custom administrative pages.
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class IndicatorValueInlineEntityFormController extends EntityInlineEntityFormController {

  /**
  * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('indicator value'),
      'plural' => t('indicator values'),
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

    $fields['indicator'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_indicatorvalue_get_indicator_label',
      'label' => t('Indicator'),
      'weight' => 20,
    );

    $fields['indicator_value'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_indicatorvalue_get_indicator_value_value',
      'label' => t('Value'),
      'weight' => 30,
    );

    $fields['indicator_unit'] = array(
      'type' => 'callback',
      'render_callback' => 'eitientity_indicatorvalue_get_indicator_value_unit',
      'label' => t('Unit'),
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
    /** @var IndicatorValueEntity $entity */
    $entity = $entity_form['#entity'];

    $indicator_information = eitientity_indicatorvalue_get_indicator_information();
    $entity_form['indicator_id'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Indicator'),
      '#default_value' => $entity->indicator_id,
      '#options' => $indicator_information['options'],
      '#options_attributes' => $indicator_information['attributes'],
      '#description' => t('The indicator type.'),
      '#theme' => 'select_indicators',
    );

    $entity_form['value_boolean'] = array(
      '#type' => 'select',
      '#title' => t('Value'),
      '#options' => array(
        EITIENTITY_INDICATORVALUE_VALUE_NO => t('No'),
        EITIENTITY_INDICATORVALUE_VALUE_YES => t('Yes'),
      ),
      '#default_value' => $entity->value_boolean,
    );
    $this->entityFormSetElementStates($entity_form['value_boolean'], 'boolean', $entity_form['#parents'], 'indicator_id');

    $entity_form['value_enum'] = array(
      '#type' => 'select',
      '#title' => t('Value'),
      '#options' => array(
        EITIENTITY_INDICATORVALUE_VALUE_NO => t('No'),
        EITIENTITY_INDICATORVALUE_VALUE_YES => t('Yes'),
        EITIENTITY_INDICATORVALUE_VALUE_PARTIALLY => t('Partially'),
      ),
      '#default_value' => $entity->value_enum,
    );
    $this->entityFormSetElementStates($entity_form['value_enum'], 'enum', $entity_form['#parents'], 'indicator_id');

    $entity_form['value_numeric'] = array(
      '#type' => 'textfield',
      '#title' => t('Numeric Value'),
      '#default_value' => $entity->value_numeric,
    );
    $this->entityFormSetElementStates($entity_form['value_numeric'], 'numeric', $entity_form['#parents'], 'indicator_id');

    $entity_form['value_unit'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit Value'),
      '#default_value' => $entity->value_unit,
    );
    $this->entityFormSetElementStates($entity_form['value_unit'], 'numeric', $entity_form['#parents'], 'indicator_id');

    $entity_form['value_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text Value'),
      '#default_value' => $entity->value_text,
    );
    $this->entityFormSetElementStates($entity_form['value_text'], 'text', $entity_form['#parents'], 'indicator_id');

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

    // Get a list of indicators that use this form element.
    $indicators = eitientity_indicator_get_by_bundle($bundle);

    // Hide form element if no indicators use it.
    if (empty($indicators)) {
      $form_element['#access'] = FALSE;
    }

    /** @var IndicatorEntity $indicator */
    foreach ($indicators as $indicator) {
      if (!empty($form_element['#states']['visible'][$states_group])) {
        $form_element['#states']['required'][$states_group][] = 'or';
        $form_element['#states']['visible'][$states_group][] = 'or';
      }
      $form_element['#states']['required'][$states_group][][$jquery_selector] = array('value' => $indicator->identifier());
      $form_element['#states']['visible'][$states_group][][$jquery_selector] = array('value' => $indicator->identifier());
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

    $indicator_entity = entity_load_single('indicator', $entity_form_values['indicator_id']);
    if (empty($indicator_entity)) {
      form_set_error($parents_path . 'indicator_id', t('Please select a valid indicator.'));
      return;
    }
    $entity_form['#indicator_entity'] = $indicator_entity;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);
  }
}
