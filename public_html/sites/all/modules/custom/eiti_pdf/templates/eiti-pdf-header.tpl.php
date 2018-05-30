<table class="pdf-header">
  <tbody>
    <tr>
      <td class="info">
        <div class="title"><?php print $title; ?></div>
        <?php if ($decision_reference): ?>
          <div class="reference"><?php print t('Decision reference:'); ?> <?php print $decision_reference; ?></div>
        <?php endif; ?>
        <div class="date"><?php print $date; ?></div>
      </td>
      <td class="page-no">
        {PAGENO}
      </td>
    </tr>
  </tbody>
</table>
