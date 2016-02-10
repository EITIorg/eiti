window.chartWidget = {};

var React = require('react');
let BarChart = require('./chartWidgets/ExtendedBar');
let PieChart = require('./chartWidgets/ExtendedPie');
let GroupedBar = require('./chartWidgets/GroupedBar');
let StackedBar = require('./chartWidgets/StackedBar');
let TreeMap = require('./chartWidgets/TreeMap');

import { render } from 'react-dom';

window.chartWidget.create = function(options, data) {
	var chartData, dataURL;
	if(typeof(data) == "string") { //assumption: URL for JSON
		dataURL = data;
	} 
	else { //assumption: data is tabular JSON data
		chartData = data;
	}
	if(options.type == "Bar") {
		render((
			<div>
				<h3>{options.name}</h3>
				<BarChart
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
	} else if(options.type == "Pie") {
		render((
			<div>
				<h3>{options.name}</h3>
				<PieChart
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	           	/>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "GroupedBar") {
		render((
			<div>
				<GroupedBar
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	            	legend = {true}
	           	/>
	           	<h4 className={'chartDescription'}>{options.description}</h4>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "StackedBar") {
		render((
			<div>
				<StackedBar
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	            	legend = {true}
	           	/>
	           	<h4 className={'chartDescription'}>{options.description}</h4>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "TreeMap") {
		render((
			<div>
				<TreeMap
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					className = {options.className}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
				/>
				<h4 className={'chartDescription'}>{options.description}</h4>
			</div>
		), document.getElementById(options.container))
	}
}

