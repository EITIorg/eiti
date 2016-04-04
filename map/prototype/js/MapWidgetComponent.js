import React, { Component } from 'react';
import { Map, Marker, Popup, TileLayer, GeoJson } from 'react-leaflet';

import { countryGeoJson } from './data/countries.js';
import { countryInfo } from './data/implementing_country.js';

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




export default class MapWidgetComponent extends Component {
  constructor() {
    super();
    //Default values
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
    var countryGeoJsonProcessed = {
        "type" : "FeatureCollection",
        "metadata" : [],
        "features" : []
      };
    // Get Legend information
    var metadata = ::this.getValues(indicator_id);

    countryGeoJson.features.forEach(function(country) {
      var datapoint = _.find(data, function(v){ return v.iso3 === country.id;});
      if(datapoint) {
        var indicator_value = 0;
        switch(indicator_id) {
          case "status":
            indicator_value = datapoint.status ? datapoint.status.tid || 0: 0;
          break;
          case "resources_oil":
            if(datapoint.reports) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Oil, volume")});
              indicator_value = indicator ? indicator.value : 0;
            }
          break;
          case "online_portal":
            if(datapoint.licenses) {
              var years = Object.keys(datapoint.licenses);
              var last = _.last(years);
              var yearData = datapoint.licenses[last];
              var indicator = yearData.length > 0;
              indicator_value = indicator;
            }
          break;
          case "online_registry":
            if(datapoint.contracts) {
              var years = Object.keys(datapoint.contracts);
              var last = _.last(years);
              var yearData = datapoint.contracts[last];
              var indicator = yearData.length > 0;
              indicator_value = indicator;
            }
          break;
          case "value":
            if(datapoint.reports) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Oil, value")});
              indicator_value = indicator;
            }
          break;
          case "value_per_capita":
            if(datapoint.reports) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Oil, value")});
              var population = yearData.find(function(v){ return (v.commodity === "Population")});
              if(population && indicator) {
                indicator_value = indicator/population;
              }
              else
              {
                indicator_value = 0;
              }
            }
          break;
          case "revenue":
            if(datapoint.revenues) {
              var years = Object.keys(datapoint.revenues);
              var last = _.last(years);
              var yearData = datapoint.revenues[last];
              var indicator = yearData.government;
              indicator_value = indicator;
            }
          break;
          case "revenue_compared":
            if(datapoint.revenues) {
              var years = Object.keys(datapoint.revenues);
              var last = _.last(years);
              var yearData = datapoint.revenues[last];
              var indicator_government = yearData.government;
              var indicator_company = yearData.company;
              indicator_value = indicator_government - indicator_company;
            }
          break;
        }

        var indicator_type = valuetypes;
        country['indicator_type'] = valuetypes;

        var indicator_color;
        indicator_color = ::this.getColor(indicator_type, indicator_value, metadata);
        country['indicator_color'] = indicator_color;
      }
      countryGeoJsonProcessed.features.push(country);
    }.bind(this));
    return countryGeoJsonProcessed;
  }

  addLayer(e) {
    if(this.removeLayer) this.removeLayer();
    const map = this.refs['map'].leafletElement;
    var indicator_id = e.target.dataset ? e.target.dataset.indicatorid : e.target.getAttribute("data-indicatorid");
    var valuetypes =  e.target.dataset ? e.target.dataset.valuetypes : e.target.getAttribute("data-valuetypes");
    ::this.addLegend(map, indicator_id);
    var countryDataProcessed = ::this.decorate(this.state.data, indicator_id, valuetypes);
    const hoverDecider = this.props.infobox ? this.onEachFeaturePage : helpers.onEachFeatureStatus;

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

          var mergedHTML = "<h2>" + ::this.getIndicatorName(indicator_id || this.state.indicator_id) + "<br/></h2>";
          indicatorMetadata.forEach(function(v) {
            mergedHTML += ('<i style="background:' + v.color + '"></i> <strong>'+ v.title + '</strong> <br/>'+ (v.subtitle || '') + '<br/>' ) ;
          });
          map.options.legend.innerHTML = mergedHTML;
      }.bind(this);

      info.addTo(map);
  }

  getIndicatorName(indicator_id){
    var values;
    switch(indicator_id) {
      case "status":
        values = "Implementation Status";
      break;
      case "resources_oil":
        values = "Oil, prices (in USD)";
      break;
      case "online_portal":
        values = "Online License Portal";
      break;
      case "online_registry":
        values = "Online Registry of Contracts";
      break;
      case "value":
        values = "Production value (in USD)";
      break;
      case "value_per_capita":
        values = "Production value per capita (in USD)";
      break;
      case "revenue":
        values = "Government Revenue (in USD)";
      break;
      case "revenue_compared":
        values = "Government Revenues vs Companies Revenues (in USD)";
      break;
    }
    return values;
  }


  onEachFeaturePage(feature, layer) {
    layer.on({
        mouseout: helpers.resetTooltip,
        click: function(e){ helpers.showInfobox(e, countryInfo) }
    });
    //debugger;
  }

  onEachFeatureStatus(feature, layer) {
      layer.on({
          mouseover: function(e){ helpers.showTooltipStatus(e, countryInfo) } ,
          mouseout: helpers.resetTooltip,
          click: helpers.zoomToFeature
      });
  }


  getColor(indicator_type, indicator_value, metadata) {
    if(indicator_type == 'fixed') {
        var completeType = _.find(metadata, function(v){ return (v.id == indicator_value)});
        return completeType.color;
    }
    else
    {
        //debugger;
        if (metadata === undefined) return;

        if(this.isNumeric(indicator_value)) {
            var value = Number(indicator_value);
            var completeType = _.find(metadata, function(v){ return value > v.range.start && value <= v.range.end;});

            return completeType !== undefined ? completeType.color : '#dddddd';
        }
        else
        {
            return '#dddddd';
        }

    }
  }

  isNumeric( obj ) {
        return !jQuery.isArray( obj ) && (obj - parseFloat( obj ) + 1) >= 0;
  }



  render() {

    const hoverDecider = this.props.infobox ? this.onEachFeaturePage : this.onEachFeatureStatus;
    const geoJsonLayer = <GeoJson data={this.state.baseMap} ref='geoJsonLayer' onEachFeature={hoverDecider} style={helpers.style}></GeoJson>;
    var buttons;
    if(this.props.buttons) {
        buttons = (<div className="map-option-wrapper">
          <ul className="map-option-widget">
            <li>
              Overview
              <ul className="map-option-items">
                <li data-indicatorid="status" data-valuetypes="fixed" onClick={::this.addLayer}>Status</li>
              </ul>
            </li>
            <li>
              Resources
              <ul className="map-option-items">
                <li data-indicatorid="resources_oil" data-valuetypes="range" onClick={::this.addLayer}>Oil</li>
              </ul>
            </li>
            <li>
              Tax & Legal Framework
              <ul className="map-option-items">
                <li data-indicatorid="online_portal" data-valuetypes="fixed" onClick={::this.addLayer}>License Registry</li>
                <li data-indicatorid="online_registry" data-valuetypes="fixed" onClick={::this.addLayer}>Contracts</li>
              </ul>
            </li>
            <li>
              Production
              <ul className="map-option-items">
                <li data-indicatorid="value" data-valuetypes="range" onClick={::this.addLayer}>Value</li>
                <li data-indicatorid="value_per_capita" data-valuetypes="range" onClick={::this.addLayer}>Value per capita</li>
              </ul>
            </li>
            <li>
              Revenues
              <ul className="map-option-items">
                <li data-indicatorid="revenue" data-valuetypes="range" onClick={::this.addLayer}>Revenue</li>
                <li data-indicatorid="revenue_compared" data-valuetypes="range" onClick={::this.addLayer}>Revenue Per Capita</li>
              </ul>
            </li>
          </ul>
        </div>);
    }
    var reportLink = (<svg id="country-report-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 160 160">
          <path className="st0" d="M156.4,132l-10.5,18.3L135.5,132V9.2c0-2.9,2.3-5.2,5.2-5.2h10.5c2.9,0,5.2,2.3,5.2,5.2V132z"/>
          <rect x="135.5" y="22.3" className="st0" width="20.9" height="10.5"/>
          <line className="st0" x1="135.5" y1="132" x2="156.4" y2="132"/>
          <line className="st0" x1="145.9" y1="150.3" x2="145.9" y2="155.6"/>
          <rect x="4.8" y="4" className="st0" width="115" height="151.6"/>
          <rect x="4.8" y="4" className="st0" width="20.9" height="151.6"/>
          <rect x="44" y="30.1" className="st0" width="57.5" height="31.4"/>
          <line className="st0" x1="54.5" y1="40.6" x2="91.1" y2="40.6"/>
          <line className="st0" x1="54.5" y1="51" x2="91.1" y2="51"/>
          </svg>);


    var selector;
    if(this.props.selector) {
      var items = [];
      var cols = [];
      var sortedCountries = _.sortBy(countryInfo, 'label');
      for(var i = 0; i < sortedCountries.length;i++) {
        var itemStyle = sortedCountries[i].status ? "member-status " + sortedCountries[i].status.name.toLowerCase() : "member-status other";
        var countryPageURL = "/implementing_country/" + countryInfo[i].id
        items.push(
            <li>
              <span className={itemStyle}></span>
              <a href={countryPageURL}>{sortedCountries[i].label}</a>
              <span className="report">
                <a href="#">
                  {reportLink}
                </a>
              </span>
            </li>
          );
        if((i+1)%4 === 0) {
          cols.push(
              <div className="country-col">
                <ul className="country-list">
                {items}
                </ul>
              </div>
            );
          items = [];
        }
      }

      //Divide in columns by 4

      selector = (
        <div className="country-list-wrapper clearfix">
          {cols}
        </div>
      );
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
        {selector}
      </div>
    );
  }
}
