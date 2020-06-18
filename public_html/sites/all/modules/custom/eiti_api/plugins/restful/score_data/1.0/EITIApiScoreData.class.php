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
    // To show validation standard in api/v1.0/score_data results
    $public_fields['standard'] = [
      'callback' => [$this, 'getStandards'],
    ];

    return $public_fields;
  }

  /**
   * Gets standards from field_score_req_standard.
   *
   * @param $emw
   *   EntityMetadataWrapper object.
   *
   * @return mixed
   *   Either NULL or an array of standards.
   */
  function getStandards($emw) {
    if (isset($emw->field_field_validation_against)) {
      $standard = $emw->field_field_validation_against->value();
      if (!empty($standard->name)) {
        return $standard->name;
      }
    }
    return NULL;
  }

}
