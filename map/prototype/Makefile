# This file can be used to install, update, backup or destroy an environment.

# To execute a target ('command'), just type `make` followed by the
# name of the command.

# The default target, if no target argument is provided to `make`.
# Build the project
build:
	@echo 'Building CSS files...'
	@npm run build
	@echo "Don't forget to update the Drupal content widget by running 'make update-library'"
	@echo 'Done!'

# Update the library installed in Drupal.
update-library:
	@echo 'Copying library to Drupal...'
	@test -f dist/js/mapWidgets.js || (echo -e '\E[33m'"[ERROR] Please run 'make build'!"'\033[0m'; exit 16)
	@test -d ../../public_html/sites/all/libraries || (echo -e '\E[33m'"[ERROR] Could not locate the Drupal libraries folder!"'\033[0m'; exit 16)
	@echo "Removing "`realpath ../../public_html/sites/all/libraries/eiti-maps`
	@rm -rf ../../public_html/sites/all/libraries/eiti-maps
	@echo "Copying dist to "`realpath ../../public_html/sites/all/libraries/eiti-maps`
	@cp -r dist ../../public_html/sites/all/libraries/eiti-maps
	@echo "Done!"
