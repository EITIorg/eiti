<?php
/**
 * @file
 * Class for the Panelizer node entity plugin.
 */

/**
 * Panelizer Entity node plugin class.
 *
 * Handles node specific functionality for Panelizer.
 */
class PanelizerEntityNode extends PanelizerEntityDefault {
  public $entity_admin_root = 'admin/structure/types/manage/%panelizer_node_type';
  public $entity_admin_bundle = 4;
  public $views_table = 'node';
  public $uses_page_manager = TRUE;
  public $supports_revisions = TRUE;

  public function entity_access($op, $entity) {
    // This must be implemented by the extending clas.
    return node_access($op, $entity);
  }

  /**
   * Implement the save function for the entity.
   */
  public function entity_save($entity) {
    if (module_exists('workbench_moderation') && workbench_moderation_node_type_moderated($entity->type)) {
      $live_entity = workbench_moderation_node_live_load($entity);
      if ($live_entity->vid != $entity->vid) {
        $entity->revision = TRUE;
      }
    }
    node_save($entity);

    // Clear page cache. This replaces the need for cache_clear_all() which is
    // normally called by node_form_submit().
    $internal_path = entity_uri('node', $entity);
    $url = url($internal_path['path'],  array('absolute' => TRUE));
    cache_clear_all($url, 'cache_page');
  }

  public function entity_identifier($entity) {
    return t('This node');
  }

  public function entity_bundle_label() {
    return t('Node type');
  }

  /**
   * Determine if the entity allows revisions.
   */
  public function entity_allows_revisions($entity) {
    $retval = array();

    list($entity_id, $revision_id, $bundle) = entity_extract_ids($this->entity_type, $entity);

    $node_options = variable_get('node_options_' . $bundle, array('status', 'promote', 'panelizer'));

    // Whether or not the entity supports revisions. Drupal core supports
    // revisions by default on nodes; if Workbench Moderation is enabled it's
    // possible to disable this.
    $retval[0] = TRUE;
    if (module_exists('workbench_moderation')) {
      $retval[0] = in_array('panelizer', $node_options);
    }

    // Whether or not the user can control if a revision is created.
    $retval[1] = user_access('administer nodes');

    // Whether or not the revision is created by default.
    $retval[2] = in_array('revision', $node_options);

    return $retval;
  }

  /**
   * {@inheritdoc}
   */
  function get_default_display($bundle, $view_mode) {
    $display = parent::get_default_display($bundle, $view_mode);
    // Add the node title to the display since we can't get that automatically.
    $display->title = '%node:title';

    // Add the node links, they probably would like these.
    $pane = panels_new_pane('node_links', 'node_links', TRUE);
    $pane->css['css_class'] = 'link-wrapper';
    $pane->configuration['build_mode'] = $view_mode;
    $pane->configuration['context'] = 'panelizer';

    // @todo -- submitted by does not exist as a pane! That's v. sad.
    $display->add_pane($pane, 'center');

    unset($pane);

    // If the content type is enabled for use with Webform, add the custom
    // submission pane.
    if (module_exists('webform')) {
      if ($view_mode == 'page_manager') {
        if (variable_get('webform_node_' . $bundle)) {
          $pane = panels_new_pane('entity_field_extra', 'node:webform', TRUE);
          $pane->configuration['context'] = 'panelizer';
          $pane->configuration['view_mode'] = 'full';
          $display->add_pane($pane, 'center');
          unset($pane);
        }
      }
    }

    // Add a custom pane for the book navigation block for the Page Manager
    // display.
    if (module_exists('book')) {
      if ($view_mode == 'page_manager') {
        $pane = panels_new_pane('node_book_nav', 'node_book_nav', TRUE);
        $pane->configuration['context'] = 'panelizer';
        $display->add_pane($pane, 'center');
        unset($pane);
      }
    }

    return $display;
  }

  /**
   * Implements a delegated hook_page_manager_handlers().
   *
   * This makes sure that all panelized entities have the proper entry
   * in page manager for rendering.
   */
  public function hook_default_page_manager_handlers(&$handlers) {
    $handler = new stdClass;
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'node_view_panelizer';
    $handler->task = 'node_view';
    $handler->subtask = '';
    $handler->handler = 'panelizer_node';
    $handler->weight = -100;
    $handler->conf = array(
      'title' => t('Node panelizer'),
      'context' => 'argument_entity_id:node_1',
      'access' => array(),
    );
    $handlers['node_view_panelizer'] = $handler;

    return $handlers;
  }

