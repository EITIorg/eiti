EITI Visualizations Prototype
==============================

This project is for the development of the visualizations to be used in the EITI project for Development Gateway.

#Architecture
The engine behind the charts is composed primarily with modified source code from the [react-d3-components] (https://github.com/codesuki/react-d3-components) library, supplemented with some features from the [react-d3] (https://github.com/esbullington/react-d3) library. All engine component files are in the js/rd3c directory.

#Development
``` 
npm install
npm run build
```
Open test.html with web server of choice.

#TODO
* add configuration for minifying final build
* organize and optimize styling
* develop a treemap chart (possible base code available in the react-d3 library)
* develop a bubble chart
* develop a sankey chart
