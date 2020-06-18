<?php

/**
 * @file
 * eitiet_organisation.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function eitiet_organisation_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_affiliated_companies_start'.
  $field_bases['field_affiliated_companies_start'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_affiliated_companies_start',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_agency_type'.
  $field_bases['field_agency_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_agency_type',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_audited_financial_state'.
  $field_bases['field_audited_financial_state'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_audited_financial_state',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_commodities'.
  $field_bases['field_commodities'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_commodities',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Aluminium (2606)' => 'Aluminium (2606)',
        'Asbestos (2524)' => 'Asbestos (2524)',
        'Ash and residues (2620)' => 'Ash and residues (2620)',
        'Bitumen and asphalt (2714)' => 'Bitumen and asphalt (2714)',
        'Bituminous mixtures (2715)' => 'Bituminous mixtures (2715)',
        'Chalk (2509)' => 'Chalk (2509)',
        'Chromium (2610)' => 'Chromium (2610)',
        'Coal (2701)' => 'Coal (2701)',
        'Coal gas (2705)' => 'Coal gas (2705)',
        'Cobalt (2605)' => 'Cobalt (2605)',
        'Coke and semi-coke (2704)' => 'Coke and semi-coke (2704)',
        'Copper (2603)' => 'Copper (2603)',
        'Crude oil (2709)' => 'Crude oil (2709)',
        'Diamonds (7102)' => 'Diamonds (7102)',
        'Dolomite (2518)' => 'Dolomite (2518)',
        'Electrical energy (2716)' => 'Electrical energy (2716)',
        'Felspar (2529)' => 'Felspar (2529)',
        'Gold (7108)' => 'Gold (7108)',
        'Granite (2516)' => 'Granite (2516)',
        'Granulated slag (2618)' => 'Granulated slag (2618)',
        'Gypsum (2520)' => 'Gypsum (2520)',
        'Iron (2601)' => 'Iron (2601)',
        'Iron pyrites (2502)' => 'Iron pyrites (2502)',
        'Kaolin (2507)' => 'Kaolin (2507)',
        'Lead (2607)' => 'Lead (2607)',
        'Lignite (2702)' => 'Lignite (2702)',
        'Limestone (2521)' => 'Limestone (2521)',
        'Manganese (2602)' => 'Manganese (2602)',
        'Marble (2515)' => 'Marble (2515)',
        'Mica (2525)' => 'Mica (2525)',
        'Mineral substances not elsewhere specified (2530)' => 'Mineral substances not elsewhere specified (2530)',
        'Molybdenum (2613)' => 'Molybdenum (2613)',
        'Natural barium sulphate (2511)' => 'Natural barium sulphate (2511)',
        'Natural borates and concentrates (2528)' => 'Natural borates and concentrates (2528)',
        'Natural calcium phosphates (2510)' => 'Natural calcium phosphates (2510)',
        'Natural cryolite (2527)' => 'Natural cryolite (2527)',
        'Natural gas (2711)' => 'Natural gas (2711)',
        'Natural graphite (2504)' => 'Natural graphite (2504)',
        'Natural magnesium carbonate (2519)' => 'Natural magnesium carbonate (2519)',
        'Natural sands (2505)' => 'Natural sands (2505)',
        'Natural steatite (2526)' => 'Natural steatite (2526)',
        'Nickel (2604)' => 'Nickel (2604)',
        'Niobium (2615)' => 'Niobium (2615)',
        'Other (2617)' => 'Other (2617)',
        'Other clays (2508)' => 'Other clays (2508)',
        'Other slag and ash (2621)' => 'Other slag and ash (2621)',
        'Peat (2703)' => 'Peat (2703)',
        'Pebbles (2517)' => 'Pebbles (2517)',
        'Petroleum coke (2713)' => 'Petroleum coke (2713)',
        'Petroleum jelly (2712)' => 'Petroleum jelly (2712)',
        'Petroleum oils excluding crude (2710)' => 'Petroleum oils excluding crude (2710)',
        'Pitch and pitch coke (2708)' => 'Pitch and pitch coke (2708)',
        'Portland cement (2523)' => 'Portland cement (2523)',
        'Precious metals (2616)' => 'Precious metals (2616)',
        'Products of the distillation of coal tar (2707)' => 'Products of the distillation of coal tar (2707)',
        'Pumice stone (2513)' => 'Pumice stone (2513)',
        'Quartz (2506)' => 'Quartz (2506)',
        'Quicklime (2522)' => 'Quicklime (2522)',
        'Salt and pure sodium chloride (2501)' => 'Salt and pure sodium chloride (2501)',
        'Siliceous fossil meals (2512)' => 'Siliceous fossil meals (2512)',
        'Silver (7106)' => 'Silver (7106)',
        'Slag (2619)' => 'Slag (2619)',
        'Slate (2514)' => 'Slate (2514)',
        'Sulphur of all kinds (2503)' => 'Sulphur of all kinds (2503)',
        'Tar distilled from coal (2706)' => 'Tar distilled from coal (2706)',
        'Tin (2609)' => 'Tin (2609)',
        'Titanium (2614)' => 'Titanium (2614)',
        'Tungsten (2611)' => 'Tungsten (2611)',
        'Uranium or thorium (2612)' => 'Uranium or thorium (2612)',
        'Zinc (2608)' => 'Zinc (2608)',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_company_type'.
  $field_bases['field_company_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_company_type',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_legal_agreem_ref_num'.
  $field_bases['field_legal_agreem_ref_num'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_legal_agreem_ref_num',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_o_commodities'.
  $field_bases['field_o_commodities'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_o_commodities',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'company_commodities' => 'company_commodities',
        ),
      ),
      'target_type' => 'taxonomy_term',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_o_sector'.
  $field_bases['field_o_sector'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_o_sector',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'entityqueue' => array(
            'status' => 0,
          ),
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'company_sectors' => 'company_sectors',
        ),
      ),
      'target_type' => 'taxonomy_term',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_payments_to_governments'.
  $field_bases['field_payments_to_governments'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_payments_to_governments',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'entity_translation_sync' => FALSE,
      'precision' => 15,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  // Exported field_base: 'field_production'.
  $field_bases['field_production'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_production',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_production_volume'.
  $field_bases['field_production_volume'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_production_volume',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'entity_translation_sync' => FALSE,
      'precision' => 10,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  // Exported field_base: 'field_status'.
  $field_bases['field_status'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_status',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Exploration' => 'Exploration',
        'Production' => 'Production',
        'Development' => 'Development',
        'Other' => 'Other',
        'Not applicable' => 'Not applicable',
      ),
      'allowed_values_function' => '',
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_stock_exchange_listing'.
  $field_bases['field_stock_exchange_listing'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_stock_exchange_listing',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_total_reported'.
  $field_bases['field_total_reported'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_total_reported',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'entity_translation_sync' => FALSE,
      'precision' => 15,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  return $field_bases;
}
