<?php

/**
 * @file
 * Contains EITIApiScoreData.
 */

/**
 * Class EITIApiScoreData
 */
class EITIApiScoreData extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['year'] = array(
      'property' => 'year',
    );
    $public_fields['board_decision_url'] = array(
      'property' => 'board_decision_url',
    );
    $public_fields['validation_documentation'] = array(
      'property' => 'validation_documentation_url',
    );

    // References.
    $public_fields['country'] = array(
      'property' => 'country_id',
      'resource' => array(
        'normal' => array(
          'name' => 'implementing_country',
          'major_version' => 1,
          'minor_version' => 0,
        ),
      ),
    );

    $public_fields['score_req_values'] = array(
      'property' => 'field_scd_score_req_values',
    );
    return $public_fields;
  }
}
