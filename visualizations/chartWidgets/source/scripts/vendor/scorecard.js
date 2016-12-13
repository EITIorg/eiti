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
	tableHeaderUpperRow.append($('<TH>').attr('rowspan', 2).html('Direction <br/>of Progress'));

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
	window.$ = undefined;
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
	    bodyRow.append($("<TD>").attr('rowspan', requirements_category.length).html(category.name));

	    _.each(requirements_category, function(requirement, idx) {
	        var currentRow;
	        if (idx === 0) {
	            currentRow = bodyRow;
	        } else {
	            currentRow = $("<TR>");
	        }

	        currentRow.append($("<TD>").html(requirement.Requirement));

	        let currentScore = undefined;
	        if (countryScore) {
		        currentScore = _.find(countryScore.score_req_values, function(value) {
		            return (value.score_req_id == requirement.id);
		        });
	        }

	        // Requirement Answers
	        if (currentScore) {
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
	        currentRow.append($("<TD>").html('&nbsp;'));
	        tableBody.append(currentRow);
	    });
	})

}




