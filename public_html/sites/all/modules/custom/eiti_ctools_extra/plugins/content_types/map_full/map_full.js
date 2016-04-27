/**
 * Fully interactive map (or Full Map) init behavior.
 */
(function($) {
  Drupal.behaviors.eitiMapFull = {
    attach: function (context, settings) {
      if (!settings.eitiMapFull.container || !settings.eitiMapFull.position) {
        return;
      }

      var map_container = $('#' + settings.eitiMapFull.container, context);
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
        name: Drupal.t('Map'),
        container: settings.eitiMapFull.container,
        position: settings.eitiMapFull.position,
        zoom: default_zoom,
        maxZoom: 5,
        minZoom: 0
      });
    }
  };
})(jQuery);
