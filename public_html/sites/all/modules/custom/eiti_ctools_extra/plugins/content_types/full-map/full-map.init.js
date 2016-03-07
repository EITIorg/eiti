/**
 * Fully interactive map (or Full Map) init behavior.
 */
(function($) {
  Drupal.behaviors.fullMap = {
    attach: function (context, settings) {
      context = $(context);

      mapWidget.createMapPage({
        name: "Homepage Map",
        container: "map1",
        position: [12.897489183755892, -12.76171875],
        zoom: 2,
        maxZoom: 5,
        minZoom: 2
      });
    }
  };
})(jQuery);
