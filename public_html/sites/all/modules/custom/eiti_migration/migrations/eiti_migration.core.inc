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


  /**
   * We need to do some work to properly import users.
   */
  public function prepareRow($row) {
    parent::prepareRow($row);

    // Fetch the old role and find out what is the correct new role.
    $query = Database::getConnection('default', 'legacy')->select('users_roles', 'ur');
    $query->join('role', 'r', 'ur.rid = r.rid');
    $query->fields('ur', array('rid'));
    $query->fields('r', array('name'));
    $query->condition('uid', $row->uid);
    $result = $query->execute();
    foreach ($result as $role_row) {
      $new_role = user_role_load_by_name($role_row->name);
      $row->roles[] = $new_role->rid;
    }
  }
}
