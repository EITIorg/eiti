'use strict';

var React = require('react');
var d3 = require('d3');
import  * as Actions from './Actions.es6';

module.exports = React.createClass({

  displayName: 'Legend',

  propTypes: {
    className:     React.PropTypes.string,
    colors:        React.PropTypes.func,
    colorAccessor: React.PropTypes.func,
    data:          React.PropTypes.array.isRequired,
    itemClassName: React.PropTypes.string,
    margins:       React.PropTypes.object,
    text:          React.PropTypes.string,
    width:         React.PropTypes.number.isRequired
  },

  getDefaultProps: function() {
    return {
      className:    'rd3-legend',
      colors:        d3.scale.category20(),
      colorAccessor: (d, idx) => idx,
      itemClassName: 'rd3-legend-item',
      text:          '#000'
    };
  },

  handleClick: function(some, thing) {
    Actions.invoke('UPDATE_GRAPH', some);
  },

  render: function() {

    var props = this.props;

    var textStyle = {
      'color': 'black',
      'fontSize': '55%',
      'verticalAlign': 'top',
      'marginLeft': '-7px'
    };

    var legendItems = [];

    props.data.forEach( (series, idx) => {
      var itemStyle = {
        'color': props.colors(series.label)
      };

      legendItems.push(
        <li
          key={idx}
          className={props.itemClassName}
          style={itemStyle}
          onClick = {this.handleClick.bind(this, series.label)}>
          <span
            style={textStyle}>
            {series.label}
          </span>
        </li>
      );

    });

    var topMargin = props.margins.top;

    var legendBlockStyle = {
      'wordWrap': 'break-word',
      'paddingLeft': '0',
      'marginBottom': '0',
      'marginTop': topMargin,
      'listStylePosition': 'inside'
    };

    return (
      <ul
        className={props.className}
        style={legendBlockStyle}
      >
        {legendItems}
      </ul>
    );
  }

});
