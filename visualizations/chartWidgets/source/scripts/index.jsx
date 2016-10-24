window.chartWidget = {};

var React = require('react');
let BarChart = require('./chartWidgets/ExtendedBar');
let PieChart = require('./chartWidgets/ExtendedPie');
let GroupedBar = require('./chartWidgets/GroupedBar');
let GroupedBarExport = require('./chartWidgets/GroupedBarExport');
let StackedBar = require('./chartWidgets/StackedBar');
let StackedBarExport = require('./chartWidgets/StackedBarExport');
let TreeMap = require('./chartWidgets/TreeMap');
let BubbleChart = require('./chartWidgets/BubbleChart');
let Sankey = require('./chartWidgets/Sankey');
let Scorecard = require('./chartWidgets/Scorecard');

import { render } from 'react-dom';

window.chartWidget.create = function(options, data) {
	var chartData, dataURL;
	if(typeof(data) == "string") { //assumption: URL for JSON
		dataURL = data;
	}
	else { //assumption: data is tabular JSON data
		chartData = data;
	}

	switch(options.type) {
		case "Bar": 
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
		            	processor = {options.processor}
		           	/>
		        </div>
			), document.getElementById(options.container))
		break;
		case "Pie": 
			render((
				<div className={options.className}>
					<h3>{options.name}</h3>
					<PieChart
						width = {options.width}
						height = {options.height}
						margin = {options.margin}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
		           	/>
		        </div>
			), document.getElementById(options.container))
		break;
		case "GroupedBar": 
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
		            	processor = {options.processor}
		           	/>
		           	<h4 className={'chartDescription'}>{options.description}</h4>
		        </div>
			), document.getElementById(options.container))
		break;
		case "GroupedBarExport": 
			render((
				<div className={options.className}>
					<GroupedBarExport
						xlabel = {options.xlabel}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
		           	/>
		        </div>
			), document.getElementById(options.container))
		break;
		case "StackedBar": 
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
		            	processor = {options.processor}
		           	/>
		           	<h4 className={'chartDescription'}>{options.description}</h4>
		        </div>
			), document.getElementById(options.container))
		break;
		case "StackedBarExport": 
			render((
				<div className={options.className}>
					<StackedBarExport
						xlabel = {options.xlabel}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
		           	/>
		        </div>
			), document.getElementById(options.container))
		break;
		case "TreeMap": 
			render((
				<div className={options.className}>
					<TreeMap
						chartTitle = {options.name}
						width = {options.width}
						height = {options.height}
						margin = {options.margin}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
					/>
					<h4 className={'chartDescription'}>{options.description}</h4>
				</div>
			), document.getElementById(options.container))
		break;
		case "BubbleChart": 
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
		            	processor = {options.processor}
					/>
					<h4 className={'chartDescription'}>{options.description}</h4>
				</div>
			), document.getElementById(options.container))
		break;
		case "Sankey": 
			render((
				<div className={options.className}>
					<Sankey
						chartTitle = {options.name}
						width = {options.width}
						height = {options.height}
						margin = {options.margin}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
					/>
					<h4 className={'chartDescription'}>{options.description}</h4>
				</div>
			), document.getElementById(options.container))
		break;
		case "Scorecard": 
			render((
				<div className={options.className}>
					<Scorecard
						chartTitle = {options.name}
						width = {options.width}
						height = {options.height}
						margin = {options.margin}
		            	dataURL = {dataURL}
		            	chartData = {chartData}
		            	processor = {options.processor}
					/>
					<h4 className={'chartDescription'}>{options.description}</h4>
				</div>
			), document.getElementById(options.container))
		break;
	}
}

