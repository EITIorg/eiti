(function ($) {

  // TODO: fix attach on ajax events.

  Drupal.behaviors.eitiArticles = {
    /**
     * Enables show/hide functionality for filters.
     * @param context
     */
    attach: function (context) {

      $('.view-articles .view-filters').hide();
      $('.view-articles .view-filters .views-exposed-widget').not('.views-submit-button').hide();

      // Filter.
      $('.view-articles .filter-toggle .filter', context).click(function (e) {
        if (!$(this).hasClass('open')) {
          $(this).addClass('open');
          $(this).closest('.view-articles').find('.view-filters').show();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-field_tags_tid').show();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-combine').show();
        }
        else {
          $(this).removeClass('open');
          if (!$(this).parent().find('.date').hasClass('open')) {
            $(this).closest('.view-articles').find('.view-filters').hide();
          }
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-field_tags_tid').hide();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-combine').hide();
        }
      });

      // Date.
      $('.view-articles .filter-toggle .date', context).click(function (e) {
        if (!$(this).hasClass('open')) {
          $(this).addClass('open');
          $(this).closest('.view-articles').find('.view-filters').show();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-created').show();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-created_1').show();
        }
        else {
          $(this).removeClass('open');
          if (!$(this).parent().find('.filter').hasClass('open')) {
            $(this).closest('.view-articles').find('.view-filters').hide();
          }
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-created').hide();
          $(this).closest('.view-articles').find('.views-exposed-widgets .views-widget-filter-created_1').hide();
        }
      });

    }
  };

})(jQuery);