  /**
   * Implements a delegated hook_form_alter.
   *
   * We want to add Panelizer settings for the bundle to the node type form.
   */
  public function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'node_type_form') {
      if (isset($form['#node_type'])) {
        $bundle = $form['#node_type']->type;
        $this->add_bundle_setting_form($form, $form_state, $bundle, array('type'));
      }

      // Additional workflow options when Workbench Moderation is enabled.
      if (module_exists('workbench_moderation')) {
        // It's now possible to disable revision creation through the Panelizer
        // interface.
        $form['workflow']['node_options']['#options']['panelizer'] = t('Enable Panelizer revisions');

        // Disable the 'revision' checkbox when the 'moderation' checkbox is
        // checked, so that moderation can not be enabled unless revisions are
        // enabled.
        $form['workflow']['node_options']['revision']['#states'] = array(
          'disabled' => array(':input[name="node_options[panelizer]"]' => array('checked' => FALSE)),
        );

        // Disable the 'moderation' checkbox when the 'revision' checkbox is
        // not checked, so that revisions can not be turned off without also
        // turning off moderation.
        $form['workflow']['node_options']['panelizer']['#description'] = t('Revisions must be enabled in order to create revisions from within Panelizer.');
        $form['workflow']['node_options']['panelizer']['#states'] = array(
          'disabled' => array(':input[name="node_options[revision]"]' => array('checked' => FALSE)),
        );
      }
    }
  }

  /**
   * {@inheritDoc}
   */
  public function add_bundle_setting_form_validate($form, &$form_state, $bundle, $type_location) {
    // Ensure that revisions are enabled if Panelizer revisions are.
    if (isset($form_state['values']['node_options']['panelizer']) || array_key_exists('panelizer', $form_state['values']['node_options'])) {
      $form_state['values']['node_options']['revision'] = 1;
    }
    parent::add_bundle_setting_form_validate($form, $form_state, $bundle, $type_location);
  }

  public function hook_page_alter(&$page) {
    // Add an extra "Panelizer" action on the content types admin page.
    if ($_GET['q'] == 'admin/structure/types') {
      // This only works with some themes.
      if (!empty($page['content']['system_main']['node_table'])) {
        // Shortcut.
        $table = &$page['content']['system_main']['node_table'];

        // Operations column should always be the last column in header.
        // Increase its colspan by one to include possible panelizer link.
        $operationsCol = end($table['#header']);
        if (!empty($operationsCol['colspan'])) {
          $operationsColKey = key($table['#header']);
          $table['#header'][$operationsColKey]['colspan']++;
        }

        // Since we can't tell what row a type is for, but we know that they
        // were generated in this order, go through the original types list.
        $types = node_type_get_types();
        $names = node_type_get_names();
        $row_index = 0;
        foreach ($names as $bundle => $name) {
          $type = $types[$bundle];
          if (node_hook($type->type, 'form')) {
            $type_url_str = str_replace('_', '-', $type->type);
            if ($this->is_panelized($bundle) && panelizer_administer_entity_bundle($this, $bundle)) {
              $table['#rows'][$row_index][] = array('data' => l(t('panelizer'), 'admin/structure/types/manage/' . $type_url_str . '/panelizer'));
            }
            else {
              $table['#rows'][$row_index][] = array('data' => '');
            }
            // Update row index for next pass.
            $row_index++;
          }
        }
      }
    }
  }

  /**
   * Implements a delegated hook_admin_paths.
   */
  public function hook_admin_paths(&$items) {
    if (variable_get('node_admin_theme')) {
      $items['node/*/panelizer*'] = TRUE;
    }
  }

  public function preprocess_panelizer_view_mode(&$vars, $entity, $element, $panelizer, $info) {
    parent::preprocess_panelizer_view_mode($vars, $entity, $element, $panelizer, $info);

    if (!empty($entity->promote)) {
      $vars['classes_array'][] = 'node-promoted';
    }
    if (!empty($entity->sticky)) {
      $vars['classes_array'][] = 'node-sticky';
    }
    if (empty($entity->status)) {
      $vars['classes_array'][] = 'node-unpublished';
    }
  }

  function render_entity($entity, $view_mode, $langcode = NULL, $args = array(), $address = NULL, $extra_contexts = array()) {
    $info = parent::render_entity($entity, $view_mode, $langcode, $args, $address, $extra_contexts);

    if (!empty($info)) {
      if (!empty($entity->promote)) {
        $info['classes_array'][] = 'node-promoted';
      }
      if (!empty($entity->sticky)) {
        $info['classes_array'][] = 'node-sticky';
      }
      if (empty($entity->status)) {
        $info['classes_array'][] = 'node-unpublished';
      }
    }

    return $info;
  }

  /**
   * Implements hook_views_plugins_alter().
   */
  function hook_views_plugins_alter(&$plugins) {
    // While it would be nice to generalize this plugin, there is no generic
    // entity view. This means that to generalize it we'll still need to have
    // each entity know how to do the view individually.
    // @todo make this happen.
    $path = drupal_get_path('module', 'panelizer') . '/plugins/views';
    $plugins['row']['panelizer_node_view'] = array(
      'title' => t('Panelizer display'),
      'help' => t('Render entities using the panels display for any that have been panelized.'),
      'handler' => 'panelizer_plugin_row_panelizer_node_view',
      'parent' => 'node',
      'base' => array('node'),
      'path' => $path,
      'uses options' => TRUE,
      'module' => 'panelizer',
      'type' => 'normal',
      'register theme' => FALSE,
      'name' => 'panelizer_node_view',
    );
  }
}
