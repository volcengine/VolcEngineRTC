/**
 * Build config for electron 'Main Process' file
 */

const path = require('path');
const packageJson = require("./package.json");

module.exports = {
  entry: './src/preload/index.js',
  target: 'electron-main',
  node: {
    __dirname: false,
    __firname: false
  },
  output: {
    filename: 'preload.js',
    path: path.resolve(__dirname, './app'),
    libraryTarget: 'commonjs2'
  },
  resolve: {
    extensions: [".js", ".jsx", ".ts", ".tsx"]
  },
  module: {
    rules: [{
      test: /\.js$/,
      use: {
        loader: 'babel-loader',
        options: {
          // presets: ['@babel/preset-env']
        }
      },
    },
    {
      test: /\.ts(?:x)?$/,
      loader: "ts-loader",
      exclude: /node_modules/,
      options: {
        transpileOnly: true,
        configFile: path.join(__dirname, "tsconfig.json"),
      },
    },
    {
      test: /\.node$/,
      loader: "native-ext-loader",
      options: {
        emit: false,
        basePath: [packageJson.appInfo.sdkName + "/build/Release"],
      },
    },
    ]
  }
};