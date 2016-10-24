<?php
/**
 * @file
 * This file contains form/UI cleanup functions.
 */

/**
 * Implements hook_update_projects_alter().
 *
 * Hide project-specific modules from the update list.
 *
 * @param array $projects
 */
function helpergeneric_update_projects_alter(&$projects) {
  $not_updated = array();
  foreach ($projects as $project_name => $project_info) {
    if ($project_info['project_type'] == 'core') {
      continue;
    }

    // Determine where the module is located.
    $project_path = drupal_get_path($project_info['project_type'], $project_info['name']);

    // Projects like 'features_extra' don't contain a module called 'features_extra' so an empty path is returned.
    $project_location = '';
    if (!empty($project_path)) {
      $project_location = dirname($project_path);
    }

    // Do not query updates for custom modules and features.
    switch ($project_location) {
      case 'sites/all/modules/custom':
      case 'sites/all/modules/features':
        // Hide project-specific modules from the update list.
        $not_updated[] = $projects[$project_name]['info']['name'];
        unset($projects[$project_name]);
        break;
    }
  }
}

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available components in the (re)create feature form.
 *
 * @param array $component_export
 * @param string $component
 */
function helpergeneric_features_component_export_alter(&$component_export, $component) {
  switch ($component) {
    case 'dependencies':
      // Hide custom features from dependencies.
      $entries_list = array(
      );
      break;

    case 'menu_custom':
      // Hide menus.
      $entries_list = array(
        'devel',
        //'main-menu',
        'management',
        'navigation',
        //'user-menu',
      );
      break;

    case 'user_permission':
      $entries_list = array(
        // Hide admin_menu.module permissions.
        'access administration menu',
        'flush caches',
        'display drupal links',

        // Hide coffee.module permissions.
        'access coffee',
        'administer coffee',

        // Hide devel.module permissions.
        'access devel information',
        'execute php code',
        'switch users',

        // Hide ds_ui.module permissions.
        'admin_view_modes',
        'admin_fields',
        'admin_classes',

        // Hide less.module permissions.
        'administer less',

        // Hide module_filter.module permissions.
        'administer module filter',

        // Hide stage_file_proxy.module permissions.
        'administer stage_file_proxy settings',
      );
      break;

    case 'variable_realm':
      $entries_list = array(
        'global:default',
        'language',
      );

      $variable_realm_name_prefixes = array(
        'language:',
      );
      foreach (array_keys($component_export['options']['sources']) as $name) {
        foreach ($variable_realm_name_prefixes as $prefix) {
          if (strpos($name, $prefix) === 0) {
            // Only remove the variable and do not display any message.
            unset($component_export['options']['sources'][$name]);
          }
        }
      }
      break;

    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // Custom variables.
        'helpergeneric_cleanup_ui_force',
        'date_format_shortest',

        // Hide CORE variables.
        'admin_theme',
        'cache',
        'cache_lifetime',
        'clean_url',
        'cron_key',
        'cron_last',
        'cron_semaphore',
        'css_js_query_string',
        'date_default_timezone',
        'date_first_day',
        'date_format_long',
        'date_format_medium',
        'date_format_short',
        'dblog_row_limit',
        'drupal_private_key',
        'drupal_css_cache_files',
        'drupal_http_request_fails',
        'drupal_js_cache_files',
        'error_level',
        'file_temporary_path',
        'image_toolkit',
        'install_profile',
        'install_task',
        'install_time',
        'javascript_parsed',
        'maintenance_mode',
        'menu_expanded',
        'menu_masks',
        'menu_rebuild_needed',
        'node_access_needs_rebuild',
        'node_admin_theme',
        'page_cache_maximum_age',
        'page_compression',
        'path_alias_whitelist',
        'preprocess_css',
        'preprocess_js',
        'site_default_country',
        'site_frontpage',
        'site_mail',
        'site_name',
        'site_slogan',
        //'teaser_length',
        'theme_default',

        // Cache specific variables.
        'cache_content_flush_cache_page',

        // Hide admin_menu.module variables.
        'admin_menu_devel_modules_enabled',

        // Hide ctools.module variables.
        'ctools_last_cron',
        'cache_class_cache_ctools_css',

        // Hide date.module variables.
        'date_api_version',
        'date_views_month_format_with_year',
        'date_views_month_format_without_year',
        'date_views_day_format_with_year',
        'date_views_day_format_without_year',
        'date_views_week_format_with_year',
        'date_views_week_format_without_year',
        'date_format_html5_tools_iso8601',
        'date_format_search_api_facetapi_SECOND',
        'date_format_search_api_facetapi_DAY',
        'date_format_search_api_facetapi_HOUR',
        'date_format_search_api_facetapi_MINUTE',
        'date_format_search_api_facetapi_YEAR',
        'date_format_search_api_facetapi_MONTH',

        // Hide entity.module variables.
        'entity_cache_tables_created',

        // Hide entitycache.module variables.
        'entitycache_enabled',

        // Hide entityreference.module variables.
        'entityreference:base-tables',

        // Hide features.module variables.
        'features_codecache',
        'features_default_export_path',
        'features_feature_locked',
        'features_ignored_orphans',
        'features_lock_mode',
        'features_modules_changed',
        'features_semaphore',

        // Hide fieldable_panels_panes.module variables.
        'fieldable_panels_panes_skip_default_type',

        // Hide htmlpurifier.module variables.
        'htmlpurifier_version_current',
        'htmlpurifier_version_check_failed',

        // Hide job_scheduler.module variables.
        'job_scheduler_rebuild_all',

        // Hide jquery_update.module variables.
        // 'jquery_update_compression_type',
        // 'jquery_update_jquery_version',
        // 'jquery_update_jquery_admin_version',
        // 'jquery_update_jquery_cdn',

        // Hide less.module variables.
        'less_devel',
        'less_dir',
        'less_engine',
        'less_watch',

        // Hide locale.module variables.
        'language_count',
        'language_default',

        // Hide media.module variables.
        'media_icon_base_directory',
        'media_dialogclass',
        'media_modal',
        'media_draggable',
        'media_resizable',
        'media_minwidth',
        'media_width',
        'media_height',
        'media_position',
        'media_zindex',
        'media_backgroundcolor',
        'media_opacity',

        // Hide media_wysiwyg.module variables.
        // 'media_wysiwyg_wysiwyg_allowed_attributes',
        // 'media_wysiwyg_wysiwyg_allowed_types',
        // 'media_wysiwyg_wysiwyg_browser_plugins',
        // 'media_wysiwyg_wysiwyg_default_view_mode',
        // 'media_wysiwyg_wysiwyg_icon_title',
        // 'media_wysiwyg_wysiwyg_upload_directory',
        'media_wysiwyg_view_mode_audio_file_wysiwyg_view_mode',
        'media_wysiwyg_view_mode_audio_file_wysiwyg_view_mode_status',
        'media_wysiwyg_view_mode_audio_wysiwyg_restricted_view_modes',
        'media_wysiwyg_view_mode_audio_wysiwyg_restricted_view_modes_status',
        'media_wysiwyg_view_mode_document_file_wysiwyg_view_mode',
        'media_wysiwyg_view_mode_document_file_wysiwyg_view_mode_status',
        'media_wysiwyg_view_mode_document_wysiwyg_restricted_view_modes',
        'media_wysiwyg_view_mode_document_wysiwyg_restricted_view_modes_status',
        'media_wysiwyg_view_mode_image_file_wysiwyg_view_mode',
        'media_wysiwyg_view_mode_image_file_wysiwyg_view_mode_status',
        'media_wysiwyg_view_mode_image_wysiwyg_restricted_view_modes',
        'media_wysiwyg_view_mode_image_wysiwyg_restricted_view_modes_status',
        'media_wysiwyg_view_mode_video_file_wysiwyg_view_mode',
        'media_wysiwyg_view_mode_video_file_wysiwyg_view_mode_status',
        'media_wysiwyg_view_mode_video_wysiwyg_restricted_view_modes',
        'media_wysiwyg_view_mode_video_wysiwyg_restricted_view_modes_status',

        // Hide memcache.module variables.
        'memcache_wildcard_flushes',

        // Hide module_filter.module variables.
        'module_filter_recent_modules',

        // Hide node.module variables.
        'node_cron_last',

        // Hide panelizer.module variables.
        'panelizer_defaults_file_audio',
        'panelizer_defaults_file_document',
        'panelizer_defaults_file_image',
        'panelizer_defaults_file_report',
        'panelizer_defaults_file_video',
        'panelizer_defaults_node_article',
        'panelizer_defaults_node_bookmark',
        'panelizer_defaults_node_document',
        'panelizer_defaults_node_mention',
        'panelizer_defaults_node_person',
        'panelizer_defaults_taxonomy_term_bookmark_type',
        'panelizer_defaults_taxonomy_term_company_commodities',
        'panelizer_defaults_taxonomy_term_document_category',
        'panelizer_defaults_taxonomy_term_person_positions',
        'panelizer_defaults_taxonomy_term_tags',
        'panelizer_defaults_user_user',

        // Hide recaptcha.module variables.
        'recaptcha_private_key',
        'recaptcha_public_key',

        // Hide rel.module variables.
        'rel_build_form_registration',
        'rel_build_registration_ignore',

        // Hide search_api.module variables.
        'search_api_facets_search_ids',
        'search_api_solr_site_hash',
        'search_api_solr_last_optimize',

        // Hide update.module variables.
        'update_last_check',

        // Hide user.module specific variables.
        'user_pictures',
        'user_register',

        // Hide update_scripts.module variables.
        'update_scripts_clear_cache',
        'update_scripts_directory',
        'update_scripts_revert_features',
        'update_scripts_user_one_updated',

        // Hide variable.module variables.
        'variable_module_list',

        // Hide views.module variables.
        'views_defaults',
        'views_show_additional_queries',

        // Hide views_ui.module variables.
        'views_ui_always_live_preview',
        'views_ui_custom_theme',
        'views_ui_display_embed',
        'views_ui_show_advanced_column',
        'views_ui_show_advanced_help_warning',
        'views_ui_show_listing_filters',
        'views_ui_show_master_display',
        'views_ui_show_performance_statistics',
        'views_ui_show_preview_information',
        'views_ui_show_sql_query',
        'views_ui_show_sql_query_where',

        // Remove Form API weirdness!?!!
        'default_ds_field_settings',
        'default_ds_layout_settings',
        'default_field_group',
        'default_nodes_main',
        'default_page_manager_handlers',
        'tabs__active_tab',
      );

      $variable_name_prefixes = array(
        'helpertheme_svg_icon_',  // helpertheme.module
        'eiti_migration_',  // eiti_migration.module

        'additional_settings__active_tab_',  // node.module
        'cache_flush_',  // memcache.module
        'cache_temporary_flush_',  // memcache.module
      );
      foreach ($component_export['options']['sources'] as $name) {
        foreach ($variable_name_prefixes as $prefix) {
          if (strpos($name, $prefix) === 0) {
            // Only remove the variable and do not display any message.
            unset($component_export['options']['sources'][$name]);
          }
        }
      }
      break;

    case 'views_view':
      // Hide views.
      $entries_list = array(
        'feeds_log',
        'redirects',
      );
      break;

  }

  if (empty($entries_list)) {
    return;
  }

  $removed_entries_list = array();
  foreach ($entries_list as $name) {
    if (isset($component_export['options']['sources'][$name])) {
      unset($component_export['options']['sources'][$name]);
      $removed_entries_list[] = check_plain($name);
    }

    if ($component == 'dependencies') {
      if (isset($component_export['options']['detected'][$name])) {
        unset($component_export['options']['detected'][$name]);
      }
    }
  }
}

