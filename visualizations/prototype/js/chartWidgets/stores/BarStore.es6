import {
	createStore
}
from 'reflux';

import * as Actions from '../Actions.es6';
import * as BarActions from '../actions/barActions';
import {
	List, Map, Record
}
from 'immutable';
import {
	StoreMixins
}
from '../mixins/StoreMixins.es6';

const BarStore = createStore({

	initialData: {
		legend: ['Oil']		
	},

	mixins: [StoreMixins],

	init() {
		this.listenTo(Actions.get('UPDATE_GRAPH'), 'updateGraph');
		//this.listenTo(BarActions.doLegend, this.updateLegend);
	},

	cleanStore() {
		debugger; 
    	this.setData(this.initialData);
	},

	getInitialState() {
		return this.get();
	},

	updateGraph(params) {
		this.setData({ toggle: params});
	},

	updateLegend(params) {
		console.log('updateLegend got something!');
		console.log(params);
		this.setData({ legend: ['Oil', 'Gas', 'Extractives']});
	}

});

export default BarStore;