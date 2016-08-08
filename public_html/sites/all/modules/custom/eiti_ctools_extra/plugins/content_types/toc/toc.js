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

      var svg_icon = '<svg viewBox="0 0 160 160" height="1em" width="1em" role="presentation" class="icon symbol--arrow"><path d="M74.868 125.108l40.514-40.513c1.133-1.133 1.695-2.47 1.695-4.015 0-1.543-.562-2.882-1.695-4.015L74.868 36.05c-1.133-1.132-2.47-1.694-4.015-1.694-1.543 0-2.882.562-4.015 1.695l-9.103 9.103c-1.133 1.133-1.695 2.47-1.695 4.015 0 1.543.562 2.882 1.695 4.015L85.13 80.58l-27.395 27.395c-1.133 1.133-1.695 2.47-1.695 4.015 0 1.543.562 2.882 1.695 4.015l9.102 9.102c1.133 1.133 2.47 1.695 4.015 1.695 1.543 0 2.882-.562 4.015-1.695zm73.085-44.528c0 12.43-3.06 23.897-9.19 34.4-6.13 10.503-14.44 18.81-24.942 24.94-10.502 6.13-21.968 9.192-34.4 9.192-12.43 0-23.896-3.06-34.4-9.19-10.502-6.13-18.81-14.44-24.94-24.942-6.13-10.503-9.19-21.97-9.19-34.4s3.06-23.897 9.19-34.4c6.13-10.503 14.438-18.81 24.94-24.94 10.504-6.13 21.97-9.192 34.4-9.192s23.898 3.06 34.4 9.19c10.504 6.13 18.81 14.44 24.942 24.942 6.13 10.503 9.19 21.97 9.19 34.4z"></path></svg>';

      var titles = [];
      var offsetBuffer = 50;
      var maxString = 60;
      var maxRows = 5;
      var menu_title = Drupal.t("On this page");

      var floatingNav = jQuery('<ul style="list-style-type:none; padding: 0;"></ul>');
      jQuery('.panelizer-view-mode .pane-title-wrapper .title').each(function (key, value) {
        var href = jQuery(value).siblings("A").attr('href');
        var text = jQuery(value).text().trim();

        if (text.length > maxString) {
          text = text.substring(0, maxString) + "..."
        }

        var offsetObj = jQuery(value).offset();
        var offset = Math.floor(offsetObj.top - offsetBuffer);
        titles.push({text: text, offset: offset, id: '#t' + offset});

        jQuery('<li id="t' + offset + '" style="margin: 0.5em 1em;"><a href="' + href + '" class="link-title-with-icon">' + svg_icon + '&nbsp;&nbsp;' + text + '</a></li>')
          .appendTo(floatingNav);
      });

      floatingNav.css({
        columns: '20em auto'
      });

      var paneContent = jQuery('<div class="pane-content"></div>');
      var row = jQuery('<div></div>');
      var containingBox = jQuery('<div style="border:1px solid #aaa;background-color:#f9f9f9"></div>'); //Inline styles, ugly. Look for replacement?
      var fieldGroup = jQuery('<div class="field field-name-field-fpp-useful-links field-type-link-field field-label-hidden"></div>');
      containingBox.html('<h4 style="padding-left:20px; color:#0093cf;">' + menu_title + '</h4>'); //Inline styles, ugly. Look for replacement?
      containingBox.append(floatingNav);
      fieldGroup.append(containingBox);
      row.append(fieldGroup);
      paneContent.append(row);

      //Change to whatever the ID/class is on the drupal page
      toc_container.append(paneContent);
    }
  };
})(jQuery);
