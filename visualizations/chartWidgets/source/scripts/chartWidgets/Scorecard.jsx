let React = require('react');
let d3 = require('d3');
let Papa = require('papaparse');
let _ = require('lodash');

import { BootstrapTable, TableHeaderColumn } from 'react-bootstrap-table';
import { findDOMNode } from 'react-dom';

let Tooltip = require('./Tooltip');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let AccessorMixin = require('./AccessorMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
  getInitialState: function () {
      return {
        table: null
      };
  },

	componentDidUpdate: function(nextProps, nextState) {
    let {width, height, margin} = this.props;
		let el = findDOMNode(this),
    parentEl = el.parentNode.parentNode.parentNode;
    this.drawTable(el);
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
    let output = [{  
      "category":"MSG Oversight",
      "requirements":"Government Engagement",
      "progress_level":"Satisfactory",
      "progress_direction":"up",
      "id":1
      }
    ];

    if(data.links && !this.state.table) {
      this.setState({table: true, tableData: output});
    }
  },

	render() {
		return (
                <div>
                    { this.state.table &&
                      <BootstrapTable data={this.state.tableData} striped={true}>
                          <TableHeaderColumn dataField="category"  dataSort={true}>Category</TableHeaderColumn>
                          <TableHeaderColumn dataField="requirements"  dataSort={true} isKey={true}>Requirement</TableHeaderColumn>
                          <TableHeaderColumn dataField="progress_level" dataSort={true}>Level of Progress</TableHeaderColumn>
                          <TableHeaderColumn dataField="progress_direction" dataSort={true}>Direction of Progress</TableHeaderColumn>
                      </BootstrapTable> }
                </div>
        );
    }
});

let Scorecard = React.createClass({
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
                output.push(outputObj);
            });
        }
    });

    output = _.uniqWith(output, _.isEqual);
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
            		margin={margin} />
			</div>
		);
	}
});

module.exports = Scorecard;
