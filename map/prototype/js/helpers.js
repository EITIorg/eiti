
import _ from 'underscore';

export var helpers = {

    getPaletteDivergent: function(index) {
        var colors = ['#42abd8', '#65c32d', '#ff6600', '#dddddd'];
        return colors[index];

    },
    getPaletteBreaks: function(index) {
        var colors = ['#f1eef6','#bdc9e1','#74a9cf','#2b8cbe','#045a8d'];
        return colors[index];
    },

    style:  function (feature) {
        return {
                weight: 1,
                opacity: 1,
                color: '#ccc',
                fillOpacity: 1,
                fillColor: helpers.getColor(feature)
            };
    },

    getColor: function(feature) {
        if(feature !== undefined) {
            //console.log(feature.indicator_value);
            if(feature.indicator_color) {
                return feature.indicator_color;
            }
            else
            {
                return '#dddddd';
            }
        }
        else
        {
            return '#dddddd';
        }
    },

    isNumeric: function( obj ) {
        return !jQuery.isArray( obj ) && (obj - parseFloat( obj ) + 1) >= 0;
    },

    showTooltipStatus: function (e) {
        var country_link = '';
        var layer = e.target;
        var country_status = layer.feature.indicator_value;
        var country_url = (country_status < 4 && linkMap[layer.feature.id]) ? '/implementing_country/' + linkMap[layer.feature.id] + '':'';
        if(country_url === '') {
            country_link = '<strong>' + layer.feature.properties.name + '</strong>';
        }
        else
        {
            country_link = '<a href="' + country_url + '"><strong>' + layer.feature.properties.name + '</strong></a>';
        }
        var popup = L.popup({autoPan:false, closeButton:false})
            .setLatLng(e.latlng)
            .setContent(country_link)
            .openOn(layer._map);
    },

    resetTooltip: function(e) {
    // Left for future reference
    },

    zoomToFeature: function(e){
        window.location = 'country_' + layer.feature.id + '.html';
    },

    onEachFeatureStatus: function (feature, layer) {
        layer.on({
            mouseover: helpers.showTooltipStatus,
            mouseout: helpers.resetTooltip,
            click: helpers.zoomToFeature
        });
    },

    showInfobox: function(e, countryInfo) {

        helpers.resetTooltip();

        var layer = e.target;
        var country = _.find(countryInfo, function(v){ return v.iso3 === layer.feature.id;});
        var country_link = '';
    
        var country_url = '/implementing_country/' +  country.id;
        
        if(country_url === '') {
            country_link = '<strong> Country Page not available </strong>';
        }
        else
        {
            country_link = '<a href="' + country_url + '"><strong>Open Country Page</strong></a>';
        }
        //debugger;
        var flagStyle = country.iso2.toLowerCase()

        // General info
        var years = Object.keys(country.reports);
        var last = _.last(years);
        var yearData = country.reports[last];

        var indicator_GDP = yearData.find(
            function(v){ 
                return (v.commodity === "Gross Domestic Product - all sectors" && v.unit === "USD")});
        var indicator_oil = yearData.find(function(v){ return (v.commodity === "Oil, volume")});
        var indicator_population = yearData.find(function(v){ return (v.commodity === "Population")});

        // Licenses
        var years_licenses = country.licenses ? Object.keys(country.licenses):[];
        var last_licenses = _.last(years_licenses);
        var indicator_licenses = country.licenses ? country.licenses[last_licenses] : undefined;

        //Contracts
        var years_contracts = country.contracts ? Object.keys(country.contracts):[];
        var last_contracts = _.last(years_contracts);
        var indicator_contracts = country.contracts ? country.contracts[last_contracts]: undefined;

        // Value & Value per capita
        var indicator_oil_value = yearData.find(function(v){ return (v.commodity === "Oil, value")});
        var indicator_oil_value_pc = 0;
        if(indicator_oil_value && indicator_population) {
            indicator_oil_value_pc = indicator_oil_value.value/indicator_population;
        }
        else
        {
            indicator_oil_value_pc = 0;
        }

        // Revenue by Government vs Extractives
        var years_revenue = Object.keys(country.revenues);
        var last_revenue = _.last(years_revenue);
        var yearData_revenue = country.revenues[last_revenue];
        var indicator_government = yearData_revenue.government;
        var indicator_company = yearData_revenue.company;
        var indicator_gov_vs_com = indicator_government - indicator_company;

        var html = '<div>' +
            '<table class="country_info">' + 
            '  <thead><tr style="background-color:#f4f4f4"><th colspan="2"><img src="http://demo.eiti.org/images/flags/gif/' + layer.feature.id.toLowerCase() + '.gif" style="height:20px;margin:0px 10px 0px 5px"/>' + layer.feature.properties.name + '</th></tr></thead>' + 
            '  <tbody>' + '    <tr><td>GDP: ' + this.formatNumber(indicator_GDP ? indicator_GDP.value : 0 ) + ' USD </td><td>Population: ' + this.formatNumber(indicator_population ? indicator_population.value : 0) + '</td></tr>' + 
            '    <tr><td colspan="2">&nbsp;<strong>Country Commodity Total</strong></td></tr>' + 
            '    <tr>' + 
            '       <td><strong>' + this.formatNumber(indicator_oil.value) + ' (' + indicator_oil.unit +')</strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> <strong>Oil</strong> </td>' + 
            '       <td><strong>N/A</strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilunrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Gas </td>' + 
            '    </tr>' + 
            '    <tr>' + 
            '       <td><strong>Online Licenses: ' + (indicator_licenses ? '<a href="' +indicator_licenses[0]+ '" target="_blank"> Yes </a>' : 'No') + '</strong></td>' + 
            '       <td><strong>Online Contracts: ' + (indicator_contracts ? '<a href="' +indicator_contracts[0]+ '" target="_blank"> Yes </a>' : 'No') + '</strong></td>' + 
            '    </tr>' + 
            '    <tr>' + 
            '       <td><strong>' + this.formatNumber(indicator_oil_value ? indicator_oil_value.value : 0) + (indicator_oil_value ? ' (' + indicator_oil_value.unit +')' : '') + '</strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Oil, Value </td>' + 
            '       <td><strong>' + this.formatNumber(indicator_oil_value_pc) + (indicator_oil_value ? ' (' + indicator_oil_value.unit +')' : '')  +'</strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Oil, Value (Per Capita)</td>' + 
            '    </tr>' + 
            '    <tr>' + 
            '       <td><strong>' + this.formatNumber(indicator_government ? indicator_government : 0) + ' (USD) </strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilunrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Revenue by Government </td>' + 
            '       <td><strong>' + this.formatNumber(indicator_company ? indicator_company : 0) +' (USD) </strong><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_oilunrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Revenue by Companies</td>' + 
            '    </tr>' + 
            '    <tr><td colspan="2"><img src="http://demo.eiti.org/images/icon-dump/eiti_popup_opencountry.svg" style="margin:0px 2px 0px 2px;width:18px"/>' + country_link + '</td></tr>' + 
            '  </tbody>' + 
            '</table>' + 
            '</div>';

        var popup = L.popup({autoPan:true, closeButton:false, maxWidth:400})
            .setLatLng(e.latlng)
            .setContent(html)
            .openOn(layer._map);
    },
    formatNumber: function(number) {
        number = Number(number);
        if(isNaN(number)) return 0;
        let n = 0;
        let x = 3;
        var re = '\\d(?=(\\d{' + (x || 3) + '})+' + (n > 0 ? '\\.' : '$') + ')';
        return number.toFixed(Math.max(0, ~~n)).replace(new RegExp(re, 'g'), '$&,');
    }

};

