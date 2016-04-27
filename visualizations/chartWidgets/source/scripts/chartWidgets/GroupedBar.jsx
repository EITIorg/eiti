var React = require('react');
var Reflux = require('reflux');
let Papa = require('papaparse');

var BarChart = require('./BarChart');
var BarStore = require('./stores/BarStore');

let GroupedBar = React.createClass ({
	mixins: [Reflux.listenTo(BarStore,"barChange")],

	barChange: function(param) {
		var key = param.toggle;
		var oldData = this.state.chartData;
		var newData = [];
		var chartLabels = oldData.map(function(item) {
			return item.label;
		});
		/* if key is currently in chartData, remove it; otherwise add it */
		if(chartLabels.indexOf(key) >= 0 ) {
			if(chartLabels.length > 1) { // can't remove last selected object
				oldData.forEach(function(item) {
					if(item.label !== key) {
						newData.push(item);
					}
				});
			}
		} else {
			this.state.rawData.forEach(function(item) {
				if(chartLabels.indexOf(item.label) >= 0 || item.label === key) {
					newData.push(item);
				}
			});
		}

		/* update active state for changed labels */
		var newChartLabels = newData.map(function(item) {
			return item.label;
		});
		var classData = this.state.rawData;
		classData.forEach(function(item){
			item.active = (newChartLabels.indexOf(item.label) < 0 ) ? false : true;
		});

		this.setState({ chartData: newData, rawData: classData });
	},

	getInitialState: function() {
	    return {
	    	chartData: [{
			    label: '',
			    values: [{x: '', y: 0}]
		    }],

		    rawData: [{
			    label: '',
			    values: [{x: '', y: 0}]
		    }]
	    }
    },

    getDefaultProps: function() {
    	return {
    		tooltip: function(x, y0, y, total) {
			    return y.toString();
			}
    	}

    },

	updateData: function(props) {
		if(props.dataURL) {
			var _this = this;
			/* Old school AJAX request to try to stay away from jQuery */
			var req = new XMLHttpRequest();
			req.onreadystatechange = function() {
			    if (req.readyState == 4 && req.status == 200) {
			    	var data = JSON.parse(req.responseText);
			    	if(props.processor) {
		               data = props.processor(data);
		            }
			    	var classData = data.map(function(item) {
			    		var newItem = item;
			    		newItem['active'] = true;
			    		return newItem;
			    	});
			    	_this.setState({rawData: classData, chartData: data, showLegend: true});
			    }
			}
			req.open("GET", props.dataURL, true);
			req.send();
		}
		else if(props.chartData) {
			var classData = props.chartData.map(function(item) {
	    		var newItem = item;
	    		newItem['active'] = true;
	    		return newItem;
	    	});
			this.setState({rawData: classData, chartData: props.chartData});
		}
	},

	componentWillMount: function() {
		this.updateData(this.props);
	},

	componentWillReceiveProps: function(nextProps) {
		this.updateData(nextProps);
	},

	doExport: function(xlabel) {
	    let output = [];
	    let data = this.state.chartData;

	    data[0].values.forEach(function(item) {
	    	var outputObj = {};
	    	outputObj[xlabel] = item.x;
	    	outputObj[data[0].label] = item.y;
	    	output.push(outputObj);
	    });

	    let dataLength = data.length;
	    for(var i=1; i<dataLength; i++) {
	    	var j = 0;
	    	data[i].values.forEach(function(item) {
	    		output[j][data[i].label] = item.y;
	    		j++;
	    	});
	    }

	    var csv = Papa.unparse(output);

	    var csvData = new Blob([csv], {type: 'text/csv;charset=utf-8;'});
	    var csvURL =  null;
	    if (navigator.msSaveBlob) {
	        csvURL = navigator.msSaveBlob(csvData, 'download.csv');
	    } else {
	        csvURL = window.URL.createObjectURL(csvData);
	    }
	    var tempLink = document.createElement('a');
	    document.body.appendChild(tempLink);
	    tempLink.href = csvURL;
	    tempLink.setAttribute('download', 'download.csv');
	    tempLink.click();
	},

	render: function() {
	    return (
	    <div>
		    <BarChart
		    	groupedBars
		    	chartTitle={this.props.chartTitle}
	            data={this.state.chartData}
	            legendData={this.state.rawData}
	            legendClass={this.props.legendClass}
	            width={this.props.width}
	            height={this.props.height}
	            margin={this.props.margin}
	        	xAxis={{label: this.props.xlabel}}
                yAxis={{label: this.props.ylabel}}
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'}
                legend={this.props.legend || false} />
                <button className="export" onClick={this.doExport.bind(this, this.props.xlabel)}> Export Data </button>
        </div>
	    )
	}
});

module.exports = GroupedBar;
