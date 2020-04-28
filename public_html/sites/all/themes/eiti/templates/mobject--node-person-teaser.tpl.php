<?php

/**
 * @file
 * Custom DS CSS Media Object layout template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="custom-layout mobject person-teaser <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (isset($side)): ?>
  <<?php print $side_wrapper ?> class="photo <?php print $side_classes; ?>">
    <?php print $side; ?>
  </<?php print $side_wrapper ?>>
  <?php endif; ?>

  <<?php print $main_wrapper ?> class="info <?php print $main_classes; ?>">
    <?php print $main; ?>

    <?php if (isset($drupal_render_children)): ?>
      <?php print $drupal_render_children ?>
    <?php endif; ?>
  </<?php print $main_wrapper ?>>

</<?php print $layout_wrapper ?>>
