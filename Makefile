## This file can be used to perform various tasks on the environment.

## To execute a target ('command'), just type `make` followed by the
## name of the command.


## Backups directory (without a trailing slash).
BACKUPS_DIRECTORY='/var/backup'


## Get the full path to the current directory, without using `pwd`
ROOT_DIRECTORY=$$(dirname $$(readlink -e $(lastword $(MAKEFILE_LIST))))

## Backup file name prefix.
NAME_PREFIX=$$(basename $(ROOT_DIRECTORY))--$$(date +'%y%m%d-%H%M')


## Avoid conflicts with files of the same name
## @see: http://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Phony-Targets.html
.PHONY: dummy backup backup-db backup-files fix fix-permissions

## The default target, if no target argument is provided to `make`.
## Update an environment with the latest changes from code.
dummy:
	@echo 'Here is a list of available commands:'
	@grep -iE "^[a-z_-]+:" $(lastword $(MAKEFILE_LIST)) | cut -d: -f1 | grep -v dummy | xargs -i{} echo "  $$ make {}"


## Backup the database and user uploaded files.
backup: backup-db backup-files
	@echo 'Finished creating a full system backup.'


## Backup the database.
backup-db:
	@# Make sure the environment is prepared.
	@test -e 'public_html/sites/default/settings.custom.php' || (echo 'Missing settings.custom.php, exiting...'; exit 8)
	@echo "Backing-up the project database."
	@time drush --root=$(ROOT_DIRECTORY)/public_html sql-dump --gzip --result-file=$(BACKUPS_DIRECTORY)/$(NAME_PREFIX).sql
	@echo 'Site database backup created.'


## Backup the user uploaded files.
backup-files:
	@# Make sure the environment is prepared.
	@test -d 'public_html/sites/default/files' || (echo 'Files directory not found.'; exit 16)
	@echo Backing-up `du --si -sm public_html/sites/default/files | cut -f1 -` Mb of user uploaded files.
	@time tar -C public_html/sites/default \
		--exclude=css \
		--exclude=ctools \
		--exclude=languages \
		--exclude=less \
		--exclude=js \
		--exclude=styles \
		--exclude=backup_migrate \
		-czf $(BACKUPS_DIRECTORY)/$(NAME_PREFIX).files.tgz files
	@echo 'Site files backup created.'


## Alias of fix-permissions
fix: fix-permissions
	@echo ''

## Fix file permissions for an environment.
fix-permissions:
	@# Make sure the environment is prepared.
	@test -e $(ROOT_DIRECTORY)'/public_html/sites/default/settings.custom.php' || (echo 'Missing settings.custom.php, exiting...'; exit 8)
	@echo "Fixing permissions for: "$(ROOT_DIRECTORY)
	@test -e '/usr/local/sbin/setup_environment' || (echo -e 'Missing setup_environment script, exiting...\nSee docs section: Setup linux server permissions for a Drupal environment'; exit 9)
	@sudo /usr/local/sbin/setup_environment $(ROOT_DIRECTORY)
	@echo 'Finished resetting file permissions.'
