let React = require('react');
let _ = require('lodash');

import { BootstrapTable, TableHeaderColumn } from 'react-bootstrap-table';
import { findDOMNode } from 'react-dom';

let Chart = require('./Chart');
let Tooltip = require('./Tooltip');
let ScorecardImport = require('../vendor/scorecard');

let scores = require('../data/scores');
let categories = require('../data/categories');
let requirements = require('../data/requirements');

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

    this.drawScorecard(el);
  },

  drawScorecard: function(el) {
    let {data, width, height, margin} = this.props;
    let scorecard = ScorecardImport.init(data.data, scores, categories, requirements, el);
	},

	render() {
		return (
                <div>
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
          scores: null,
          requirements: null,
          categories: null
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

            _this.setState({chartData: data});
        }
      };
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
            		margin={margin} />
			</div>
		);
	}
});

module.exports = Scorecard;
