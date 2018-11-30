import React, { Component } from 'react';
import { Map, Marker, Popup, TileLayer, GeoJson } from 'react-leaflet';

import { countryGeoJson } from './data/countries.js';
//import { countryInfo } from './data/implementing_country.js';

import { helpers } from './helpers.js' ;
import { translations } from './data/translations.js' ;
import _ from 'underscore';

// Legend information
import { indicator_list } from './data/indicator_list.js';
import { status } from './data/status.js';
import { online_oil_registry } from './data/online_oil_registry.js';
import { online_mining_registry } from './data/online_mining_registry.js';
import { online_contracts } from './data/online_contracts.js';
import { oil_volume } from './data/oil_volume.js';
import { gas_volume } from './data/gas_volume.js';
import { coal_volume } from './data/coal_volume.js';
import { gold_volume} from './data/gold_volume.js';
import { copper_volume } from './data/copper_volume.js';
import { revenue } from './data/revenue.js';
import { revenue_per_capita } from './data/revenue_per_capita.js';
import { share_revenues } from './data/share_revenues.js';

import geostats from 'geostats';



export default class MapWidgetComponent extends Component {
  constructor() {
    super();
    this.state = {
      initialized: false,
      indicator_id: 'status',
      valuetypes: 'fixed',
      baseMap: undefined,
      data: {},
      latlng: {
          lat: 12.897489183755892,
          lng: -12.76171875
      },
      hasLocation: false,
    };
  }


