<?php
// @todo document this!
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!empty($title)): ?>
    <div <?php if (!empty($title_wrapper_attributes)) { print drupal_attributes($title_wrapper_attributes); } ?>>
      <<?php print $title_element;?> <?php print $title_attributes; ?>>
      <?php if (!empty($entity_url)): ?>
        <a href="<?php print $entity_url; ?>"><?php print $title; ?></a>
      <?php else: ?>
        <?php print $title; ?>
      <?php endif; ?>
      </<?php print $title_element;?>>
    </div>
  <?php endif; ?>
  <div class="single-fluid-row-wrapper">
    <?php print render($title_suffix); ?>
    <?php print $content; ?>
  </div>
</div>
