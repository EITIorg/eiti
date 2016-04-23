<?php

/**
 * @file
 * Country header containing the banner, logo and various other information.
 */

$plugin = array(
  'title' => t('Country Header'),
  'description' => t('Country header containing the banner, logo and various other information.'),
  'category' => t('EITI Country'),
  'render callback'  => 'eiti_ctools_extra__country_header__render',
  'required context' => array(
    new ctools_context_required(t('Implementing Country'), 'implementing_country'),
  ),
);

/**
 * Output function for the 'Country Header' content type.
 */
function eiti_ctools_extra__country_header__render($subtype, $conf, $panel_args, $context) {
  if ($context[0]->plugin == 'entity:implementing_country' && !empty($context[0]->data)) {
    /** @var ImplementingCountryEntity $entity */
    $entity = $context[0]->data;
  }

  if (empty($entity)) {
    return NULL;
  }

  /** @var EntityMetadataWrapper $entity_wrapper */
  $entity_wrapper = entity_metadata_wrapper($entity->entityType(), $entity);

  $block['banner'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'country-banner-wrapper',
        'clearfix',
      ),
    )
  );

  // Add the country "cover" image.
  if (!empty($entity->field_ic_cover)) {
    // Get the file URI.
    $cover_file_info = $entity_wrapper->field_ic_cover->value();
    $cover_file_uri = $cover_file_info['uri'];

    // Get the image URI.
    $style_name = 'bg-large';
    $cover_url = image_style_url($style_name, $cover_file_uri);

    $block['banner']['#attributes']['class'][] = 'with-background-image';
    $block_style = "background-image: url(${cover_url});";
    $block['banner']['#attributes']['style'] = $block_style;
  }
  else {
    $block['banner']['#attributes']['class'][] = 'no-background-image';
  }

  $block['banner']['name_and_logo'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'country-logo-wrapper',
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

    $block['banner']['name_and_logo']['logo'] = array(
      '#theme' => 'image',
      '#path' => $logo_url,
      '#alt' => $logo_file_alt_text,
    );
  }

  $block['banner']['name_and_logo']['name'] = array(
    '#theme' => 'html_tag',
    '#tag' => 'h1',
    '#value' => $entity_wrapper->label(),
    '#attributes' => array('class' => array('page-title')),
  );

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

  // Add the country website information.
  if (!empty($entity->field_ic_website)) {
    $url_info = $entity_wrapper->field_ic_website->value();
    $value = l($url_info['title'], $url_info['url'], $url_info);

    $block['info']['website'] = array(
      '#type' => 'html_container',
      '#tag' => 'div',
      '#title' => t('Country Website'),
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
