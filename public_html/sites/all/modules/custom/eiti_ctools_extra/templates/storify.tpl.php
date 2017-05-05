<?php

/**
 * This is the template for the storify embedded widget.
 */

?>

<div class="storify">
  <iframe src="<?php print $url; ?>/embed?border=false" width="100%" height="750" frameborder="no" allowtransparency="true"></iframe>
  <script src="<?php print $url; ?>.js?border=false"></script>
  <noscript>
    [<a href="<?php print $url; ?>" target="_blank"><?php print $title; ?></a>]
  </noscript>
</div>
