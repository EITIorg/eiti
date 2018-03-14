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
      $theme_args = array(
        'data' => $json->data[0],
        'hasProgress' => $hasProgress,
      );
      $html = theme('eiti_pdf_scorecard', $theme_args);
      // $json->data[0]->label
      // $json->data[0]->year
      // $json->data[0]->country->label
      // $json->data[0]->score_req_values[0]->progress_value
    }
  }
  $mpdf = new Mpdf();
  $mpdf->WriteHTML($html);
  $mpdf->Output();
}
