import {
	createStore
}
from 'reflux';

import * as Actions from '../Actions.es6';

import {
	StoreMixins
}
from '../mixins/StoreMixins.es6';

const BarStore = createStore({

	initialData: {
		toggle: ''		
	},

	mixins: [StoreMixins],

	init() {
		this.listenTo(Actions.get('UPDATE_GRAPH'), 'updateGraph');
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
	}

});

export default BarStore;