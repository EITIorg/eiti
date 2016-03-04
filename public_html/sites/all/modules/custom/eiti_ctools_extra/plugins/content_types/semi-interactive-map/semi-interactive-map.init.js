/**
 * Semi-interactive map init behavior.
 */
(function($) {
  Drupal.behaviors.semiInteractiveMap = {
    attach: function (context, settings) {
      if (!settings.semiInteractiveMap.container || !settings.semiInteractiveMap.position) {
        return;
      }

      mapWidget.createHomePage({
        name: Drupal.t('Homepage Map'),
        container: settings.semiInteractiveMap.container,
        position: settings.semiInteractiveMap.position,
        zoom: 2,
        maxZoom: 5,
        minZoom: 2
      });
    }
  };
})(jQuery);
