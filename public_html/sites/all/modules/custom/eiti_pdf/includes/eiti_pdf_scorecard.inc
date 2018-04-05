<?php

require DRUPAL_ROOT . '/../vendor/autoload.php';
use \Mpdf\Mpdf;

/**
 * Scorecard PDF page callback.
 */
function eiti_pdf_scorecard_page() {
  $url_options = array('absolute' => TRUE);
  if (isset($_GET['filter'])) {
    $url_options['query']['filter'] = $_GET['filter'];
  }
  $url = url('api/v1.0/score_data', $url_options);
  $data = drupal_http_request($url);

  $html_footer = theme('eiti_pdf_footer');
  $html_title_page = '';
  $html_header = '';
  $html_scorecard_table = '';
  $filename = 'EITI - validation';

  if (isset($data->code, $data->data) && $data->code == 200) {
    $json = json_decode($data->data);
    if ($json && isset($json->data[0])) {
      $score_data = entity_object_load($json->data[0]->id, 'score_data');

      // Title page and header.
      $theme_args = array(
        'logo' => drupal_get_path('module', 'eiti_pdf') . '/images/logo.png',
        'date' => '',
        'title' => '',
        'decision_reference' => '',
      );
      if (isset($score_data->field_scd_pdf_date['und'][0]['value'])) {
        $timestamp = strtotime($score_data->field_scd_pdf_date['und'][0]['value']);
        if ($timestamp) {
          $theme_args['date'] = format_date($timestamp, 'custom', $format = 'j F Y');
        }
      }
      if (isset($score_data->field_scd_pdf_decision_ref['und'][0]['value'])) {
        $theme_args['decision_reference'] = check_plain($score_data->field_scd_pdf_decision_ref['und'][0]['value']);
      }
      if (isset($score_data->field_scd_pdf_title['und'][0]['value'])) {
        $theme_args['title'] = check_plain($score_data->field_scd_pdf_title['und'][0]['value']);
      }
      $html_title_page = theme('eiti_pdf_title_page', $theme_args);
      unset($theme_args['logo']);
      $html_header = theme('eiti_pdf_header', $theme_args);

      // Scorecard table.
      // Based on visualizations/chartWidgets/source/scripts/vendor/scorecard.js
      $hasProgress = FALSE;
      if (isset($json->data[0]->score_req_values[0]->progress_value) && $json->data[0]->score_req_values[0]->progress_value != 3) {
        $hasProgress = TRUE;
      }

      $table_data = _eiti_pdf_get_scorecard_table_data($json);
      $legend_data = _eiti_pdf_get_scorecard_legend_data();

      $theme_args = array(
        'hasProgress' => $hasProgress,
        'categories' => $table_data['categories'],
        'requirements' => $table_data['requirements'],
        'legend_items' => $legend_data['legend_items'],
        'progress_items' => $legend_data['progress_items'],
        'text_before' => '',
        'text_after' => '',
      );
      if (isset($score_data->field_scd_pdf_text1['und'][0]['safe_value'])) {
        $theme_args['text_before'] = $score_data->field_scd_pdf_text1['und'][0]['safe_value'];
      }
      if (isset($score_data->field_scd_pdf_text2['und'][0]['safe_value'])) {
        $theme_args['text_after'] = $score_data->field_scd_pdf_text2['und'][0]['safe_value'];
      }
      $html_scorecard_table = theme('eiti_pdf_scorecard', $theme_args);

      // File name.
      if (isset($json->data[0]->country->label) && $json->data[0]->country->label) {
        $filename = 'EITI - ' . trim(strip_tags($json->data[0]->country->label)) .  ' validation';
      }
      if (isset($timestamp) && $timestamp) {
        $filename .= ' ' . date('Y-m-d', $timestamp);
      }
    }
  }

  // Generate and output the PDF.
  $mpdf_config = array(
    'setAutoTopMargin' => 'stretch',
    'setAutoBottomMargin' => 'stretch',
  );
  $mpdf = new Mpdf($mpdf_config);
  $css = file_get_contents(DRUPAL_ROOT . '/sites/all/libraries/eitiChartWidgets/css/chartWidgets.css');
  $mpdf->WriteHTML($css, 1);
  $css = file_get_contents(__DIR__ . '/../css/pdf.css');
  $mpdf->WriteHTML($css, 1);
  $mpdf->SetHTMLFooter($html_footer);
  if ($html_title_page) {
    $mpdf->WriteHTML($html_title_page, 2);
  }
  if ($html_header) {
    $mpdf->SetHTMLHeader($html_header);
  }
  if ($html_scorecard_table) {
    $mpdf->AddPage();
    $mpdf->WriteHTML($html_scorecard_table, 2);
  }
  $filename = $filename . '.pdf';
  $mpdf->Output($filename, \Mpdf\Output\Destination::INLINE);
}

/**
 * Returns data for the scorecard table.
 */
