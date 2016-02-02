<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class RevenueStreamEntity extends HelperEntity {
  // Define some default values.
  public $id = NULL;
  public $type = '';
  public $gfs_code_id = NULL;
  public $report_status = NULL;
  public $name = NULL;
  public $organisation_id = NULL;

  public $revenue = NULL;
  public $currency = NULL;
  public $original_revenue = NULL;
  public $original_currency = NULL;

  /**
   * Getter callback for gfs_code_id.
   *
   * @return entity
   *   GFS Code entity.
   */
  public function gfscodeid() {
    return entity_load_single('gfs_code', $this->gfs_code_id);
  }

  /**
   * Setter for gfs_code_id.
   *
   * @param entity $gfs_code
   *
   *  GFS Code entity instance.
   */
  public function setGfscodeid($gfs_code) {
    $this->gfs_code = is_object($gfs_code->id) ? $gfs_code->id : $gfs_code;
  }
  /**
   * Getter callback for organisation_id.
   *
   * @return entity
   *   Organisation entity.
   */
  public function organisationid() {
    return entity_load_single('organisation', $this->organisation_id);
  }

  /**
   * Setter for organisation_id.
   *
   * @param entity $organisation
   *
   *  Organisation entity instance.
   */
  public function setOrganisationid($organisation) {
    $this->organisation_id = is_object($organisation->id) ? $organisation->id : $organisation;
  }
}
