let React = require('react');
let d3 = require('d3');
let Papa = require('papaparse');

import { findDOMNode } from 'react-dom';

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');
let SankeyImport = require('../vendor/sankey');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
  getInitialState: function () {
      return {
        table: ""
      };
  },

	componentDidUpdate: function(nextProps, nextState) {
    let {width, height, margin} = this.props;
		let el = findDOMNode(this),
        parentEl = el.parentNode.parentNode.parentNode;

    if(parentEl.clientWidth >= width + margin.left + margin.right) {
      this.drawSankey(el);
    } else {
      this.drawTable(el);
    }    
  },

  drawSankey: function(el) {
    let {data, width, height, margin} = this.props;

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

  drawTable: function(el) {
    let data = this.props.data;
    console.log(data);
    let table = <table>
                  <thead>
                    <tr>
                      <th> Company Revenue Stream </th>
                      <th> Receiving Entity </th>
                      <th> Amount </th>                                    
                    </tr>
                  </thead>
                </table>;
    if(this.state.table == "") {
      this.setState({table: table});
    }
  },

	render() {

		return (
                <div>
                    {this.state.table}
                </div>
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
            var data = JSON.parse(req.responseText), 
                nodedata = [], 
                linkdata = [],
                processedData;
            if(props.processor) {
                    data = props.processor(data);
                } 
            }
            var nodes = (data) ?  data.nodes : {};
            for (var node in nodes) {
              nodedata.push(nodes[node]);
            }
            var links = (data) ? data.links : {};
            for (var link in links) {
              linkdata.push({ "source": nodedata.indexOf(nodes[links[link].source]),
                              "target": nodedata.indexOf(nodes[links[link].target]),
                              "value": links[link].value});
            }
            processedData = {"nodes" : nodedata, "links": linkdata};
            _this.setState({chartData: processedData});
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

  doExport: function(anything) {
    let output = [];
    this.state.chartData.links.forEach(function(link) {
        if(link.source.sourceLinks.length > 0 && link.source.targetLinks.length == 0) {  // Company names
            var company = link.source.name;
            link.source.sourceLinks.forEach(function (item) {
                var outputObj = { "Company Name" : company,
                                  "Revenue Stream" : item.target.name,
                                  "Receiving Entity" : item.target.sourceLinks[0].target.name,
                                  "Amount" : item.value
                                };
                if(output.indexOf(outputObj) == -1) {
                  output.push(outputObj);
                }
            });
        }
    });

    var csv = Papa.unparse(output);

    var csvData = new Blob([csv], {type: 'text/csv;charset=utf-8;'});
    var csvURL =  null;
    if (navigator.msSaveBlob) {
        csvURL = navigator.msSaveBlob(csvData, 'download.csv');
    } else {
        csvURL = window.URL.createObjectURL(csvData);
    }
    var tempLink = document.createElement('a');
    tempLink.href = csvURL;
    tempLink.setAttribute('download', 'download.csv');
    tempLink.click();
  },

	render() {
		let {width,
			 height,
			 margin,
			 chartTitle} = this.props;

		return (
			<div>	
					<h3 className={"chartTitle"}>{chartTitle}</h3>		
          <button onClick={this.doExport.bind(this, "input")}>	Export Data </button>
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
