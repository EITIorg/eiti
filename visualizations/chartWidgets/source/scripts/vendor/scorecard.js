/*

$().ready(function(){
	initScorecard('/result.json');
});
*/

export var init = function(data, scores, categories, requirements, el) {
	renderScorecard(
		{ 
			result: data,
			requirements: requirements.requirements,
			categories: categories.categories,
			scores: scores.scores
		}, el);
};

function renderScorecard(data, placeholder) {
	window.$ = window.jQuery;

	var table = $('<TABLE>').addClass('country_scorecard');
	var tableHeader = $('<THEAD>');

	var tableHeaderUpperRow = $('<TR>');
	tableHeaderUpperRow.append($('<TH>').attr('colspan', 2).html('EITI Requirements'));
	tableHeaderUpperRow.append($('<TH>').attr('colspan', 5).html('Level of Progress'));
	//tableHeaderUpperRow.append($('<TH>').attr('rowspan', 2).html('Direction <br/>of Progress'));

	var tableHeaderLowerRow = $('<TR>');
	tableHeaderLowerRow.append($('<TH>').html('Categories'));
	tableHeaderLowerRow.append($('<TH>').html('Requirements'));
	tableHeaderLowerRow.append($('<TH>').addClass('scores').html('<div><span>No</span></div>'));
	tableHeaderLowerRow.append($('<TH>').addClass('scores').html('<div><span>Inadequate</span></div>'));
	tableHeaderLowerRow.append($('<TH>').addClass('scores').html('<div><span>Meaningful</span></div>'));
	tableHeaderLowerRow.append($('<TH>').addClass('scores').html('<div><span>Satisfactory</span></div>'));
	tableHeaderLowerRow.append($('<TH>').addClass('scores').html('<div><span>Beyond</span></div>'));

	tableHeader.append(tableHeaderUpperRow);
	tableHeader.append(tableHeaderLowerRow);
	table.append(tableHeader);

	var tableBody = $('<TBODY>');
	table.append(tableBody);
	$(placeholder).append(table);


	//Append requirements rows based on the results
	appendRows(data, tableBody);
	var legend = $('<DIV>').addClass('scorecard-legend').html(getLegend());
	$(placeholder).append(legend);

	window.$ = undefined;
}

function getLegend() {
	var legendHTML = '<div class="scorecard-legend-item">' +
    '  <i style="background:#C00000">&nbsp;</i>' +
    '  <div>' +
    '    The country has made no progress in addressing the requirement.  The broader objective of the requirement is in no way fulfilled.' +
    '  </div>' +
    '</div>' +
    '<div class="scorecard-legend-item">' +
    '  <i style="background:#FAC433">&nbsp;</i>' +
    '  <div>The country has made inadequate progress in meeting the requirement. Significant elements of the requirement are outstanding and the broader objective of the requirement is far from being fulfilled.' +
    '  </div>' +
    '</div>' +
    '<div class="scorecard-legend-item">' +
    '  <i style="background:#84AD42">&nbsp;</i>' +
    '  <div>The country has made progress in meeting the requirement. Significant elements of the requirement are being implemented and the broader objective of the requirement is being fulfilled.</div>' +
    '</div>' +
    '<div class="scorecard-legend-item">' +
    '  <i style="background:#2D8B2A">&nbsp;</i>' +
    '  <div>The country is compliant with the EITI requirement.</div>' +
    '</div>' +
    '<div class="scorecard-legend-item">' +
    '  <i style="background:#5182bb">&nbsp;</i>' +
    '  <div>The country has gone beyond the requirement.</div>' +
    '</div>' +
    '<div class="scorecard-legend-item">' +
    '  <i style="background:#ccc">&nbsp;</i>' +
    '  <div>This requirement is only encouraged or recommended and should not be taken into account in assessing compliance.</div>' +
    '</div>';

	return legendHTML;

}

function appendRows(data, tableBody) {
	var categories = data.categories;
	var requirements = data.requirements;
	var scores = data.scores;
	var result = data.result;

	var countryScore = _.first(data.result);

	_.each(categories, function(category) {
	    var bodyRow = $("<TR>");
	    tableBody.append(bodyRow);

	    var requirements_category = _.filter(requirements, function(requirement) {
	        return (requirement.Category === category.id);
	    });
	    bodyRow.append($("<TD>").attr('rowspan', requirements_category.length).addClass('requirement').html(category.name));

	    _.each(requirements_category, function(requirement, idx) {
	        var currentRow;
	        if (idx === 0) {
	            currentRow = bodyRow;
	        } else {
	            currentRow = $("<TR>");
	        }


	        let currentScore = undefined;
	        if (countryScore) {
		        currentScore = _.find(countryScore.score_req_values, function(value) {
		            return (value.score_req_id == requirement.id);
		        });
	        }
	        var req_cell = $("<TD>");
	        currentRow.append(req_cell.html(requirement.Requirement));

	        // Requirement Answers
	        if (currentScore) {
	        	req_cell.attr('Title', currentScore.description);
	        	var cellStyle = '';
			    if (currentScore.is_applicable == 0) {
			        cellStyle = 'not_applicable ';
		            _.each(scores, function(value) {
		                currentRow.append($("<TD>").addClass(cellStyle).html('&nbsp;'));
		            });
			    }
			    else
			    {
		            _.each(scores, function(value) {
		                var on = value.id;
		                var cellStatus = (Number(currentScore.value) === on);
		                cellStyle = cellStatus ? value.name.toLowerCase() : '';
		                currentRow.append($("<TD>").addClass(cellStyle).html('&nbsp;'));
		            });
			    }
	        } else {
	            _.each(scores, function(value) {
	                currentRow.append($("<TD>").html('&nbsp;'));
	            });
	        }
	        //Direction of Progress
	        
	        //currentRow.append($("<TD>").html('&nbsp;'));
	        tableBody.append(currentRow);
	    });
	})

}




