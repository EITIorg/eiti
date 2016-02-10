let React = require('react');
let d3 = require('d3');

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let TreeMap = React.createClass({
	mixins: [DefaultPropsMixin,
			 HeightWidthMixin,
			 AccessorMixin,
			 TooltipMixin],

	propTypes: {
		sort: React.PropTypes.any
	},

	getDefaultProps() {
		return {
			sort: undefined
		};
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
			    	_this.setState({rawData: classData, chartData: data});
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
			this.setState({rawData: classData, chartData: this.props.chartData});
		}
	},

	render() {
		let {width,
			 height,
			 margin,
			 colorScale,
			 sort,
			 x,
			 y,
			 values} = this.props;

		
		return (
			<div>
				<Chart height={height} width={width} margin={margin}>
				</Chart>
			</div>
		);
	}
});

module.exports = TreeMap;
