(function ($) {

Drupal.behaviors.browserWarnings = {
  /**
   * Allows users to permanently hide old browser warning.
   * @param context
   */
  attach: function(context) {
    // Add anchor links in the markup.
    $('.oldbrowser-warning .ignore-link', context).click(function (e) {
      e.preventDefault();

      // Set a ignore oldbrowser cookie.
      document.cookie = 'ignore_oldbrowser=1; path=/';

      // Remove the current warning.
      $(this).closest('.oldbrowser-warning').remove();
    });
  }
};

Drupal.behaviors.toggleSiteNavigation = {
  /**
   * Enable the hamburger menu functionality.
   * @param context
   */
  attach: function(context) {
    $('.site-navigation-toggle-wrapper .link', context).click(function (e) {
      var footer_navigation = $('.footer-site-navigation-wrapper', context);
      if (!footer_navigation.size) {
        return true;
      }

      e.preventDefault();

      // Remove the current warning.
      var button_wrapper = $(this).closest('.site-navigation-toggle-wrapper');
      var button_offset = button_wrapper.offset();
      var button_height = button_wrapper.outerHeight();

      if ($('body', context).hasClass('site-navigation-visible')) {
        footer_navigation.slideUp('fast');
        $('body', context).removeClass('site-navigation-visible');
      }
      else {
        footer_navigation.css({
          'position': 'absolute',
          'top': button_offset.top + button_height,
          'left': button_offset.left
        });
        footer_navigation.slideDown('fast');
        $('body', context).addClass('site-navigation-visible');
      }
    });
  }
};

})(jQuery);
