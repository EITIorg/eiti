<?php

/**
 * @file
 * Contains EITIApiScoreData2.
 */

/**
 * Class EITIApiScoreData2
 */
class EITIApiScoreData2 extends EITIApiScoreData {

  /**
   * Overrides EITIApiScoreData::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // References.
    $public_fields['country']['resource']['normal']['major_version'] = 2;

    $public_fields['score_req_values']['process_callbacks'] = array(array($this, 'prepareScoreReqValues'));

    return $public_fields;
  }

  /**
   * A standard processing callback for score_req_values.
   */
  function prepareScoreReqValues($score_req_values) {
    foreach ($score_req_values as $key => $sq) {
      if (is_numeric($sq->score_req->created)) {
        $score_req_values[$key]->score_req->created = eiti_api_timestamp_to_iso_8601($sq->score_req->created);
      }
    }
    return $score_req_values;
  }
}
