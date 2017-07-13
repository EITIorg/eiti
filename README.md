
# Extractive Industries Transparency Initiative
The new version of the https://eiti.org/ portal.

## Requirements

Please see the **happy-deployer** requirements and setup instructions: https://github.com/devgateway/happy-deployer

## HOST: Environment Setup Instructions:

1.  Clone the repo:
    ```
    git clone git@github.com:devgateway/eiti.git eiti-local
    ```

2.  For PREPROD and PRODUCTION environments always use the stable branch.
    ```
    git checkout master
    ```

    For LOCAL and STAGING environments switch to the main develop branch.
    ```
    git checkout develop
    ```

3.  Build the VM and install all required software.
    ```
    cd deployer/
    vagrant up --provision
    ```
    NOTES:

    *   This might take a while! You can add `time` before the command name to see the execution time, it should take about 10 minutes.
        ```
        time vagrant up --provision
        ```

    *   Ignore this message, it just means your computer is slow :p
        ```
        default: Error: Remote connection disconnect. Retrying...
        ```

    *   This one means that you don't have any VirtualBox Guest Additions in the VM, and that you should have patience.
        ```
        No installation found.
        ```

4.  Make sure that your `/etc/hosts` file has been updated and contains the following entries:
    ```
    10.10.10.49  eiti-local.dev  # ...
    10.10.10.49  www.eiti-local.dev  # ...
    ```

5.  You can now SSH into the VM.
    ```
    vagrant ssh
    ```
    NOTE: On windows you can run `vagrant ssh-config` to view the information required for [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/).

6.  For now the visualisations can be be access on [eiti-visualizations-local.dev](http://eiti-visualizations-local.dev/).
    To setup the Drupal project continue with the next set of instructions.


## GUEST: Environment Setup Instructions:

1.  Once inside the VM, run to go into the project folder:
    ```
    cd /var/www/eiti-local/public_html/
    ```

2.  Prepare drupal for installation, run these inside the VM in the project folder:
    *   Prepare the environment by running one of the following commands for your environment:
        ```
        # Prepare environment for local development.
        make prepare-local

        # Prepare environment for staging.
        make prepare-staging

        # Prepare environment for preprod.
        make prepare-preprod

        # Prepare environment for production.
        make prepare-production
        ```
        For staging, preprod and production environments you will need to update the database credentials in `settings.custom.php`.

    *   Check the database connection settings of the project:
        ```
        drush sqlc
        ```
        You should see the DB prompt with the project database selected. To quit, just execute `\q`.

    *   For local development environments copy the sample update script:
        ```
        cp sites/default/update_scripts/environment/setup.local{_sample,}.php
        ```
        Please note that other `setup.*.php` files exist for other environments.

3.  Install the project.
    *   If you have a database dump, you can import it using:
        ```
        zcat DUMP.sql.gz | drush sqlc
        # Make sure to update the project settings for the current environment.
        make update
        ```

    *   Alternatively, if you want a new and clean installation run:
        ```
        make install
        ```

4.  Check if the project has been installed properly, for local development go to: [eiti.local](http://eiti.local/)


## More Info:

* Please follow the [**GitFlow** Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
* Please configure your IDE with [EditorConfig](http://editorconfig.org/). This helps define and maintain consistent coding styles between different editors and IDEs.
