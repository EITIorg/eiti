var React = require('react');
let Papa = require('papaparse');

let GroupedBarExport = React.createClass ({

	getInitialState: function() {
	    return {
	    	chartData: [{
			    label: '',
			    values: [{x: '', y: 0}]
		    }],

		    rawData: [{
			    label: '',
			    values: [{x: '', y: 0}]
		    }]
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
		               data = props.processor(data);
		            }
			    	var classData = data.map(function(item) {
			    		var newItem = item;
			    		newItem['active'] = true;
			    		return newItem;
			    	});
			    	_this.setState({rawData: classData, chartData: data});
			    }
			}
			req.open("GET", props.dataURL, true);
			req.send();
		}
		else if(props.chartData) {
			var classData = props.chartData.map(function(item) {
	    		var newItem = item;
	    		newItem['active'] = true;
	    		return newItem;
	    	});
			this.setState({rawData: classData, chartData: props.chartData});
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

	    data[0].values.forEach(function(item) {
	    	var outputObj = {};
	    	outputObj[xlabel] = item.x;
	    	outputObj[data[0].label] = item.y;
	    	output.push(outputObj);
	    });

	    let dataLength = data.length;
	    for(var i=1; i<dataLength; i++) {
	    	var j = 0;
	    	data[i].values.forEach(function(item) {
	    		output[j][data[i].label] = item.y;
	    		j++;
	    	});
	    }

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

	render: function() {
	    return (
	    <div>
                <button className="export" onClick={this.doExport.bind(this, this.props.xlabel)}> Export Data </button>
        </div>
	    )
	}
});

module.exports = GroupedBarExport;
