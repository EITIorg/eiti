
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
      <?php print render($navigation); ?>
      <?php print render($legal); ?>
    </div>
  </div>
</footer>
