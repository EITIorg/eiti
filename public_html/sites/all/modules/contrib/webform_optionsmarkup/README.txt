Description
-----------
Adds a new "Options with Markup" component to Webforms which allow you to
create Radio Button/Checkbox lists using HTML Markup for the option labels.

Requirements
------------
Drupal 7.x
Webform 4.x

Installation
------------
1. Copy the entire webform directory the Drupal sites/all/modules directory.

2. Login as an administrator. Enable the module in the "Administer" -> "Modules"

3. (Optional) Edit the settings under "Administer" -> "Configuration" ->
   "Content authoring" -> "Webform settings"

NOTES:
------
* The Text Format option "Convert line breaks into HTML (i.e. <br> and <p>)"
  will cause the labels on your options to be wrapped in <p> tags.  For this
  reason, it is recommended that you create a separate text format for use
  with this field rather than using the default "Filtered HTML" format.


