<?php

/**
 * @file
 * Controller for providing the UI for bundable entities.
 */

/**
 * Override EntityBundleableUIController to customize our menu items.
 */
class HelperEntityBundleableUIController extends EntityBundleableUIController {
  protected $entity_path;
  protected $entity_id_count;
  protected $bundle_path;
  protected $wildcard;
  protected $hide_content_ui;

  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);
    $this->id_count = count(explode('/', $this->path));
    $this->entity_path = $this->entityInfo['admin ui']['entity path'];
    $this->entity_id_count = count(explode('/', $this->entity_path));
    $this->bundle_path = $this->entityInfo['admin ui']['bundle path'];

    // Set this on the object so classes that extend hook_menu() can use it.
    $this->wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    if (isset($this->entityInfo['admin ui']['hide content ui'])) {
      $this->hide_content_ui = $this->entityInfo['admin ui']['hide content ui'];
    }
  }

  /**
   * Define menu items and page callbacks.
   */
  public function hook_menu() {
    $items = array();

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
    $items[$this->entity_path . '/' . $this->wildcard] = array(
        'title callback' => 'entity_ui_get_page_title',
        'title arguments' => array('view', $this->entityType, $this->entity_id_count),
        'page callback' => 'entity_ui_entity_page_view',
        'page arguments' => array($this->entity_id_count),
        'load arguments' => array($this->entityType),
        'access callback' => 'entity_access',
        'access arguments' => array('view', $this->entityType, $this->entity_id_count),
      ) + $defaults;
    $items[$this->entity_path . '/' . $this->wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );
    $items[$this->entity_path . '/' . $this->wildcard . '/edit'] = array(
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
    $items[$this->entity_path . '/' . $this->wildcard . '/delete'] = array(
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
    if (empty($this->hide_content_ui)) {
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
    }

    /**
     * Add admin/structure specific menu items.
     */
    if (module_exists('field_ui')) {
      $items[$this->bundle_path] = array(
        'title' => $plural_label,
        'page callback' => 'helperentity_entity_overview_types',
        'page arguments' => array($this->entityType),
        'description' => t('Manage !label entities.', array('!label' => $plural_label)),
        'access callback' => 'entity_access',
        'access arguments' => array('administer', $this->entityType),
        'type' => MENU_NORMAL_ITEM,
        'file' => $this->entityInfo['module'] . '.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module']),
      );
      $items[$this->bundle_path . '/overview'] = array(
        'title' => 'Overview',
        'type' => MENU_DEFAULT_LOCAL_TASK,
        'weight' => -10,
      );

      if (!function_exists($this->entityInfo['module'] . '_type_get_name')) {
        die('Missing page callback function: ' . $this->entityInfo['module'] . '_type_get_name');
      }
      foreach ($this->entityInfo['bundles'] as $bundle_type => $bundle_info) {
        $items[$this->bundle_path . '/manage/' . $bundle_type] = array(
          'title' => $bundle_info['label'] . ' info',
          'page callback' => $this->entityInfo['module'] . '_type_get_name',
          'page arguments' => array($bundle_type),
          'access callback' => 'entity_access',
          'access arguments' => array('administer', $this->entityType),
        );
        $items[$this->bundle_path . '/manage/' . $bundle_type . '/view'] = array(
          'title' => 'View',
          'type' => MENU_DEFAULT_LOCAL_TASK,
          'weight' => -10,
        );
      }
    }

    return $items;
  }

  /**
   * Returns the operation count for calculating column spanning.
   */
  protected function operationCount() {
    // We use ctools_dropbutton.
    return 1;
  }

  /**
   * Generates the render array for a overview table for arbitrary entities
   * matching the given conditions.
   *
   * @param $conditions
   *   An array of conditions as needed by entity_load().
   *
   * @return array
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
        'data' => t('ID'),
        'type' => 'property',
        'specifier' => 'id',
        'class' => array($css_class_prefix . '-ui-id'),
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
       'data' => t('Changed'),
       'type' => 'property',
       'specifier' => 'changed',
       'class' => array($css_class_prefix . '-ui-changed'),
       'sort' => 'desc',
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
    /** @var SummaryDataEntity $entity */
    foreach ($entities as $entity) {
      $cols = array(
        check_plain($this->entityInfo['bundles'][$entity->bundle()]['label']),
        format_date($entity->created, 'short'),
        format_date(!empty($entity->changed) ? $entity->changed : $entity->created, 'short'),
      );
      $rows[] = $this->overviewTableRow($conditions, $entity->identifier(), $entity, $cols);
    }

    $render = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('None.'),
      '#attributes' => array('class' => array('fix-ctools-dropbutton')),
    );
    return $render;
  }

  /**
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   *
   * @param $conditions
   * @param $id
   * @param SummaryDataEntity $entity
   * @param $additional_cols
   *   Additional columns to be added after the entity label column.
   * @return array
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => entity_label($this->entityType, $entity),
        '#name' => !empty($this->entityInfo['exportable']) ? $entity->identifier() : FALSE,
        '#url' => $entity_uri ? $entity_uri : FALSE,
        '#entity_type' => $this->entityType
      ),
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

    $row[] = $entity->status ? t('published') : t('not published');

    // Add operations.
    $operations = array();

    $operations[] = array(
      'title' => t('edit'),
      'href' => $this->entity_path . "/$id/edit",
      'query' => drupal_get_destination(),
    );

    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);
    if ($i18n) {
      $operations[] = array(
        'title' => t('translate'),
        'href' => $this->entity_path . "/$id/translate",
      );
    }

    $operations[] = array(
      'title' => t('delete'),
      'href' => $this->entity_path . "/$id/delete",
      'query' => drupal_get_destination(),
    );

    $row[] = theme('links__ctools_dropbutton', array('links' => $operations, 'attributes' => array('class' => array())));

    return $row;
  }
}
