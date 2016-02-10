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

		    showLegend: false
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
			    	var classData = data.map(function(item) {
			    		var newItem = item;
			    		newItem['active'] = true;
			    		return newItem;
			    	});
			    	_this.setState({rawData: classData, chartData: data, showLegend: true});
			    }
			  }
			req.open("GET", this.props.dataURL, true);
			req.send();
		}
		else if(this.props.chartData) {
			var classData = this.props.chartData.map(function(item) {
	    		var newItem = item;
	    		newItem['active'] = true;
	    		return newItem;
	    	});
			this.setState({rawData: classData, chartData: this.props.chartData, showLegend: true});
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
                legend={this.props.legend && this.state.showLegend} />
	    )
	}
});

module.exports = StackedBar;