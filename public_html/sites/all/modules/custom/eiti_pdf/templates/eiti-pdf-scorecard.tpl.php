<table class="country_scorecard">
  <thead>
    <tr>
      <th colspan="2"><?php print t('EITI Requirements'); ?></th>
      <th colspan="5"><?php print t('Level of Progress'); ?></th>
      <?php if ($hasProgress): ?>
        <th rowspan="2"><?php print t('Direction <br>of Progress'); ?></th>
      <?php endif; ?>
    </tr>
    <tr>
      <th><?php print t('Categories'); ?></th>
      <th><?php print t('Requirements'); ?></th>
      <th class="scores"><?php print t('<div><span>No Progress</span></div>'); ?></th>
      <th class="scores"><?php print t('<div><span>Inadequate</span></div>'); ?></th>
      <th class="scores"><?php print t('<div><span>Meaningful</span></div>'); ?></th>
      <th class="scores"><?php print t('<div><span>Satisfactory</span></div>'); ?></th>
      <th class="scores"><?php print t('<div><span>Beyond</span></div>'); ?></th>
    </tr>
  </thead>
  <tbody>
  <?php foreach ($categories as $c_tid => $category): ?>
    <?php $new_category = TRUE; ?>
    <?php if (isset($requirements[$c_tid])): ?>
      <?php foreach ($requirements[$c_tid] as $requirement): ?>
      <tr>
        <?php if ($new_category): ?>
          <td class="requirement" style="border-bottom: 1px solid black;" rowspan="<?php print $category['count']; ?>">
            <?php print $category['name']; ?>
          </td>
          <?php $new_category = FALSE; ?>
        <?php endif; ?>
        <td><?php print $requirement['name']; ?></td>
        <?php if (!$requirement['is_applicable']): ?>
          <td class="not_applicable" colspan="5">&nbsp;</td>
        <?php elseif ($requirement['is_required']): ?>
          <td class="only_encouraged" colspan="5">&nbsp;</td>
        <?php else: ?>
          <td<?php if ($requirement['value'] == 0): ?> class="no_progress"<?php endif; ?>>&nbsp;</td>
          <td<?php if ($requirement['value'] == 1): ?> class="inadequate"<?php endif; ?>>&nbsp;</td>
          <td<?php if ($requirement['value'] == 2): ?> class="meaningful"<?php endif; ?>>&nbsp;</td>
          <td<?php if ($requirement['value'] == 3): ?> class="satisfactory"<?php endif; ?>>&nbsp;</td>
          <td<?php if ($requirement['value'] == 4): ?> class="beyond"<?php endif; ?>>&nbsp;</td>
        <?php endif; ?>
        <?php if ($hasProgress): ?>
          <?php if ($requirement['progress_value'] == 0): ?>
            <td><div style="color: #676767; text-align: center; font-weight: bold;">&equals;</div></td>
          <?php elseif ($requirement['progress_value'] == 1): ?>
            <td><div style="color: #84AD42; text-align: center; font-weight: bold;">&rarr;</div></td>
          <?php elseif ($requirement['progress_value'] == 2): ?>
            <td><div style="color: red; text-align: center; font-weight: bold;">&larr;</div></td>
          <?php else: ?>
            <td><div style="color: #676767; text-align: center; font-weight: bold;">&nbsp;</div></td>
          <?php endif; ?>
        <?php endif; ?>
      </tr>
      <?php endforeach; ?>
    <?php endif; ?>
  <?php endforeach; ?>
  </tbody>
</table>
