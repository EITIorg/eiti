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
          var widgetData = widgetSetting.widgetData;
          chartWidget.create(widgetSetting, widgetData);
        }
      }
    }
  };


  // Declare an object with all the functions accessible globally.
  Drupal.contentWidgets = {
    getChartWidgetTypes: function() {
      return [
        'GroupedBar'
      ];
    }
  }
})(jQuery);
