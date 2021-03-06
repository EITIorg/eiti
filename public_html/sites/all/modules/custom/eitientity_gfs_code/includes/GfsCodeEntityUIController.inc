<?php

/**
 * @file
 * Controllers extending the Entity API providing custom administrative pages.
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class GfsCodeEntityUIController extends EntityBundleableUIController {
  protected $entity_path;
  protected $entity_id_count;

  /**
   * {@inheritdoc}
   */
  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);
    $this->id_count = count(explode('/', $this->path));
    $this->entity_path = $this->entityInfo['admin ui']['entity path'];
    $this->entity_id_count = count(explode('/', $this->entity_path));
  }

  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = array();

    // Set this on the object so classes that extend hook_menu() can use it.
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    $defaults = array(
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' =>  isset($this->entityInfo['admin ui']['file path']) ? $this->entityInfo['admin ui']['file path'] : drupal_get_path('module', $this->entityInfo['module']),
    );
    $entity_ui_defaults = array(
      'file' => 'includes/entity.ui.inc',
      'file path' => drupal_get_path('module', 'entity'),
    );

    /**
     * Add entity specific menu items.
     */
    $items[$this->entity_path . '/' . $wildcard] = array(
      'title callback' => 'entity_ui_get_page_title',
      'title arguments' => array('view', $this->entityType, $this->entity_id_count),
      'page callback' => 'entity_ui_entity_page_view',
      'page arguments' => array($this->entity_id_count),
      'load arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType, $this->entity_id_count),
    ) + $defaults;
    $items[$this->entity_path . '/' . $wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );
    $items[$this->entity_path . '/' . $wildcard . '/edit'] = array(
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, $this->entity_id_count),
      'load arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('edit', $this->entityType, $this->entity_id_count),
      'title' => 'Edit',
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight' => 0,
    ) + $defaults;
    $items[$this->entity_path . '/' . $wildcard . '/delete'] = array(
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_operation_form', $this->entityType, $this->entity_id_count, 'delete'),
      'load arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('delete', $this->entityType, $this->entity_id_count),
      'title' => 'Delete',
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 1,
    ) + $defaults;

    /**
     * Add admin/content specific menu items.
     */
    $items[$this->path] = array(
      'title' => $plural_label,
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_overview_form', $this->entityType),
      'description' => 'Manage ' . $plural_label . '.',
      'access callback' => 'entity_access',
      'access arguments' => array('access overview', $this->entityType),
      'type' => MENU_LOCAL_TASK | MENU_NORMAL_ITEM,
    ) + $entity_ui_defaults;
    $items[$this->path . '/overview'] = array(
      'title' => 'Overview',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    $items[$this->entity_path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'system_admin_menu_block_page',
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
      'file' => 'system.admin.inc',
      'file path' => drupal_get_path('module', 'system'),
    );

    /**
     * Add bundle_add specific menu items.
     */
    if (isset($this->entityInfo['bundles callback']) && function_exists($this->entityInfo['bundles callback'])) {
      foreach ($this->entityInfo['bundles callback']() as $bundle_type => $bundle_info) {
        $type_url_str = str_replace('_', '-', $bundle_type);
        $items[$this->entity_path . '/add/' . $type_url_str] = array(
          'title callback' => 'entity_ui_get_action_title',
          'title arguments' => array('add', $this->entityType, $bundle_type),
          'description' => $bundle_info['description'],
          'page callback' => 'entity_ui_get_bundle_add_form',
          'page arguments' => array($this->entityType, $bundle_type),
          'access callback' => 'entity_access',
          'access arguments' => array('create', $this->entityType),
          'weight' => isset($bundle_info['weight']) ? $bundle_info['weight'] : 0,
        ) + $defaults;
      }
    }
    else {
      $items[$this->entity_path . '/add/%'] = array(
        'title callback' => 'entity_ui_get_action_title',
        'title arguments' => array('add', $this->entityType, $this->entity_id_count + 1),
        'page callback' => 'entity_ui_get_bundle_add_form',
        'page arguments' => array($this->entityType, $this->entity_id_count + 1),
        'access callback' => 'entity_access',
        'access arguments' => array('create', $this->entityType),
      ) + $defaults;
    }

    return $items;
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

    // Do not show "Fixed" entities on the admin form.
    $query->entityCondition('bundle', 'fixed', '!=');

    // Add all conditions to query.
    foreach ($conditions as $key => $value) {
      $query->propertyCondition($key, $value);
    }

    if ($this->overviewPagerLimit) {
      $query->pager($this->overviewPagerLimit);
    }

    $css_class_prefix = drupal_html_class($this->entityType);

    $header = array(
      array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'name',
        'class' => array($css_class_prefix . '-ui-name'),
        'sort' => 'desc',
      ),
      array(
        'data' => t('Type'),
        'type' => 'property',
        'specifier' => 'type',
        'class' => array($css_class_prefix . '-ui-type'),
      ),
      array(
        'data' => t('Created'),
        'type' => 'property',
        'specifier' => 'created',
        'class' => array($css_class_prefix . '-ui-created'),
      ),
      array(
        'data' => t('Status'),
        'type' => 'property',
        'specifier' => 'status',
        'class' => array($css_class_prefix . '-ui-status'),
        'sort' => 'desc',
      ),
      array(
        'data' => t('Operations'),
        'class' => array($css_class_prefix . '-ui-operations'),
        'colspan' => $this->operationCount(),
      ),
    );
    $query->tableSort($header);

    $results = $query->execute();

    $ids = isset($results[$this->entityType]) ? array_keys($results[$this->entityType]) : array();
    $entities = $ids ? entity_load($this->entityType, $ids) : array();

    $rows = array();
    /** @var GfsCodeEntity $entity */
    foreach ($entities as $entity) {
      $cols = array(
        check_plain($this->entityInfo['bundles'][$entity->bundle()]['label']),
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
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   *
   * @param $conditions
   * @param $id
   * @param GfsCodeEntity $entity
   * @param $additional_cols
   *   Additional columns to be added after the entity label column.
   * @return array
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

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
