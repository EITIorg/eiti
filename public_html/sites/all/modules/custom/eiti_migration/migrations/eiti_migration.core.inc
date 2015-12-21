<?php

/**
 * @file
 * Contains Migrations classes used for migrations.
 */

/**
 * Migration used to migrate users from the legacy to the new system.
 */
class EITIUsersMigration extends DrupalUser7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Let's add some metadata.
    $this->description = t('This migration is used to pull all the users from the legacy system to the new one. Preserving their roles.');
    $this->team[] = new MigrateTeamMember('Sergiu Nagailic', 'snagailic@developmentgateway.org', t('Developer'));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    // @TODO
    // Decide the roles.
  }
}