/**
 * Implements hook_features_api_alter().
 *
 * Prevent exporting of some features API components.
 *
 * @param array $components
 */
function helpergeneric_features_api_alter(&$components) {
  // We manage menu_links manually or via update scripts.
  unset($components['menu_links']);
}

/**
 * Implements hook_form_features_export_form_alter().
 */
function helpergeneric_form_features_export_form_alter(&$form, &$form_state, $form_id) {
  // Always expand Advanced Options fieldset on feature export forms.
  $form['advanced']['#collapsed'] = FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter() for node_form().
 *
 * @param array $form
 * @param array $form_state
 * @param string $form_id
 */
function helpergeneric_form_node_form_alter(&$form, &$form_state, $form_id) {
  if (helpergeneric_cleanup_ui()) {
    // Do not display as vertical tabs.
    unset($form['additional_settings']['#type']);

    if (isset($form['menu'])) {
      $form['menu']['#access'] = FALSE;
    }

    if (isset($form['revision_information'])) {
      $form['revision_information']['#access'] = FALSE;
    }

    if (isset($form['options']['promote'])) {
      $form['options']['promote']['#access'] = FALSE;
    }

    // We don't need to hide these anymore.
    // if (isset($form['options']['sticky'])) {
    //   $form['options']['sticky']['#access'] = FALSE;
    // }
  }

  // Add Cancel link.
  // A destination in $_GET always overrides the function arguments.
  // We do not allow absolute URLs to be passed via $_GET, as this can be an attack vector.
  $cancel_link_options = array();
  if (isset($_GET['destination']) && !url_is_external($_GET['destination'])) {
    $destination = drupal_parse_url($_GET['destination']);
    $cancel_link_path = $destination['path'];
    $cancel_link_options['query'] = $destination['query'];
    $cancel_link_options['fragment'] = $destination['fragment'];
  }
  else if (!empty($form_state['node']->nid)) {
    $entity_uri = entity_uri('node', $form_state['node']);
    $cancel_link_path = $entity_uri['path'];
  }

  if (isset($cancel_link_path)) {
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => $cancel_link_path,
      '#options' => $cancel_link_options,
      '#weight' => 20,
    );
  }

  // Restrict summary length.
  $form['#validate'][] = 'helpergeneric_node_form_summary_validate';
}

