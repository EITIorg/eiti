<?php
/**
 * @file
 * Default theme implementation to display a file.
 *
 * @var array $content
 */
?>

<?php
  // We hide the links now so that we can render them later.
  hide($content['links']);
  print render($content);
?>
