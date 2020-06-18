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

  /**
   * Get subsections structure for disclosure checklist section
   */
  public function disclosureCheclishGetSubsections() {
    return array(
      'EITI Requirement 2.1: Legal framework and fiscal regime',
      'EITI Requirement 2.2: Contract and license allocations',
      'EITI Requirement 2.3: Register of licenses',
      'EITI Requirement 2.4: Contract disclosure',
      'EITI Requirement 2.5: Beneficial ownership',
      'EITI Requirement 2.6: State participation',
      'EITI Requirement 3.1: Exploration',
      'EITI Requirement 3.2: Production by commodity',
      'EITI Requirement 3.3: Exports',
      'EITI Requirement 4.1: Comprehensiveness',
      'EITI Requirement 4.2: In-kind revenues',
      'EITI Requirement 4.3: Barter agreements',
      'EITI Requirement 4.4: Transportation revenues',
      'EITI Requirement 4.5: SOE transactions',
      'EITI Requirement 4.6: Direct subnational payments',
      'EITI Requirement 4.8: Data timeliness',
      'EITI Requirement 4.9: Data quality',
      'EITI Requirement 5.1: Distribution of extractive industry revenues',
      'EITI Requirement 5.2: Subnational transfers',
      'EITI Requirement 5.3: Revenue management and expenditures',
      'EITI Requirement 6.1: Social expenditures',
      'EITI Requirement 6.2: Quasi-fiscal expenditures',
      'EITI Requirement 6.3: Economic contribution',
      'EITI Requirement 6.4: Environmental impact',
    );
  }

  /**
   * Get elements to be skipped during data parsing
   */
  public function disclosureCheclishGetSkipItems() {
    return array(
      'Does the government publish information about',
      '(Harmonised System Codes)',
      'If yes, what was the volume received?',
      'If yes, what was sold?',
    );
  }

  /**
   * Get sections for Reporting entities tab
   */
  public function reportingEntitiesSections() {
    return array(
      'Reporting government entities list',
      "Reporting companies' list",
      "Reporting projects' list",
    );
  }

  /**
   * Get skip rows items for Reporting entities section
   */
  public function reportingEntitiesSkipRows() {
    return array(
      'Full name of agency',
      'Company ID references',
      'Tax Identification Number',
      'Full company name',
      'Full project name',
    );
  }

  /**
   * Get list of possible untis
   */
  public function getUnits() {
    $units = [
      'Sm3',
      'Sm3 o.e.',
      'Barrels',
      'Tonnes',
      'oz',
      'carats',
      'Scf',
      'employees',
      'm3',
      'person',
      'people'
    ];

    $currencies = $this->getCurrenciesList();
    $units = array_merge($units, $currencies);

    return $units;
  }

  /**
   * Get list of possible currencies
   */
  public function getCurrenciesList() {
    $list = [
      'AED',
      'AFN',
      'ALL',
      'AMD',
      'ANG',
      'AOA',
      'ARS',
      'AUD',
      'AWG',
      'AZN',
      'BAM',
      'BBD',
      'BDT',
      'BGN',
      'BHD',
      'BIF',
      'BMD',
      'BND',
      'BOB',
      'BRL',
      'BSD',
      'BTN',
      'BWP',
      'BYR',
      'BZD',
      'CAD',
      'CDF',
      'CHF',
      'CLF',
      'CNH',
      'COP',
      'CRC',
      'CUC',
      'CVE',
      'CZK',
      'DJF',
      'DKK',
      'DOP',
      'DZD',
      'EGP',
      'ERN',
      'ETB',
      'EUR',
      'FJD',
      'FKP',
      'GBP',
      'GEL',
      'GGP',
      'GHS',
      'GIP',
      'GMD',
      'GNF',
      'GTQ',
      'GYD',
      'HKD',
      'HNL',
      'HRK',
      'HTG',
      'HUF',
      'IDR',
      'ILS',
      'IMP',
      'INR',
      'IQD',
      'IRR',
      'ISK',
      'JEP',
      'JMD',
      'JOD',
      'JPY',
      'KES',
      'KGS',
      'KHR',
      'KMF',
      'KPW',
      'KRW',
      'KWD',
      'KYD',
      'KZT',
      'LAK',
      'LBP',
      'LKR',
      'LRD',
      'LSL',
      'LYD',
      'MAD',
      'MDL',
      'MGA',
      'MKD',
      'MMK',
      'MNT',
      'MOP',
      'MRO',
      'MUR',
      'MVR',
      'MWK',
      'MXN',
      'MYR',
      'MZN',
      'NAD',
      'NGN',
      'NIO',
      'NOK',
      'NPR',
      'NZD',
      'OMR',
      'PAB',
      'PEN',
      'PGK',
      'PHP',
      'PKR',
      'PLN',
      'PYG',
      'QAR',
      'RON',
      'RSD',
      'RUB',
      'RWF',
      'SAR',
      'SBD',
      'SCR',
      'SDG',
      'SEK',
      'SGD',
      'SHP',
      'SLL',
      'SOS',
      'SRD',
      'SSP',
      'STD',
      'SYP',
      'SZL',
      'THB',
      'TJS',
      'TMT',
      'TND',
      'TOP',
      'TRY',
      'TTD',
      'TVD',
      'TWD',
      'TZS',
      'UAH',
      'UGX',
      'USD',
      'USD',
      'UYU',
      'UZS',
      'VEF',
      'VND',
      'VUV',
      'WST',
      'XAF',
      'XCD',
      'XOF',
      'YER',
      'ZAR',
      'ZMW',
    ];

    return $list;
  }
}
