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
<html class="no-js" <?php print $html_attributes; ?>>
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <script type="text/javascript" src="//downloads.mailchimp.com/js/signup-forms/popup/embed.js" data-dojo-config="usePlainJson: true, isDebug: false"></script><script type="text/javascript">require(["mojo/signup-forms/Loader"], function(L) { L.start({"baseUrl":"mc.us5.list-manage.com","uuid":"691e61806662528c68908252f","lid":"6aa20b6ee3"}) })</script>
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
