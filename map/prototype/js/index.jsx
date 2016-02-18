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
			<Map center={options.position} zoom={options.zoom} maxZoom={options.maxZoom} minZoom={options.minZoom} scrollWheelZoom={false}>
				<TileLayer url='' onLeafletLoad={helpers.addLegend}/>
				<GeoJson data={countriesData} onEachFeature={helpers.onEachFeature} style={helpers.style}>
				</GeoJson>
			</Map>
	);
	render(map, document.getElementById(options.container));
}


window.mapWidget.createMapPage = function(options) {
  var formatnumber =function(number) {
    if(isNaN(number)) return 0;
    let n = 0;
    let x = 3;
    var re = '\\d(?=(\\d{' + (x || 3) + '})+' + (n > 0 ? '\\.' : '$') + ')';
    return number.toFixed(Math.max(0, ~~n)).replace(new RegExp(re, 'g'), '$&,');
};
  var showTooltip = function (e) {
      var layer = e.target;
      //debugger;
      var country = countryStatus.find(function(v){return v.ISO3===layer.feature.id});
      if(country === undefined || country.EITI_Status == 4) return;

      var html = '<div>' +
        '<table class="country_info">' + 
        '  <thead><tr style="background-color:#f4f4f4"><th colspan="2"><img src="images/flags/gif/' + layer.feature.id.toLowerCase() + '.gif" style="margin:0px 10px 0px 5px"/>' + layer.feature.properties.name + '</th></tr></thead>' + 
        '  <tbody>' + '    <tr><td>GDP: ' + formatnumber(country.GDP) + ' USD </td><td>Population: ' + formatnumber(country.Pop) + '</td></tr>' + 
        '    <tr><td colspan="2">&nbsp;<strong>Country Commodity Total</strong></td></tr>' + 
        '    <tr><td><strong>' + formatnumber(country.oil) + '</strong><img src="images/icon-dump/eiti_popup_oilunrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Crude Oil (b)</td>' + 
        '        <td><strong>' + country.refined + '</strong><img src="images/icon-dump/eiti_popup_oilrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Refined Oil</td>' + 
        '        </tr>' + 
        '    <tr><td><strong>' + country.mineral + '</strong><img src="images/icon-dump/eiti_popup_mineral.svg" style="margin:0px 2px 0px 2px;width:18px"/> Mineral</td>' + 
        '        <td><strong>' + country.other + '</strong><img src="images/icon-dump/eiti_popup_other.svg" style="margin:0px 2px 0px 2px;width:18px"/> Other</td></tr>' 
        + '    <tr><td colspan="2"><img src="images/icon-dump/eiti_popup_opencountry.svg" style="margin:0px 2px 0px 2px;width:18px"/> <a href="countries.html' + country.ISO3 + '" style="color:#0b82d6">Open Country Page </td></tr>' + 
        '  </tbody>' + 
        '</table>' + 
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
      <Map center={options.position} zoom={options.zoom} maxZoom={options.maxZoom} minZoom={options.minZoom} scrollWheelZoom={false}>
        <TileLayer url='' onLeafletLoad={helpers.addLegend}/>
        <GeoJson data={countriesData} onEachFeature={onEachFeature} style={helpers.style}>
        </GeoJson>
      </Map>
  );

  render(map, document.getElementById(options.container));

}


