import {createStore} from 'reflux';

const FALSE_DATA = {};

const StoreMixins = {
	initialData: FALSE_DATA,
	mixins: [],

	init: function() {
		if (this.initialData === FALSE_DATA) {
			throw new Error('Stores must specify an initialData static property');
		}
		this.data = this.initialData;
	},
	
	setData: function(newData) {
		this.data = newData;
		this.emit();
	},

	get: function() {
		return this.data;
	},

	emit: function() {
		this.trigger(this.get());
	},

	getInitialState: function() {
		return this.get();
	},


}


export {StoreMixins};
