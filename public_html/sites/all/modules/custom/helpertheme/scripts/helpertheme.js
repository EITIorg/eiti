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
        var navigation_links = footer_navigation.find('.navigation-links');
        navigation_links.removeClass('has-expanded-child');
        navigation_links.find('.item').removeClass('expanded');
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

Drupal.behaviors.toggleSiteNavigationSubLevel = {
  /**
   * Enable the hamburger menu sub-levels functionality.
   * @param context
   */
  attach: function(context) {
    $('.site-navigation-wrapper .navigation-links', context).once('expandable', function() {
      $(this).find('.item.has-sublevel > .link').click(function (e) {
        var list_item = $(e.target).closest('.has-sublevel');

        if (list_item.is('.expanded')) {
          list_item.removeClass('expanded');
          list_item.parent().removeClass('has-expanded-child');
        }
        else {
          list_item.addClass('expanded');
          list_item.parent().addClass('has-expanded-child');
          list_item.parent().children().not(list_item).removeClass('expanded');
        }
      });

      $(this).find('.item.has-sublevel > a.link').click(function (e) {
        e.preventDefault();
      })
    });
  }
};

})(jQuery);