/**
 * Form validation handler for node_form_alter().
 *
 * @param array $form
 * @param array $form_state
 * @param string $form_id
 */
function helpergeneric_node_form_summary_validate($form, &$form_state) {
  $entity = $form_state['node'];

  if (isset($entity->body)) {
    $body_field_language = field_language('node', $entity, 'body', $entity->language);
    if (!empty($form_state['values']['body'][$body_field_language][0]['summary'])) {
      $teaser_length = variable_get('teaser_length', 600);
      $summary_length = drupal_strlen(trim($form_state['values']['body'][$body_field_language][0]['summary']));
      if ($summary_length > $teaser_length) {
        form_set_error('body][und][0][summary', t('The Summary must be less than %max characters, you provided %count characters.', array('%max' => $teaser_length, '%count' => $summary_length)));
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_profile_form().
 *
 * @param array $form
 * @param array $form_state
 * @param string $form_id
 */
function helpergeneric_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  if (!helpergeneric_cleanup_ui()) {
    return;
  }

  // Allow user administrators should also be able to change assigned roles.
  if (isset($form['account']['roles']['#access'])) {
    $roles = array_map('check_plain', user_roles(TRUE));
    $form['account']['roles']['#access'] = $roles && user_access('administer users');
  }

  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  if (isset($form['profile_main']['redirect'])) {
    $form['profile_main']['redirect']['#access'] = FALSE;
  }
}

/**
 * Implements hook_form_alter().
 *
 * @param array $form
 * @param array $form_state
 * @param string $form_id
 */
function helpergeneric_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_login') {
    if (arg(0) == 'user') {
      // Only update on the login page. And not the 403 pages.
      drupal_set_title('Log in');
    }

    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Request new password'),
      '#href' => 'user/password',
      '#weight' => 20,
    );
  }

  if (in_array($form_id, array('file_entity_add_upload', 'media_internet_add_upload', 'media_wysiwyg_format_form'))) {
    if (!helpergeneric_cleanup_ui()) {
      return;
    }

    if (isset($form['redirect'])) {
      $form['redirect']['#access'] = FALSE;
    }

    if (isset($form['options']['fields']['redirect'])) {
      $form['options']['fields']['redirect']['#access'] = FALSE;
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for file_entity_edit().
 *
 * @param array $form
 * @param array $form_state
 * @param string $form_id
 */
function helpergeneric_form_file_entity_edit_alter(&$form, &$form_state, $form_id) {
  if (!helpergeneric_cleanup_ui()) {
    return;
  }

  if (isset($form['path'])) {
    $form['path']['#access'] = FALSE;
  }

  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  if (isset($form['user'])) {
    $form['user']['#access'] = FALSE;
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for taxonomy_overview_vocabularies().
 *
 * @param array $form
 * @param array $form_state
 */
function helpergeneric_form_taxonomy_overview_vocabularies_alter(&$form, $form_state) {
  // Well, we want to hide "Add term" for cases where user doesn't have access for those.
  $elements = element_children($form);
  foreach ($elements as $element) {
    if (!empty($form[$element]['add'])) {
      $vid = $element;
      if (!user_access("helpergeneric add taxonomy terms in $vid") && !user_access('administer taxonomy')) {
        unset($form[$element]['add']);
      }
    }
    if (!empty($form[$element]['edit']) && !user_access('administer taxonomy')) {
      unset($form[$element]['edit']);
    }
  }
}
