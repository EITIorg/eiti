/**
 * @file
 * Attaches behaviors for the ContentWidget module.
 *
 * @var {Drupal} Drupal
 * @var {Plotly} Plotly
 */

(function ($) {

Drupal.eitiContentWidget = Drupal.eitiContentWidget || {};

/**
 * Update Plotly chart.
 *
 * @param {Object} chartSettings
 */
Drupal.eitiContentWidget.updatePlotlyChart = function (chartSettings) {
  $.get(chartSettings.endpoint, chartSettings.endpoint_data, function (response) {
    var $chartContainer = $('#' + chartSettings.container);

    if (!response.data || !response.data.length) {
      var message = Drupal.t('There is no data.');
      if (chartSettings.endpoint_data.filter.year) {
        message = Drupal.t('There is no data for !year.', {'!year': chartSettings.endpoint_data.filter.year});
      }

      $chartContainer.html('<p class="no-chart">' + message + '</p>');
      return;
    }

    for (var delta in response.data) {
      if (!response.data.hasOwnProperty(delta)) {
        continue;
      }

      response.data[delta].type = 'bar';
    }

    $chartContainer.html('');  // HACK: Remove any markup, this avoids a layout bug in plotly.
    Plotly.newPlot(chartSettings.container, response.data, chartSettings.layout, {displaylogo: false});
  });
};

Drupal.eitiContentWidget.plotlyChartDefaultLayout = {
  font: {
    family: '"Open Sans", sans-serif'
  },
  barmode:'group'
};

Drupal.behaviors.eitiContentWidgetPlotlyInit = {
  /**
   * Attach the behavior.
   * @param {Object} context
   * @param {Object} settings
   * @param {Object} settings.eitiContentWidgetPlotly
   */
  attach: function (context, settings) {
    if (!settings.eitiContentWidgetPlotly) {
      return;
    }

    for (var key in settings.eitiContentWidgetPlotly) {
      if (!settings.eitiContentWidgetPlotly.hasOwnProperty(key)) {
        continue;
      }

      this._initializePlotlyChart(context, settings.eitiContentWidgetPlotly[key]);
    }
  },

  /**
   * Initializes a chart.
   *
   * @var {Drupal} Drupal
   * @param {Object} context
   * @param {Object} chartSettings
   * @param {string} chartSettings.title
   * @param {string} chartSettings.description
   * @param {string} chartSettings.container
   * @param {Object} chartSettings.layout
   * @param {string} chartSettings.xlabel
   * @param {string} chartSettings.ylabel
   * @param {string} chartSettings.year_selector_class
   * @param {string} chartSettings.endpoint
   * @param {Object} chartSettings.endpoint_data
   *
   * @private
   */
  _initializePlotlyChart: function (context, chartSettings) {
    if (!chartSettings.container || !chartSettings.endpoint) {
      return;
    }

    // Make sure the chart container exists. We should have only one.
    var chart_container = $('#' + chartSettings.container, context);
    if (chart_container.length !== 1) {
      return;
    }

    // Update the chart layout.
    chartSettings.layout = $.extend({}, Drupal.eitiContentWidget.plotlyChartDefaultLayout, {
      title: chartSettings.title,
      description: chartSettings.description,
      xaxis: {
        title: chartSettings.xlabel
      },
      yaxis: {
        title: chartSettings.ylabel
      }
    });

    // Enable the year selector.
    if (chartSettings.year_selector_class && chartSettings.year_selector_class !== '') {
      $('.' + chartSettings.year_selector_class, context).bind('change', function () {
        var selected_year = $(this).val();
        chartSettings.endpoint_data.filter.year = selected_year;

        chartSettings.layout.title = Drupal.t('@title for @year', {
          '@title': chartSettings.title,
          '@year': selected_year
        });
        chartSettings.layout.description = Drupal.t('@title for @year', {
          '@title': chartSettings.description,
          '@year': selected_year
        });

        Drupal.eitiContentWidget.updatePlotlyChart(chartSettings);
      }).trigger('change');
    }
    else {
      Drupal.eitiContentWidget.updatePlotlyChart(chartSettings);
    }
  }
};

  Drupal.behaviors.contentWidgetInit = {
    attach: function (context, settings) {
      // Initialize the widgets.
      return;
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
              var $selector = $(yearSelectorStr).change(function(evObj) {
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
    }
  };


Drupal.behaviors.contentWidgetTabs = {
  /**
   * Initialize the tabs widget.
   *
   * @param {Object} context
   * @param {Object} settings
   */
  attach: function (context, settings) {
    // Initialize the tabs.
    if ($('.tabs-widget-wrapper', context).length) {
      $('.tabs-widget-wrapper', context).tabs();
    }
  }
};


// Declare an object with all the functions accessible globally.
Drupal.contentWidgets = {
  getChartWidgetTypes: function () {
    return [
      'BubbleChart',
      'Sankey'
    ];
  }
};

})(jQuery);
