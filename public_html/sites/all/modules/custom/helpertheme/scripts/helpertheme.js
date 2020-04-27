(function ($) {

  Drupal.behaviors.browserWarnings = {
    /**
     * Allows users to permanently hide old browser warning.
     * @param context
     */
    attach: function (context) {
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
    attach: function (context) {
      $('.site-navigation-toggle-wrapper .link').append('<span></span>'); // Adding hamburger for mobile
      $('.site-navigation-toggle-wrapper .link', context).click(function (e) {
        var footer_navigation = $('.footer-site-navigation-wrapper', context);
        if (!footer_navigation.size) {
          return true;
        }
        e.preventDefault();
        e.stopPropagation(); //Prevent toggle hamburger menu 

        // Close search
        $('.header-search-form').fadeOut('fast', function () {
          $(this).removeClass('open');
        });
        $('.search-open').removeClass('open');

        // Remove the current warning.
        var button_wrapper = $(this).closest('.site-navigation-toggle-wrapper');
        var button_offset = button_wrapper.offset();
        var button_height = button_wrapper.outerHeight();
        if (window.matchMedia("(max-width: 76em)").matches) {
          if ($('body', context).hasClass('site-navigation-visible')) {
            footer_navigation.slideUp('fast');
            var navigation_links = footer_navigation.find('.navigation-links');
            navigation_links.removeClass('has-expanded-child');
            navigation_links.find('.item').removeClass('expanded');
            $('body', context).removeClass('site-navigation-visible');
            button_wrapper.removeClass('open');
          }
          else {
            footer_navigation.css({
              'position': 'fixed',
              'top': 0,
              'right': 0
            });
            footer_navigation.slideDown('fast');
            $('body', context).addClass('site-navigation-visible');
            button_wrapper.addClass('open');
          }
        } else {
          if ($('body', context).hasClass('site-navigation-visible')) {
            footer_navigation.slideUp('fast');
            var navigation_links = footer_navigation.find('.navigation-links');
            navigation_links.removeClass('has-expanded-child');
            navigation_links.find('.item').removeClass('expanded');
            $('body', context).removeClass('site-navigation-visible');
            button_wrapper.removeClass('open');
          }
          else {
            footer_navigation.css({
              'position': 'absolute',
              'top': button_offset.top + button_height - 40,
              'left': button_offset.left,
              'right': 'initial'
            });
            footer_navigation.slideDown('fast');
            $('body', context).addClass('site-navigation-visible');
            button_wrapper.addClass('open');
          }
        }
        // Change hamburger menu position on window resize
        $(window).on('resize', function () {
          if (window.matchMedia("(max-width: 76em)").matches) {
            footer_navigation.css({
              'position': 'fixed',
              'top': 0,
              'right': 0,
              'left': 'initial'
            });
          } else {
            button_offset = button_wrapper.offset();
            button_height = button_wrapper.outerHeight();
            footer_navigation.css({
              'position': 'absolute',
              'top': button_offset.top + button_height - 40,
              'left': button_offset.left,
              'right': 'initial'
            });
          }
        });
      });
      $('#site-navigation .nav-close .link', context).click(function (e) {
        e.preventDefault();
        var footer_navigation = $('.footer-site-navigation-wrapper', context);
        var button_wrapper = $('.main-header .site-navigation-toggle-wrapper', context);

        if ($('body', context).hasClass('site-navigation-visible')) {
          footer_navigation.slideUp('fast');
          var navigation_links = footer_navigation.find('.navigation-links');
          navigation_links.removeClass('has-expanded-child');
          navigation_links.find('.item').removeClass('expanded');
          $('body', context).removeClass('site-navigation-visible');
          button_wrapper.removeClass('open');
        }
      });
      // Close hamburger menu when clicking outside toggle button
      $('body', context).click(function (e) {
        var footer_navigation = $('.footer-site-navigation-wrapper', context);
        if ($(e.target).is('#site-navigation, #site-navigation *')) {
          return;
        } else if ($('body', context).hasClass('site-navigation-visible')) {
          footer_navigation.slideUp('fast');
          var navigation_links = footer_navigation.find('.navigation-links');
          navigation_links.removeClass('has-expanded-child');
          navigation_links.find('.item').removeClass('expanded');
          $('body', context).removeClass('site-navigation-visible');
          $('.site-navigation-toggle-wrapper', context).removeClass('open');
        }
      });
    }
  };

  Drupal.behaviors.toggleSiteNavigationSubLevel = {
    /**
     * Enable the hamburger menu sub-levels functionality.
     * @param context
     */
    attach: function (context) {
      $('.site-navigation-wrapper .navigation-links', context).once('expandable', function () {
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

  Drupal.behaviors.toggleSiteSearch = {
    /**
     * Enable the header search show-hide functionality.
     * @param context
     */
    attach: function (context) {
      $('.header-site-search .search-open .link', context).click(function (e) {
        e.preventDefault();
        $(this).closest('.header-site-search').find('.header-search-form').fadeIn('fast').addClass('open');
        $(this).closest('.header-site-search').find('.search-open').addClass('open');
      });
      $('.header-site-search .search-close .link', context).click(function (e) {
        e.preventDefault();
        $(this).closest('.header-search-form').fadeOut('fast', function () {
          $(this).removeClass('open');
        });
        $('.search-open').removeClass('open');
      });
      $('body', context).click(function (e) {
        if (!$(e.target).closest('.header-site-search').length) {
          $('.header-search-form').fadeOut('fast', function () {
            $(this).removeClass('open');
          });
          $('.search-open').removeClass('open');
        }
      });
    }
  };

  Drupal.behaviors.toggleBackgroundImageHoverState = {
    /**
     * Help with text visibility on linked blocks of content.
     *
     * @param context
     */
    attach: function (context) {
      $('.with-background-image .title a', context).hover(function () {
        $(this).closest('.with-background-image').addClass('hover');
      }, function () {
        $(this).closest('.with-background-image').removeClass('hover');
      });
    }
  };


  Drupal.behaviors.toggleMinimalisticWidgets = {
    attach: function (context) {
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
        var minimalistic_footer = $(this).parents('.pane-minimalistic-footer');
        var animation_time = $(this).data('animation-time');
        var targetID = $(this).data('target');
        if (targetID === undefined || targetID === "") { // Last resort to determine unique ID
          targetID = $(this).parents('.pane-minimalistic-footer').attr("class").split(' ').filter(function (k, v) { return k.indexOf("pane-pid-") != -1; })[0];
        }
        var dismissible = $(this).data('dismissible');
        var dismissible_group = $(this).data('group');

        if (!minimalistic_footer.size) {
          return true;
        }

        // We just hide it and that's it.
        if (dismissible == true) {
          if (dismissible_group !== undefined && dismissible_group !== "") {
            $.cookie('minimalistic-footer-group' + dismissible_group, 'closed', { expires: 30 });
            $('.group-' + dismissible_group, context).stop(true).slideUp(animation_time);
            $('.group-' + dismissible_group + ' .footer-close-action', context).toggleClass('footer-close-action').toggleClass('footer-show-action');
          }
          else {
            $.cookie('minimalistic-footer-' + targetID, 'closed', { expires: 30 });
            minimalistic_footer.stop(true).slideUp(animation_time);
            $(this).toggleClass('footer-close-action').toggleClass('footer-show-action');
          }
        }
        else {
          minimalistic_footer.stop(true).slideUp(animation_time);
          $(this).toggleClass('footer-close-action').toggleClass('footer-show-action');
        }
        e.preventDefault();
      });
      $('.footer-close-action', context).each(function () {
        var minimalistic_footer = $(this).parents('.minimalistic-footer');
        var animation_time = $(this).data('animation-time');
        var animation_delay = $(this).data('animation-delay');
        var dismissible = $(this).data('dismissible');
        var dismissible_group = $(this).data('group');

        var targetID = $(this).data('target');
        if (targetID === undefined || targetID === "") { // Last resort to determine unique ID
          targetID = $(this).parents('.pane-minimalistic-footer').attr("class").split(' ').filter(function (k, v) { return k.indexOf("pane-pid-") != -1; })[0];
        }

        var cookieValue;

        // If this is group, then we check whether the group is dismissed.
        if (dismissible_group !== undefined && dismissible_group !== "") {
          cookieValue = $.cookie('minimalistic-footer-group' + dismissible_group);
        }
        else {
          cookieValue = $.cookie('minimalistic-footer-' + targetID);
        }

        // By default widgets are closed.
        if (cookieValue == 'closed') {
          minimalistic_footer.hide();
        }
        else {
          if (animation_delay !== 0) {
            minimalistic_footer.show().delay(animation_delay).slideUp(animation_time);
          }
          else {
            minimalistic_footer.show();
          }
        }
      });
    }
  };

  Drupal.behaviors.headerVideoMedia = {
    attach: function (context) {
      var $media = $('.media-controllers', context);
      if ($media.length > 0) {
        $media.find('.controller').click(function () {
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

  Drupal.behaviors.responsiveTables = {
    attach: function (context) {
      // Adding classes for board decisions table
      $('.board-decisions .view-board-decisions .view-content').addClass('table-wrapper');
      $('.board-decisions .view-board-decisions .view-content .views-table').wrap('<div class="table-responsive"></div>');
      // Adding scroll bg on right of the table
      function tableScroll() {
        if ($('.table-wrapper').length > 0) {
          $('.table-wrapper').each(function (index, value) {
            if ($(this).find('table').outerWidth() > $(this).outerWidth()) {
              $(this).addClass('scroll');
            } else {
              $(this).removeClass('scroll');
            }
          });
        }
      }
      tableScroll();
      $(window).on('resize', function () {
        tableScroll();
      });
    }
  };

  Drupal.behaviors.boardCollapseMenu = {
    attach: function (context) {
      $('.pane-board-decision-info .link-items .label').on('click', function () {
        $(this).toggleClass('open');
        $(this).siblings('.field-items').slideToggle('fast');
      });
    }
  };

  /**
   * Define a small helper class with handy functions.
   */
  Drupal.eitiHelpers = Drupal.eitiHelpers || {};
  Drupal.eitiHelpers.scrollToElement = function (selector, targetSelector) {
    var offset = $(selector).offset();
    var top = $(document).scrollTop();
    var diffOffset = (top >= offset.top) ? -1 : 0;
    var scrollTarget = $(targetSelector);
    $(scrollTarget).animate({
      scrollTop: (offset.top + diffOffset)
    }, 500);
  };  

})(jQuery);
