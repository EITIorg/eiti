window.mapWidget = {};

import React from 'react';
import { render } from 'react-dom';

import MapWidgetComponent from './MapWidgetComponent';

window.mapWidget.createHomePage = function(options) {
	options['buttons'] = false;
	render(<MapWidgetComponent options={options} />, document.getElementById(options.container));
}

window.mapWidget.createMapPage = function(options) {
	options['buttons'] = true;
	options['infobox'] = true;
	render(<MapWidgetComponent options={options} />, document.getElementById(options.container));
}
