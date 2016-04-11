var webpack = require("webpack");
var	path = require("path");

module.exports = {
  entry: {
    "chartWidgets": path.resolve(__dirname, "js/index.jsx"),
    "chartWidgets.min": path.resolve(__dirname, "js/index.jsx")
  },
  output: {
    path: path.join(__dirname, 'dist', 'js'),
    filename: "[name].js"
  },
  plugins: [
    new webpack.NoErrorsPlugin(),
    new webpack.optimize.UglifyJsPlugin({
      include: /\.min\.js$/,
      minimize: true
    })
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
