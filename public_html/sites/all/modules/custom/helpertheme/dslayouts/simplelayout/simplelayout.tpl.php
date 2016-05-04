<?php

/**
 * @file
 * Custom DS layout template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="custom-layout custom-simplelayout <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <<?php print $main_wrapper; if (isset($main_attributes)) { print drupal_attributes($main_attributes);} ?> class="group-main <?php print $main_classes; ?>">
    <?php print $main; ?>

    <?php if (!empty($drupal_render_children)): ?>
      <?php print $drupal_render_children ?>
    <?php endif; ?>
  </<?php print $main_wrapper ?>>

</<?php print $layout_wrapper ?>>
