var React = require('react');
var d3 = require('d3');

var BarChart = require('./BarChart');

let GroupedBar = React.createClass ({
	getInitialState: function() {
	    return {
	    	chartData: [{
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

	componentWillMount: function() {
		if(this.props.dataURL) {
			var _this = this;
			/* Old school AJAX request to try to stay away from jQuery */
			var req = new XMLHttpRequest();
			req.onreadystatechange = function() {
			    if (req.readyState == 4 && req.status == 200) {
			    	var data = JSON.parse(req.responseText);
			    	_this.setState({chartData: data});
			    }
			  }
			req.open("GET", this.props.dataURL, true);
			req.send();
		}
		else if(this.props.chartData) {
			this.setState({chartData: this.props.chartData});
		}
	},

	render: function() {
	    return (
		    <BarChart
		    	groupedBars
	            data={this.state.chartData}
	            width={this.props.width}
	            height={this.props.height}
	            margin={this.props.margin}
	        	xAxis={{label: this.props.xlabel}}
                yAxis={{label: this.props.ylabel}} 
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'} 
                legend={false} />
	    )
	}
});

module.exports = GroupedBar;