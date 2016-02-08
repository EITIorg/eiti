var React = require('react');
var Reflux = require('reflux');

var BarChart = require('./BarChart');
var BarStore = require('./stores/BarStore');

let StackedBar = React.createClass ({
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
		this.setState({ chartData: newData });
	},

	getInitialState: function() {
	    return {
	    	chartData: [{
			    label: 'Total',
			    values: [{x: '', y: 0}]
		    }],

		    rawData: [{
			    label: 'Total',
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

	componentWillMount: function() {
		if(this.props.dataURL) {
			var _this = this;
			/* Old school AJAX request to try to stay away from jQuery */
			var req = new XMLHttpRequest();
			req.onreadystatechange = function() {
			    if (req.readyState == 4 && req.status == 200) {
			    	var data = JSON.parse(req.responseText);
			    	_this.setState({rawData: data, chartData: data});
			    }
			  }
			req.open("GET", this.props.dataURL, true);
			req.send();
		}
		else if(this.props.chartData) {
			this.setState({rawData: this.props.chartData, chartData: this.props.chartData});
		}
	},

	render: function() {
	    return (
		    <BarChart
	            chartTitle={this.props.chartTitle}
	            data={this.state.chartData}
	            legendData={this.state.rawData}
	            width={this.props.width}
	            height={this.props.height}
	            margin={this.props.margin}
	        	xAxis={{label: this.props.xlabel}}
                yAxis={{label: this.props.ylabel}} 
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'} 
                legend={this.props.legend || false} />
	    )
	}
});

module.exports = StackedBar;