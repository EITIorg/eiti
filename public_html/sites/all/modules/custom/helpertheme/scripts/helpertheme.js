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

  Drupal.behaviors.toggleBackgroundImageHoverState = {
    /**
     * Help with text visibility on linked blocks of content.
     *
     * @param context
     */
    attach: function(context) {
      $('.with-background-image .title a', context).hover(function () {
        $(this).closest('.with-background-image').addClass('hover');
      }, function () {
        $(this).closest('.with-background-image').removeClass('hover');
      });
    }
  };


  Drupal.behaviors.toggleMinimalisticWidgets = {
    attach: function(context) {
      $('.header-close-action', context).click(function (e) {
          var minimalistic_header = $(this).parents('.pane-minimalistic-header');
          var animation_time = $(this).data('animation-time');

          if (!minimalistic_header.size) {
              return true;
          }
          else {
              minimalistic_header.slideUp(animation_time);
          }
          e.preventDefault();
      });
      $('.footer-close-action', context).click(function (e) {
          var minimalistic_footer = $(this).parents('.minimalistic-footer');
          var animation_time = $(this).data('animation-time');
          var targetID = $(this).data('target');
          var dismissible = $(this).data('dismissible');

          if (!minimalistic_footer.size) {
              return true;
          }

          // We just hide it and that's it.
          if (dismissible == true) {
            $.cookie('minimalistic-footer-' + targetID, 'closed', { expires: 30 });
          }
          minimalistic_footer.slideUp(animation_time);
          $(this).toggleClass('close-action').toggleClass('show-action');
          e.preventDefault();
      });
      $('.footer-close-action', context).each(function() {
        var minimalistic_footer = $(this).parents('.minimalistic-footer');
        var animation_time = $(this).data('animation-time');
        var animation_delay = $(this).data('animation-delay');
        var dismissible = $(this).data('dismissible');
        var targetID = $(this).data('target');
        var cookieValue = $.cookie('minimalistic-footer-' + targetID);
        if (cookieValue == 'closed') {
          // It's closed, we just show the footer for a delay, and hide it afterwords.
          if (animation_delay !== 0) {
            minimalistic_footer.delay(animation_delay).slideUp(animation_time);
          }
          else {
            minimalistic_footer.hide();
          }
        }
      });
    }
  };

  Drupal.behaviors.headerVideoMedia = {
    attach: function(context) {
      var $media = $('.media-controllers', context);
      if ($media.length > 0) {
        $media.find('.controller').click(function() {
          var $this = $(this);
          if ($this.hasClass('icon--media-play') || $this.hasClass('icon--media-pause')) {
            if ($media.hasClass('playing')) {
              $media.removeClass('playing');
              $('video.background-video', context).get(0).pause();
            }
            else {
              $media.addClass('playing');
              $('video.background-video', context).get(0).play();
            }

          }
          if ($this.hasClass('icon--media-mute') || $this.hasClass('icon--media-unmute')) {
            if ($media.hasClass('muted')) {
              $('video.background-video', context).get(0).muted = false;
              $media.removeClass('muted');
            }
            else {
              $('video.background-video', context).get(0).muted = true;
              $media.addClass('muted');
            }
          }
        });
      }
    }
  };

  /**
   * Define a small helper class with handy functions.
   */
  Drupal.eitiHelpers = Drupal.eitiHelpers || {};
  Drupal.eitiHelpers.scrollToElement = function(selector, targetSelector) {
    var offset = $(selector).offset();
    var top = $(document).scrollTop();
    var diffOffset = (top >= offset.top) ? -1 : 0;
    var scrollTarget = $(targetSelector);
    $(scrollTarget).animate({
      scrollTop: (offset.top + diffOffset)
    }, 500);
  };

})(jQuery);
