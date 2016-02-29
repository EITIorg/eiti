
(function ($) {

Drupal.behaviors.variantsToggleLink = {
  /**
   * Toggles the visibility of colour palette items.
   *
   * @param context
   */
  attach: function(context) {
    var selector = '.palette-overview-toggle';
      if (!$(selector).length) {
      return;
    }

    // Add anchor links in the markup.
    $(selector).click(function () {
      $(this).closest('.helpertheme-color-palette-wrapper').toggleClass('variants-hidden');
    });
  }
};

})(jQuery);
