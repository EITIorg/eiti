/**
 * Semi-interactive map init behavior.
 */
(function ($) {
  'use strict';

  Drupal.behaviors.eitiTableOfContents = {
    attach: function (context, settings) {
      if (!settings.eitiTableOfContents.container) {
        return;
      }

      var toc_container = $('#' + settings.eitiTableOfContents.container, context);
      if (!toc_container.length) {
        return;
      }

      // @TODO: Add JS code for the widget.
    }
  };
})(jQuery);
