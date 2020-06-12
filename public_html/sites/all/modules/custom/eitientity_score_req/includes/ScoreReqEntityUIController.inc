<?php

/**
 * @file
 * Controllers extending the Entity API providing custom administrative pages.
 */

/**
 * Override HelperEntityBundleableUIController to customize our menu items.
 */
class ScoreReqEntityUIController extends HelperEntityBundleableUIController {
  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[EITIENTITY_SCORE_REQ_ADMIN_UI_PATH]['title'] = t('List Requirements');
    return $items;
  }

  /**
   * Generates the render array for a overview table for arbitrary entities
   * matching the given conditions.
   *
   * @param $conditions
   *   An array of conditions as needed by entity_load().
   *
   * @return Array
   *   A renderable array.
   */
  public function overviewTable($conditions = array()) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->entityType);

    // Add all conditions to query.
    foreach ($conditions as $key => $value) {
      $query->propertyCondition($key, $value);
    }

    if ($this->overviewPagerLimit) {
      $query->pager($this->overviewPagerLimit);
    }

    $header = array(
      array(
        'data' => t('Category'),
        'class' => array('score-req-category-ui-name'),
      ),
      array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'name',
        'class' => array('score-req-ui-name'),
      ),
      array(
        'data' => t('Code'),
        'type' => 'property',
        'specifier' => 'name',
        'class' => array('score-req-ui-name'),
      ),
      array(
        'data' => t('Standard'),
        'type' => 'property',
        'specifier' => 'name',
        'class' => array('score-req-ui-standard'),
      ),
      array(
        'data' => t('Created'),
        'type' => 'property',
        'specifier' => 'created',
        'class' => array('score-req-ui-created'),
      ),
      array(
        'data' => t('Status'),
        'type' => 'property',
        'specifier' => 'status',
        'class' => array('score-req-ui-status'),
        'sort' => 'desc',
      ),
      array(
        'data' => t('Operations'),
        'class' => array('score-req-ui-operations'),
        'colspan' => $this->operationCount(),
      ),
    );
    $query->tableSort($header);

    $results = $query->execute();

    $ids = isset($results[$this->entityType]) ? array_keys($results[$this->entityType]) : array();
    $entities = $ids ? entity_load($this->entityType, $ids) : array();

    $rows = array();
    /** @var ScoreReqEntity $entity */
    foreach ($entities as $entity) {
      $standards_labels = [];
      if (!empty($entity->field_score_req_standard)) {
        $req_standards = $entity->field_score_req_standard;
        foreach ($req_standards[LANGUAGE_NONE] as $req_standard) {
          $standards_labels[] = taxonomy_term_load($req_standard['tid'])->name;
        }
      }
      $cols = array(
        !empty($entity->code) ? $entity->code : t('N/A'),
        !empty($standards_labels) ? implode(', ', $standards_labels) : t('N/A'),
        format_date(!empty($entity->changed) ? $entity->changed : $entity->created, 'short'),
      );
      $rows[] = $this->overviewTableRow($conditions, $entity->identifier(), $entity, $cols);
    }

    $render = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('None.'),
    );
    return $render;
  }

  /**
   * Returns the operation count for calculating colspans.
   */
  protected function operationCount() {
    $count = 3;
    $count += !empty($this->entityInfo['i18n controller class']) ? 1 : 0;
    return $count;
  }

  /**
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   *
   * @param $conditions
   * @param $id
   * @param ScoreReqEntity $entity
   * @param $additional_cols
   *   Additional columns to be added after the entity label column.
   * @return array
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $score_req_emw = entity_metadata_wrapper('score_req', $entity);
    $category_value = $score_req_emw->field_score_req_category->value();
    $row[] = !empty($category_value) ? $category_value->name : t('No category');


    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => entity_label($this->entityType, $entity),
      '#name' => !empty($this->entityInfo['exportable']) ? $entity->identifier() : FALSE,
      '#url' => $entity_uri ? $entity_uri : FALSE,
      '#entity_type' => $this->entityType),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array('data' => array(
        '#theme' => 'entity_status',
        '#status' => $entity->{$this->statusKey},
      ));
    }

    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    $row[] = $entity->status ? t('published') : t('not published');

    // Add operations.
    $row[] = l(t('edit'), $this->entity_path . "/$id/edit", array('query' => drupal_get_destination()));
    if ($i18n) {
      $row[] = l(t('translate'), $this->entity_path . "/$id/translate");
    }
    $row[] = l(t('delete'), $this->entity_path . "/$id/delete", array('query' => drupal_get_destination()));
    return $row;
  }
}
