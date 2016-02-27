/**
 * Here is where we init the widgets and do more widget-related stuff.
 */
(function($) {
  Drupal.behaviors.contentWidgets = {
    attach: function (context, settings) {
      context = $(context);

      // Initialize the widgets.
      var chartTypes = Drupal.contentWidgets.getChartWidgetTypes();
      for (var key in settings.contentwidgets) {
        if (settings.contentwidgets[key].hasOwnProperty('type') && ($.inArray(settings.contentwidgets[key].type, chartTypes) >= 0)) {
          var widgetSetting = settings.contentwidgets[key];
          if (widgetSetting.hasOwnProperty('widgetData')) {
            var widgetData = widgetSetting.widgetData;
            chartWidget.create(widgetSetting, widgetData);
          }
          else {
            // Set the processor function that returns JSON.data.
            widgetSetting.processor = function(input) {
              if (input.data.length == 0) {
                return false;
              }
              return input.data;
            };
            // Now this case is much more FUN!
            if (widgetSetting.expose_year) {
              var yearSelectorStr = '.' + widgetSetting.year_selector_class;

              var $selector = $(yearSelectorStr).on('change', function(evObj) {
                var value = $(this).val();
                widgetSetting.name = Drupal.t('@title for @year', {
                  '@title': widgetSetting.name_original,
                  '@year': value
                });
                widgetSetting.description = Drupal.t('@description for @year', {
                  '@description': widgetSetting.description_original,
                  '@year': value
                });
                chartWidget.create(widgetSetting, widgetSetting.endpoint + '&filter[year][0]=' + value);
              });
              $selector.val(widgetSetting.current_year);
              chartWidget.create(widgetSetting, widgetSetting.endpoint_year);
            }
            else {
              // Otherwise just return.
              chartWidget.create(widgetSetting, widgetSetting.endpoint);
            }
          }
        }
      }

      // Initialize the tabs.
      $('.tabs-widget-wrapper').tabs();
    }
  };


  // Declare an object with all the functions accessible globally.
  Drupal.contentWidgets = {
    getChartWidgetTypes: function() {
      return [
        'GroupedBar',
        'StackedBar',
        'BubbleChart',
        'Sankey'
      ];
    }
  }
})(jQuery);
