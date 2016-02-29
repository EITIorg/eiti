var webpack = require("webpack");
var	path = require("path");

module.exports = {
	entry: [
		'webpack-hot-middleware/client',
		path.resolve(__dirname, "js/index.jsx")
	],
	output: {
		path: path.join(__dirname, 'dist'),
		filename: 'mapWidgets.js'    
	},
	plugins: [
    	new webpack.HotModuleReplacementPlugin(),
    	new webpack.NoErrorsPlugin()
    ],
	module: {
		loaders: [{
			test: /\.(js|jsx|es6)$/,
			loaders: ['babel-loader']
		}, {
			test: /\.jpe?g$|\.gif$|\.eot$|\.png$|\.svg$|\.woff$|\.woff2$|\.ttf$|\.wav$|\.mp3$/,
			loader: "file"
		}
		]
	},
	resolve: {
		extensions: ["", ".webpack.js", ".web.js", ".js", ".jsx",".es6"]
	}
};