  componentWillMount() {
    jQuery.get(helpers.getEndPoint() + '?fields=id', function(result) {
        var calls = [];
        var results = [];

        for (var i = 0; i < result.count / helpers.getPageSize(); i++) {
            calls.push(
                jQuery.get(helpers.getEndPointPage(i + 1), function(result) {
                    results.push(result.data);
                })
            );
        }

        jQuery.when.apply(null, calls).done(function() {
            var consolidated = [];
            results.forEach(function(r) {
                consolidated = consolidated.concat(r);
            });

            var baseMap = ::this.decorate(consolidated, this.state.indicator_id, this.state.valuetypes);
            this.setState({
                baseMap: baseMap,
                data: consolidated
            });

        }.bind(this));

    }.bind(this));
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
        var indicator_unit = '';
        switch(indicator_id) {
          case "status":
            indicator_value = datapoint.status ? datapoint.status.tid || 0: 0;
          break;
          case "online_oil_registry":
            if(datapoint.licenses) {
              var years = Object.keys(datapoint.licenses);
              var last = _.last(years);
              var yearData = datapoint.licenses[last];
              indicator_value = yearData['Public registry of licences, oil'] !== undefined;
            }
          break;
          case "online_mining_registry":
            if(datapoint.licenses) {
              var years = Object.keys(datapoint.licenses);
              var last = _.last(years);
              var yearData = datapoint.licenses[last];
              indicator_value = yearData['Public registry of licences, mining'] !== undefined;
            }
          break;
          case "online_contracts":
            if(datapoint.contracts) {
              var years = Object.keys(datapoint.contracts);
              var last = _.last(years);
              var yearData = datapoint.contracts[last];
              indicator_value = yearData['Publicly available registry of contracts'] !== undefined;
            }
          break;
          case "oil_volume":
            if(datapoint.reports && Object.keys(datapoint.reports).length > 0) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Oil, volume" && v.unit && v.unit.toLowerCase() === 'sm3')});
              indicator_value = indicator ? indicator.value : 0;
              indicator_unit = indicator ? indicator.unit : 0;
            }
          break;
          case "gas_volume":
            if(datapoint.reports && Object.keys(datapoint.reports).length > 0) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Gas, volume" && v.unit && v.unit.toLowerCase() === 'sm3')});
              indicator_value = indicator ? indicator.value : 0;
              indicator_unit = indicator ? indicator.unit : 0;
            }
          break;
          case "coal_volume":
            if(datapoint.reports && Object.keys(datapoint.reports).length > 0) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){return (v.commodity === "Coal, volume" && v.unit && (v.unit.toLowerCase() === 'tonne' || v.unit.toLowerCase() === 'tonnes' || v.unit.toLowerCase() === 'tons'))});
              indicator_value = indicator ? indicator.value : 0;
              indicator_unit = indicator ? indicator.unit : 0;
            }
          break;
          case "gold_volume":
            if(datapoint.reports && Object.keys(datapoint.reports).length > 0) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Gold, volume" && v.unit && (v.unit.toLowerCase() === 'tonne' || v.unit.toLowerCase() === 'tonnes' || v.unit.toLowerCase() === 'tons'))});
              indicator_value = indicator ? indicator.value : 0;
              indicator_unit = indicator ? indicator.unit : 0;
            }
          break;
          case "copper_volume":
            if(datapoint.reports && Object.keys(datapoint.reports).length > 0) {
              var years = Object.keys(datapoint.reports);
              var last = _.last(years);
              var yearData = datapoint.reports[last];
              var indicator = yearData.find(function(v){ return (v.commodity === "Copper, volume" && v.unit && (v.unit.toLowerCase() === 'tonne' || v.unit.toLowerCase() === 'tonnes' || v.unit.toLowerCase() === 'tons'))});
              indicator_value = indicator ? indicator.value : 0;
              indicator_unit = indicator ? indicator.unit : 0;
            }
          break;
          case "revenue":
            if(datapoint.revenues) {
              var years = Object.keys(datapoint.revenues);
              var last = _.last(years);
              var yearData = datapoint.revenues[last];
              var indicator = yearData.government;
              indicator_value = indicator;
              indicator_unit = 'USD';
            }
          break;
          case "revenue_per_capita":
            if(datapoint.revenues && datapoint.reports) {
              var years = Object.keys(datapoint.revenues);
              var last = _.last(years);
              var yearData = datapoint.revenues[last];
              var generalYearData = datapoint.reports[last];
              var indicator = yearData.government;
              var population = generalYearData ? generalYearData.find(function(v){ return (v.commodity === "Population")}) : undefined;
              if(population && indicator) {
                indicator_value = indicator/population.value;
              }
              else
              {
                indicator_value = 0;
              }
              indicator_unit = 'USD/population';
            }
          break;
          case "share_revenues":
            if(datapoint.revenues && datapoint.reports) {
              var years = Object.keys(datapoint.revenues);
              var last = _.last(years);
              var yearData = datapoint.revenues[last];
              var generalYearData = datapoint.reports[last];
              var indicator_government = yearData.government;
              var indicator_allsectors = generalYearData ? generalYearData.find(function(v){ return (v.commodity === "Government revenue - all sectors")}) : undefined;
              if(indicator_government && indicator_allsectors && indicator_allsectors.value !== 0 && indicator_government !== 0 && indicator_allsectors.unit === 'USD') {
                indicator_value = indicator_government*100/indicator_allsectors.value;
              }
              else
              {
                indicator_value = 'n/a';
              }
              indicator_unit = '';
            }
          break;
        }

        var indicator_type = valuetypes;
        country['indicator_type'] = valuetypes;
        country['indicator_value'] = indicator_value;
        country['indicator_unit'] = indicator_unit;

      }
      countryGeoJsonProcessed.features.push(country);

    }.bind(this));

    if(valuetypes === 'range') {
      // Update metadata with ranges
      metadata = this.updateMetadata(countryGeoJsonProcessed, metadata);
    }

    // Assign color with the new metadata
    countryGeoJsonProcessed.features.forEach(function(feature) {
        var indicator_color;
        indicator_color = ::this.getColor(feature.indicator_type, feature.indicator_value, metadata);
        feature['indicator_color'] = indicator_color;
      }.bind(this));

    return countryGeoJsonProcessed;
  }

  updateMetadata(data, metadata) {
    var values = _.map(_.pluck(data.features, 'indicator_value'),function(v){ return v?v*1:0;});
    var part = _.pluck(data.features, 'indicator_unit');

    var unit = _.find(part, function(v) { return v !== undefined && v !== "" && v !== 0;});

    var classifier = new geostats(values);
    var ranges = classifier.getEqInterval(metadata.length);

    for(var i=0; i< metadata.length;i++) {
      metadata[i].unit = unit;
      metadata[i].range.start = ranges[i];
      metadata[i].range.end = ranges[i+1];
      metadata[i].title = helpers.formatNumber(ranges[i]) + ' - ' + helpers.formatNumber(ranges[i+1]);
    }
    return metadata;
  }

  addLayer(e) {
    //Deactivate anything selected
    jQuery('.map-option-wrapper').find("LI").removeClass('active')
    //Activate current selected
    jQuery(e.target).parents("LI").addClass('active');
    //Activate itself
    jQuery(e.target).addClass('active')

    if(this.removeLayer) this.removeLayer();
    const map = this.refs['map'].leafletElement;
    var indicator_id = e.target.dataset ? e.target.dataset.indicatorid : e.target.getAttribute("data-indicatorid");
    var valuetypes =  e.target.dataset ? e.target.dataset.valuetypes : e.target.getAttribute("data-valuetypes");
    var countryDataProcessed = ::this.decorate(this.state.data, indicator_id, valuetypes);
    const hoverDecider = this.props.infobox ? function(feature, layer){this.onEachFeaturePage(feature, layer)}.bind(this) : function(feature, layer){this.onEachFeatureStatus(feature, layer)}.bind(this);

    ::this.addLegend(map, indicator_id, countryDataProcessed);

    this.refs['geoJsonLayer'].leafletElement = L.geoJson(countryDataProcessed, {style:helpers.style, onEachFeature:hoverDecider}).addTo(map);
  }

  getValues(indicator_id) {
    var values;
    switch(indicator_id) {
      case "status":
        values = status;
      break;
      case "online_oil_registry":
        values = online_oil_registry;
      break;
      case "online_mining_registry":
        values = online_mining_registry;
      break;
      case "online_contracts":
        values = online_contracts;
      break;
      case "oil_volume":
        values = oil_volume;
      break;
      case "gas_volume":
        values = gas_volume;
      break;
      case "coal_volume":
        values = coal_volume;
      break;
      case "gold_volume":
        values = gold_volume;
      break;
      case "copper_volume":
        values = copper_volume;
      break;
      case "revenue":
        values = revenue;
      break;
      case "revenue_per_capita":
        values = revenue_per_capita;
      break;
      case "share_revenues":
        values = share_revenues;
      break;
    }
    return values;
  }

  removeLayer() {
    const map = this.refs['map'].leafletElement;
    const geoJsonLayer = this.refs['geoJsonLayer'].leafletElement;
    map.removeLayer(geoJsonLayer);
  }

  addLegend(map, indicator_id, countryDataProcessed) {
      var info = L.control({position: 'bottomleft'});

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

          var indicatorData = ::this.getIndicatorData(indicator_id || this.state.indicator_id)
          var indicatorName = indicatorData["name"];
          var indicatorDescription = indicatorData["description"];
          var indicatorHeader = indicatorData["header"];
          var indicatorFooter = indicatorData["footer"];

          var unit = _.find(_.pluck(indicatorMetadata, 'unit'), function(v) {return v !== undefined});

          var h2El = document.createElement("H2");
          h2El.innerText = helpers.t(indicatorDescription) + " " + (unit ? "("+unit+ ")" : "");
          h2El.className = "responsive-header";

          var spanEl = document.createElement("SPAN");
          spanEl.innerText = helpers.t("show");
          h2El.appendChild(spanEl);

          var h2El_2 = document.createElement("H2");
          h2El_2.innerText = helpers.t(indicatorDescription) + " " + (unit ? "("+unit+ ")" : "");

          var spanEl_2 = document.createElement("SPAN");
          spanEl_2.innerText = helpers.t("hide");
          h2El_2.appendChild(spanEl_2);

          var divLegend = document.createElement("DIV");
          divLegend.className = "responsive-legend";


          var mergedHTML = "";
          var headerText = '<div class="legend_header" >' + helpers.t(indicatorHeader) + "</div>";
          mergedHTML += headerText;
          var noDataIncluded = false;
          indicatorMetadata.forEach(function(v) {
            noDataIncluded = (v.color === "#dddddd" && noDataIncluded === false) ? noDataIncluded = true : false;
            if(v.use_style) {
              mergedHTML += '<i class="' + v.title.toLowerCase().replace(/<[^>]*>/g, "").replace(/\/| /g,"_") + '"></i> <div class="legend_title">'+helpers.t(v.title)+ '<br/></div>';
            }
            else {
              mergedHTML += '<i style="background:' + v.color + '"></i> <div class="legend_title">'+helpers.t(v.title)+ '<br/></div>';
            }
            if(v.subtitle != "") {
              mergedHTML += (helpers.t(v.subtitle) || '') + '<br>';
            }
          });
          //if (noDataIncluded === false) mergedHTML += ('<i style="background:#dddddd"></i> <strong>'+helpers.t('No data')+ '</strong><br/><br/>' ) ;

          var footerText = '<div class="legend_footer" >' + helpers.t(indicatorFooter) + "</div>";
          mergedHTML += footerText;

          var sourceText = '<a class="legend_source" href="/data">' + helpers.t('Source: EITI summary data') + "</a>";

          var divLegendBody = document.createElement("DIV");
          divLegendBody.innerHTML = mergedHTML + sourceText;
          divLegend.appendChild(h2El_2);
          divLegend.appendChild(divLegendBody);

          while (map.options.legend.firstChild) {
              map.options.legend.removeChild(map.options.legend.firstChild);
          }

          map.options.legend.appendChild(h2El);
          map.options.legend.appendChild(divLegend);

          spanEl.onclick = function() {
            divLegend.style.display = 'block';
            h2El.style.display = 'none';
          };

          spanEl_2.onclick = function() {
            divLegend.style.display = 'none';
            h2El.style.display = 'block';
          };
      }.bind(this);

      info.addTo(map);
  }

  getIndicatorData(indicator_id){
    var current_indicator = _.find(indicator_list, function(v){ return (v.name == indicator_id)});
    return current_indicator;
  }

  onEachFeaturePage(feature, layer) {
    layer.on({
        mouseover: function(e){ helpers.showHint(e) },
        mouseout: helpers.resetTooltip,
        click: function(e){ helpers.showInfobox(e, this.state.data) }.bind(this)
    });
  }

  onEachFeatureStatus(feature, layer) {
      var data = this.state.data;
      layer.on({
          mouseover: function(e){ helpers.showTooltipStatus(e, data) },
          mouseout: helpers.resetTooltip,
          click: function(e){ helpers.zoomToFeature(e, data) }
      });
  }


  getColor(indicator_type, indicator_value, metadata) {
    if(indicator_type == 'fixed') {
        var completeType = _.find(metadata, function(v){ return (v.id == indicator_value)});

        return completeType ? completeType.color: '#dddddd';
    }
    else
    {
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
    //if(!this.state || !this.state.baseMap) return;
    const hoverDecider = this.props.infobox ? function(feature, layer){this.onEachFeaturePage(feature, layer)}.bind(this) : function(feature, layer){this.onEachFeatureStatus(feature, layer)}.bind(this);
    var geoJsonLayer;
    if(this.state.baseMap === undefined) {
      geoJsonLayer == null;
    }
    else {
      geoJsonLayer = <GeoJson data={this.state.baseMap} ref='geoJsonLayer' onEachFeature={hoverDecider} style={helpers.style}></GeoJson>;
    }
    var buttons;

    if(this.props.buttons) {
        buttons = (<div className="map-option-wrapper">
          <ul className="map-option-widget">
            <li data-indicatorid="status" data-valuetypes="fixed" onClick={::this.addLayer} className="active">
              {helpers.t('Overview')}
            </li>
            <li>
              {helpers.t('Tax & Legal Framework')}
              <ul className="map-option-items">
                <li data-indicatorid="online_oil_registry" data-valuetypes="fixed" onClick={::this.addLayer}>{helpers.t('Online oil registry')}</li>
                <li data-indicatorid="online_mining_registry" data-valuetypes="fixed" onClick={::this.addLayer}>{helpers.t('Online mining registry')}</li>
                <li data-indicatorid="online_contracts" data-valuetypes="fixed" onClick={::this.addLayer}>{helpers.t('Online registry of contracts')}</li>
              </ul>
            </li>
            <li>
              {helpers.t('Production')}
              <ul className="map-option-items">
                <li data-indicatorid="oil_volume" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Oil, volume')}</li>
                <li data-indicatorid="gas_volume" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Gas, volume')}</li>
                <li data-indicatorid="coal_volume" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Coal, tons')}</li>
                <li data-indicatorid="gold_volume" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Gold, tons')}</li>
                <li data-indicatorid="copper_volume" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Copper, tons')}</li>
              </ul>
            </li>
            <li>
              {helpers.t('Revenues')}
              <ul className="map-option-items">
                <li data-indicatorid="revenue" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Government extractives revenue')}</li>
                <li data-indicatorid="revenue_per_capita" data-valuetypes="range" onClick={::this.addLayer}>{helpers.t('Revenues per capita')}</li>
                <li data-indicatorid="share_revenues" data-valuetypes="percentage" onClick={::this.addLayer}>{helpers.t('Share of revenues')}</li>
              </ul>
            </li>
          </ul>
        </div>);
    }
/*    var reportLink = (<svg id="country-report-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 160 160">
          <rect x="4.8" y="4" className="st0" width="115" height="151.6"/>
          <rect x="4.8" y="4" className="st0" width="20.9" height="151.6"/>
          <rect x="44" y="30.1" className="st0" width="57.5" height="31.4"/>
          <line className="st0" x1="54.5" y1="40.6" x2="91.1" y2="40.6"/>
          <line className="st0" x1="54.5" y1="51" x2="91.1" y2="51"/>
          </svg>);*/


    var selector;
    if(this.props.selector) {
      var items = [];
      var cols = [];
      var countries = _.sortBy(this.state.data, 'label');
      var sortedCountries = countries.filter(function(k,v){ return (k.status.name !== "Other")})
      var cutout = Math.ceil(sortedCountries.length/4);
      for (var i = 0; i < sortedCountries.length;i++) {
        var itemStyle = sortedCountries[i].status ? "member-status " + sortedCountries[i].status.name.toLowerCase().replace(/\/| /g,"_") : "member-status other";
        if(sortedCountries[i].status.name === "Other") continue;
        var countryPageURL = "/implementing_country/" + sortedCountries[i].id;

        var years = Object.keys(sortedCountries[i].metadata);
        var last = _.last(years);
        var yearData = sortedCountries[i].metadata[last];
        // If there's an attached report to the implementing country, use that one. If not, look for it in the metadata
        var reportURL = sortedCountries[i].annual_report_file;
        var reportClass = "";
        if(reportURL === undefined || reportURL === null) {
          var reportObj = yearData && yearData.web_report_links && yearData.web_report_links.length > 0 ? _.first(yearData.web_report_links) : undefined;
          reportURL = reportObj ? reportObj.url : "";
          reportClass = reportObj ? "" : "empty";
        }
        var country_name = helpers.t(sortedCountries[i].label);

        items.push(
            <li>
              <span className={itemStyle}></span>
              <a href={countryPageURL}>{country_name}</a>
            </li>
          );
        if((i+1)%cutout === 0 || i+1 === sortedCountries.length) {
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
    var screenWidth = (window.innerWidth > 0) ? window.innerWidth : screen.width;
    var zoom = 2;

    if(screenWidth <= 400) {
      zoom = 1;
    }

    // If there's a selector, add the responsive classes.
    var containerClass = 'map-container';
    var elementClass;
    if(selector) {
      containerClass = 'map-container media-resizable-element';
      elementClass = 'resizable-map';
    }

    return (

      <div className={containerClass}>
        {buttons}
        <div>
          <Map className={elementClass}
            center={this.state.latlng}
            length={4}
            ref='map'
            zoom={zoom}
            maxZoom={8}
            minZoom={1}
            height={500}
            scrollWheelZoom={false}
            >
            <TileLayer
              url=''
              onLeafletLoad={function(e) {
                if(!this.state.initialized) {
                  this.addLegend(e.target._map, this.state.indicator_id);
                  this.setState({initialized:true});
                }
              }.bind(this)}
            />
            {geoJsonLayer}
          </Map>
        </div>
        {selector}
      </div>
    );
  }
}
