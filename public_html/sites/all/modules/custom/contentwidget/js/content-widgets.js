/**
 * @file
 * Attaches behaviors for the ContentWidget module.
 *
 * @var {chartWidget} chartWidget
 * @var {Drupal} Drupal
 * @var {Plotly} Plotly
 */

(function ($) {
  Drupal.eitiContentWidget = Drupal.eitiContentWidget || {};

  /**
   * Update Plotly Chart.
   *
   * @param {Object} chartSettings
   */
  Drupal.eitiContentWidget.updatePlotlyChart = function (chartSettings) {
    // Load data from an API endpoint.
    if (chartSettings.hasOwnProperty('endpoint')) {
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

          // @TODO: Remove!
          response.data[delta].type = 'bar';
        }

        $chartContainer.html('');  // HACK: Remove any markup, this avoids a layout bug in plotly.
        Plotly.newPlot(chartSettings.container, response.data, chartSettings.layout, {displaylogo: false});

        // @HACK: Reuse the export functionality form the eitiChartWidgets library.
        // @TODO: Remove dependency on the eitiChartWidgets library.
        var exportWidgetSettings = $.extend({}, chartSettings);
        exportWidgetSettings.type += 'Export';
        exportWidgetSettings.container += '--export';
        chartWidget.create(exportWidgetSettings, response.data);
      });
    }
    // Use provided data.
    else if (chartSettings.hasOwnProperty('widgetData')) {
      var $chartContainer = $('#' + chartSettings.container);

      for (var delta in chartSettings.widgetData) {
        if (!chartSettings.widgetData.hasOwnProperty(delta)) {
          continue;
        }

        // @TODO: Remove!
        chartSettings.widgetData[delta].type = 'bar';
      }

      $chartContainer.html('');  // HACK: Remove any markup, this avoids a layout bug in plotly.
      Plotly.newPlot(chartSettings.container, chartSettings.widgetData, chartSettings.layout, {displaylogo: false});
    }
  };

  /**
   * Default layout configuration for Plotly charts.
   */
  Drupal.eitiContentWidget.plotlyChartDefaultLayout = {
    font: {
      family: '"Open Sans", sans-serif'
    },
    barmode: 'group'
  };

  Drupal.behaviors.eitiContentWidgetPlotlyInit = {
    /**
     * Initialize Plotly Chart widgets.
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
     * @param {string} chartSettings.legend_position
     * @param {string} chartSettings.year_selector_class
     * @param {string} chartSettings.type
     * @param {string} chartSettings.endpoint
     * @param {Object} chartSettings.endpoint_data
     *
     * @private
     */
    _initializePlotlyChart: function (context, chartSettings) {
      if (!chartSettings.container) {
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

      // Show the legend above the chart when there are many options or the options have long names.
      if (chartSettings.legend_position) {
        if (chartSettings.legend_position === 'above') {
          chartSettings.layout.legend = {
            x: 0,
            y: 1,
            yanchor: 'bottom',
            xanchor: 'left'
          };
        }
        else if (chartSettings.legend_position === 'right') {
          chartSettings.layout.legend = {
            x: 1,
            y: 1,
            yanchor: 'top',
            xanchor: 'left'
          };
        }
      }

      if (chartSettings.type && chartSettings.type === 'StackedBar') {
        chartSettings.layout.barmode = 'stack';
      }

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
    /**
     * Initialize Custom Chart widgets.
     *
     * @param {Object} context
     * @param {Object} settings
     * @param {Object} settings.contentWidgets
     */
    attach: function (context, settings) {
      var chartTypes = [
        'Scorecard',
        'BubbleChart',
        'Sankey'
      ];

      for (var key in settings.contentWidgets) {
        if (!settings.contentWidgets.hasOwnProperty(key)) {
          continue;
        }

        if (!settings.contentWidgets[key].hasOwnProperty('type')) {
          continue;
        }

        if ($.inArray(settings.contentWidgets[key].type, chartTypes) >= 0) {
          this._initializeCustomChart(context, settings.contentWidgets[key]);
        }
      }
    },

    /**
     * Initializes the chart.
     *
     * @var {Drupal} Drupal
     * @param {Object} context
     * @param {Object} widgetSetting
     * @param {string} widgetSetting.container
     * @param {string} widgetSetting.endpoint
     * @param {function} widgetSetting.processor
     * @param {string} widgetSetting.widgetData
     *
     * @private
     */
    _initializeCustomChart: function (context, widgetSetting) {
      if (!widgetSetting.container || !widgetSetting.endpoint) {
        return;
      }

      // Make sure the chart container exists. We should have only one.
      var chart_container = $('#' + widgetSetting.container, context);
      if (chart_container.length !== 1) {
        return;
      }

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

        // Otherwise just return.
        chartWidget.create(widgetSetting, widgetSetting.endpoint);
      }
    }
  };

  Drupal.behaviors.contentWidgetTabs = {
    /**
     * Initialize the tabs widgets.
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

})(jQuery);
