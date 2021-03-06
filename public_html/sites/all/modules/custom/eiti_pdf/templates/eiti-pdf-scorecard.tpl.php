<?php if ($text_before): ?>
  <div class="scorecard-text before-table">
    <h2 class="title">
      <?php print t("The Board's decision"); ?>
      <tocentry content="<?php print t("The Board's decision"); ?>" />
    </h2>
    <?php print $text_before; ?>
  </div>
<?php endif; ?>

<?php if ($text_before2): ?>
  <div class="scorecard-text before-table">
    <h2 class="title">
      <?php print t("Background"); ?>
      <tocentry content="<?php print t("Background"); ?>" />
    </h2>
    <?php print $text_before2; ?>
  </div>
<?php endif; ?>

<h2 class="title">
  <?php print t('Scorecard'); ?>
  <tocentry content="<?php print t('Scorecard'); ?>" />
</h2>
<table class="country_scorecard">
  <thead>
    <tr class="first">
      <th colspan="2"><?php print t('EITI Requirements'); ?></th>
      <th colspan="5"><?php print t('Level of Progress'); ?></th>
      <?php if ($hasProgress): ?>
        <th rowspan="2"><?php print t('Direction <br>of Progress'); ?></th>
      <?php endif; ?>
    </tr>
    <tr>
      <th><?php print t('Categories'); ?></th>
      <th><?php print t('Requirements'); ?></th>
      <th class="scores"><?php print t('<p><span>No Progress</span></p>'); ?></th>
      <th class="scores"><?php print t('<p><span>Inadequate</span></p>'); ?></th>
      <th class="scores"><?php print t('<p><span>Meaningful</span></p>'); ?></th>
      <th class="scores"><?php print t('<p><span>Satisfactory</span></p>'); ?></th>
      <th class="scores"><?php print t('<p><span>Beyond</span></p>'); ?></th>
    </tr>
  </thead>
  <tbody>
  <?php foreach ($categories as $c_tid => $category): ?>
    <?php foreach ($requirements[$c_tid] as $requirement): ?>
    <tr>
      <?php if ($requirement['add_category_td']): ?>
        <td class="requirement last" rowspan="<?php print $category['count']; ?>">
          <?php print $category['name']; ?>
        </td>
      <?php endif; ?>
      <td class="name <?php print $requirement['td_classes']; ?>">
        <?php if ($requirement['print_name']): ?>
          <?php print $requirement['name']; ?>
          <?php if ($requirement['description']): ?>
          <annotation content="<?php print $requirement['description']; ?>" icon="Note" />
          <?php endif; ?>
        <?php endif; ?>
      </td>
      <?php if (!$requirement['is_applicable']): ?>
        <td class="not_applicable <?php print $requirement['td_classes']; ?>" colspan="5"></td>
      <?php elseif (!$requirement['is_required']): ?>
        <td class="only_encouraged <?php print $requirement['td_classes']; ?>" colspan="5"></td>
      <?php else: ?>
        <td class="<?php if ($requirement['value'] == 0): ?>no_progress<?php endif; ?> <?php print $requirement['td_classes']; ?>"></td>
        <td class="<?php if ($requirement['value'] == 1): ?>inadequate<?php endif; ?> <?php print $requirement['td_classes']; ?>"></td>
        <td class="<?php if ($requirement['value'] == 2): ?>meaningful<?php endif; ?> <?php print $requirement['td_classes']; ?>"></td>
        <td class="<?php if ($requirement['value'] == 3): ?>satisfactory<?php endif; ?> <?php print $requirement['td_classes']; ?>"></td>
        <td class="<?php if ($requirement['value'] == 4): ?>beyond<?php endif; ?> <?php print $requirement['td_classes']; ?>"></td>
      <?php endif; ?>
      <?php if ($hasProgress): ?>
        <td class="<?php print $requirement['td_classes']; ?> <?php print $requirement['progress_classes']; ?>">
          <?php print $requirement['progress_symbol']; ?>
        </td>
      <?php endif; ?>
    </tr>
    <?php endforeach; ?>
  <?php endforeach; ?>
  </tbody>
</table>

<table class="scorecard-legend">
  <tbody>
  <?php foreach ($legend_items as $l_item): ?>
    <tr class="spacing"><td colspan="2"></td></tr>
    <tr class="scorecard-legend-item">
      <td class="color <?php print $l_item['classes']; ?>"></td>
      <td class="text"><?php print $l_item['text']; ?></td>
    </tr>
  <?php endforeach; ?>
  </tbody>
</table>

<?php if ($hasProgress): ?>
  <table class="scorecard-progress">
    <tbody>
      <tr><td colspan="2"><strong><?php print t('Direction of progress'); ?></strong></td></tr>
      <tr class="spacing"><td colspan="2"></td></tr>
      <?php foreach ($progress_items as $p_item): ?>
        <tr class="scorecard-legend-item <?php print $p_item['classes']; ?>">">
          <td class="symbol"><?php print $p_item['symbol']; ?></td>
          <td class="text"><?php print $p_item['text']; ?></td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
<?php endif; ?>

<?php if ($text_after): ?>
  <div class="scorecard-text after-table">
    <h2 class="title">
      <?php print t('Corrective actions'); ?>
      <tocentry content="<?php print t('Corrective actions'); ?>" />
    </h2>
    <?php print $text_after; ?>
  </div>
<?php endif; ?>

<?php if ($news_items): ?>
  <div class="scorecard-news">
    <h2 class="title">
      <?php print t('News'); ?>
      <tocentry content="<?php print t('News'); ?>" />
    </h2>
    <?php foreach ($news_items as $news_item): ?>
      <div class="news-item">
        <h3 class="title"><?php print $news_item['title']; ?></h3>
        <div class="body"><?php print $news_item['body']; ?></div>
      </div>
    <?php endforeach; ?>
  </div>
<?php endif; ?>
