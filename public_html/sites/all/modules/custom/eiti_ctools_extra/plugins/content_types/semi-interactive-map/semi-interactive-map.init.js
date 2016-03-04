/**
 * Semi-interactive map init behavior.
 */
(function($) {
  Drupal.behaviors.semiInteractiveMap = {
    attach: function (context, settings) {
      if (!settings.semiInteractiveMap.container || !settings.semiInteractiveMap.position) {
        return;
      }

      var map_container = $('#' + settings.semiInteractiveMap.container, context);
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

      mapWidget.createHomePage({
        name: Drupal.t('Homepage Map'),
        container: settings.semiInteractiveMap.container,
        position: settings.semiInteractiveMap.position,
        zoom: default_zoom,
        maxZoom: 5,
        minZoom: 0
      });
    }
  };
})(jQuery);
