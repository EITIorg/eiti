
window.mapWidget = {};


import React from 'react';
import { render } from 'react-dom';
import MapWidgetComponent from './MapWidgetComponent';

window.mapWidget.createHomePage = function(options) {
	options['buttons'] = false;
  createMapPage(options);
}

window.mapWidget.createMapPage = function(options) {
	render(<MapWidgetComponent {...options} buttons="true" infobox="true" selector="true"/>, document.getElementById(options.container));
}


// Polyfill not being loaded by Babel

if (!Array.prototype.find) {

  Array.prototype.find = function(predicate) {
    if (this === null) {
      throw new TypeError('Array.prototype.find called on null or undefined');
    }
    if (typeof predicate !== 'function') {
      throw new TypeError('predicate must be a function');
    }
    var list = Object(this);
    var length = list.length >>> 0;
    var thisArg = arguments[1];
    var value;

    for (var i = 0; i < length; i++) {
      value = list[i];
      if (predicate.call(thisArg, value, i, list)) {
        return value;
      }
    }
    return undefined;
  };
}
