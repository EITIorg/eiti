(function ($) {

  Drupal.behaviors.eitiArticles = {
    /**
     * Enables show/hide functionality for filters.
     * @param context
     */
    attach: function (context) {

      // On load.
      $('.view-articles').once('filter').each(function() {
        $(this).find('.view-filters .views-exposed-widget').not('.views-submit-button').hide();
        var display_filter = false;
        var f_field1 = $(this).find('.views-exposed-widgets .views-widget-filter-field_tags_tid .form-text');
        var f_field2 = $(this).find('.views-exposed-widgets .views-widget-filter-combine .form-text');
        if (f_field1.val() || f_field2.val()) {
          display_filter = true;
          $(this).find('.filter-toggle .filter').addClass('open');
          $(this).find('.views-exposed-widgets .views-widget-filter-field_tags_tid').show();
          $(this).find('.views-exposed-widgets .views-widget-filter-combine').show();
        }
        var display_date = false;
        var d_field1 = $(this).find('.views-exposed-widgets .views-widget-filter-created .form-text');
        var d_field2 = $(this).find('.views-exposed-widgets .views-widget-filter-created_1 .form-text');
        if (d_field1.val() || d_field2.val()) {
          display_date = true;
          $(this).find('.filter-toggle .date').addClass('open');
          $(this).find('.views-exposed-widgets .views-widget-filter-created').show();
          $(this).find('.views-exposed-widgets .views-widget-filter-created_1').show();
        }

        if (display_filter || display_date) {
          $(this).find('.view-filters').show();
        }
        else {
          $(this).find('.view-filters').hide();
        }
      });

      // Filter click.
      $('.view-articles .filter-toggle .filter').once('filter-click').click(function (e) {
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

      // Date click.
      $('.view-articles .filter-toggle .date').once('date-click').click(function (e) {
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
