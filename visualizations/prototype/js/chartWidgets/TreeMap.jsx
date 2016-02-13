let React = require('react');
let d3 = require('d3');

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
	componentDidMount: function() {
		let {width, height, margin} = this.props;

	    let el = this.getDOMNode();

	    let svg = d3.select(el).append("svg")
                .attr("width", width + margin.left + margin.right)
                .attr("height", height + margin.bottom + margin.top)
                .style("margin-left", -margin.left + "px")
                .style("margin-right", -margin.right + "px")
                .append("g")
                .attr("transform", "translate(" + margin.left + "," + margin.top + ")")
                .style("shape-rendering", "crispEdges");

        let grandparent = svg.append("g")
            .attr("class", "grandparent");

        grandparent.append("rect")
            .attr("y", -margin.top)
            .attr("width", width)
            .attr("height", margin.top);

        grandparent.append("text")
            .attr("x", 6)
            .attr("y", 6 - margin.top)
            .attr("dy", ".75em");

        this.setState({svg: svg, grandparent: grandparent});       
	},

	componentDidUpdate: function(nextProps, nextState) {
		let data = this.props.data;
		this.initialize(data);
		this.accumulate(data);
		this.layout(data);
		this.display(data);
	},

	initialize: function(root) {
        root.x = root.y = 0;
        root.dx = this.props.width;
        root.dy = this.props.height;
        root.depth = 0;
    },

    // Aggregate the values for internal nodes. This is normally done by the
	// treemap layout, but not here because of our custom implementation.
	// We also take a snapshot of the original children (_children) to avoid
	// the children being overwritten when when layout is computed.
    accumulate: function(d) {
    	var self = this;
        return (d._children = d.children)
            ? d.value = d.children.reduce(function(p, v) { return p + self.accumulate(v); }, 0)
            : d.value;
    },

	// Compute the treemap layout recursively such that each group of siblings
	// uses the same size (1×1) rather than the dimensions of the parent cell.
	// This optimizes the layout for the current zoom state. Note that a wrapper
	// object is created for the parent node for each group of siblings so that
	// the parent’s dimensions are not discarded as we recurse. Since each group
	// of sibling was laid out in 1×1, we must rescale to fit using absolute
	// coordinates. This lets us use a viewport to zoom.
	layout: function(d) {
		if (d._children) {
		  this.props.treemap.nodes({_children: d._children});
		  var self = this;
		  d._children.forEach(function(c) {
		    c.x = d.x + c.x * d.dx;
		    c.y = d.y + c.y * d.dy;
		    c.dx *= d.dx;
		    c.dy *= d.dy;
		    c.parent = d;
		    self.layout(c);
		  });
		}
	},

	display: function(d) {
		let {svg, grandparent} = this.state;
		let {x, y, formatNumber} = this.props;
		var transitioning;
		var self = this;

	    grandparent
	        .datum(d.parent)
	        .on("click", this.transition)
	      	.select("text")
	        .text(this.name(d));

	    var g1 = svg.insert("g", ".grandparent")
	        .datum(d)
	        .attr("class", "depth");

	    var g = g1.selectAll("g")
	        .data(d._children)
	      	.enter().append("g");

	    g.filter(function(d) { return d._children; })
	        .classed("children", true)
	        .on("click", this.transition);

	    g.selectAll(".child")
	        .data(function(d) { return d._children || [d]; })
	      	.enter().append("rect")
	        .attr("class", "child")
	        .call(this.rect);

	    g.append("rect")
	        .attr("class", "parent")
	        .call(this.rect)
	      	.append("title")
	        .text(function(d) { return formatNumber(d.value); });

	    g.append("text")
	        .attr("dy", ".75em")
	        .text(function(d) { return d.name; })
	        .call(this.text);

	    function transition(d) {
	    	console.log('transition triggered!');
			if (transitioning || !d) return;
			transitioning = true;

			var g2 = self.display(d),
			t1 = g1.transition().duration(750),
			t2 = g2.transition().duration(750);

			// Update the domain only after entering new elements.
			x.domain([d.x, d.x + d.dx]);
			y.domain([d.y, d.y + d.dy]);

			// Enable anti-aliasing during the transition.
			svg.style("shape-rendering", null);

			// Draw child nodes on top of parent nodes.
			svg.selectAll(".depth").sort(function(a, b) { return a.depth - b.depth; });

			// Fade-in entering text.
			g2.selectAll("text").style("fill-opacity", 0);

			// Transition to the new view.
			t1.selectAll("text").call(text).style("fill-opacity", 0);
			t2.selectAll("text").call(text).style("fill-opacity", 1);
			t1.selectAll("rect").call(rect);
			t2.selectAll("rect").call(rect);

			// Remove the old node when the transition is finished.
			t1.remove().each("end", function() {
			svg.style("shape-rendering", "crispEdges");
			transitioning = false;
			});
	    }

	    return g;
	},

	text: function(text) {
		let {x, y} = this.props;
		text.attr("x", function(d) { return x(d.x) + 6; })
	    .attr("y", function(d) { return y(d.y) + 6; });
	},

	rect: function(rect) {
		let {x, y} = this.props;
		rect.attr("x", function(d) { return x(d.x); })
	    .attr("y", function(d) { return y(d.y); })
	    .attr("width", function(d) { return x(d.x + d.dx) - x(d.x); })
	    .attr("height", function(d) { return y(d.y + d.dy) - y(d.y); });
	},

	name: function(d) {
		return d.parent
	    ? name(d.parent) + "." + d.name
	    : d.name;
	},

	render() {
		return (
                <div></div>
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

	getInitialState: function() {
		return {
	    	chartData:{
			  "name":"",
			  "children":[]
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
			console.log(this.state);
		}
	},

	render() {
		let {width,
			 height,
			 margin,
			 colorScale,
			 sort,
			 values} = this.props;

		let formatNumber = d3.format(",d");

		let x = d3.scale.linear()
            .domain([0, width])
            .range([0, width]);

        let y = d3.scale.linear()
            .domain([0, height])
            .range([0, height]);

        let treemap = d3.layout.treemap()
	        .children(function(d, depth) { return depth ? null : d._children; })
	        .sort(function(a, b) { return a.value - b.value; })
	        .ratio(height / width * 0.5 * (1 + Math.sqrt(5)))
	        .round(false);

		return (
			<div>				
					<DataSet
            		data={this.state.chartData}
            		width={width}
            		height={height - margin.top - margin.bottom}
            		margin={margin}
            		formatNumber={formatNumber}
            		x={x}
            		y={y}          
            		treemap={treemap}  		           		
            		/>
			</div>
		);
	}
});

module.exports = TreeMap;
