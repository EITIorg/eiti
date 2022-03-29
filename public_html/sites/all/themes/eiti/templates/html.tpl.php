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
  <meta name="robots" content="noindex">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <!-- Google Tag Manager -->
  <script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push(
      {'gtm.start': new Date().getTime(),event:'gtm.js'}
    );var f=d.getElementsByTagName(s)[0],
      j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
      'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
    })(window,document,'script','dataLayer','GTM-W57C5B4');</script>
  <!-- End Google Tag Manager -->
  <?php print $scripts; ?>
  <script type="text/javascript" src="//downloads.mailchimp.com/js/signup-forms/popup/embed.js" data-dojo-config="usePlainJson: true, isDebug: false"></script><script type="text/javascript">require(["mojo/signup-forms/Loader"], function(L) { L.start({"baseUrl":"mc.us5.list-manage.com","uuid":"691e61806662528c68908252f","lid":"6aa20b6ee3"}) })</script>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <!-- Google Tag Manager (noscript) -->
  <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-W57C5B4"
                    height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
  <!-- End Google Tag Manager (noscript) -->
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>

  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
