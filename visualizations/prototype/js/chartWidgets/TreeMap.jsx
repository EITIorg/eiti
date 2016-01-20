let React = require('react');
let d3 = require('d3');

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
	propTypes: {
		colorScale: React.PropTypes.func.isRequired,
		strokeWidth: React.PropTypes.number,
		stroke: React.PropTypes.string,
		fill: React.PropTypes.string,
		opacity: React.PropTypes.number,
		x: React.PropTypes.func.isRequired
	},

	getDefaultProps() {
		return {
			strokeWidth: 2,
			stroke: '#000',
			fill: 'none',
			opacity: 0.3
		};
	},

	render() {
		let {height,
			 width,
			 margin,
			 formatNumber,
			 transitioning,
			 colorScale,
			 radius,
			 strokeWidth,
			 stroke,
			 fill,
			 opacity,
			 x,
			 y,
			 onMouseEnter,
			 onMouseLeave} = this.props;

		var x = d3.scale.linear()
            .domain([0, width])
            .range([0, width]);

        var y = d3.scale.linear()
            .domain([0, height])
            .range([0, height]);		

		return (
			<g>
			</g>
		);
	}
});

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

	_tooltipHtml(d, position) {
        let html = this.props.tooltipHtml(this.props.x(d), this.props.y(d));

        return [html, 0, 0];
	},

	render() {
		let {data,
			 width,
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
				<g>
				<DataSet
					width={width}
					height={height}
					colorScale={colorScale}
					x={x}
					y={y}
					onMouseEnter={this.onMouseEnter}
					onMouseLeave={this.onMouseLeave}
				/>
				</g>
				{ this.props.children }
				</Chart>

                <Tooltip {...this.state.tooltip}/>
				</div>
		);
	}
});

module.exports = TreeMap;
