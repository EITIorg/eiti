<?php

/**
 * @file
 * Custom DS layout template.
 *
 * @var string $layout_wrapper
 * @var string $layout_attributes
 * @var string $classes
 * @var array $title_suffix
 * @var string $above
 * @var string $above_wrapper
 * @var string $above_classes
 * @var string $main
 * @var string $main_wrapper
 * @var array $main_attributes
 * @var string $main_classes
 * @var string $below
 * @var string $below_wrapper
 * @var string $below_classes
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="custom-layout custom-widelayout <?php print $classes;?>">

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>

<?php if (isset($above)): ?>
  <<?php print $above_wrapper ?> class="group-above <?php print $above_classes; ?>">
  <?php print $above; ?>
  </<?php print $above_wrapper ?>>
<?php endif; ?>

<<?php print $main_wrapper; if (isset($main_attributes)) { print drupal_attributes($main_attributes);} ?> class="group-main <?php print $main_classes; ?>">
<?php print $main; ?>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
</<?php print $main_wrapper ?>>

<?php if (isset($below)): ?>
  <<?php print $below_wrapper ?> class="group-below <?php print $below_classes; ?>">
  <?php print $below; ?>
  </<?php print $below_wrapper ?>>
<?php endif; ?>

</<?php print $layout_wrapper ?>>
