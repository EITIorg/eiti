var React = require('react');
let Papa = require('papaparse');
var BarChart = require('./BarChart');

let ExtendedBar = React.createClass ({
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
    		tooltip: function(x, y0, y, total) {
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

	doExport: function(xlabel) {
	    let output = [];
	    let data = this.state.chartData;
	    console.log(data);
	    
	    data[0].values.forEach(function(item) {
	    	var outputObj = {};
	    	outputObj[xlabel] = item.x;
	    	outputObj[data[0].label] = item.y;
	    	output.push(outputObj);
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

	render: function() {
	    return (
	    	<div>
			    <BarChart
		            data={this.state.chartData}
		            width={this.props.width}
		            height={this.props.height}
		            margin={this.props.margin}
		        	xAxis={{label: this.props.xlabel}}
	                yAxis={{label: this.props.ylabel}} 
	                tooltipHtml={this.props.tooltip}
	                tooltipMode={'mouse'} 
	                legend={false} />
	            <button className="export" onClick={this.doExport.bind(this, this.props.xlabel)}> Export Data </button>
            </div>
	    )
	}
});

module.exports = ExtendedBar;