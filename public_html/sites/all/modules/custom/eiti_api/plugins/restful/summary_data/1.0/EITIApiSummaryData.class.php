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

    // Some metadata and related.
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
    $public_fields['year_start'] = array(
      'property' => 'year_start',
    );
    $public_fields['year_end'] = array(
      'property' => 'year_end',
    );

    // Covered sectors.
    $public_fields['sector_oil'] = array(
      'property' => 'field_sd_oil_sector',
    );
    $public_fields['sector_mining'] = array(
      'property' => 'field_sd_mining_sector',
    );
    $public_fields['sector_gas'] = array(
      'property' => 'field_sd_gas_sector',
    );
    $public_fields['sector_other'] = array(
      'property' => 'field_sd_other_sector',
    );

    // References.
    $public_fields['country'] = array(
      'property' => 'country_id',
      'resource' => array(
        'normal' => 'implementing_country',
      ),
    );
    $public_fields['indicator_values'] = array(
      'property' => 'field_sd_indicator_values',
      'resource' => array(
        'indicator_value' => 'indicator_value',
      ),
    );
    $public_fields['revenue_government'] = array(
      'property' => 'field_sd_revenue_government',
    );
    $public_fields['revenue_company'] = array(
      'property' => 'field_sd_revenue_company',
    );
    return $public_fields;
  }
}
