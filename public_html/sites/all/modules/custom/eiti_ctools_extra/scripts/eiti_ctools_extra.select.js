/**
 * @file
 * Attaches behaviors for the Select2 library.
 */

(function ($) {

  Drupal.behaviors.eitiCtoolsExtraSelect = {
    /**
     * Initialize the tabs widgets.
     *
     * @param {Object} context
     * @param {Object} settings
     */
    attach: function (context, settings) {
      // Initialize the select2 powered widgets.
      $('.form-select.jquery-select2-enabled').each(function(index, element) {
        var options = {};

        if (element.hasAttribute('data-placeholder')) {
          options.placeholder = $(element).attr('data-placeholder');
        }

        $(element).select2(options);
      });

    }
  };

})(jQuery);