function _eiti_pdf_get_scorecard_table_data($json) {
  // Requirements.
  // Obtaining initial requirement info is based on the eitientity_score_req_value_get_score_req_information() function.
  $requirements = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'score_req');
  $query->propertyOrderBy('code');
  $results = $query->execute();
  foreach ($results['score_req'] as $result) {
    $score_req = entity_load_single('score_req', $result->id);
    $score_req_emw = entity_metadata_wrapper('score_req', $score_req);
    $category = $score_req_emw->field_score_req_category->value();
    if (!empty($category)) {
      $requirements[$category->tid][$result->id] = array(
        'name' => t(filter_xss($score_req->label())) . ' (#' . check_plain($score_req->code) . ')',
        'description' => '',
        'is_applicable' => TRUE,
        'is_required' => FALSE,
        'value' => -1,
        'progress_value' => -1,
        'print_name' => ($score_req->code == '0.0') ? FALSE : TRUE,
      );
      if ($score_req->code == '0.0') {
        $zero_cat_tid = $category->tid;
      }
    }
  }
  if (isset($requirements[$zero_cat_tid])) {
    $zero_cat = $requirements[$zero_cat_tid];
    unset($requirements[$zero_cat_tid]);
    $requirements[$zero_cat_tid] = $zero_cat;
  }

  foreach ($json->data[0]->score_req_values as $score_value) {
    if (isset($score_value->score_req->field_score_req_category->und[0]->tid)) {
      $category_tid = $score_value->score_req->field_score_req_category->und[0]->tid;
      if ($requirements[$category_tid][$score_value->score_req_id]['value'] != -1) {
        continue;
      }
      $requirements[$category_tid][$score_value->score_req_id] = array(
        'name' => t($score_value->score_req->name) . ' (#' . $score_value->score_req->code . ')',
        'description' => t($score_value->description),
        'is_applicable' => $score_value->is_applicable,
        'is_required' => $score_value->is_required,
        'value' => $score_value->value,
        'progress_value' => $score_value->progress_value,
        'print_name' => ($score_value->score_req->code == '0.0') ? FALSE : TRUE,
      );
    }
  }
  // Add additional information for easier html building and styling.
  foreach ($requirements as $c_tid => $r_vals) {
    $add_category_td = TRUE;
    foreach ($r_vals as $key => $r_val) {
      $requirements[$c_tid][$key]['add_category_td'] = FALSE;
      $requirements[$c_tid][$key]['td_classes'] = '';
      $requirements[$c_tid][$key]['progress_classes'] = 'progress';
      $requirements[$c_tid][$key]['progress_symbol'] = '';
      if ($add_category_td) {
        $requirements[$c_tid][$key]['add_category_td'] = TRUE;
        $add_category_td = FALSE;
      }
      if (!isset($r_vals[$key + 1])) {
        $requirements[$c_tid][$key]['td_classes'] = 'last';
      }
      if ($r_val['progress_value'] == 0) {
        $requirements[$c_tid][$key]['progress_symbol'] = '=';
      }
      elseif ($r_val['progress_value'] == 1) {
        $requirements[$c_tid][$key]['progress_symbol'] = '&rarr;';
        $requirements[$c_tid][$key]['progress_classes'] .= ' value-1';
      }
      elseif ($r_val['progress_value'] == 2) {
        $requirements[$c_tid][$key]['progress_symbol'] = '&larr;';
        $requirements[$c_tid][$key]['progress_classes'] .= ' value-2';
      }
    }
  }

  // Categories.
  $category_voc = taxonomy_vocabulary_machine_name_load('score_requirement_category');
  $category_terms = entity_load('taxonomy_term', FALSE, array('vid' => $category_voc->vid));
  $categories = array();
  foreach ($requirements as $c_tid => $requirement) {
    if (isset($category_terms[$c_tid])) {
      $categories[$c_tid] = array(
        'name' => t($category_terms[$c_tid]->name),
        'count' => count($requirements[$c_tid]),
      );
    }
  }

  $table_data = array(
    'requirements' => $requirements,
    'categories' => $categories
  );
  return $table_data;
}

/**
 * Returns data for the scorecard legend.
 */
function _eiti_pdf_get_scorecard_legend_data() {
  // Legend items.
  $legend_items = array(
    array(
      'classes' => 'no',
      'text' => t('<strong>No progress.</strong> All or nearly all aspects of the requirement remain outstanding and the broader objective of the requirement is not fulfilled.'),
    ),
    array(
      'classes' => 'inadequate',
      'text' => t('<strong>Inadequate progress.</strong> Significant aspects of the requirement have not been implemented and the broader objective of the requirement is far from fulfilled.'),
    ),
    array(
      'classes' => 'meaningful',
      'text' => t('<strong>Meaningful progress.</strong> Significant aspects of the requirement have been implemented and the broader objective of the requirement is being fulfilled.'),
    ),
    array(
      'classes' => 'satisfactory',
      'text' => t('<strong>Satisfactory progress.</strong> All aspects of the requirement have been implemented and the broader objective of the requirement has been fulfilled.'),
    ),
    array(
      'classes' => 'beyond',
      'text' => t('<strong>Beyond.</strong> The country has gone beyond the requirements.'),
    ),
    array(
      'classes' => 'only_encouraged',
      'text' => t('This requirement is only encouraged or recommended and should not be taken into account in assessing compliance.'),
    ),
    array(
      'classes' => 'not_applicable',
      'text' => t('The MSG has demonstrated that this requirement is not applicable in the country.'),
    ),
  );

  // Progress (legend) items.
  $progress_items = array(
    array(
      'classes' => '',
      'symbol' => '=',
      'text' => t('No change in performance since the last Validation.'),
    ),
    array(
      'classes' => 'value-2',
      'symbol' => '&larr;',
      'text' => t('The country is performing worse that in the last Validation.'),
    ),
    array(
      'classes' => 'value-1',
      'symbol' => '&rarr;',
      'text' => t('The country is performing better than in the last Validation.'),
    ),
  );

  $legend_data = array(
    'legend_items' => $legend_items,
    'progress_items' => $progress_items
  );
  return $legend_data;
}
