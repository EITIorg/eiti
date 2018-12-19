<?php

/**
 * @file
 * Contains EITIApiRevenueStreams.
 */

/**
 * Class EITIApiRevenueStreams
 */
class EITIApiRevenueStreams extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Let's expose some data, as few as needed.
    $public_fields['type'] = array(
      'property' => 'type',
    );
    $public_fields['gfs'] = array(
      'property' => 'gfs_code_id',
      'resource' => array(
        'gfs_code' => array(
          'name' => 'gfs_code',
          'major_version' => 1,
          'minor_version' => 0,
        ),
      )
    );
    $public_fields['report_status'] = array(
      'property' => 'report_status',
    );
    $public_fields['organisation'] = array(
      'callback' => array($this, 'getOrganisation'),
      'property' => 'organisation_id',
    );
    $public_fields['revenue'] = array(
      'property' => 'revenue',
    );
    $public_fields['currency'] = array(
      'property' => 'currency',
    );
    return $public_fields;
  }

  /**
   * Gets the value of the organisation.
   */
  public function getOrganisation($value_emw) {
    $organisation = $value_emw->organisation_id->value();

    // These are extra, we don't need'em.
    unset($organisation->status);
    unset($organisation->created);
    unset($organisation->changed);
    return $organisation;
  }
}
