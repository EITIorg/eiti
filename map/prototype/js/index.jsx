window.mapWidget = {};

import React from 'react';
import { render } from 'react-dom';
import { Map, Marker, Popup, TileLayer, GeoJson } from 'react-leaflet';

import { countriesData } from './data/countries.js';
import { countryStatus } from './data/countryStatus.js';

import { helpers } from './helpers.js' ;

//var countries = require('json!./data/countries.js')
//TODO: Refactor all of this!

window.mapWidget.createHomePage = function(options) {

	var map = (
			<Map center={options.position} zoom={options.zoom} maxZoom={options.maxZoom} minZoom={options.minZoom} >
				<TileLayer url='' onLeafletLoad={helpers.addLegend}/>
				<GeoJson data={countriesData} onEachFeature={helpers.onEachFeature} style={helpers.style}>
				</GeoJson>
			</Map>
	);
	render(map, document.getElementById(options.container));
}


window.mapWidget.createMapPage = function(options) {

  var showTooltip = function (e) {
      var layer = e.target;
      //debugger;
      var country = countryStatus.find(function(v){return v.ISO3===layer.feature.id});
      if(country === undefined || country.EITI_Status == 4) return;
      var html = '<div>'+
        '<table class="country_info">'+
        '  <thead><tr style="background-color:#f4f4f4"><th colspan="3"><img src="img/flags/gif/'  + layer.feature.id.toLowerCase() + '.gif" style="margin:0px 10px 0px 5px"/>'  + layer.feature.properties.name + '</th></tr></thead>'+
        '  <tbody>'+
        '    <tr><td colspan="2">GDP: 32.69 Billion USD (2013)</td><td>Population: 67.51 million</td></tr>'+
        '    <tr><td colspan="3">&nbsp;<strong>Country Commodity Total</strong><hr style="margin:2px;border-color:#77cde4"/></td></tr>'+
        '    <tr><td><strong>123</strong><img src="img/oil1.gif" style="margin:0px 2px 0px 2px"/> Crude Oil</td><td><strong>123</strong><img src="img/oil2.gif" style="margin:0px 2px 0px 2px"/> Refined Oil</td><td><strong>123</strong><img src="img/oil3.gif" style="margin:0px 2px 0px 2px"/> Other</td></tr>'+
        '    <tr><td><strong>45</strong><img src="img/min1.gif" style="margin:0px 2px 0px 2px"/> Mineral</td><td></td><td></td></tr>'+
        '    <tr><td colspan="3"><hr style="margin:2px;border-color:#77cde4"/><img src="img/cp.gif" style="margin:0px 2px 0px 2px"/> <a href="countries.html"style="color:#0b82d6">Open Country Page </td></tr>'+
        '  </tbody>'+
        '</table>'+
        '</div>';
      var popup = L.popup({autoPan:true, closeButton:false, maxWidth:400})
        .setLatLng(e.latlng)
        .setContent(html)//'<strong>' + layer.feature.properties.name + '</strong>');
        .openOn(layer._map);
  };

  var onEachFeature = function (feature, layer) {
      layer.on({
          mouseover: showTooltip,
          mouseout: helpers.resetTooltip,
          click: helpers.zoomToFeature
      });
  };

  var map = (
      <Map center={options.position} zoom={options.zoom} maxZoom={options.maxZoom} minZoom={options.minZoom}>
        <TileLayer url='' onLeafletLoad={helpers.addLegend}/>
        <GeoJson data={countriesData} onEachFeature={onEachFeature} style={helpers.style}>
        </GeoJson>
      </Map>
  );

  render(map, document.getElementById(options.container));

}


