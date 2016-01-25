<?php

/**
 * @file
 * Contains EITIApiSummaryData.
 */

/**
 * Class EITIApiSummaryData
 */
class EITIApiSummaryData extends RestfulEntityBase {
  /**
   * Overrides RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['links'] = array(
      'property' => 'field_sd_file_links',
      'sub_property' => 'url',
    );

    $public_fields['email'] = array(
      'property' => 'field_sd_contact_email_address',
    );

    $public_fields['government_entities_nr'] = array(
      'property' => 'field_sd_no_reporting_gov',
    );

    $public_fields['company_entities_nr'] = array(
      'property' => 'field_sd_no_reporting_com',
    );

//    $public_fields['country'] = array(
//      'property' => 'country_id',
//      'resource' => array(
//        'implementing_country' => 'implementing_country',
//      ),
//    );
    return $public_fields;
  }
}
