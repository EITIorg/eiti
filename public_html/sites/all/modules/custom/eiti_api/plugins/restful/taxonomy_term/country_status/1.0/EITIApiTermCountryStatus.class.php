<?php

/**
 * @file
 * Contains EITIApiTermCountryStatus.
 */

class EITIApiTermCountryStatus extends RestfulEntityBaseTaxonomyTerm {

  /**
   * Overrides RestfulEntityBaseTaxonomyTerm::checkEntityAccess().
   */
  protected function checkEntityAccess($op, $entity_type, $entity) {
    // Deny the ability to override / edit the country status via API.
    if ($op == 'edit') {
      return FALSE;
    }
  }

  /**
   * Overrides the default public fields, adds others.
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    // Some metadata and related.
    $public_fields['color'] = array(
      'property' => 'field_tx_country_color',
    );

    return $public_fields;
  }
}
