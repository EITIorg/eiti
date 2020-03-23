/**
 * @file
 * Attaches behaviors for the maskedinput library.
 */

(function ($) {

  Drupal.behaviors.maskedinput = {
    attach: function (context) {
      $(document).ready(function() {
        $("#edit-field-bd-number-und-0-value").mask("9999-99");
      });
    }
  };

})(jQuery);
