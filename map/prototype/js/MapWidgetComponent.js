import React, { Component } from 'react';
import { Map, Marker, Popup, TileLayer, GeoJson } from 'react-leaflet';

import { countriesData } from './data/countries.js';

import { helpers } from './helpers.js' ;
import _ from 'underscore';

// TODO: Move all metadata to definition/configuration
// Overview
import { status } from './data/status.js';

// Resources
import { resources_oil } from './data/resources_oil.js';

// Tax & Legal Framework
import { online_portal } from './data/online_portal.js';
import { online_registry } from './data/online_registry.js';

// Production
import { value } from './data/value.js';
import { value_per_capita } from './data/value_per_capita.js';

// Revenues
import { revenue } from './data/revenue.js';
import { revenue_compared } from './data/revenue_compared.js';

//Info box Information
import { countryInfo } from './data/country.js';


export default class MapWidgetComponent extends Component {
  constructor() {
    super();
    var indicator_id = "status";
    var valuetypes = "fixed";

    this.state = {
      hasLocation: false,
      latlng: {
        lat: 12.897489183755892,
        lng: -12.76171875
      },
      baseMap: ::this.decorate(countryInfo, indicator_id, valuetypes),
      data: countryInfo,
      indicator_id: indicator_id,
      valuetypes: valuetypes
    };
  }

  decorate(data, indicator_id, valuetypes) {
    var countryDataProcessed = {"type":"FeatureCollection","features":[]};

    countriesData.features.forEach(function(country) {
      var datapoint = _.find(data, function(v){ return v.ISO3 === country.id;});
      if(datapoint) {
        country['indicator_value'] = datapoint[indicator_id];
        country['indicator_type'] = valuetypes;
        country['metadata'] = ::this.getValues(indicator_id);
      }
      countryDataProcessed.features.push(country);
    }.bind(this));
    return countryDataProcessed;
  }

  addLayer(e) {
    if(this.removeLayer) this.removeLayer();
    const map = this.refs['map'].leafletElement;
    var indicator_id = e.target.dataset ? e.target.dataset.indicatorid : e.target.getAttribute("data-indicatorid");
    var valuetypes =  e.target.dataset ? e.target.dataset.valuetypes : e.target.getAttribute("data-valuetypes");
    ::this.addLegend(map, indicator_id);
    var countryDataProcessed = ::this.decorate(this.state.data, indicator_id, valuetypes);
    const hoverDecider = this.props.options.infobox ? this.onEachFeaturePage : helpers.onEachFeatureStatus;

    this.refs['geoJsonLayer'].leafletElement = L.geoJson(countryDataProcessed, {style:helpers.style, onEachFeature:hoverDecider}).addTo(map);
  }

  // TODO: Replace with retrieval from endpoint data

  getValues(indicator_id) {
    //debugger;
    var values;
    switch(indicator_id) {
      case "status": 
        values = status;
      break;
      case "resources_oil":
        values = resources_oil;
      break;
      case "online_portal":
        values = online_portal;
      break;
      case "online_registry":
        values = online_registry;
      break;
      case "value":
        values = value;
      break;
      case "value_per_capita":
        values = value_per_capita;
      break;
      case "revenue":
        values = revenue;
      break;
      case "revenue_compared":
        values = revenue_compared;
      break;
    }
    return values;
  }

  removeLayer() {
    const map = this.refs['map'].leafletElement;
    const geoJsonLayer = this.refs['geoJsonLayer'].leafletElement;
    map.removeLayer(geoJsonLayer);
  }

  addLegend(map, indicator_id) {
      var info = L.control({position: 'bottomleft'});
      //var map = e.target._map;

      info.onAdd = function (map) {
          if(map.options.legend === undefined) {
              map.options.legend = L.DomUtil.create('div', 'info legend');
          }
          this.update();
          return map.options.legend;
      };

      info.update = function (props) {
          var indicatorMetadata;
          indicatorMetadata = ::this.getValues(indicator_id || this.state.indicator_id);

          var mergedHTML = "";
          indicatorMetadata.forEach(function(v) {
            mergedHTML += ('<i style="background:' + v.color + '"></i> <strong>'+ v.title + '</strong> <br/>'+ (v.subtitle || '') + '<br/>' ) ;
          });
          map.options.legend.innerHTML = mergedHTML;
      }.bind(this);

      info.addTo(map);
  }



  onEachFeaturePage(feature, layer) {
    layer.on({
        mouseout: helpers.resetTooltip,
        click: function(e){ helpers.showInfobox(e, countryInfo) } 
    });
    //debugger;
  }


  render() {

    const hoverDecider = this.props.options.infobox ? this.onEachFeaturePage : helpers.onEachFeatureStatus;
    const geoJsonLayer = <GeoJson data={this.state.baseMap} ref='geoJsonLayer' onEachFeature={hoverDecider} style={helpers.style}></GeoJson>;
    var buttons;
    if(this.props.options.buttons) {
        buttons = (<div>
          <ul>
            <li>
              Overview
              <ul>
                <li data-indicatorid="status" data-valuetypes="fixed" onClick={::this.addLayer}>Status</li>
              </ul>
            </li>
            <li>
              Resources
              <ul>
                <li data-indicatorid="resources_oil" data-valuetypes="range" onClick={::this.addLayer}>Oil</li>
              </ul>
            </li>
            <li>
              Tax & Legal Framework
              <ul>
                <li data-indicatorid="online_portal" data-valuetypes="fixed" onClick={::this.addLayer}>License Registry</li>
                <li data-indicatorid="online_registry" data-valuetypes="fixed" onClick={::this.addLayer}>Contracts</li>
              </ul>
            </li>
            <li>
              Production
              <ul>
                <li data-indicatorid="value" data-valuetypes="range" onClick={::this.addLayer}>Value</li>
                <li data-indicatorid="value_per_capita" data-valuetypes="range" onClick={::this.addLayer}>Value per capita</li>
              </ul>
            </li>
            <li>
              Revenues
              <ul>
                <li data-indicatorid="revenue" data-valuetypes="range" onClick={::this.addLayer}>Revenue</li>
                <li data-indicatorid="revenue_compared" data-valuetypes="range" onClick={::this.addLayer}>Revenue Per Capita</li>
              </ul>
            </li>
          </ul>
        </div>);
    }

    return (

      <div className="map-container">
        {buttons}
        <div>
          <Map
            center={this.state.latlng}
            length={4}
            ref='map'
            zoom={2}
            height={500}
            scrollWheelZoom={false}
            >
            <TileLayer
              url=''
              onLeafletLoad={function(e) {this.addLegend(e.target._map)}.bind(this)}
            />
            {geoJsonLayer}
          </Map>
        </div>

      </div>
    );
  }
}
