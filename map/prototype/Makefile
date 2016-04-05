# This file can be used to install, update, backup or destroy an environment.
# TODO: Use webpack

# To execute a target ('command'), just type `make` followed by the
# name of the command.

# The default target, if no target argument is provided to `make`.
# Build LESS files
build-css: clean-css
	@echo 'Building CSS files...'
	@lessc source/styles/mapWidgets.less dist/css/mapWidgets.css
	@echo 'Copying source/images to dist...'
	@cp -r source/images dist
	@echo "Don't forget to run webpack and update the Drupal content widget by running 'make update-library'"
	@echo 'Done!'

# Remove built files.
clean-css:
	@echo 'Cleaning dist/css and dist/images.'
	@rm -rf dist/css dist/images

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
