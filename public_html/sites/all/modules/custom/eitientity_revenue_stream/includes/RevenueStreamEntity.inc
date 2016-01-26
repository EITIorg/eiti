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
}
