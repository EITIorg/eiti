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
  $html = '';
  if (isset($data->code, $data->data) && $data->code == 200) {
    $json = json_decode($data->data);
    if ($json && isset($json->data[0])) {
      // Based on visualizations/chartWidgets/source/scripts/vendor/scorecard.js
      $hasProgress = FALSE;
      if (isset($json->data[0]->score_req_values[0]->progress_value) && $json->data[0]->score_req_values[0]->progress_value != 3) {
        $hasProgress = TRUE;
      }

      // Requirements.
      $requirements = array();
      foreach ($json->data[0]->score_req_values as $score_value) {
        if (isset($score_value->score_req->field_score_req_category->und[0]->tid)) {
          $category_tid = $score_value->score_req->field_score_req_category->und[0]->tid;
          $requirements[$category_tid][] = array(
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

      $theme_args = array(
        'hasProgress' => $hasProgress,
        'categories' => $categories,
        'requirements' => $requirements,
      );
      $html = theme('eiti_pdf_scorecard', $theme_args);
    }
  }
  $mpdf = new Mpdf();
  if ($html) {
    $css = file_get_contents(DRUPAL_ROOT . '/sites/all/libraries/eitiChartWidgets/css/chartWidgets.css');
    $mpdf->WriteHTML($css, 1);
    $css = file_get_contents(__DIR__ . '/../css/pdf.css');
    $mpdf->WriteHTML($css, 1);
    $mpdf->WriteHTML($html, 2);
  }
  $mpdf->Output();
}
