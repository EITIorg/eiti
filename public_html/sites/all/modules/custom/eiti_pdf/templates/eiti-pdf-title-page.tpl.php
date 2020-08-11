<div class="pdf-title-page">
  <div class="logo"><img src="<?php print $logo; ?>" alt="EITI" height="120" /></div>
  <table class="line">
    <tbody>
      <tr>
        <td class="board"><?php print t('EITI Board'); ?></td>
        <td class="date"><?php print $date; ?></td>
      </tr>
    </tbody>
  </table>
  <?php if ($pre_title): ?>
  <div class="pre-title"><?php print $pre_title; ?></div>
  <?php endif; ?>
  <div class="title"><?php print $title; ?></div>
  <?php if ($progress_level): ?>
    <div class="sub-title"><?php print $progress_level; ?></div>
  <?php endif; ?>
  <?php if ($decision_reference): ?>
    <div class="reference"><?php print t('Decision reference:'); ?> <?php print $decision_reference; ?></div>
  <?php endif; ?>
</div>
