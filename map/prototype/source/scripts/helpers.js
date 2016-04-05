
import _ from 'underscore';

export var helpers = {
    getBasePath: function() {
        return window.Drupal && window.Drupal.settings && window.Drupal.settings.eitiMapWidgetsLibPath ? window.Drupal.settings.eitiMapWidgetsLibPath : 'dist';
    },

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

    showTooltipStatus: function (e, countryInfo) {
        var layer = e.target;

        var country = _.find(countryInfo, function(v){ return v.iso3 === layer.feature.id;});
        var country_link = '';


        if(country) {
            country_link = '<a href="/implementing_country/' +  country.id + '"><strong>' + layer.feature.properties.name + '</strong></a>';
        }
        else
        {
            country_link = '<strong>' + layer.feature.properties.name + '</strong>';
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

    // Helper function that can translate strings.
    t: function(string) {
        // Check if window.Drupal.t() exists and call it.
        if (window.Drupal && typeof window.Drupal.t === 'function') {
            return window.Drupal.t(string);
        }
        return string;
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
        else {
            country_link = '<a href="' + country_url + '"><strong>Open Country Page</strong></a>';
        }

        // General info
        var years = Object.keys(country.reports);
        var last = _.last(years);
        var yearData = country.reports[last];

        var indicator_GDP = yearData.find(function(v) {
                return (v.commodity === "Gross Domestic Product - all sectors" && v.unit === "USD")
            });
        var indicator_oil = yearData.find(function(v){ return (v.commodity === "Oil, volume")});
        var indicator_population = yearData.find(function(v){ return (v.commodity === "Population")});

        // Licenses
        var years_licenses = country.licenses ? Object.keys(country.licenses):[];
        var last_licenses = _.last(years_licenses);
        var indicator_licenses = country.licenses ? country.licenses[last_licenses] : undefined;

        // Contracts
        var years_contracts = country.contracts ? Object.keys(country.contracts):[];
        var last_contracts = _.last(years_contracts);
        var indicator_contracts = country.contracts ? country.contracts[last_contracts]: undefined;

        // Value & Value per capita
        var indicator_oil_value = yearData.find(function(v){ return (v.commodity === "Oil, value")});
        var indicator_oil_value_pc = 0;
        if (indicator_oil_value && indicator_population) {
            indicator_oil_value_pc = indicator_oil_value.value/indicator_population;
        }
        else {
            indicator_oil_value_pc = 0;
        }

        // Revenue by Government vs Extractives
        var years_revenue = Object.keys(country.revenues);
        var last_revenue = _.last(years_revenue);
        var yearData_revenue = country.revenues[last_revenue];
        var indicator_government = yearData_revenue.government;
        var indicator_company = yearData_revenue.company;

        var currency_code = 'USD';
        var info_header = '';
        var info_content = '';
        var info_top_indicators = '';

        // Add country info.
        info_header = info_header +
            '<img src="' + this.getResourceUrl('images/flags/gif/' + layer.feature.id.toLowerCase() + '.gif') + '" style=""/>' +
            '<span>' + layer.feature.properties.name + '</span>';

        // Add GDP indicator info.
        info_top_indicators = info_top_indicators +
            '<span class="info">' +
            '  <span class="label">' + this.t('GDP') + ':</span> <span class="value">' + this.formatNumber(indicator_GDP ? indicator_GDP.value : 0 ) +  ' ' + currency_code + '</span>' +
            '</span>';

        // Add Population indicator info.
        info_top_indicators = info_top_indicators +
            '<span class="info">' +
            '  <span class="label">' + this.t('Population') + ':</span> <span class="value">' + this.formatNumber(indicator_population ? indicator_population.value : 0) + '</span>' +
            '</span>';

        // Add info about Oil.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + this.formatNumber(indicator_oil.value) + '</span>' +
            '  <span class="unit">(' + indicator_oil.unit + ')</span>' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" />' +
            '  <span class="label">' + this.t('Oil') + '</span>' +
            '</div>';

        // Add info about GAS.
        // TODO: use values from the indicator.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + 'N/A' + '</span>' +
            // '  <span class="unit">(' + 'N/A' + ')</span>' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilunrefined.svg') + '" alt="Gas Icon" />' +
            '  <span class="label">' + this.t('Gas') + '</span>' +
            '</div>';

        // Add info about Online Licenses.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="label">' + this.t('Online Licenses') + ':</span>' +
            '  <span class="value">' + (indicator_licenses ? '<a href="' +indicator_licenses[0]+ '" target="_blank">' + this.t('Yes') + '</a>' : this.t('No')) + '</span>' +
            '</div>';

        // Add info about Online Contracts.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="label">' + this.t('Online Contracts') + ':</span>' +
            '  <span class="value">' + (indicator_contracts ? '<a href="' +indicator_contracts[0]+ '" target="_blank">' + this.t('Yes') + '</a>' : this.t('No')) + '</span>' +
            '</div>';

        // Add info about Oil.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + this.formatNumber(indicator_oil_value ? indicator_oil_value.value : 0) + (indicator_oil_value ? ' (' + indicator_oil_value.unit +')' : '') + '</span>' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" />' +
            '  <span class="label">' + this.t('Oil, Value') + '</span>' +
            '</div>';

        // Add info about Oil per capita.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + this.formatNumber(indicator_oil_value_pc) + (indicator_oil_value ? ' (' + indicator_oil_value.unit +')' : '') + '</span>' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" />' +
            '  <span class="label">' + this.t('Oil, Value (Per Capita)') + '</span>' +
            '</div>';

        // Add info about Revenue by Government.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + this.formatNumber(indicator_government ? indicator_government : 0) + '</span>( ' + currency_code + ')' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" />' +
            '  <span class="label">' + this.t('Revenue by Government') + '</span>' +
            '</div>';

        // Add info about Revenue by Companies.
        info_content = info_content +
            '<div class="info-block">' +
            '  <span class="value">' + this.formatNumber(indicator_company ? indicator_company : 0) + '</span>( ' + currency_code + ')' +
            '  <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" />' +
            '  <span class="label">' + this.t('Revenue by Companies') + '</span>' +
            '</div>';

        // Add online contracts.
        var html = '<aside class="country-info-wrapper">' +
            '<div class="country-info-header">' + info_header + '</div>' +
            '<div class="country-info-top-indicators">' + info_top_indicators + '</div>' +
            '<h3 class="title">' + this.t('Country Commodity Total') + '</h3>' +
            '<div class="country-info-content">' + info_content + '</div>' +
            '<div class="country-link">' + '<img class="country-icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_opencountry.svg') + '" /> ' + country_link + '</div>' +
            '</aside>';

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
    },

    getResourceUrl: function(relative_path) {
        return this.getBasePath() + '/' + relative_path;
    }
};
