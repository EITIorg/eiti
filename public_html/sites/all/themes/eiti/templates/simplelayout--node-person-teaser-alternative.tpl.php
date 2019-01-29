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
<?php if (!isset($content['field_person_picture'])): ?>
  <div class="field field-name-field-person-picture"></div>
<?php endif; ?>
<?php print $main; ?>
<a class="person-link" href="<?php print $node_url; ?>"></a>
<p class="person-profile"><?php print t('View profile'); ?></p>
<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
</<?php print $main_wrapper ?>>

</<?php print $layout_wrapper ?>>
