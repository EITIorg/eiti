import React, { Component } from 'react';
import { Map, Marker, Popup, TileLayer, GeoJson } from 'react-leaflet';

import { countriesData } from './data/countries.js';

import { helpers } from './helpers.js' ;
import _ from 'underscore';

// TODO: Move all metadata to definition/configuration
import { status } from './data/status.js';
import { online_portal } from './data/online_portal.js';
import { online_registry } from './data/online_registry.js';
import { resources_oil } from './data/resources_oil.js';

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
      var datapoint = data.find(function(v){ return v.ISO3 === country.id;});
      if(datapoint) {
        country['indicator_value'] = datapoint[indicator_id];
        country['indicator_type'] = valuetypes;
        switch(indicator_id) {
          case "status": 
            country['metadata'] = status;
          break;
          case "resources_oil":
            country['metadata'] = resources_oil;
          break;
          case "online_portal":
            country['metadata'] = online_portal;
          break;
          case "online_registry":
            country['metadata'] = online_registry;
          break;
        }
      }
      countryDataProcessed.features.push(country);
    });
    return countryDataProcessed;
  }

  addLayer(e) {
    if(this.removeLayer) this.removeLayer();
    const map = this.refs['map'].leafletElement;
    var indicator_id = e.target.dataset.indicatorid;
    var valuetypes = e.target.dataset.valuetypes;
    ::this.addLegend(map, indicator_id);
    var countryDataProcessed = ::this.decorate(this.state.data, indicator_id, valuetypes);
    const hoverDecider = this.props.options.infobox ? this.onEachFeaturePage : helpers.onEachFeatureStatus;

    this.refs['geoJsonLayer'].leafletElement = L.geoJson(countryDataProcessed, {style:helpers.style, onEachFeature:hoverDecider}).addTo(map);
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
          switch(indicator_id || this.state.indicator_id) {
            case "status": 
              indicatorMetadata = status;
            break;
            case "resources_oil":
              indicatorMetadata = resources_oil;
            break;
            case "online_portal":
              indicatorMetadata = online_portal;
            break;
            case "online_registry":
              indicatorMetadata = online_registry;
            break;
          }
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
          <input type="button" data-indicatorid="status" data-valuetypes="fixed" value="Load Overview" onClick={::this.addLayer}/>
          <input type="button" data-indicatorid="resources_oil" data-valuetypes="range" value="Load Resources Oil" onClick={::this.addLayer}/>
          <input type="button" data-indicatorid="online_portal" data-valuetypes="fixed" value="License Registry" onClick={::this.addLayer}/>
          <input type="button" data-indicatorid="online_registry" data-valuetypes="fixed" value="Contracts" onClick={::this.addLayer}/>
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
