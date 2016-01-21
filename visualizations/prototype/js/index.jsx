window.chartWidget = {};

var React = require('react');
let BarChart = require('./chartWidgets/BarChart');
let PieChart = require('./chartWidgets/PieChart');
let GroupedBar = require('./chartWidgets/GroupedBar');
let StackedBar = require('./chartWidgets/StackedBar');

import { render } from 'react-dom';

window.chartWidget.create = function(options, data) {
	var chartData, dataURL;
	if(typeof(data) == "string") { //assumption: URL for JSON
		dataURL = data;
	} 
	else { //assumption: data is tabular JSON data
		chartData = data;
	}
	
	if(options.type == "GroupedBar") {
		render((
			<div>
				<h3>{options.name}</h3>
				<GroupedBar
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	           	/>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "StackedBar") {
		render((
			<div>
				<h3>{options.name}</h3>
				<StackedBar
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	           	/>
	        </div>
		), document.getElementById(options.container))
	}
}

