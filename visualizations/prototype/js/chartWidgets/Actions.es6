import {createActions, createAction} from 'reflux'

let actionsDef = {}

const actions = createActions(actionsDef);


/**
 * Call  action by name
 * @param  String name    [description]
 * @param  Object options [description]
 */
let invoke = (name, options) => {
	if (!actions[name]) {
		let a = createAction();
		actions[name] = a;
	}
	actions[name](options);
}

/**
 * Get action by name 
 * @param  String name [description]
 * @return {[type]}      [description]
 */
let get = (name) => {
	if (!actions[name]) {
		let a = createAction();
		actions[name] = a;
	}
	return actions[name]
}

export {
	get, invoke
};