/**
 * Fully interactive map (or Full Map) init behavior.
 */
(function($) {
  Drupal.behaviors.fullMap = {
    attach: function (context, settings) {
      context = $(context);

      var map_container = $('#' + settings.fullMap.container, context);
      if (!map_container.length) {
        return;
      }

      var default_zoom = 2;

      // Set the default zoom based on the map size.
      var map_container_width = map_container.width();
      if (map_container_width <= 480) {
        default_zoom = 0;
      }
      else if (map_container_width > 480 && map_container_width <= 800) {
        default_zoom = 1;
      }

      mapWidget.createMapPage({
        name: "Homepage Map",
        container: settings.fullMap.container,
        position: settings.fullMap.position,
        zoom: default_zoom,
        maxZoom: 5,
        minZoom: 2
      });
    }
  };
})(jQuery);
