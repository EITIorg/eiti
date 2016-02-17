window.chartWidget = {};

var React = require('react');
let BarChart = require('./chartWidgets/ExtendedBar');
let PieChart = require('./chartWidgets/ExtendedPie');
let GroupedBar = require('./chartWidgets/GroupedBar');
let StackedBar = require('./chartWidgets/StackedBar');
let TreeMap = require('./chartWidgets/TreeMap');
let BubbleChart = require('./chartWidgets/BubbleChart');
let Sankey = require('./chartWidgets/Sankey');

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
			<div className={options.className}>
				<h3>{options.name}</h3>
				<BarChart
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	           	/>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "Pie") {
		render((
			<div className={options.className}>
				<h3>{options.name}</h3>
				<PieChart
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	           	/>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "GroupedBar") {
		render((
			<div className={options.className}>
				<GroupedBar
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	            	legend = {true}
	            	legendClass = {options.legendClass}
	           	/>
	           	<h4 className={'chartDescription'}>{options.description}</h4>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "StackedBar") {
		render((
			<div className={options.className}>
				<StackedBar
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
					xlabel = {options.xlabel}
	            	ylabel = {options.ylabel}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
	            	legend = {true}
	            	legendClass = {options.legendClass}
	           	/>
	           	<h4 className={'chartDescription'}>{options.description}</h4>
	        </div>
		), document.getElementById(options.container))
	} else if(options.type == "TreeMap") {
		render((
			<div className={options.className}>
				<TreeMap
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
				/>
				<h4 className={'chartDescription'}>{options.description}</h4>
			</div>
		), document.getElementById(options.container))
	} else if(options.type == "BubbleChart") {
		render((
			<div className={options.className}>
				<BubbleChart
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					diameter = {options.diameter}
					margin = {options.margin}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
				/>
				<h4 className={'chartDescription'}>{options.description}</h4>
			</div>
		), document.getElementById(options.container))
	} else if(options.type == "Sankey") {
		render((
			<div className={options.className}>
				<Sankey
					chartTitle = {options.name}
					width = {options.width}
					height = {options.height}
					margin = {options.margin}
	            	dataURL = {dataURL}
	            	chartData = {chartData}
				/>
				<h4 className={'chartDescription'}>{options.description}</h4>
			</div>
		), document.getElementById(options.container))
	}
}

