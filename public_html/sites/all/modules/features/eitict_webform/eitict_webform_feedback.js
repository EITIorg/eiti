(function ($) {

  Drupal.behaviors.feedbackForm = {
    /**
     * Feedback form manipulation.
     *
     * @param context
     */
    attach: function (context) {
      var f_form_wrapper = $('.feedback-form');
      if (f_form_wrapper.length) {
        var f_form = f_form_wrapper.find('.webform-client-form');
        var feedback = f_form.find('.webform-component--feedback');
        var email = f_form.find('.webform-component--email');
        var actions = f_form.find('.form-actions');
        var rate = f_form.find('.webform-component--rate select');
        var star = f_form.find('.webform-component--rate .stars .star');
        var rate_val = parseInt(rate.val(), 10);
        if (!rate_val) {
          rate_val = 0;
        }
        else {
          feedback.show();
          email.show();
          actions.show();
        }

        // Star html.
        if (!star.length) {
          var stars_html = '<span class=stars>';
          var step;
          for (step = 1; step < 6; step++) {
            if (rate_val >= step) {
              stars_html += '<span class="star star-' + step + ' selected" data-id="' + step + '">S</span>';
            }
            else {
              stars_html += '<span class="star star-' + step + '" data-id="' + step + '">S</span>';
            }
          }
          stars_html += '</span>';
          rate.before(stars_html);
        }

        f_form_wrapper.show();

        // Star click sync with select.
        star = f_form.find('.webform-component--rate .stars .star');
        star.click(function() {
          var val = parseInt($(this).data('id'), 10);
          rate_val = parseInt(rate.val(), 10);
          star.removeClass('selected');
          if (val === rate_val) {
            rate.val('');
            feedback.hide();
            email.hide();
            actions.hide();
          }
          else {
            star.each(function() {
              if (parseInt($(this).data('id'), 10) <= val) {
                $(this).addClass('selected');
              }
            });
            rate.val(val);
            feedback.show();
            email.show();
            actions.show();
          }
        });
      }
    }
  };

})(jQuery);
