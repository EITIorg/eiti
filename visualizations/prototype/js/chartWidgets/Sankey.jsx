let React = require('react');
let d3 = require('d3');

import { findDOMNode } from 'react-dom';

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');
let SankeyImport = require('../vendor/sankey');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
	componentDidUpdate: function(nextProps, nextState) {
		let {data, width, height, margin} = this.props;

		let el = findDOMNode(this);

    d3.select(el).select("svg").remove(); // clear nodes with state change

	    let svg = d3.select(el).append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

		let formatNumber = d3.format(",.0f"),
            format = function(d) { return "$" + formatNumber(d); },
            color = d3.scale.category20();

    let sankey = d3.sankey()
        .nodeWidth(15)
        .nodePadding(10)
        .size([width, height]);

    let path = sankey.link();

		sankey
              .nodes(data.nodes)
              .links(data.links)
              .layout(32);

          var link = svg.append("g").selectAll(".link")
              .data(data.links)
              .enter().append("path")
              .attr("class", "link")
              .attr("d", path)
              .style("stroke-width", function(d) { return Math.max(1, d.dy); })
              .sort(function(a, b) { return b.dy - a.dy; });

          link.append("title")
              .text(function(d) { return d.source.name + " → " + d.target.name + "\n" + format(d.value); });

          var node = svg.append("g").selectAll(".node")
              .data(data.nodes)
              .enter().append("g")
              .attr("class", "node")
              .attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; })
              .call(d3.behavior.drag()
              .origin(function(d) { return d; })
              .on("dragstart", function() { this.parentNode.appendChild(this); })
              .on("drag", dragmove));

          node.append("rect")
              .attr("height", function(d) { return d.dy; })
              .attr("width", sankey.nodeWidth())
              .style("fill", function(d) { return d.color = color((d.name||" ").replace(/ .*/, "")); })
              .style("stroke", function(d) { return d3.rgb(d.color).darker(2); })
              .append("title")
              .text(function(d) { return d.name + "\n" + format(d.value); });

          node.append("text")
              .attr("x", -6)
              .attr("y", function(d) { return d.dy / 2; })
              .attr("dy", ".35em")
              .attr("text-anchor", "end")
              .attr("transform", null)
              .text(function(d) { return d.name; })
              .filter(function(d) { return d.x < width / 2; })
              .attr("x", 6 + sankey.nodeWidth())
              .attr("text-anchor", "start");

          function dragmove(d) {
            d3.select(this).attr("transform", "translate(" + d.x + "," + (d.y = Math.max(0, Math.min(height - d.dy, d3.event.y))) + ")");
            sankey.relayout();
            link.attr("d", path);
          }
	},	

	// Returns a flattened hierarchy containing all leaf nodes under the root.
    classes: function(root) {
      var classes = [];      

      function recurse(name, node) {
        if (node.children) {
        	node.children.forEach(function(child) { 
        		recurse(node.name, child); 
        	});
        } else {
        	classes.push({packageName: name, className: node.name, value: node.size});
        }
      }

      recurse(null, root);
      return {children: classes};
    },

	render() {
		return (
                <div></div>
        );
    }
});

let Sankey = React.createClass({
	mixins: [DefaultPropsMixin,
			 HeightWidthMixin,
			 AccessorMixin,
			 TooltipMixin],

	getInitialState: function() {
		return {
	    	chartData: {
			  "nodes": [],
			  "links": []
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

	render() {
		let {width,
			 height,
			 margin,
			 chartTitle} = this.props;

		return (
			<div>	
					<h3 className={"chartTitle"}>{chartTitle}</h3>			
					<DataSet
            		data={this.state.chartData}
            		width={width - margin.left - margin.right}
            		height={height - margin.top - margin.bottom}
            		margin={margin}             		
            		/>
			</div>
		);
	}
});

module.exports = Sankey;
