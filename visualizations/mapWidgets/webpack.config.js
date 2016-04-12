/* eslint-disable */
var webpack = require('webpack');

module.exports = {
  debug: true,
  devtool: 'source-map',
  entry: {
    'mapWidgets': __dirname + '/source/scripts/index.js',
    'mapWidgets.min': __dirname + '/source/scripts/index.js'
  },
  module: {
    loaders: [{
      test: /\.js$/,
      exclude: /node_modules/,
      loader: 'babel',
      query: {
        plugins: []
      }
    }]
  },
  output: {
    path: __dirname + '/dist/js',
    filename: '[name].js',
    publicPath: 'http://localhost:8000/dist'
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env': {
        'NODE_ENV': '"production"'
      }
    }),
    new webpack.optimize.DedupePlugin(),
    new webpack.optimize.OccurrenceOrderPlugin(),
    new webpack.optimize.UglifyJsPlugin({
      include: /\.min\.js$/,
      minimize: true
    })
  ],
  devServer: {
    colors: true,
    contentBase: __dirname,
    historyApiFallback: true,
    hot: true,
    inline: true,
    port: 8000,
    progress: true,
    stats: {
      cached: false
    }
  }
};
