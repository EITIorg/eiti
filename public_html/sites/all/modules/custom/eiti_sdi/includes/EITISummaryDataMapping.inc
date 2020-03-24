<?php

/**
 * Implements class EITISummaryDataMapping
 */
class EITISummaryDataMapping {

  /**
   * Get mapping values for iteration through About section
   */
  public function getAboutSectionFields() {
    return array(
      'Country or area name' => 'country_id',
      'ISO Alpha-3 Code' => 'field_sd_iso_alpha_3_code',
      'National currency name' => 'field_sd_national_currency_name',
      'National currency ISO-4217' => 'field_sd_nation_currency_iso4217',
      'Start Date' => 'year_start',
      'End Date' => 'year_end',
      'Has an EITI Report been prepared by an Independent Administrator?' => 'field_sd_report_prep_independent',
      'What is the name of the company?' => 'company_id_name',
      'Date that the EITI Report was made public' => 'published',
      'URL, EITI Report' => 'field_sd_report_file',
      'Does the government systematically disclose EITI data at a single location?' => 'field_sd_gov_system_discl_locat',
      'Publication date of the EITI data' => 'field_sd_public_date_eiti_data',
      'Website link (URL) to EITI data' => 'field_sd_site_link_url_eiti_data',
      'Are there other files of relevance?' => 'field_sd_other_files_relecance',
      'Date that other file was made public' => 'field_sd_date_other_file_public',
      'URL' => 'field_sd_file_links',
      'Does the government have an open data policy?' => 'field_sd_goverm_open_data_policy',
      'Open data portal / files' => 'field_sd_open_data_portal_files',
      'Oil' => 'field_sd_oil_sector',
      'Gas' => 'field_sd_gas_sector',
      'Mining (incl. Quarrying)' => 'field_sd_mining_sector',
      'Other, non-upstream sectors' => 'field_sd_other_non_upstr_sectors',
      'If yes, please specify name (insert new rows if multiple)' => 'field_sd_other_sector_name',
      'Number of reporting government entities (incl SOEs if recipient)' => 'field_sd_no_reporting_gov',
      'Number of reporting companies (incl SOEs if payer)' => 'field_sd_no_reporting_com',
      'Reporting currency (ISO-4217 currency codes)' => 'currency_code',
      'Exchange rate used: 1 USD = ' => 'currency_rate',
      'Exchange rate source (URL,…)' => 'field_sd_exchange_rate_src_url',
      '… by revenue stream' => 'field_sd_disagg_revenue_stream',
      '… by government agency' => 'field_sd_disagg_gover_agg',
      '… by company' => 'field_sd_disagg_company',
      '… by project' => 'field_sd_disagg_project',
      'Systematically disclosed' => 'field_sd_systematic_disclosed',
      'Through EITI Reporting' => 'field_sd_through_eiti_reporting',
      'Not applicable' => 'field_sd_not_applicable',
      'Not available' => 'field_sd_not_available',
      'Name' => 'field_sd_contact_name',
      'Organisation' => 'field_sd_contact_organisation',
      'Email address' => 'field_sd_contact_email_address',
    );
  }
}
