var React = require('react');
var PieChart = require('./PieChart');

let ExtendedPie = React.createClass ({
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
    		tooltip: function(x, y, total) {
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
               			var processedData = props.processor(data);
			    	  	_this.setState({chartData: processedData});
		            } else {
		              	_this.setState({chartData: data});
		            }
			    }
			  }
			req.open("GET", props.dataURL, true);
			req.send();
		}
		else if(props.chartData) {
			this.setState({chartData: props.chartData});
		}
	},

	componentWillMount: function() {
		this.updateData(this.props);
	},

	componentWillReceiveProps: function(nextProps) {
		this.updateData(nextProps);
	},

	render: function() {
	    return (
		    <PieChart
	            data={this.state.chartData}
	            width={this.props.width}
	            height={this.props.height}
	            margin={this.props.margin}
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'} />
	    )
	}
});

module.exports = ExtendedPie;
