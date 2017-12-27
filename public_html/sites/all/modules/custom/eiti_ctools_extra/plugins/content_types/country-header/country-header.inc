<?php

/**
 * @file
 * Country header containing the banner, logo and various other information.
 */

$plugin = array(
  'title' => t('Country Header'),
  'description' => t('Country header containing the banner, logo and various other information.'),
  'category' => t('Widget Library'),
  'render callback'  => 'eiti_ctools_extra__country_header__render',
  'edit form' => 'eiti_ctools_extra__country_header__settings_form',
  // HACK: Avoid missing context issue.
  // 'required context' => array(
  //   new ctools_context_required(t('Implementing Country'), 'implementing_country'),
  // ),
  'defaults' => array(
    'title_display' => '',
    'background_style' => '',
  ),
);

/**
 * Output function for the 'Country Header' content type.
 */
function eiti_ctools_extra__country_header__render($subtype, $conf, $panel_args, $context) {
  if (!empty($context[0]->data) && $context[0]->plugin == 'entity:implementing_country') {
    /** @var ImplementingCountryEntity $entity */
    $entity = $context[0]->data;
  }
  else if (arg(0) == 'implementing_country') {
    /** @var ImplementingCountryEntity $entity */
    $entity = menu_get_object('implementing_country');
  }

  if (empty($entity)) {
    return NULL;
  }

  /** @var EntityMetadataWrapper $entity_wrapper */
  $entity_type = $entity->entityType();
  $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);

  $block['banner'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'country-banner-wrapper',
      ),
    )
  );

  $entity_language = entity_language($entity_type, $entity);
  $image_field_language = field_language($entity_type, $entity, 'field_ic_cover', $entity_language);
  if (!empty($entity->field_ic_cover[$image_field_language][0])) {
    $cover_image_data = $entity->field_ic_cover[$image_field_language][0];

    // Use the featured image as background image.
    $entity_id = entity_id($entity_type, $entity);
    $selector_prefix = implode('-', array($entity_type, $entity_id));

    $with_overlay = TRUE;
    if (isset($conf['background_style']) && $conf['background_style'] == 'no-overlay') {
      $with_overlay = FALSE;
    }

    helpertheme_get_background_image_with_overlay($block['banner'], $cover_image_data, $selector_prefix, $with_overlay);
  }
  else {
    $block['banner']['#attributes']['class'][] = 'no-background-image';
  }

  $block['banner']['overlay']['name_and_logo'] = array(
    '#type' => 'html_container',
    '#tag' => 'h1',
    '#attributes' => array(
      'class' => array(
        'page-title',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );

  // Add the country "logo" image.
  if (!empty($entity->field_ic_logo)) {
    $logo_file_info = $entity_wrapper->field_ic_logo->value();
    $logo_file_uri = $logo_file_info['uri'];
    $logo_file_alt_text = $logo_file_info['field_file_image_alt_text'];

    // Create the logo URL.
    $style_name = 'logo-scaled-height';
    $logo_url = image_style_url($style_name, $logo_file_uri);

    $block['banner']['overlay']['name_and_logo']['logo'] = array(
      '#theme' => 'image',
      '#path' => $logo_url,
      '#alt' => $logo_file_alt_text,
      '#attributes' => array('role' => 'presentation'),
      '#weight' => -1,
    );
  }

  $block['banner']['overlay']['name_and_logo']['name'] = array(
    '#type' => 'html_tag',
    '#tag' => 'span',
    '#value' => $entity_wrapper->label(),
    '#attributes' => array('class' => array('name')),
  );
  if (!empty($conf['title_display'])) {
    $block['banner']['overlay']['name_and_logo']['name']['#attributes']['class'][] = drupal_clean_css_identifier($conf['title_display']);
  }

  $block['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'country-information-wrapper',
      ),
    ),
    '#prefix' => '<div class="single-fluid-row-wrapper">',
    '#suffix' => '</div>',
  );

  // Add the country status information.
  if (!empty($entity->field_ic_status)) {
    $term = $entity_wrapper->field_ic_status->value();
    $value = entity_label('taxonomy_term', $term);

    $block['info']['status'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('EITI Status'),
      '#title_tag' => 'span',
      '#title_icon' => array(
        'symbol' => 'status',
        'options' => array('width' => '1em', 'height' => '1em'),
      ),
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'info',
        ),
      ),
    );

    $block['info']['status']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $value,
      '#attributes' => array('class' => array('value')),
    );
  }

  // Add the country status change information.
  if (!empty($entity->field_ic_change_status_date)) {
    $timestamp = $entity_wrapper->field_ic_change_status_date->value();
    $value = format_date($timestamp, 'custom', 'Y');

    $block['info']['date'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('EITI Member Since'),
      '#title_tag' => 'span',
      '#title_icon' => array(
        'symbol' => 'member',
        'options' => array('width' => '1em', 'height' => '1em'),
      ),
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'info',
        ),
      ),
    );

    $block['info']['date']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $value,
      '#attributes' => array('class' => array('value')),
    );
  }

  // Add the country latest summary data information.
  $query = db_select('eiti_summary_data');
  $latest_summary_data_timestamp = $query->condition('country_id', $entity->identifier())
    ->orderBy('year_end', 'DESC')
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if (!empty($latest_summary_data_timestamp)) {
    $value = format_date($latest_summary_data_timestamp, 'custom', 'Y');

    $block['info']['latest_data'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Latest Data From'),
      '#title_tag' => 'span',
      '#title_icon' => array(
        'symbol' => 'crosshair',
        'options' => array('width' => '1em', 'height' => '1em'),
      ),
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'info',
        ),
      ),
    );

    $block['info']['latest_data']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $value,
      '#attributes' => array('class' => array('value')),
    );
  }

  // Add the country latest validation information.
  if (!empty($entity->field_ic_validation_date)) {
    $timestamp = $entity_wrapper->field_ic_validation_date->value();

    $latest_validation_year = format_date($timestamp, 'custom', 'Y');

    $value = $latest_validation_year;

    if (!empty($entity->field_ic_validation_link)) {
      $node = $entity_wrapper->field_ic_validation_link->value();

      $entity_uri = entity_uri('node', $node);

      $value = l($latest_validation_year, $entity_uri['path']);
    }

    $block['info']['latest_validation_date'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Latest Validation'),
      '#title_tag' => 'span',
      '#title_icon' => array(
        'symbol' => 'validation',
        'options' => array('width' => '1em', 'height' => '1em'),
      ),
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'info',
        ),
      ),
    );

    $block['info']['latest_validation_date']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $value,
      '#attributes' => array('class' => array('value')),
    );
  }
  // Add the country website information.
  if (!empty($entity->field_ic_website)) {
    $url_info = $entity_wrapper->field_ic_website->value();
    $value = l($url_info['title'], $url_info['url'], $url_info);

    $block['info']['website'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Website'),
      '#title_tag' => 'span',
      '#title_icon' => array(
        'symbol' => 'website',
        'options' => array('width' => '1em', 'height' => '1em'),
      ),
      '#title_attributes' => array('class' => array('label')),
      '#attributes' => array(
        'class' => array(
          'info',
        ),
      ),
    );

    $block['info']['website']['value'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $value,
      '#attributes' => array('class' => array('value')),
    );
  }

  return (object) array(
    'content' => $block,
  );
}

/**
 * Settings form for the country header.
 */
function eiti_ctools_extra__country_header__settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $cleanup_list = array(
    'context',
    'override_title',
    'override_title_text',
    'override_title_heading',
    'override_title_markup',
  );
  foreach ($cleanup_list as $key) {
    if (isset($form[$key])) {
      $form[$key]['#access'] = FALSE;
    }
  }

  $form['title_display'] = array(
    '#title' => t('Title Display'),
    '#type' => 'select',
    '#options' => array(
      '' => t('Default'),
      'element-invisible' => t('No Title'),
    ),

    '#default_value' => $conf['title_display'],
  );

  $form['background_style'] = array(
    '#title' => t('Background Style'),
    '#type' => 'select',
    '#options' => array(
      '' => t('Default'),
      'no-overlay' => t('No overlay'),
    ),

    '#default_value' => $conf['background_style'],
  );

  return $form;
}

function eiti_ctools_extra__country_header__settings_form_submit($form, &$form_state) {
  // Remove unneeded values.
  form_state_values_clean($form_state);

  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
