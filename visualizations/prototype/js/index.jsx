var React = require('react');
import { render } from 'react-dom';

var d3 = require('d3');
var rd3c= require('./rd3c');

window.CHART_WIDGETS = {};

var BarChart = rd3c.BarChart;

var GroupedBar = React.createClass ({
	getInitialState: function() {
	    return {
	      chartData: [
		    {
		    label: 'Oil',
		    values: [{x: '2009', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: 'Gas',
		    values: [{x: '2009', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: 'NGL',
		    values: [{x: '2009', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: 'Condensate',
		    values: [{x: '2009', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    }
		  ]		  
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
		d3.json(this.props.filename, function(error, data) {
			if (error) throw error;
			this.setState({chartData: data});
		}.bind(this))
	},

	render: function() {
	    return (
		    <BarChart
		    	groupedBars
	            data={this.state.chartData}
	            width={800}
	            height={600}
	            margin={{top: 10, bottom: 50, left: 100, right: 10}}
	        	xAxis={{label: this.props.xlabel}}
                yAxis={{label: this.props.ylabel}} 
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'} 
                legend={true} />
	    )
	}
});


var StackedBar = React.createClass ({
	getInitialState: function() {
	    return {
	      chartData: [
		    {
		    label: '1112E1 Ordinary taxes on income, profits and capital gains',
		    values: [{x: '2008', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: '114521E Licence fees',
		    values: [{x: '2008', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: '114522E Emission and pollution taxes',
		    values: [{x: '2008', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: '1412E2 From government participation (equity)',
		    values: [{x: '2008', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    },
		    {
		    label: '1413E Withdrawals from income of quasi-corporations',
		    values: [{x: '2008', y: 0}, {x: '2010', y: 0}, {x: '2011', y: 0}, {x: '2012', y: 0}, {x: '2013', y: 0}]
		    }
		  ]		  
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
		d3.json(this.props.filename, function(error, data) {
			if (error) throw error;
			this.setState({chartData: data});
		}.bind(this))
	},

	render: function() {
	    return (
		    <BarChart
	            data={this.state.chartData}
	            width={800}
	            height={600}
	            margin={{top: 10, bottom: 50, left: 100, right: 10}}
	        	xAxis={{label: this.props.xlabel}}
                yAxis={{label: this.props.ylabel}} 
                tooltipHtml={this.props.tooltip}
                tooltipMode={'mouse'} 
	            legend={true} />
	    )
	}
});


window.CHART_WIDGETS.createGroupedBar = function(options) {
	render((
		<div>
			<GroupedBar
	            filename = {options.filename}
	            xlabel = {options.xlabel}
	            ylabel = {options.ylabel}
	        />
        </div>
	), document.getElementById(options.container))
}

window.CHART_WIDGETS.createStackedBar = function(options) {
	render((
			<div>
				<StackedBar
		            filename = {options.filename}
		            xlabel = {options.xlabel}
		            ylabel = {options.ylabel}
		        />
	        </div>
		), document.getElementById(options.container))
}
