/**
 * Floating Navigation for Progress Pages.
 */
(function($, Drupal) {
  Drupal.behaviors.navigationFloating = {
    attach: function (context, settings) {
      if (!settings.eitiNavigationFloating) {
        return;
      }

      var titles = [];
      var offsetBuffer = 50;
      var firstPane = true;

      // Generate the content.
      var $floatingNavList = $('<ul class="navigation-list"></ul>');

      for (var i in settings.eitiNavigationFloating.pane_order) {
        var paneId = settings.eitiNavigationFloating.pane_order[i];

        // This is very useful as now we know what to expect from this pane.
        var paneSettings = settings.eitiNavigationFloating.pane_properties[paneId];
        var $pane = $('.panel-pane.pane-pid-' + paneId, context);
        var $title = $pane.find('.title');
        var text = '';
        var href = undefined;
        $pane.data('pane_id', paneId);

        // Let's initially see if the widget should be excluded.
        if (paneSettings.exclude)
          continue;

        // Yes, not all widgets have titles, but all might have overridden floating menu title.
        if ($title.length == 0) {
          text = Drupal.t('No Widget Title');
        }
        else {
          href = $title.siblings("a").attr('href');
          text = $title.text().trim();
        }

        if (paneSettings.override) {
          text = paneSettings.override;
        }

        var offsetObj = $pane.offset();
        var offset = Math.floor(offsetObj.top - offsetBuffer);
        titles.push({text: text, offset: offset, id: '#t' + offset});

        // Create the list-item element with a link.
        var $liElement = $('<li id="t' + offset + '" class="nav-item-' + paneId + '"><a href="' + (href ? href : '#' + paneId) + '" class="link-title-with-icon">' + text + '</a></li>');
        if (!href) {
          $liElement.find('> a').on("click", function(evOvj){
            var $link = $(this);
            var paneId = $link.attr('href').slice(1);

            // Use our custom scroll to element helper function, for a smooth transition.
            if (settings.eitiNavigationFloating.use_smooth_transition) {
              Drupal.eitiHelpers.scrollToElement('.panel-pane.pane-pid-' + paneId, 'body, html');
            }
            else {
              $('.panel-pane.pane-pid-' + paneId).get(0).scrollIntoView();
            }
            return false;
          });
        }
        else {
          $liElement.find('> a').on("click", function(evOvj){
            var $link = $(this);
            var targetId = $link.attr('href');

            // Use our custom scroll to element helper function, for a smooth transition.
            if (settings.eitiNavigationFloating.use_smooth_transition) {
              Drupal.eitiHelpers.scrollToElement(targetId, 'body, html');
            }
            else {
              $(targetId).get(0).scrollIntoView();
            }
            return false;
          });
        }

        // Now let's figure out where do we want to append it.
        if (paneSettings.second == false) {
          $liElement.appendTo($floatingNavList);
        }
        else {
          var $lastDeepList = $floatingNavList.find('> li:last > ul');
          if ($lastDeepList.length == 0) {
            // No deep-list? Let's create one in the last li element (top level).
            var $lastLiElement = $floatingNavList.find('> li').last();
            var $deepList = $('<ul class="sub-menu"></ul>').append($liElement);
            $deepList.appendTo($lastLiElement);
          }
          else {
            // Do nothing.
          }
        }

        // Create the 'tracking' behavior.
        if (settings.eitiNavigationFloating.use_position_tracking && $.fn.waypoint) {
          $pane.waypoint(function(direction) {
            var $this = $(this.element);
            $floatingNavList.find('li').removeClass('current');
            $('.nav-item-' + $this.data('pane_id'), context).toggleClass('current');
          }, {
            offset: firstPane ? -10 : '10%'
          });
        }
        firstPane = false;
      }

      $('#navigation-floating', context).append($floatingNavList);
      if ($.fn.waypoint) {
        $('#navigation-floating').waypoint(function(direction) {
          var $this = $(this.element);
          $this.parent().fadeToggle(400);
        }, {
          offset: '20%'
        });
      }
    }
  };
})(jQuery, Drupal);
