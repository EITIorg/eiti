<?php
/**
 * @file
 * Markup for the site footer.
 *
 * @var string $classes
 * @var string $identity
 * @var string $contact
 * @var string $information
 * @var string $social
 * @var string $legal_navigation
 * @var string $legal
 * @var string $site_navigation
 */
?>

<footer role="contentinfo" class="<?php print $classes; ?>">
  <?php print render($identity); ?>

  <div class="columns clearfix">
    <div class="footer-column footer-contact-wrapper">
      <?php print render($contact); ?>
    </div>
    <div class="footer-column footer-information-wrapper">
      <?php print render($information); ?>
    </div>
    <div class="footer-column footer-social-wrapper">
      <?php print render($social); ?>
    </div>
    <div class="footer-column footer-navigation-legal-wrapper">
      <?php print render($legal_navigation); ?>
      <?php print render($legal); ?>
    </div>
  </div>
</footer>

<div id="site-navigation" class="footer-site-navigation-wrapper clearfix">
  <?php print render($site_navigation); ?>
</div>
