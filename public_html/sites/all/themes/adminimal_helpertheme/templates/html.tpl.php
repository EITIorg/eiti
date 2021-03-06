<?php

/**
 * @file
 * Theme implementation to display the basic html structure of a single page.
 *
 * @var string $html_attributes
 * @var string $head
 * @var string $head_title
 * @var string $styles
 * @var string $scripts
 * @var string $classes
 * @var string $attributes
 * @var string $page_top
 * @var string $page
 * @var string $page_bottom
 *
 * NOTES:
 *  - RDF specific variables were removed.
 */
/**
 * Avoid outputting anything before the DOCTYPE declaration. Some browsers took the specification seriously!
 * @see http://www.w3.org/TR/2011/WD-html5-20110525/tokenization.html#before-doctype-name-state
 */
?><!DOCTYPE html>
<html <?php print $html_attributes; ?>>
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
<div id="skip-link">
  <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
</div>

<?php print $page_top; ?>
<?php print $page; ?>
<?php print $page_bottom; ?>
</body>
</html>
